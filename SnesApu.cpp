#include "SnesApu.h"

#include <iostream>
using namespace std;

Snapshot::Snapshot(snes_apu_context_t *context)
{
    snapshot = get_snapshot(context);
}

Snapshot::Snapshot(const Snapshot& other)
{
    snapshot = clone_snapshot(other.snapshot);
}

Snapshot::~Snapshot()
{
    free_snapshot(snapshot);
}

Snapshot& Snapshot::operator =(const Snapshot& rhs)
{
    snapshot = clone_snapshot(rhs.snapshot);
    return *this;
}

const int16_t *Snapshot::GetLeftOutputBuffer() const
{
    return get_snapshot_left_output_buffer(snapshot);
}

const int16_t *Snapshot::GetRightOutputBuffer() const
{
    return get_snapshot_right_output_buffer(snapshot);
}

const unsigned char *Snapshot::GetRam() const
{
    return get_snapshot_ram(snapshot);
}

bool Snapshot::GetResamplingModeIsGaussian() const
{
    return get_snapshot_resampling_mode_is_gaussian(snapshot) != 0;
}

bool Snapshot::GetResamplingModeIsLinear() const
{
    return get_snapshot_resampling_mode_is_linear(snapshot) != 0;
}

bool Snapshot::GetVoiceIsMuted(int voiceIndex) const
{
    return get_snapshot_voice_is_muted(snapshot, voiceIndex) != 0;
}

const int32_t *Snapshot::GetVoiceRawOutputBuffer(int voiceIndex) const
{
    return get_snapshot_voice_raw_output_buffer(snapshot, voiceIndex);
}

const int32_t *Snapshot::GetVoiceLeftOutputBuffer(int voiceIndex) const
{
    return get_snapshot_voice_left_output_buffer(snapshot, voiceIndex);
}

const int32_t *Snapshot::GetVoiceRightOutputBuffer(int voiceIndex) const
{
    return get_snapshot_voice_right_output_buffer(snapshot, voiceIndex);
}

SnesApu::SnesApu()
{
    context = create_context();
}

SnesApu::~SnesApu()
{
    free_context(context);
}

void SnesApu::Reset()
{
    reset(context);
}

void SnesApu::Stop()
{
    stop(context);
}

void SnesApu::SetSong(const char *filename)
{
    set_song(context, filename);
}

void SnesApu::SetResamplingModeGaussian()
{
    set_resampling_mode_gaussian(context);
}

void SnesApu::SetResamplingModeLinear()
{
    set_resampling_mode_linear(context);
}

void SnesApu::SetVoiceIsMuted(int voiceIndex, bool value)
{
    set_voice_is_muted(context, voiceIndex, value ? 1 : 0);
}

Snapshot SnesApu::GetSnapshot()
{
    return Snapshot(context);
}
