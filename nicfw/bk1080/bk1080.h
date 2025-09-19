



void BK1080_Init(void);
void BK1080_WriteRegisters(uint8_t Index, const uint8_t *pValues, uint8_t Size);
void BK1080_ReadRegisters(uint8_t Index, uint8_t *pValues, uint8_t Size);



void fmtEqualize(channelInfo* vfo);
void fmtStart(const u8 stealth);
void fmtTick(void);
void fmtDisable(void);
void fmtMute(const u8 mute);
