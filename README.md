# snes-apu-dbg
A Qt-based graphical debugger for my [snes-apu](https://github.com/emu-rs/snes-apu) project.

![screen shot 2015-10-25 at 4 14 46 pm 2](https://cloud.githubusercontent.com/assets/3166056/10718610/bf77b716-7b34-11e5-8765-01a2ff6f4d49.png)

## Description
This is a simple debugging tool that was used to help find emulation bugs in the [snes-apu](https://github.com/emu-rs/snes-apu) project. It was also used as a proof-of-concept test for building UI's for [Rust](https://www.rust-lang.org) projects using [Qt](http://www.qt.io).

_Note: Due to current limitations in [the emu project](https://github.com/emu-rs/emu) on which this depends, this will only build on OS X. Other platforms will be supported promptly._

## Features
- RAM viewer
  - Blue channel indicates the byte value
  - Red channel indicates how recently the byte was changed between snapshots
- Individual stereo voice output viewers
- Voice mutes/solos
- Gaussian and linear resampling modes
- Final stereo output viewer

## How it works
A rendering thread continuously renders audio by simulating a SNES audio unit. Every ~20ms, the simulation is frozen and parts of its state are extracted, and this state is reflected by the UI.

## Building
This project was developed using Qt 5.5.1 and Rust 1.3.0 stable. Newer versions should work just fine.

As usual with Qt projects, building is simple:

`qmake && make`

The resulting build will be in the `target` directory.

## Opening songs
A song (.spc file) can be opened using the `File` menu, or passed as an argument on the command line.

## Architecture
The heart of the project is a Rust project ([snes-apu-c](https://github.com/yupferris/snes-apu-dbg/tree/master/domain-model/snes-apu-c)), which exposes a C API to create a `Context` object, which represents a running SNES audio unit and the current song that's playing (if applicable). The API also exposes the ability to make simple state changes through a `Context`, such as loading a song, enabling/disabling voice mutes/solos, and the ability to query the state of the APU by producing a `Snapshot` object. All of these state changes are managed by a `Mutex` on the Rust side and are guaranteed to be thread-safe.

`Snapshot`'s are immutable data structures owned by Rust `Arc`'s, which means they're atomically reference-counted. By `clone`'ing and `free`'ing through the [C API](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/snes_apu_c.h), we can have any number of owners accross any number of threads, and they're guaranteed to be memory- and thread-safe. This is important because the emulator runs on the audio rendering thread, is queried by a timer thread, and the resulting `Snapshot`'s needs to be stored locally by some of the controls to be used later by the UI rendering thread.

To even better expose this API to the Qt UI, `Context`'s are wrapped in a C++ `SnesApu` class, and `Snapshot`'s are wrapped by a `Snapshot` class (see [SnesApu.cpp](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/SnesApu.cpp) and [SnesApu.h](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/SnesApu.h)). By taking advantage of RAII, we can ensure that management of `Snapshot`'s is automatically handled as long as we pass `Snapshot`'s around by value. All this requires is a properly-implemented copy constructor and assignment operator, which are trivial in this case.

While this code itself isn't the cleanest in the world (in particular the somewhat-mammoth [lib.rs](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/snes-apu-c/src/lib.rs) in [snes-apu-c](https://github.com/yupferris/snes-apu-dbg/tree/master/domain-model/snes-apu-c)), this pattern of exposing a mutable `Context` and immutable `Snapshot`'s from Rust to C++ seems to be a pretty nice pattern for doing Qt UI's, and is one I'll certainly repeat in the future. It's something I've had in my head for awhile, and I'm quite pleased with how nice it was to implement.

## License
This code is licensed under the BSD2 license (see LICENSE).
