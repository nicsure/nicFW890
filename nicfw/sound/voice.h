
#define VOICE_ID_FREQUENCY_MODE                0U
#define VOICE_ID_CHANNEL_MODE                  1U
#define VOICE_ID_ON                            2U
#define VOICE_ID_OFF                           3U
#define VOICE_ID_SCANNING                      4U
#define VOICE_ID_VOX                           5U
#define VOICE_ID_DUALSTANDBY                   6U
#define VOICE_ID_BANDSELECT                    7U
#define VOICE_ID_STARTUP_SETTINGS              8U
#define VOICE_ID_STARTUP_LOGO                  9U
#define VOICE_ID_VOLTAGE_DISPLAY               10U
#define VOICE_ID_STARTUP_RINGTONE              11U
#define VOICE_ID_PROMPT_TEXT                   12U
#define VOICE_ID_SYSTEM_PROMPT                 13U
#define VOICE_ID_VOICE_PROMPT                  14U
#define VOICE_ID_KEY_BEEP                      15U
#define VOICE_ID_ROGER_BEEP                    16U
#define VOICE_ID_CHANNEL_REPORT                17U
#define VOICE_ID_BASIC_SETTINGS                18U
#define VOICE_ID_TX_PRIORITY                   19U
#define VOICE_ID_SAVE_MODE                     20U
#define VOICE_ID_FREQUENCY_STEP                21U
#define VOICE_ID_SQ_LEVEL                      22U
#define VOICE_ID_DISPLAY_TIMER                 23U
#define VOICE_ID_LOG_TIMER                     24U
#define VOICE_ID_TIMEOUT_TIMER                 25U
#define VOICE_ID_VOX_LEVEL                     26U
#define VOICE_ID_VOX_DELAY                     27U
#define VOICE_ID_WEATHER_MONITOR               28U
#define VOICE_ID_SM_STANDBY                    29U
#define VOICE_ID_DUAL_DISPLAY                  30U
#define VOICE_ID_FOOK_KNOWS                    31U
#define VOICE_ID_SCANNING_DIRECTION            32U
#define VOICE_ID_PERSONAL_ID                   33U
#define VOICE_ID_SEND_ID                       34U
#define VOICE_ID_DATA_INIT                     35U
#define VOICE_ID_CHANNEL_SETTINGS              36U
#define VOICE_ID_PRIVACY_CODE                  37U
#define VOICE_ID_RX_PRIVACY_CODE               38U
#define VOICE_ID_TX_PRIVACY_CODE               39U
#define VOICE_ID_TX_POWER                      40U
#define VOICE_ID_BANDWIDTH                     41U
#define VOICE_ID_TX_BUSYLOCK                   42U
#define VOICE_ID_VOICE_SCRAMBLER               43U
#define VOICE_ID_DCS_ENCRYPT                   44U
#define VOICE_ID_MUTE_CODE                     45U
#define VOICE_ID_AM_RECEIVE                    46U
#define VOICE_ID_CHANNEL_NAME                  47U
#define VOICE_ID_SAVE_CHANNEL                  48U
#define VOICE_ID_DELETE_CHANNEL                49U
#define VOICE_ID_SIDE_KEY                      50U
#define VOICE_ID_KEY1_PRESS_LONG               51U
#define VOICE_ID_KEY1_PRESS_SHORT              52U
#define VOICE_ID_KEY2_PRESS_LONG               53U
#define VOICE_ID_KEY2_PRESS_SHORT              54U
#define VOICE_ID_RECORD_SETTINGS               55U
#define VOICE_ID_RX_RECORD                     56U
#define VOICE_ID_TX_RECORD                     57U
#define VOICE_ID_INSTRUCTION                   58U
#define VOICE_ID_FIRMWARE_VERSION              59U
#define VOICE_ID_MONIT                         60U
#define VOICE_ID_LOCAL_ALARM                   61U
#define VOICE_ID_REMOTE_ALARM                  62U
#define VOICE_ID_FREQUENCY_DETECT              63U
#define VOICE_ID_REPEATER_MODE                 64U
#define VOICE_ID_FREQUENCY_INVERSE             65U
#define VOICE_ID_WEATHER_MONITOR2              66U
#define VOICE_ID_MANUAL_RECORD                 67U
#define VOICE_ID_GPS                           68U
#define VOICE_ID_SEND_GPS                      69U
#define VOICE_ID_0                             70U
#define VOICE_ID_1                             71U
#define VOICE_ID_2                             72U
#define VOICE_ID_3                             73U
#define VOICE_ID_4                             74U
#define VOICE_ID_5                             75U
#define VOICE_ID_6                             76U
#define VOICE_ID_7                             77U
#define VOICE_ID_8                             78U
#define VOICE_ID_9                             79U
#define VOICE_ID_10                            80U
#define VOICE_ID_11                            81U
#define VOICE_ID_12                            82U
#define VOICE_ID_13                            83U
#define VOICE_ID_14                            84U
#define VOICE_ID_15                            85U
#define VOICE_ID_16                            86U
#define VOICE_ID_17                            87U
#define VOICE_ID_18                            88U
#define VOICE_ID_19                            89U
#define VOICE_ID_20                            90U
#define VOICE_ID_30                            91U
#define VOICE_ID_40                            92U
#define VOICE_ID_50                            93U
#define VOICE_ID_60                            94U
#define VOICE_ID_70                            95U
#define VOICE_ID_80                            96U
#define VOICE_ID_90                            97U
#define VOICE_ID_100                           98U
#define VOICE_ID_200                           99U
#define VOICE_ID_300                           100U
#define VOICE_ID_400                           101U
#define VOICE_ID_500                           102U
#define VOICE_ID_600                           103U
#define VOICE_ID_700                           104U
#define VOICE_ID_800                           105U
#define VOICE_ID_900                           106U
#define VOICE_NONE                             255U

volatile u32 sampleAddress1, sampleAddress2, sampleAddress3;
volatile u8 previousSamp, samplePlaying;

void voiceInit(void);
void voicePlay(const u8 id);
void voicePlay3(const u8 id1, const u8 id2, const u8 id3);
void voiceWait(void);
void voiceDisable(void);
void voiceEnable(void);
void HandleLCDDimming(void);