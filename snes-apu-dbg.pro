QT += core gui widgets

rust.depends = FORCE
rust.target = domain-model/snes-apu-c/target/release/libsnes_apu_c.a
rust.commands = cd domain-model/snes-apu-c && cargo build --release

PRE_TARGETDEPS += domain-model/snes-apu-c/target/release/libsnes_apu_c.a
QMAKE_EXTRA_TARGETS += rust

TEMPLATE = app
TARGET = snes-apu-dbg

DESTDIR = target
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

CONFIG += c++11
LIBS += -Ldomain-model/snes-apu-c/target/release -lsnes_apu_c -framework AudioUnit

FORMS += MainWindow.ui \
    RamViewer.ui \
    VoiceViewer.ui \
    VoiceOutputViewer.ui \
    OutputViewer.ui
SOURCES += main.cpp \
    domain-model/SnesApu.cpp \
    MainWindow.cpp \
    RamViewer.cpp \
    VoiceViewer.cpp \
    VoiceOutputViewer.cpp \
    OutputViewer.cpp
HEADERS += domain-model/snes_apu_c.h \
    domain-model/SnesApu.h \
    MainWindow.h \
    RamViewer.h \
    VoiceViewer.h \
    VoiceOutputViewer.h \
    OutputViewer.h
RESOURCES += \
    resources/application.qrc
