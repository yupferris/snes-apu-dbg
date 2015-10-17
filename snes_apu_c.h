#ifndef __SNES_APU_C_H__
#define __SNES_APU_C_H__

typedef void SnesApuContext;

extern "C"
{
    SnesApuContext *create_context();
    void free_context(SnesApuContext *);

    void set_song(SnesApuContext *, const char *);

    const unsigned char *get_ram_snapshot(SnesApuContext *);
    void free_ram_snapshot(const unsigned char *);
}

#endif
