#ifndef __SNES_APU_H__
#define __SNES_APU_H__

#include "snes_apu_c.h"

class RamSnapshot
{
public:
    RamSnapshot(SnesApuContext *);
    ~RamSnapshot();

    const unsigned char *GetData() const;

private:
    const unsigned char *snapshot;
};

class SnesApu
{
public:
    SnesApu();
    ~SnesApu();

    void SetSong(const char*);

    RamSnapshot GetRamSnapshot();

private:
    SnesApuContext *context;
};

#endif
