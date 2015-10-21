extern crate libc;

extern crate emu;
extern crate spc;
extern crate snes_apu;

use std::sync::{Arc, Mutex};

use std::ffi::CStr;
use libc::{c_void, c_char};

use emu::audio_driver::AudioDriver;
use emu::core_audio_driver::CoreAudioDriver;

use spc::spc::{Spc, RAM_LEN};
use snes_apu::apu::Apu;
use snes_apu::dsp::dsp::{SAMPLE_RATE, BUFFER_LEN};
use snes_apu::dsp::voice::VOICE_BUFFER_LEN;

struct ContextState {
    apu: Box<Apu>,
    spc: Option<Spc>
}

struct Context {
    state: Arc<Mutex<ContextState>>,
    _driver: CoreAudioDriver
}

impl Context {
    fn new() -> Context {
        let state = Arc::new(Mutex::new(ContextState {
            apu: Apu::new(),
            spc: None
        }));

        let mut driver = CoreAudioDriver::new();
        driver.set_sample_rate(SAMPLE_RATE as i32);
        let render_callback_state = state.clone();
        let mut left = [0; BUFFER_LEN];
        let mut right = [0; BUFFER_LEN];
        driver.set_render_callback(Some(Box::new(move |buffer, num_frames| {
            render_callback_state.lock().unwrap().apu.render(&mut left, &mut right, num_frames as i32);
            for i in 0..num_frames {
                let j = i * 2;
                buffer[j + 0] = left[i] as f32 / 32768.0;
                buffer[j + 1] = right[i] as f32 / 32768.0;
            }
        })));

        Context {
            state: state,
            _driver: driver
        }
    }

    fn set_song(&mut self, spc: Option<Spc>) {
        let state = &mut self.state.lock().unwrap();
        state.apu.reset();
        if let Some(ref spc) = spc {
            state.apu.set_state(&spc);
            state.apu.clear_echo_buffer();
        }
        state.spc = spc;
    }

    fn set_voice_is_muted(&mut self, voice_index: i32, value: bool) {
        let state = &mut self.state.lock().unwrap();
        state.apu.dsp.as_mut().unwrap().voices[voice_index as usize].is_muted = value;
    }

    fn get_snapshot(&mut self) -> Snapshot {
        let state = &mut self.state.lock().unwrap();
        Snapshot::new(&mut state.apu)
    }
}

struct Snapshot {
    ram: Box<[u8; RAM_LEN]>,
    voices: Vec<VoiceSnapshot>
}

impl Snapshot {
    fn new(apu: &mut Apu) -> Snapshot {
        let mut ram = Box::new([0; RAM_LEN]);
        for i in 0..RAM_LEN {
            ram[i] = apu.read_u8(i as u32);
        }
        let mut ret = Snapshot {
            ram: ram,
            voices: Vec::with_capacity(8)
        };
        for i in 0..8 {
            let voice = &mut apu.dsp.as_mut().unwrap().voices[i as usize];
            let mut voice_snapshot = VoiceSnapshot {
                is_muted: voice.is_muted,

                raw_output_buffer: Box::new([0; VOICE_BUFFER_LEN]),
                left_output_buffer: Box::new([0; VOICE_BUFFER_LEN]),
                right_output_buffer: Box::new([0; VOICE_BUFFER_LEN]),
            };
            for i in 0..VOICE_BUFFER_LEN {
                let index = ((voice.output_buffer.pos as usize) + i) % VOICE_BUFFER_LEN;
                let output = voice.output_buffer.buffer[index];
                voice_snapshot.raw_output_buffer[index] = output.last_voice_out;
                voice_snapshot.left_output_buffer[index] = output.left_out;
                voice_snapshot.right_output_buffer[index] = output.right_out;
            }
            ret.voices.push(voice_snapshot);
        }
        ret
    }
}

struct VoiceSnapshot {
    is_muted: bool,

    raw_output_buffer: Box<[i32; VOICE_BUFFER_LEN]>,
    left_output_buffer: Box<[i32; VOICE_BUFFER_LEN]>,
    right_output_buffer: Box<[i32; VOICE_BUFFER_LEN]>
}

#[no_mangle]
pub extern fn create_context() -> *mut c_void {
    Box::into_raw(Box::new(Context::new())) as *mut c_void
}

#[no_mangle]
pub unsafe extern fn free_context(context: *mut c_void) {
    Box::from_raw(context as *mut Context);
}

#[no_mangle]
pub extern fn set_song(context: *mut c_void, filename: *const c_char) {
    let context = unsafe { &mut *(context as *mut Context) };
    let spc = if filename.is_null() {
        None
    } else {
        let filename = unsafe { CStr::from_ptr(filename) }.to_str().unwrap();
        Some(Spc::load(filename).unwrap())
    };
    context.set_song(spc);
}

#[no_mangle]
pub extern fn set_voice_is_muted(context: *mut c_void, voice_index: i32, value: i32) {
    let context = unsafe { &mut *(context as *mut Context) };
    context.set_voice_is_muted(voice_index, value != 0);
}

#[no_mangle]
pub extern fn get_snapshot(context: *mut c_void) -> *mut c_void {
    let context = unsafe { &mut *(context as *mut Context) };
    let snapshot = Box::new(Arc::new(context.get_snapshot()));
    Box::into_raw(snapshot) as *mut c_void
}

#[no_mangle]
pub extern fn clone_snapshot(snapshot: *mut c_void) -> *mut c_void {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    let clone = Box::new(snapshot.clone());
    Box::into_raw(clone) as *mut c_void
}

#[no_mangle]
pub unsafe extern fn free_snapshot(snapshot: *mut c_void) {
    Box::from_raw(snapshot as *mut Arc<Snapshot>);
}

#[no_mangle]
pub extern fn get_snapshot_ram(snapshot: *mut c_void) -> *const u8 {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    &snapshot.ram[0] as *const _
}

#[no_mangle]
pub extern fn get_snapshot_voice_is_muted(snapshot: *mut c_void, voice_index: i32) -> i32 {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    if snapshot.voices[voice_index as usize].is_muted { 1 } else { 0 }
}

#[no_mangle]
pub extern fn get_snapshot_voice_raw_output_buffer(snapshot: *mut c_void, voice_index: i32) -> *const i32 {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    &snapshot.voices[voice_index as usize].raw_output_buffer[0] as *const _
}

#[no_mangle]
pub extern fn get_snapshot_voice_left_output_buffer(snapshot: *mut c_void, voice_index: i32) -> *const i32 {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    &snapshot.voices[voice_index as usize].left_output_buffer[0] as *const _
}

#[no_mangle]
pub extern fn get_snapshot_voice_right_output_buffer(snapshot: *mut c_void, voice_index: i32) -> *const i32 {
    let snapshot = unsafe { &mut *(snapshot as *mut Arc<Snapshot>) };
    &snapshot.voices[voice_index as usize].right_output_buffer[0] as *const _
}
