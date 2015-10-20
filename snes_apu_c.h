#ifndef __SNES_APU_C_H__
#define __SNES_APU_C_H__

typedef void snes_apu_context_t;
typedef void snes_apu_snapshot_t;
typedef void snes_apu_voice_snapshot_t;

extern "C"
{
    snes_apu_context_t *create_context();
    void free_context(snes_apu_context_t *);

    void set_song(snes_apu_context_t *, const char *);
    void set_voice_is_muted(snes_apu_context_t *, int, int);
    int get_voice_is_muted(snes_apu_context_t *, int);

    snes_apu_snapshot_t *get_snapshot(snes_apu_context_t *);
    void free_snapshot(snes_apu_snapshot_t *);

    const unsigned char *get_snapshot_ram(snes_apu_snapshot_t *);
}

#endif
