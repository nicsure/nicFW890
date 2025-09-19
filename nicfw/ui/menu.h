
#define OPTION 1
#define VALUE16 20
#define VALUE8 21
#define VALUE8ZO 22
#define VALUECTS 23
#define VALUEDCS 24
#define VALUE16ZO 25
#define VALUE8S 26
#define VALUE8L 27
#define VALUE16S 28

#define MENU_COUNT 66 
//((sizeof(menus)/3)-1)
#define MENU_TYPE (*((u8*)menu))
#define MENU_VAR (*(((MENU*)menu)->var))
#define MENU_VAR16 (*(((MENU16*)menu)->var))

#define NEWVALUE_KEEPOLD 0xffffffffu
#define NEWVALUE_ADD1 0xfffffffeu
#define NEWVALUE_SUB1 0xfffffffdu
#define NEWVALUE_1ST 0xfffffffcu
#define NEWVALUE_NEGATE 0xfffffffbu


typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
} MENU;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    const char* opts[7];
} MENUOPTS;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    const char* opts[2];
} MENUOPTS2;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    const char* opts[3];
} MENUOPTS3;

typedef struct
{
    u8 type;
    u8 min;
    u8 max;
    u8 voicePrompt;
    u8* var;    
    char* title;
    const char* opts[4];
} MENUOPTS4;


typedef struct
{
    u8 type;
    u16 min;
    u16 max;
    u8 decimals;
    u8 voicePrompt;
    u16* var;    
    char* title;
} MENU16;

void menuDraw(const u32 newValue);
void menuTick(void);
void menuInit(void);
void menuDrawPin(void);

