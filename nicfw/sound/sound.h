
static u8 beepDuration;
static u32 beepWaveLength;

void soundBeep(u8 duration, u32 waveLength);
void soundBlip(const u8 duration, const u16 waveLength, const u8 twice);
void differentialKeyTone(const u8 duration, const u8 key);

