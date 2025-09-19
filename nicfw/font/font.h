const FONT font6x8 = {
    FONT6x8BASE,
    6,
    8,
    8
};

const FONT font8x8 = {
    FONT8x8BASE,
    8,
    8,
    8
};

const FONT font8x16 = {
    FONT8x16BASE,
    8,
    16,
    16
};

const FONT font16x16 = {
    FONT16x16BASE,
    16,
    16,
    32
};

const FONT* CHIPFONT[4] = {
    &font6x8,
    &font8x8,
    &font8x16,
    &font16x16,
};

//#define FONT6X8BASE ((u32)CHIPFONT[0])
//#define FONT8X8BASE ((u32)CHIPFONT[1])
//#define FONT8X16BASE ((u32)CHIPFONT[2])


void fontDrawText(const char* text, const FONT* font, u8 x, const u8 y, const u16 fg, const u16 bg);
void fontDraw16x16 (const char* text, const u8 x, const u8 y, const u16 col);
void fontDraw6x8 (const char* text, const u8 x, const u8 y, const u16 col);
void fontDraw8x8 (const char* text, const u8 x, const u8 y, const u16 col, const u8 lrg);
void fontDraw8x16 (const char* text, const u8 x, const u8 y, const u16 col);
const u16 lowerColor(u16 color);

