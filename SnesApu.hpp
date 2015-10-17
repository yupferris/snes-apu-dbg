#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include "snes_apu_c.h"

class SnesApu
{
public:
    SnesApu();
    ~SnesApu();

    void SetSong(const char*);

private:
    SnesApuContext *context;
};

#endif
