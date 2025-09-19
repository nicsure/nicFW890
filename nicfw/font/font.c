static u8 fontBuffer[32];

void fontDrawQuadrant(const u8 bufferOffset, const u8 x, const u8 y, const u8 w, const u16 fg, const u16 bg)
{
    u8 m, c;
    u16 col2;
    col2 = lowerColor(fg);    
    lcdRegion(x, y, w, 8);
    for(c=0; c!=w; c++)
    {
        for(m=128; m; m>>=1)
        {
            lcdSend16( (fontBuffer[c+bufferOffset]&m) ? col2 : bg);
        }
    }
}

void fontCustomSymbol(const u8 sym, const u8 x, const u8 y, const u16 col)
{
    eepromRead(fontBuffer, SYMBOLSBASE + (sym<<3), 8); // corrected : address
    fontDrawQuadrant(0, x, y, 8, col, COL_BGROUND); 
}

const u16 lowerColor(u16 color)
{
    RGBCOL* col=(RGBCOL*)&color;
    if(dimColor)
    {
        switch(DIM_INACTIVE_VFO)
        {
            default:
                col->RGB.r>>=1;
                col->RGB.b>>=1;
                col->RGB.gl>>=1;
                col->RGB.gh>>=1;                                     
                break;
            case 2:
                col->bytes.c1 |= 0x1c; // 0b00011100;
                col->bytes.c2 |= 0xe7; // 0b11100111;
                break;
            case 0:
                break;
        }
    }
    return col->value;
}


void fontDrawText(const char* text, const FONT* font, u8 x, const u8 y, const u16 fg, const u16 bg)
{
    u32 addr;
    u8 ascii, vparts, hparts, partWidth, partHeight, sx, sy, i;
    vparts = font->charHeight > 8 ? 2 : 1;
    hparts = font->charWidth > 8 ? 2 : 1;
    partWidth = font->charWidth / hparts;
    partHeight = 8 * hparts;
    for(i=0; 1; i++)
    {
        ascii = text[i];
        if(ascii==0) break;
        addr = font->base + (((u32)ascii-32) * (u32)font->charByteCount);
        eepromRead(fontBuffer, addr, font->charByteCount);
        for(sy=0; sy<vparts; sy++)
        {
            for(sx=0; sx<hparts; sx++)
            {
                fontDrawQuadrant( 
                    (partHeight * sy) + (partWidth * sx),
                    x + (partWidth * sx),
                    y + (8 * sy),
                    partWidth, 
                    fg, bg
                );
            }
        }
        x+=font->charWidth;
    }
}

void fontDraw16x16 (const char* text, const u8 x, const u8 y, const u16 col)
{
    fontDrawText(text, &font16x16, x, y, col, COL_BGROUND);
}

void fontDraw6x8 (const char* text, const u8 x, const u8 y, const u16 col)
{
    fontDrawText(text, &font6x8, x, y, col, COL_BGROUND);
}

void fontDraw8x8 (const char* text, const u8 x, const u8 y, const u16 col, const u8 lrg)
{
    fontDrawText(text, lrg ? &font16x16 : &font8x8, x, y, col, COL_BGROUND);
}

void fontDraw8x16 (const char* text, const u8 x, const u8 y, const u16 col)
{
    fontDrawText(text, &font8x16, x, y, col, COL_BGROUND);
}
