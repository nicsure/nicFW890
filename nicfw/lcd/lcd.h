enum {
	ST7735S_CMD_NOP       = 0x00U,
	ST7735S_CMD_SWRESET   = 0x01U,
	ST7735S_CMD_RDDID     = 0x04U,
	ST7735S_CMD_RDDST     = 0x09U,
	ST7735S_CMD_RDDPM     = 0x0AU,
	ST7735S_CMD_RDDMADCTL = 0x0BU,
	ST7735S_CMD_RDDCOLMOD = 0x0CU,
	ST7735S_CMD_RDDIM     = 0x0DU,
	ST7735S_CMD_RDDSM     = 0x0EU,
	ST7735S_CMD_RDDSDR    = 0x0FU,
	ST7735S_CMD_SLPIN     = 0x10U,
	ST7735S_CMD_SLPOUT    = 0x11U,
	ST7735S_CMD_PTLON     = 0x12U,
	ST7735S_CMD_NORON     = 0x13U,
	ST7735S_CMD_INVOFF    = 0x20U,
	ST7735S_CMD_INVON     = 0x21U,
	ST7735S_CMD_GAMSET    = 0x26U,
	ST7735S_CMD_DISPOFF   = 0x28U,
	ST7735S_CMD_DISPON    = 0x29U,
	ST7735S_CMD_CASET     = 0x2AU,
	ST7735S_CMD_RASET     = 0x2BU,
	ST7735S_CMD_RAMWR     = 0x2CU,
	ST7735S_CMD_RGBSET    = 0x2DU,
	ST7735S_CMD_RAMRD     = 0x2EU,
	ST7735S_CMD_PTLAR     = 0x30U,
	ST7735S_CMD_SCRLAR    = 0x33U,
	ST7735S_CMD_TEOFF     = 0x34U,
	ST7735S_CMD_TEON      = 0x35U,
	ST7735S_CMD_MADCTL    = 0x36U,
	ST7735S_CMD_VSCSAD    = 0x37U,
	ST7735S_CMD_IDMOFF    = 0x38U,
	ST7735S_CMD_IDMON     = 0x39U,
	ST7735S_CMD_COLMOD    = 0x3AU,

    LCD_PAUSE             = 0x80U,
    LCD_CMD               = 0x81U,

	ST7735S_CMD_RDID1     = 0xDAU,
	ST7735S_CMD_RDID2     = 0xDBU,
	ST7735S_CMD_RDID3     = 0xDCU,
	ST7735S_CMD_FRMCTR1   = 0xB1U,
	ST7735S_CMD_FRMCTR2   = 0xB2U,
	ST7735S_CMD_FRMCTR3   = 0xB3U,
	ST7735S_CMD_INVCTR    = 0xB4U,
	ST7735S_CMD_PWCTR1    = 0xC0U,
	ST7735S_CMD_PWCTR2    = 0xC1U,
	ST7735S_CMD_PWCTR3    = 0xC2U,
	ST7735S_CMD_PWCTR4    = 0xC3U,
	ST7735S_CMD_PWCTR5    = 0xC4U,
	ST7735S_CMD_VMCTR1    = 0xC5U,
	ST7735S_CMD_VMOFCTR   = 0xC7U,
	ST7735S_CMD_WRID2     = 0xD1U,
	ST7735S_CMD_WRID3     = 0xD2U,
	ST7735S_CMD_NVFCTR1   = 0xD9U,
	ST7735S_CMD_NVFCTR2   = 0xDEU,
	ST7735S_CMD_NVFCTR3   = 0xDFU,
	ST7735S_CMD_GMCTRP1   = 0xE0U,
	ST7735S_CMD_GMCTRN1   = 0xE1U,
	ST7735S_CMD_GCV       = 0xFCU,

    LCD_SEQ_END           = 0xFFU,
};

static void lcdSendByte(const u8 byt);
void lcdSend(const u8 data, const u8 cmd);
void lcdInit(void);
void lcdCls(void);
void lcdSend16(const u16 data);
void lcdFill(const u8 x, const u8 y, const u8 w, const u8 h, const u16 col);
void lcdRegion(const u8 x, u8 y, const u8 w, const u8 h);
void lcdBL(const u8 dc);
void lcdInvert(const u8 inverted);
void lcdGamma(void);
void lcdSleep(const u8 asleep);


void lcdScrollTest(void);
