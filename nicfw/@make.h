#include <at32f421.h>
#include <stddef.h>

#define SPRINT_NUMBER(b, v, u, d, p, z) sp_Value=(v); sp_Decimals=(d); sp_Units=(u); sprint_number((b), (p), (z)); 


void Main(void) __attribute__((noreturn));
void BSS_Init(void);
void DATA_Init(void);
void applyBankChange(void);

typedef union __attribute__((packed, aligned(2))) {
    u16 value;
    struct __attribute__((packed)) {
        u8 lo;
        u8 hi;
    } bytes;
    struct __attribute__((packed)) {
        u16 n0 : 4;
        u16 n1 : 4;
        u16 n2 : 4;
        u16 n3 : 4;
    } nibbles;
    u8 array[2];
} U16;

typedef union __attribute__((packed, aligned(4))) {
    u32 value;
    struct __attribute__((packed)) {
        u16 lo;
        u16 hi;
    } words;
    struct __attribute__((packed)) {
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u8 byte3;
    } bytes;
    u8 array[4];
} U32;

typedef struct __attribute__((packed)) {
    u8 tank;
    u8 latch;
    u8 lp;
} KEY;

typedef struct __attribute__((packed)) {
    u32 base;
    u8 charWidth;
    u8 charHeight;
    u8 charByteCount;
} FONT;

#define C32(x) ((U32*)&x)
#define C16(x) ((U16*)&x)

typedef struct __attribute__((packed, aligned(4))) {
    u16 magic;                  // 0x00
    u8 squelch;                 // 0x02
    u8 dualWatch;               // 0x03
    u8 autoFloor;               // 0x04
    u8 activeVfo;               // 0x05
    u16 step;                   // 0x06
    u16 rxSplit;                // 0x08
    u16 txSplit;                // 0x0a
    u8 pttMode;                 // 0x0c
    u8 txModMeter;              // 0x0d
    u8 micGain;                 // 0x0e
    u8 txDeviation;             // 0x0f
    s8 UNUSED_xtal671;          // 0x10
    u8 battStyle;               // 0x11
    u16 scanRange;              // 0x12      
    U16 scanPersist;            // 0x14
    u8 scanResume;              // 0x16
    u8 ultraScan;               // 0x17
    u8 toneMonitor;             // 0x18
    u8 lcdBrightness;           // 0x19
    u8 lcdTimeout;              // 0x1a
    u8 breathe;                 // 0x1b
    u8 dtmfDev;                 // 0x1c
    u8 gamma;                   // 0x1d
    u16 repeaterTone;           // 0x1e
    struct __attribute__((packed)) { // 0x20
        struct __attribute__((packed)) {
            u8 group;
            u8 lastGroup;
            u8 groupModeChannels[16];
            u8 mode;
        } vfoState[2];
    } bankState[4];
    u8 keyLock;                 // 0x46 this and subsequently is +0x72
    u8 bluetooth;               // 0x47
    u8 powerSave;               // 0x48
    u8 keyTones;                // 0x49
    u8 ste;                     // 0x4a
    u8 rfGain;                  // 0x4b
    u32 lastFmtFreq;            // 0x4c
    u8 sBarStyle;               // 0x50   u32 lastFmtFreq;
    u8 sqNoiseLev;              // 0x51   u8 sBarStyle;
    u16 voxTail;                // 0x52   u8 sqNoiseLev;
    u8 vox;                     // 0x54
    u8 txTimeout;               // 0x55
    u8 dimmer;                  // 0x56
    u8 dtmfSpeed;               // 0x57
    u8 noiseGate;               // 0x58
    u8 scanUpdate;              // 0x59
    u8 asl;                     // 0x5a
    u8 disableFmt;              // 0x5b
    u16 pin;                    // 0x5c
    u8 pinAction;               // 0x5e
    u8 lcdInverted;             // 0x5f
    u8 afFilters;               // 0x60
    u8 ifFreq;                  // 0x61
    u8 sBarAlwaysOn;            // 0x62
    u8 setVfo;                  // 0x63
    u8 vfoLock;                 // 0x64
    u8 dwDelay;                 // 0x65
    u8 stDev;                   // 0x66
    u8 txCurrent;               // 0x67
    u8 pcbVersion;              // 0x68
    u8 rfiCompAmount;           // 0x69
    u8 channelBank;             // 0x6a
    u8 gain0;                   // 0x6b
    u8 gain1;                   // 0x6c
    u8 gain2;                   // 0x6d
    u8 gain3;                   // 0x6e
    u8 amFix;                   // 0x6f
} settingsBlock;

typedef struct __attribute__((packed, aligned(4)))
{
    U32 rxFreq;
    U32 txFreq;
    U16 rxSubTone;
    U16 txSubTone;
    u8 txPower;
    u8 unused;
    union __attribute__((packed))
    {
        u16 value;
        struct __attribute__((packed))
        {
            u16 g0 : 4;
            u16 g1 : 4;
            u16 g2 : 4;
            u16 g3 : 4;
        } single;
    } groups;
    struct __attribute__((packed))
    {
        u8 bandwidth : 1;
        u8 modulation : 2;
        u8 position : 1;
        u8 pttID : 2;
        u8 reversed : 1;
        u8 busyLock : 1;
    } bits;
    char reserved[3];
    char name[12];
} channelInfo;


typedef struct __attribute__((packed, aligned(4)))
{
    u8 number;
    u8 rxplan;
    u8 txplan;
    u8 modulation;
    u8 txPower;
    u8 rxBandwidth;
    u8 txBandwidth;
    u8 rxIsVhf;
    u8 txIsVhf;
    u8 isFmTuner;
    u16 alignto4;
} channelXtra;

typedef struct __attribute__((packed, aligned(4)))
{
    u32 startFreq;
    u32 endFreq;
    u8 maxPower;
    struct __attribute__((packed))
    {
        u8 txAllowed : 1;
        u8 wrap : 1;
        u8 modulation : 3;
        u8 bandwidth : 3;
    } bits;
    char padding[2];
} planInfo;

typedef struct __attribute__((packed, aligned(4)))
{
    U32 startFreq;
    u16 range;
    u16 step;
    u8 resume;
    u8 persist;
    struct __attribute__((packed)) {
        u8 modulation : 2;
        u8 ultrascan : 6;
    } bits;
    char label[13];
} scanPresetInfo;

typedef struct __attribute__((packed, aligned(4))) 
{
    struct __attribute__((packed)) 
    {
        u16 length : 4; // byte 0
        u16 d0 : 4;
        u16 d1 : 4;     // byte 1
        u16 d2 : 4;
	} first;
	struct __attribute__((packed)) 
    {
        u16 d3 : 4;     // byte 2
        u16 d4 : 4;
        u16 d5 : 4;     // byte 3
        u16 d6 : 4;
    } second;
    struct __attribute__((packed)) 
    {
        u8 d7 : 4;      // byte 4
        u8 d8 : 4;
    } third;
} dtmfSequence;

typedef struct __attribute__((packed, aligned(4))) {
    dtmfSequence sequence;
    char label[7];
} dtmfPreset;

typedef struct __attribute__((packed, aligned(4))) {
    s8 defunct;
    u8 uhfPeakWatts;
    u8 uhfPeakSetting;
    u8 vhfPeakWatts;
    u8 vhfPeakSetting;
    u8 padding1;
    s16 xtal671;
} tuningBlock;

typedef union __attribute__((packed, aligned(2)))
{
    u16 value;
    struct
    {
        u16 r : 5;
        u16 gl : 3;
        u16 gh : 3;
        u16 b : 5;
    } RGB;
    struct
    {
        u8 c2;
        u8 c1;
    } bytes;
} RGBCOL;

#define SPIBASE 0x1AC000
#define CHANNELBASE SPIBASE                     // length 0x7D00

#define CHANNELBANKBASE (   (((u32)settings.channelBank&3)<<13)+CHANNELBASE    )

#define SETTINGSBASE CHANNELBASE + 0x8000
#define SCANPRESETBASE SETTINGSBASE + 0x100
#define DTMFPRESETBASE SCANPRESETBASE + 0x200
#define GROUPLABELBASE DTMFPRESETBASE + 0x100
#define BANDPLANBASE GROUPLABELBASE + 0x100
#define BANDLABELSBASE BANDPLANBASE + 0x100

#define TUNINGBASE BANDLABELSBASE + 0x100
#define VHFTABLEBASE TUNINGBASE + 0x100
#define UHFTABLEBASE VHFTABLEBASE + 0x100

#define LOGOBASE UHFTABLEBASE + 0x200           // length 0x7A80
#define FONTBASE LOGOBASE + 0x7B00
#define FONT6x8BASE FONTBASE                    // length 0x300
#define FONT8x8BASE FONTBASE + 0x300            // length 0x300
#define FONT8x16BASE FONTBASE + 0x600           // length 0x600
#define FONT16x16BASE FONTBASE + 0xC00          // length 0xC00 // total 0x1800
#define SKINPOSBASE FONTBASE + 0x1900
#define SKINCOLBASE SKINPOSBASE + 0x100
#define LP0BASE SKINCOLBASE + 0x100
#define LP1BASE LP0BASE + 0x100
#define SYMBOLSBASE LP1BASE + 0x100

#define JOURNALDATA 0x1C0000
#define JOURNALINFO 0x1C1000

#define HI_NOISE_LEVEL 0x37

#define LOOPMODE_RADIO 0
#define LOOPMODE_FMTUNER 1
#define LOOPMODE_SCOPE 2
#define LOOPMODE_SCAN 4
#define LOOPMODE_SCANMONITOR 8
#define LOOPMODE_FREQCOUNTER 16
#define LOOPMODE_SCANFMT 32

#define INPUTMODE_NONE 0
#define INPUTMODE_MENU 1
#define INPUTMODE_INPUT 2
#define INPUTMODE_SERIAL 4

#define DOUBLE_SIZE 1
#define NORMAL_SIZE 0

#define FONT6X8NUM 0
#define FONT8X8NUM 1
#define FONT8X16NUM 2
#define FONT16X16NUM 3

#define VFOSTATE(x) (  settings.bankState[settings.channelBank].vfoState[x]  )
#define ACTIVE_VFOSTATE (settings.bankState[settings.channelBank].vfoState[settings.activeVfo])
#define ACTIVE_VFO (VFO[settings.activeVfo])
#define APPLIED_VFO (VFO[appliedVfo])
#define ACTIVE_VFOX (VFOX[settings.activeVfo])
#define APPLIED_VFOX (VFOX[appliedVfo])
#define ACTIVE_RXPLAN (plans[VFOX[settings.activeVfo].rxplan])
#define ACTIVE_TXPLAN (plans[VFOX[settings.activeVfo].txplan])
#define VFOA_ISACTIVE (!settings.activeVfo)
#define VFOB_ISACTIVE (settings.activeVfo)





