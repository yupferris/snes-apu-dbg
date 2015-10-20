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

    fn get_ram_snapshot(&mut self) -> Box<[u8; RAM_LEN]> {
        let state = &mut self.state.lock().unwrap();
        let mut ret = Box::new([0; RAM_LEN]);
        for i in 0..RAM_LEN {
            ret[i] = state.apu.read_u8(i as u32);
        }
        ret
    }
}

#[no_mangle]
pub extern fn create_context() -> *mut c_void {
    Box::into_raw(Box::new(Context::new())) as *mut c_void
}

#[no_mangle]
pub extern fn free_context(context: *mut c_void) {
    unsafe { Box::from_raw(context as *mut Context) };
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
pub extern fn get_ram_snapshot(context: *mut c_void) -> *mut u8 {
    let context = unsafe { &mut *(context as *mut Context) };
    let snapshot = context.get_ram_snapshot();
    Box::into_raw(snapshot) as *mut u8
}

#[no_mangle]
pub extern fn free_ram_snapshot(snapshot: *mut c_void) {
    unsafe { Box::from_raw(snapshot as *mut [u8; RAM_LEN]) };
}
