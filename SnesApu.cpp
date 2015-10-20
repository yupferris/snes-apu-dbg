#include "SnesApu.h"

Snapshot::Snapshot(snes_apu_context_t *context)
{
    snapshot = get_snapshot(context);
}

Snapshot::~Snapshot()
{
    free_snapshot(snapshot);
}

const unsigned char *Snapshot::GetRam() const
{
    return get_snapshot_ram(snapshot);
}

SnesApu::SnesApu()
{
    context = create_context();
}

SnesApu::~SnesApu()
{
    free_context(context);
}

void SnesApu::SetSong(const char *filename)
{
    set_song(context, filename);
}

void SnesApu::SetVoiceIsMuted(int voiceIndex, bool value)
{
    set_voice_is_muted(context, voiceIndex, value ? 1 : 0);
}

bool SnesApu::GetVoiceIsMuted(int voiceIndex)
{
    return get_voice_is_muted(context, voiceIndex) != 0;
}

Snapshot SnesApu::GetSnapshot()
{
    return Snapshot(context);
}
