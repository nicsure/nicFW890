void radioSetFilters(const u8 rx, const u8 vhf);
void radioSetLED(const u8 red, const u8 green);
void validateVfo2(const u8 vfoPosition);
void validateVfo(const u8 vfoPosition);
void radioSwapVfo(void);
void radioInitLEDs(void);
void radioToggleVfoMode(const u8 newMode, const u8 group, const u8 chstep);
void radioSetScanStartFreqToVfo(void);
const s16 step833(const u8 dir);
void radioToggleVfoModeAndGroup(u8 newMode, u8 group, const u8 chstep, const u8 grpDir);

