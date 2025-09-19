#define KEY_PTTA 0x10
#define KEY_PTTB 0x11
#define KEY_FLSH 0x12
#define KEY_0 0x00
#define KEY_1 0x01
#define KEY_2 0x02
#define KEY_3 0x03
#define KEY_4 0x04
#define KEY_5 0x05
#define KEY_6 0x06
#define KEY_7 0x07
#define KEY_8 0x08
#define KEY_9 0x09
#define KEY_MENU 0x0A
#define KEY_UP 0x0B
#define KEY_DOWN 0x0C
#define KEY_EXIT 0x0D
#define KEY_STAR 0x0E
#define KEY_HASH 0x0F
#define KEY_NONE 0xFF
#define KEY_LONGACTIONED 0xFE

#define KEY_LONGACK 0xFE


void keypadTick(const u8 ticks);
void keypadInit(void);
const u8 keypadSinglePress(void);
const u8 keypadPTTA(void);
const u8 keypadPTTB(void);
const u8 keypadPTT(void);
const u8 keypadReadRow(void);
