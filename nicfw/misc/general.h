const u8 memCmp2(const u8* s1, const u8* s2, u16 len);
const u8 subCounter(u8* var, const u8 by);
void sprint_power(const u8 dutyCycle, const u8 isVhf);
void sprint_number(char* buffer, const u8 padSpaces, const u8 nullTerminate);
const char groupLetter(const u8 groupNumber);
const u8 isValidFreq(const u32* freq);
const u8 clampFreq(u32* freq);
const u8 isFreqVhf(const u32* freq, const u8 rx);
const u8 crc32(void);

