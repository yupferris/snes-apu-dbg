QT += core gui widgets

rust.depends = FORCE
rust.target = snes-apu-c/target/release/libsnes_apu_c.a
rust.commands = cd snes-apu-c && cargo build --release

PRE_TARGETDEPS += snes-apu-c/target/release/libsnes_apu_c.a
QMAKE_EXTRA_TARGETS += rust

TEMPLATE = app
TARGET = snes-apu-dbg

DESTDIR = target
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

CONFIG += c++11
LIBS += -Lsnes-apu-c/target/release -lsnes_apu_c -framework AudioUnit

FORMS += MainWindow.ui \
    RamViewer.ui
SOURCES += main.cpp \
    SnesApu.cpp \
    MainWindow.cpp \
    RamViewer.cpp
HEADERS += snes_apu_c.h \
    SnesApu.h \
    MainWindow.h \
    RamViewer.h
