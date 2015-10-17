#include "SnesApu.h"

RamSnapshot::RamSnapshot(SnesApuContext *context)
{
    snapshot = get_ram_snapshot(context);
}

RamSnapshot::~RamSnapshot()
{
    free_ram_snapshot(snapshot);
}

const unsigned char *RamSnapshot::GetData() const
{
    return snapshot;
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

RamSnapshot SnesApu::GetRamSnapshot()
{
    return RamSnapshot(context);
}
