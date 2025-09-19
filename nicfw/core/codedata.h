const struct {
    char SPACE12   ;
    char SPACE11   ;
    char SPACE10   ;
    char SPACE9    ;
    char SPACE8    ;
    char SPACE7    ;
    char SPACE6    ;
    char SPACE5    ;
    char SPACE4    ;
    char SPACE3    ;
    char SPACE2    ;
    char SPACE1    ;
    char SPACEZERO ;
} SPACES = { 32,32,32,32,32,32,32,32,32,32,32,32,0 };

#define SPACE12   (SPACES.SPACE12  )
#define SPACE11   (SPACES.SPACE11  )
#define SPACE10   (SPACES.SPACE10  )
#define SPACE9    (SPACES.SPACE9   )
#define SPACE8    (SPACES.SPACE8   )
#define SPACE7    (SPACES.SPACE7   )
#define SPACE6    (SPACES.SPACE6   )
#define SPACE5    (SPACES.SPACE5   )
#define SPACE4    (SPACES.SPACE4   )
#define SPACE3    (SPACES.SPACE3   )
#define SPACE2    (SPACES.SPACE2   )
#define SPACE1    (SPACES.SPACE1   )
#define SPACEZERO (SPACES.SPACEZERO)

const char NT[] = "N/T ";
const char VFOn[] = "VFO-%";
const char GRPn[] = "GRP-%";
const char CHn[] = "CH%%%";
const char SCANNING[] = "Scanning   ";
const char ACTIVITY[] = "Activity   ";
const char MONITORING[] = "Monitoring ";
const char FREQCOUNT[] = "Freq Count ";

const char TX_LABEL[] = "TX";
const char RX_LABEL[] = "RX";
const char STN_LABEL[] = "STN";
const char DTMF_LABEL[] = "DTMF";
const char SCAN_LABEL[] = "Scan ";
const char ACIV_LABEL[] = "Actv ";

const char FM[] = " FM";
const char AM[] = " AM";
const char USB[] = "USB";
const char FMT[] = "FMT";
const char NR[] = "N/R";
const char optionOff[] = "Off";
const char optionOn[] = "On";
const char optionNo[] = "No";
const char optionYes[] = "Yes";
const char optionWide[] = "Wide";
const char optionNarrow[] = "Narrow";
const char option2_0[] = "2.0";
const char option2_1[] = "2.1";
const char AUTO[] = "Auto";
const char NA[] = "N/A";
const char DUAL[] = "Dual";
const char SINGLE[] = "Single";
const char HYBRID[] = "Hybrid";
const char ICON[] = "Icon";
const char PERCENT[] = "Percent";
const char VOLTS[] = "Volts";
const char DIFFERENTIAL[] = "Differential";
const char VOICE[] = "Voice";
const char BOTH[] = "Both";
const char AGC[] = "AGC";
const char SOLID[] = "Solid";
const char SEGMENT[] = "Segment";
const char STEPPED[] = "Stepped";
const char CANCEL[] = "Cancel";
const char SEND[] = "Send";
const char RECEIVE[] = "Receive";
const char CRC[] = "CRC";
const char OK[] = "OK ";
const char BAD[] = "BAD";
const char COSI[] = "I-COS";
const char POWERON[] = "Power On";
const char CLONE[] = "Clone";
const char BOT[] = "BoT";
const char EOT[] = "EoT";

const char IF1[] = "8.46";
const char IF2[] = "7.25";
const char IF3[] = "6.35";
const char IF4[] = "5.64";
const char IF5[] = "5.08";
const char IF6[] = "4.62";
const char IF7[] = "4.23";

const char SCANPRESETS[] = "Scan Presets";
const char KHZ[] = "kHz";
const char US[] = "US:";


const char SIGNATURE[] = {
    ' ', 'n', 'i', 'c', 'F', 'W', ' ', 0,
    '3', '.', '0', '0', '.', '1', '6', 0, 'R', 0
};
//const char SIGNATURE[] = " nicFW ";
//const char VERSION[] = "3.00.03";
//const char RELEASE_TYPE[] = "P";
#define VERSION (&SIGNATURE[8])

const u32 FREQ_MIN = 1800000l;
const u32 FREQ_MAX = 129999999l;

const u32 CRC32POLYNOMIAL = 0xEDB88320UL;
const u16 PLANMAGIC_ = 0xA46D;
const u16 SETTINGSMAGIC = 0xD93F;


const u16 ifTable[] = {
    0x2aab,
    0x4924,
    0x6800,
    0x871c,
    0xa666,
    0xc5d1,
    0xe555,
};



const u16 gainTable[] = {
    0x03BE,
    0x0000,
    0x0008,
    0x0010,
    0x0001,
    0x0009,
    0x0011,
    0x0002,
    0x000A,
    0x0012,
    0x0003,
    0x000B,
    0x0013,
    0x0004,
    0x000C,
    0x000D,
    0x001C,
    0x001D,
    0x001E,
    0x001F,
    0x003E,
    0x003F,
    0x005E,
    0x005F,
    0x007E, // gain0
    0x007F,
    0x009F,
    0x00BF,
    0x00DF,
    0x00FF,
    0x01DF,
    0x01FF,
    0x02BF, // gain1
    0x02DF,
    0x02FF,
    0x035E,
    0x035F,
    0x037E, // gain2
    0x037F, 
    0x038F,
    0x03BF, // gain3
    0x03DF,
    0x03FF,
};

