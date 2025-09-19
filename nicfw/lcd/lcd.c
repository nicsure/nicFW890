

void lcdSendByte(const u8 byt)
{
	u8 m;
	//if(squelchOpen && settings.rfiCompAmount) DELAY_WaitUS(settings.rfiCompAmount);
	for (m = 128; m > 0; m >>= 1) {
		if (byt & m) {
			gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_SDA);
		} else {
			gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_SDA);
		}
		gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_SCL);
		gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_SCL);
	}
}

void lcdSend(const u8 data, const u8 cmd)
{
	if(cmd) gpio_bits_reset(GPIOF, BOARD_GPIOF_LCD_DCX);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_LCD_CS);
	lcdSendByte(data);
	gpio_bits_set(GPIOC, BOARD_GPIOC_LCD_CS);
	if(cmd) gpio_bits_set(GPIOF, BOARD_GPIOF_LCD_DCX);
}

void lcdSend16(const u16 data)
{
	gpio_bits_reset(GPIOC, BOARD_GPIOC_LCD_CS);
	lcdSendByte(C16(data)->bytes.hi);
	lcdSendByte(C16(data)->bytes.lo);
	//lcdSendByte(data >> 8);
	//lcdSendByte(data & 0xFF);
	gpio_bits_set(GPIOC, BOARD_GPIOC_LCD_CS);
}

void lcdRegion(const u8 x, u8 y, const u8 w, const u8 h)
{
    y=((u8)98+LCD_VADJUST)-y;
	lcdSend(ST7735S_CMD_CASET, 1);
	lcdSend16(y-h);
	lcdSend16(y-1);
	lcdSend(ST7735S_CMD_RASET, 1);
	lcdSend16(x);
	lcdSend16(x+w-1);
	lcdSend(ST7735S_CMD_RAMWR, 1);
}

void lcdFill(const u8 x, const u8 y, const u8 w, const u8 h, const u16 col)
{
    u16 cnt;
    lcdRegion(x,y,w,h);
    cnt=w*h;
    while(cnt--)
        lcdSend16(col);
}

void lcdFillFromEeprom(const u8 x, const u8 y, const u8 w, const u8 h, const u32 addr)
{
    lcdRegion(x,y,w,h);
    eepromReadToDisplay(addr, (u16)w*(u16)h*2);
}

void lcdCls(void)
{
    lcdFill(0,0,160,98,0);
}

const u8 lcdInitSeq[] = { 
	LCD_CMD, (ST7735S_CMD_SLPOUT),
	LCD_PAUSE, (120),
	LCD_CMD, (ST7735S_CMD_FRMCTR1),
	(0x05),
	(0x3C),
	(0x3C),
	LCD_CMD, (ST7735S_CMD_FRMCTR2),
	(0x05),
	(0x3C),
	(0x3C),
	LCD_CMD, (ST7735S_CMD_FRMCTR3),
	(0x05),
	(0x3C),
	(0x3C),
	(0x05),
	(0x3C),
	(0x3C),
	LCD_CMD, (ST7735S_CMD_INVCTR),
	(0x03),
	LCD_CMD, (ST7735S_CMD_PWCTR1),
	(0x28),
	(0x08),
	(0x04),
	LCD_CMD, (ST7735S_CMD_PWCTR2),
	(0xC0),
	LCD_CMD, (ST7735S_CMD_PWCTR3),
	(0x0D),
	(0x00),
	LCD_CMD, (ST7735S_CMD_PWCTR4),
	(0x8D),
	(0x2A),
	LCD_CMD, (ST7735S_CMD_PWCTR5),
	(0x8D),
	(0xEE),
	LCD_CMD, (ST7735S_CMD_VMCTR1),
	(0x1A),
	LCD_CMD, (ST7735S_CMD_MADCTL),
	(0xc8),
	LCD_CMD, (ST7735S_CMD_GMCTRP1),
	(0x04),
	(0x22),
	(0x07),
	(0x0A),
	(0x2E),
	(0x30),
	(0x25),
	(0x2A),
	(0x28),
	(0x26),
	(0x2E),
	(0x3A),
	(0x00),
	(0x01),
	(0x03),
	(0x13),
	LCD_CMD, (ST7735S_CMD_GMCTRN1),
	(0x04),
	(0x16),
	(0x06),
	(0x0D),
	(0x2D),
	(0x26),
	(0x23),
	(0x27),
	(0x27),
	(0x25),
	(0x2D),
	(0x3B),
	(0x00),
	(0x01),
	(0x04),
	(0x13),
	LCD_CMD, (ST7735S_CMD_COLMOD),
	(0x05),
};

void lcdInit(void)
{
    u8 i, j;

    gpio_bits_set(GPIOF, GPIO_PINS_0);
	DELAY_WaitMS(1);

	gpio_bits_reset(GPIOF, GPIO_PINS_0);
	DELAY_WaitMS(1);

	gpio_bits_set(GPIOF, GPIO_PINS_0);
	DELAY_WaitMS(120);

    i=0, j=0;
    while(j!=LCD_SEQ_END)
    {
        j = lcdInitSeq[i++];
        switch(j)
        {
            case LCD_PAUSE:
                DELAY_WaitMS(lcdInitSeq[i++]);
                break;
            case LCD_CMD:
                lcdSend(lcdInitSeq[i++], 1);
                break;
            default:
                lcdSend(j, 0);
                break;
            case LCD_SEQ_END:
                break;
        }
    }
    lcdFillFromEeprom(0,0,160,98, LOGOBASE);
    lcdBL(1);
    //gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_RESX);
}

void lcdBL(const u8 dc)
{
	KEY_LED = dc;
	if(dc)
	{
		//gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_RESX);
		lcdTimer = settings.lcdTimeout;
	}
	else {
		//gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_RESX);
	}
	lcdSleep(!settings.dimmer && !dc);
	//lcdSend(dc?ST7735S_CMD_DISPON : ST7735S_CMD_DISPOFF, 1);
}

void lcdGamma(void)
{
    lcdSend(0x26, 1);
    lcdSend(1<<settings.gamma, 0);
}

void lcdInvert(const u8 inverted)
{
    lcdSend(inverted?0x21:0x20, 1);
}

void lcdSleep(const u8 asleep)
{
    lcdSend(asleep?0x10:0x11, 1);
    lcdSend(asleep?0x28:0x29, 1);
}

/*
void lcdScrollTest(void)
{
	u16 t;
	t=0;
	lcdSend(ST7735S_CMD_SCRLAR, 1);
	lcdSend16(23);
	lcdSend16(50);
	while(1)
	{
		lcdSend(ST7735S_CMD_VSCSAD, 1);
		lcdSend16(t);
		if (t >= 98-22) {
			t = 0;
		} else {
			t++;
		}
		delay(10);
	}
}
*/

