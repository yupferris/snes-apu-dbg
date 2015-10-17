#ifndef __SNES_APU_C_H__
#define __SNES_APU_C_H__

typedef void SnesApuContext;

extern "C"
{
    SnesApuContext *create_context();
    void free_context(SnesApuContext *);
}

#endif
