extern crate libc;

extern crate emu;
extern crate spc;
extern crate snes_apu;

use libc::c_void;
use std::mem::transmute;

use emu::audio_driver::AudioDriver;
use emu::core_audio_driver::CoreAudioDriver;

use spc::spc::Spc;
use snes_apu::apu::{Apu, BUFFER_LEN};

struct Context {
    _driver: CoreAudioDriver
}

impl Context {
    pub fn new() -> Context {
        let spc = Spc::load("/Users/yupferris/dev/projects/spc/ct/102 Chrono Trigger.spc").unwrap();
        let mut apu = Apu::new();
        apu.set_state(&spc);

        let mut driver = CoreAudioDriver::new();
        driver.set_sample_rate(32000);
        let mut left = [0; BUFFER_LEN];
        let mut right = [0; BUFFER_LEN];
        driver.set_render_callback(Some(Box::new(move |buffer, num_frames| {
            apu.render(&mut left, &mut right, num_frames as i32);
            for i in 0..num_frames {
                let j = i * 2;
                buffer[j + 0] = left[i] as f32 / 32768.0;
                buffer[j + 1] = right[i] as f32 / 32768.0;
            }
        })));

        Context {
            _driver: driver
        }
    }
}

#[no_mangle]
pub extern fn create_context() -> *mut c_void {
    unsafe { transmute(Box::new(Context::new())) }
}

#[no_mangle]
pub extern fn free_context(context: *mut c_void) {
    let _: Box<Context> = unsafe { transmute(context) };
}
