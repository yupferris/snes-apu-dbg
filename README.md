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
The main idea here is to treat the domain model (in this case, the running SNES audio unit and the current song that's playing, if any) as a black box. From this, we can extract immutable snapshots of the data, which can be used for updating the UI (or for other things like persistence). Changes to the domain model are done by requesting changes through function calls (load new song, mute voice, etc). After a change request call (which is assumed to be synchronous), we can grab a new immutable snapshot of the data if desired. The old snapshot remains unchanged and is still valid, though it may be outdated.

While in this case the snapshots are extracted by polling, the general idea could be extended with an event that fires when a change occurs, eliminating that need. Polling is appropriate in this case, though, because we're running a real-time simulation that changes constantly. In this way, polling is equivalent to having change events that fire all the time, and throttling them.

All of the interactions with the domain model should be inherently thread-safe, without ever touching any threading code on the outside of the black box.

All of this serves to greatly simplify the way that data and changes flow between the data model and the UI, keeping the UI layer as simple and thin as possible. Since most of the domain models I want to make for applications I have in mind are based on a similar "black box" structure I described anyways, coming up with a good pattern for working with these in Qt makes a lot of sense.

The heart of the implementation is a Rust project ([snes-apu-c](https://github.com/yupferris/snes-apu-dbg/tree/master/domain-model/snes-apu-c)), which exposes a C API to create a `Context` object. A `Context` is the aforementioned "black box", and represents a running SNES audio unit and the current song that's playing (if applicable). The API exposes the ability to make simple state changes through a `Context`, such as loading a song, enabling/disabling voice mutes/solos, and the ability to query the state of the APU by producing a `Snapshot` object. All of these state changes are managed by a `Mutex` on the Rust side and are guaranteed to be thread-safe.

`Snapshot`'s are handles to immutable data structures owned by Rust `Arc`'s, which means they're atomically reference-counted. Because they're immutable, they can never have cyclic references. By `clone`'ing and `free`'ing through the [C API](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/snes_apu_c.h), we can have any number of owners accross any number of threads, and they're guaranteed to be memory- and thread-safe. This is important in this case because the emulator runs on the audio rendering thread, is queried by a timer thread, and the resulting `Snapshot`'s need to be stored locally by some of the controls to be used later by the UI rendering thread.

To even better expose this C API to the Qt C++ UI, `Context`'s are wrapped in a `SnesApu` class, and `Snapshot`'s are wrapped by a `Snapshot` class (see [SnesApu.cpp](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/SnesApu.cpp) and [SnesApu.h](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/SnesApu.h)). By taking advantage of RAII, we can ensure that management of `Snapshot`'s is automatically handled as long as we pass `Snapshot`'s around by value. All this requires is a properly-implemented copy constructor and assignment operator, which are trivial in this case.

While this code itself isn't the cleanest in the world (in particular sub-par naming and the somewhat-mammoth [lib.rs](https://github.com/yupferris/snes-apu-dbg/blob/master/domain-model/snes-apu-c/src/lib.rs) in [snes-apu-c](https://github.com/yupferris/snes-apu-dbg/tree/master/domain-model/snes-apu-c)), this pattern of exposing a mutable `Context` and immutable `Snapshot`'s from Rust to C++ seems to be a pretty nice pattern for doing Qt UI's, and is one I'll certainly repeat in the future. It's something I've had in my head for awhile, and I'm quite pleased with how nice it was to implement.

## License
This code is licensed under the BSD2 license (see LICENSE).
