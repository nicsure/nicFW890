static u32 pAddr;
static U32 bkTone[2];
static u32 sp_Value;
static u32 scanFreqStart;
static u32 scanFreqEnd;
static u32 channelMap[252];
static u32 dcsTemp;
static u32 wrapAdjustment;
static u32 scanFreq;
static u32 scanIgnores[50];
static u32 inputStringSource;
static u32 inputValue;
static u32 inputMag;
static u32 hiFreq;
static u32 vfoSaveRX;
static u32 vfoSaveTX;
static u32 topFreq;
static U32 customBaud;

static u8 eepromBuffer[128];
//static u8 verifyBuffer[128];
static u8 uartPendingBytes[256];
static u8 scanMultiPreset[20];
static char TXT[32];
static char TXTEDIT[32];
static u8 nowt[32];
static u8 fskBlockBuffer[32];

static struct __attribute__((packed, aligned(4))) {
    U16 planMagic_;
    u16 planDummy_;
    planInfo plans_[20]; // 240 bytes
} planStruct;

#define planMagic planStruct.planMagic_
#define plans planStruct.plans_

static U16 bkReg[0x81];
static u16 COL_BGROUND;
static u16 groupMap[252];
static u16 heardTone;
static u16 rxSubToneMenuVal;
static u16 txSubToneMenuVal;
static u16 menuTemp;
static u16 menuBG;
static u16 menuTemp;
static u16 battReceive;
static u16 battXmit;

static settingsBlock settings;
static settingsBlock settings2;


static u8 pState;
static u8 pCnt;
static u8 pCS;
volatile u8 uartReadPos;
volatile u8 uartWritePos;
volatile u8 timerDisable;
volatile u8 vtimerDisable;
static u8 keypadShort;
static u8 keypadLong;
volatile u8 scopeBarWidth;

static tuningBlock tuning;

static u8 currentModulation;
static u8 POW2822_;
static u8 tonePlaying;
static u8 appliedVfo;
static channelXtra VFOX[2];
static channelInfo VFO[2];
static u8 squelchOpen;
static u8 fmtActive;
static u8 noiseFloor;
static u8 xmitActive;
static u8 txTimer;
static u8 wlCloneTrigger;
static u8 actualPower;
static u8 playDtmfOnPTT;
static dtmfSequence manualSeq;
static u8 keypadPressed = 0xff;
static u8 inputMode;
static u8 scopeActive;
static u8 dimColor;
static u8 feedDimmer;
static u8 uartReset;

static u8 sp_Units;
static u8 sp_Decimals;
static u8 noChName;;
static u8 loopMode;
static u8 scanActivityMode;

static u8 scanningSkip;

static u8 eepromTimer;
static u8 skipNextScope;
//static u8 reqSettingsSave;

static u8 rfiAdjust;;
static u8 lpShift;
static u8 lastDtmfPreset;

static u8 fmtPlan;

static u8 step833Counter;
static u8 scanDirection;
static u8 externalKey;
static u8 KEY_LED;
static u8 initComplete;
static u8 lcdTimer;
static u8 rxToneDetected;
static u8 signalPresent;
static u8 steTimer;
static u8 subToneOverride;
static u8 anyKeyInUse;
static u8 scanningResume;

static u8 heardToneCounter;
static u8 toneChanged;
static u8 fmtResume;
static u8 rssiTrigger;
static u8 updateTimer;
static u8 scanningCount;
static u8 fmtScanDown;
static u8 scanModSave;

static u8 ultraFloor;
static u8 usFloorCount;
static u8 usLowSig;
static u8 scanPresetIndex;
static u8 scanMultiPreset[20];
static u8 scanningChannel;
static u8 updateScanChannel;
static u8 RXA_LED;
static u8 scanIgnoreIndex;
static u8 freqScanVhfFilter;
static scanPresetInfo scanPresetBuffer;

static u8 inputUnits;
static u8 inputUnitsCnt;

static u8 inputDecimalCount;
static u8 inputDecimals;
static u8 inputX;
static u8 inputY;
static u8 inputFont;

static u8 octalInput;
static u8 offsetInput;
static u8 inputAsString;
static u8 inputAsDTMF;
static u8 inputAsGroup;
static u8 inputState;

static char singleChar[2];
static u8 bandwidthMenuVal;
static u8 txPowerMenuVal;
static u8 txMaxPowerMenuVal;

static u8 modulationMenuVal;
static u8 busyLockMenuVal;
static u8 pttIDMenuVal;
static u8 addGroupTrigger;
static u8 delGroupTrigger;
static u8 menuTens;
static u8 menuEdit;

static u8 menuVoice;
static u8 menuUnits;
static u8 menuDecimals;
static u8 menuNumber;

static u8 powerSaveSuspend;
static u8 voxTank;
static u8 voxTailTimer;
static u8 voxIgnore;
static u8 xmitRequest;
static u8 dualWatchStartTimer;
static u8 enteringPin;

static u8 lastDtmfKey;
static u8 noiseLimited;
static u8 breatheTimer;
static u8 squelchOverride;

static u8 battVolts;
static u8 vposTemp;
static union {
    u8 bytes[8];
    struct {
        u8 filler[6];
        u16 value;
    } checksum;
    u16 words[4];
} fskBuffer;

static u8 lastSig;
static u8 skipMeter;
static u8 amFixGain;
static u8 fmtStealth;
static u8 squelchOpenPause;


static struct __attribute__((packed, aligned(4))) { 
    u8 SMETER_DPTT_YPOS ; // = 
    u8 SBAR_DPTT_YPOS ; // = 2;
    u8 VFOA_YPOS ; // = 22;
    u8 VFOB_YPOS ; // = 83;
    u8 VFOS_YPOS ; // = 22;
    u8 VFO_RXXPOS ; // = 23;
    u8 VFO_RXYPOS ; // = 19;
    u8 VFO_TXXPOS ; // = 65;
    u8 VFO_TXYPOS ; // = 36;
    u8 VFO_POWERX ; // = 0;
    u8 VFO_POWERY ; // = 36;
    u8 VFO_CH_NAMEX ; // = 38;
    u8 VFO_CH_NAMEY ; // = 0;
    u8 VFO_NAMEX ; // = 0;
    u8 VFO_NAMEY ; // = 0;
    u8 VFO_GROUPX ; // = 0;
    u8 VFO_GROUPY ; // = 9;
    u8 VFO_REVERSEX ; // = 12;
    u8 VFO_REVERSEY ; // = 22;
    u8 VFO_BWX ; // = 38;
    u8 VFO_BWY ; // = 9;
    u8 VFO_GR_LETTERSX ; // = 2
    u8 VFO_GR_LETTERSY ; // = 3
    u8 VFO_TX_STX ; // = 55;
    u8 VFO_TX_STY ; // = 9;
    u8 VFO_RX_STX ; // = 78;
    u8 VFO_RX_STY ; // = 9;
    u8 VFO_MODX ; // = 103;
    u8 VFO_MODY ; // = 9;
    u8 VFO_SCANSYMX  ; //= 1;
    u8 VFO_SCANSYMY ; // = 22;
    u8 FLAGS_YPOS_DUAL ; // = 7
    u8 FLAGS_YPOS_SINGLE ; // =
    u8 FLAGS_TONEMONITORX ; // 
    u8 FLAGS_DWX ; // = 1;
    u8 FLAGS_KLX ; // = 11;
    u8 FLAGS_BTX ; // = 21;
    u8 FLAGS_VOXX ; // = 31;
    u8 FLAGS_ASLX ; // = 41;
    u8 FLAGS_BATTX ; // = 103;
    u8 LARGE_CH_NAME ; // = 0;
    u8 SMETER_SPTT_YPOS ; // = 
    u8 SBAR_SPTT_YPOS ; // = 2;
    u8 DIM_INACTIVE_VFO ; // = 
    u8 VFO_HEIGHT ; // = 45;
    u8 VFO_LJ_FREQ ; // = 0;
    u8 VFO_CHANGERXFREQNOTBG ; 
    u8 SCOPE_SOLID ; // = 0;
    u8 FLAGS_PTTMODE ; // = 51;    
    u8 LCD_VADJUST; // = 0
    u8 FLAGS_BANK; // = 0
    u8 VFO_SMALL_RXFREQ; // = 0
} SKINPOS;

static struct __attribute__((packed, aligned(4))) {
    u16 COL_SMETEROFF     ; //= 0x8210;
    u16 COL_SMETERLOW     ; //= 0x07C0;
    u16 COL_SMETERMID     ; //= 0x07FF;
    u16 COL_SMETERHIGH    ; //= 0xA29F;
    u16 COL_SMETERTX      ; //= 0x001F;
    u16 COL_SMETERTXMOD   ; //= 0x07E0;
    u16 COL_SMETEREXNOISE ; //= 0xF9AD;
    u16 COL_SUNIT         ; //= 0x07FF;
    u16 COL_PUNIT         ; //= 0xA29F;
    u16 COL_DBM           ; //= 0x6E8D;
    u16 COL_MENUENTRY     ; //= 0xD7FF;
    u16 COL_BATTICONBODY  ; //= 0xFE9A;
    u16 COL_FWBGROUND     ; //= 0x0000;
    u16 COL_INPUT         ; //= 0x87D0;
    u16 COL_MENUEDIT      ; //= 0x065F;
    u16 COL_MENU          ; //= 0xFFFF;
    u16 COL_MENUBG        ; //= 0x7800;
    u16 COL_MENUEDITBG    ; //= 0x1280;
    u16 COL_BLACK         ; //= 0x0000;
    u16 COL_VFOPOWER      ; //= 0x7D1F;
    u16 COL_VFOCHNAME     ; //= 0xFFC5;
    u16 COL_VFORXFREQ     ; //= 0xA7DF;
    u16 COL_VFOTXFREQ     ; //= 0x7FCF;
    u16 COL_VFOCORNER     ; //= 0xFDD4;
    u16 COL_VFOCORNER2    ; //= 0xFEDB;
    u16 COL_VFOIDLE       ; //= 0xAA82;
    u16 COL_VFOSCAN       ; //= 0x788E;
    u16 COL_VFORX         ; //= 0x2C42;
    u16 COL_VFOTX         ; //= 0x0014;
    u16 COL_VFOLABELS     ; //= 0x2E9F;
    u16 COL_ASLFLAG       ; //= 0x4A5F;
    u16 COL_BATTHIGH      ; //= 0x3FC7;
    u16 COL_BATTLOW       ; //= 0x39DF;
    u16 COL_SCOPEBAR      ; //= 0xFFFF;
    u16 COL_SCOPEBARMID   ; //= 0x07FF;    
} SKINCOL;



#define SMETER_DPTT_YPOS     (SKINPOS.SMETER_DPTT_YPOS )
#define SBAR_DPTT_YPOS       (SKINPOS.SBAR_DPTT_YPOS)
#define VFOA_YPOS            (SKINPOS.VFOA_YPOS)
#define VFOB_YPOS            (SKINPOS.VFOB_YPOS)
#define VFOS_YPOS            (SKINPOS.VFOS_YPOS)
#define VFO_RXXPOS           (SKINPOS.VFO_RXXPOS)
#define VFO_RXYPOS           (SKINPOS.VFO_RXYPOS)
#define VFO_TXXPOS           (SKINPOS.VFO_TXXPOS)
#define VFO_TXYPOS           (SKINPOS.VFO_TXYPOS)
#define VFO_POWERX           (SKINPOS.VFO_POWERX)
#define VFO_POWERY           (SKINPOS.VFO_POWERY)
#define VFO_CH_NAMEX         (SKINPOS.VFO_CH_NAMEX)
#define VFO_CH_NAMEY         (SKINPOS.VFO_CH_NAMEY)
#define VFO_NAMEX            (SKINPOS.VFO_NAMEX)
#define VFO_NAMEY            (SKINPOS.VFO_NAMEY)
#define VFO_GROUPX           (SKINPOS.VFO_GROUPX)
#define VFO_GROUPY           (SKINPOS.VFO_GROUPY)
#define VFO_REVERSEX         (SKINPOS.VFO_REVERSEX)
#define VFO_REVERSEY         (SKINPOS.VFO_REVERSEY)
#define VFO_BWX              (SKINPOS.VFO_BWX)
#define VFO_BWY              (SKINPOS.VFO_BWY)
#define VFO_GR_LETTERSX      (SKINPOS.VFO_GR_LETTERSX)
#define VFO_GR_LETTERSY      (SKINPOS.VFO_GR_LETTERSY)
#define VFO_TX_STX           (SKINPOS.VFO_TX_STX)
#define VFO_TX_STY           (SKINPOS.VFO_TX_STY)
#define VFO_RX_STX           (SKINPOS.VFO_RX_STX)
#define VFO_RX_STY           (SKINPOS.VFO_RX_STY)
#define VFO_MODX             (SKINPOS.VFO_MODX)
#define VFO_MODY             (SKINPOS.VFO_MODY)
#define VFO_SCANSYMX         (SKINPOS.VFO_SCANSYMX)
#define VFO_SCANSYMY         (SKINPOS.VFO_SCANSYMY)
#define FLAGS_YPOS_DUAL      (SKINPOS.FLAGS_YPOS_DUAL)
#define FLAGS_YPOS_SINGLE    (SKINPOS.FLAGS_YPOS_SINGLE)
#define FLAGS_TONEMONITORX   (SKINPOS.FLAGS_TONEMONITORX)
#define FLAGS_DWX            (SKINPOS.FLAGS_DWX)
#define FLAGS_KLX            (SKINPOS.FLAGS_KLX)
#define FLAGS_BTX            (SKINPOS.FLAGS_BTX)
#define FLAGS_VOXX           (SKINPOS.FLAGS_VOXX)
#define FLAGS_ASLX           (SKINPOS.FLAGS_ASLX)
#define FLAGS_BATTX          (SKINPOS.FLAGS_BATTX)
#define LARGE_CH_NAME        (SKINPOS.LARGE_CH_NAME)
#define SMETER_SPTT_YPOS     (SKINPOS.SMETER_SPTT_YPOS)
#define SBAR_SPTT_YPOS       (SKINPOS.SBAR_SPTT_YPOS)
#define DIM_INACTIVE_VFO     (SKINPOS.DIM_INACTIVE_VFO)
#define VFO_HEIGHT           (SKINPOS.VFO_HEIGHT)
#define VFO_LJ_FREQ          (SKINPOS.VFO_LJ_FREQ)
#define VFO_CHANGERXFREQNOTBG (SKINPOS.VFO_CHANGERXFREQNOTBG  )
#define SCOPE_SOLID          (SKINPOS.SCOPE_SOLID)
#define FLAGS_PTTMODE        (SKINPOS.FLAGS_PTTMODE)
#define LCD_VADJUST          (SKINPOS.LCD_VADJUST)
#define FLAGS_BANK           (SKINPOS.FLAGS_BANK)
#define VFO_SMALL_RXFREQ     (SKINPOS.VFO_SMALL_RXFREQ)

#define COL_SMETEROFF     (SKINCOL.COL_SMETEROFF     )
#define COL_SMETERLOW     (SKINCOL.COL_SMETERLOW     )
#define COL_SMETERMID     (SKINCOL.COL_SMETERMID     )
#define COL_SMETERHIGH    (SKINCOL.COL_SMETERHIGH    )
#define COL_SMETERTX      (SKINCOL.COL_SMETERTX      )
#define COL_SMETERTXMOD   (SKINCOL.COL_SMETERTXMOD   )
#define COL_SMETEREXNOISE (SKINCOL.COL_SMETEREXNOISE )
#define COL_SUNIT         (SKINCOL.COL_SUNIT         )
#define COL_PUNIT         (SKINCOL.COL_PUNIT         )
#define COL_DBM           (SKINCOL.COL_DBM           )
#define COL_MENUENTRY     (SKINCOL.COL_MENUENTRY     )
#define COL_BATTICONBODY  (SKINCOL.COL_BATTICONBODY  )
#define COL_FWBGROUND     (SKINCOL.COL_FWBGROUND     )
#define COL_INPUT         (SKINCOL.COL_INPUT         )
#define COL_MENUEDIT      (SKINCOL.COL_MENUEDIT      )
#define COL_MENU          (SKINCOL.COL_MENU          )
#define COL_MENUBG        (SKINCOL.COL_MENUBG        )
#define COL_MENUEDITBG    (SKINCOL.COL_MENUEDITBG    )
#define COL_BLACK         (SKINCOL.COL_BLACK         )
#define COL_VFOPOWER      (SKINCOL.COL_VFOPOWER      )
#define COL_VFOCHNAME     (SKINCOL.COL_VFOCHNAME     )
#define COL_VFORXFREQ     (SKINCOL.COL_VFORXFREQ     )
#define COL_VFOTXFREQ     (SKINCOL.COL_VFOTXFREQ     )
#define COL_VFOCORNER     (SKINCOL.COL_VFOCORNER     )
#define COL_VFOCORNER2    (SKINCOL.COL_VFOCORNER2    )
#define COL_VFOIDLE       (SKINCOL.COL_VFOIDLE       )
#define COL_VFOSCAN       (SKINCOL.COL_VFOSCAN       )
#define COL_VFORX         (SKINCOL.COL_VFORX         )
#define COL_VFOTX         (SKINCOL.COL_VFOTX         )
#define COL_VFOLABELS     (SKINCOL.COL_VFOLABELS     )
#define COL_ASLFLAG       (SKINCOL.COL_ASLFLAG       )
#define COL_BATTHIGH      (SKINCOL.COL_BATTHIGH      )
#define COL_BATTLOW       (SKINCOL.COL_BATTLOW       )
#define COL_SCOPEBAR      (SKINCOL.COL_SCOPEBAR      )
#define COL_SCOPEBARMID   (SKINCOL.COL_SCOPEBARMID   )
