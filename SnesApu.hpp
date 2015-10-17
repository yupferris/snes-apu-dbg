#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include "snes_apu_c.h"

class SnesApu
{
public:
    SnesApu();
    ~SnesApu();

private:
    SnesApuContext *context;
};

#endif
