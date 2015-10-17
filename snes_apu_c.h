#ifndef __SNES_APU_C_H__
#define __SNES_APU_C_H__

typedef void SnesApuContext;

extern "C"
{
    unsigned long add(unsigned long, unsigned long);

    SnesApuContext *create_context();
    void free_context(SnesApuContext *);
}

#endif
