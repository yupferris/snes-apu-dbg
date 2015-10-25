#ifndef __SNES_APU_C_H__
#define __SNES_APU_C_H__

#include <inttypes.h>

typedef void snes_apu_buffer_t;
typedef void snes_apu_context_t;
typedef void snes_apu_snapshot_t;

extern "C"
{
    const uint8_t *get_buffer_bytes(snes_apu_buffer_t *);
    int32_t get_buffer_len(snes_apu_buffer_t *);
    void free_buffer(snes_apu_buffer_t *);

    snes_apu_context_t *create_context();
    void free_context(snes_apu_context_t *);

    void reset(snes_apu_context_t *);
    void stop(snes_apu_context_t *);
    void set_song(snes_apu_context_t *, const uint8_t *, int32_t);
    void set_resampling_mode_gaussian(snes_apu_context_t *);
    void set_resampling_mode_linear(snes_apu_context_t *);
    void set_voice_is_muted(snes_apu_context_t *, int32_t, int32_t);
    void set_voice_is_solod(snes_apu_context_t *, int32_t, int32_t);
    void mute_all(snes_apu_context_t *);
    void clear_mutes(snes_apu_context_t *);
    void clear_solos(snes_apu_context_t *);

    snes_apu_snapshot_t *get_snapshot(snes_apu_context_t *);
    snes_apu_snapshot_t *clone_snapshot(snes_apu_snapshot_t *);
    void free_snapshot(snes_apu_snapshot_t *);

    snes_apu_buffer_t *get_snapshot_song_name(snes_apu_snapshot_t *);
    const int16_t *get_snapshot_left_output_buffer(snes_apu_snapshot_t *);
    const int16_t *get_snapshot_right_output_buffer(snes_apu_snapshot_t *);
    const unsigned char *get_snapshot_ram(snes_apu_snapshot_t *);
    int32_t get_snapshot_resampling_mode_is_gaussian(snes_apu_snapshot_t *);
    int32_t get_snapshot_resampling_mode_is_linear(snes_apu_snapshot_t *);
    int32_t get_snapshot_voice_is_muted(snes_apu_snapshot_t *, int32_t);
    int32_t get_snapshot_voice_is_solod(snes_apu_snapshot_t *, int32_t);
    const int32_t *get_snapshot_voice_raw_output_buffer(snes_apu_snapshot_t *, int32_t);
    const int32_t *get_snapshot_voice_left_output_buffer(snes_apu_snapshot_t *, int32_t);
    const int32_t *get_snapshot_voice_right_output_buffer(snes_apu_snapshot_t *, int32_t);
}

#endif
