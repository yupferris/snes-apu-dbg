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

Snapshot SnesApu::GetSnapshot()
{
    return Snapshot(context);
}
