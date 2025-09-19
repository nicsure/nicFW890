

const u8 eepromOut(const u8 data)
{
    u8 received, m;
    received = 0;
    for(m = 128; m; m >>= 1)
    {
        gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_CLK);
        if(data & m)
            gpio_bits_set(GPIOB, BOARD_GPIOB_SF_MISO);
        else
            gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_MISO);
        gpio_bits_set(GPIOB, BOARD_GPIOB_SF_CLK);
        if (gpio_input_data_bit_read(GPIOA, BOARD_GPIOA_SF_MOSI))
			received |= m;
    }
    gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_CLK);
    return received;
}

const u8 eepromIn(void)
{
    return eepromOut(0xff);
}

void eepromCmd(const u8 cmd)
{
	gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_CS);
	eepromOut(cmd);
}

void eepromCmdAddr(const u8 cmd, const u32 addr)
{
    eepromCmd(cmd);
	eepromSendAddr(addr);    
}

void eepromSetCS(void)
{
	gpio_bits_set(GPIOB, BOARD_GPIOB_SF_CS);
}

void eepromWriteMode(void)
{
    eepromCmd(0x06);
    eepromSetCS();
}

const u8 eepromStatus(void)
{
	u8 status;
    eepromCmd(0x05);
	status = eepromIn();
    eepromSetCS();
	return status;
}

void eepromWait(void)
{
	while (eepromStatus() & 1U) { }
}

void eepromSendAddr(const u32 addr)
{
	eepromOut(C32(addr)->bytes.byte2);
	eepromOut(C32(addr)->bytes.byte1);
	eepromOut(C32(addr)->bytes.byte0);
}

void eepromInit(void)
{
	gpio_bits_set(GPIOB, BOARD_GPIOB_SF_CS);
	eepromIn();
}


static u32 bufferedPage;
static u8 pageBuffer[0x1000];
static u8 dirtyPage;

void eeprom_ErasePage(uint32_t Page)
{
	eepromWriteMode();
	eepromWait();
	gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_CS);
    eepromOut(0x20);
	eepromOut((Page >> 16) & 0xFF);
	eepromOut((Page >>  8) & 0xFF);
	eepromOut((Page >>  0) & 0xFF);
	gpio_bits_set(GPIOB, BOARD_GPIOB_SF_CS);
	eepromWait();
}

void eeprom_Commit(void)
{
    if(dirtyPage && bufferedPage)
    {
        eeprom_Burn(pageBuffer, bufferedPage);
    }
    dirtyPage=0;
}


// note, ensure writes DO NOT span page boundaries 
void eeprom_Write(const u8 *data, const u32 addr, u16 size)
{
    u32 pageAddr;
    u32 offset;

    if(!initComplete || loopMode) return;

    pageAddr = addr&0xFFFFF000U;
    offset = addr&0xFFF;

    if( (offset+size) > 0x1000)
    {
        while(1)
        {
            delay(50);
            gpio_bits_set(GPIOA, BOARD_GPIOA_LED_RED);
            delay(50);
            gpio_bits_reset(GPIOA, BOARD_GPIOA_LED_RED);
        }
    }
    if(bufferedPage != pageAddr)
    {
        eeprom_Commit();
        bufferedPage = pageAddr;
        eepromRead(pageBuffer, pageAddr, 0x1000);
    }
    while(size--)
    {
        if(pageBuffer[offset+size] != data[size]) {
            dirtyPage = 1;
        }
        pageBuffer[offset+size] = data[size];
    }
    eepromTimer=5;
}

void eeprom_Burn(const u8 *data, u32 addr)
{
    u8 i;
    u16 j;
    u16 size;
    size = 0x1000;
    j=0;
    size&=0xff80;
    voiceDisable();  
    eeprom_ErasePage(addr);
    while(size)
    {
        size-=0x80;
        eepromWriteMode();
        eepromCmdAddr(0x02, addr);
        for (i = 0; i != 0x80; i++) {
            eepromOut(data[j++]);
        }
        eepromSetCS();
        eepromWait();
        addr+=0x80;
    }
    voiceEnable();     
}

void eepromReadUnsafe(u8* data, const u32 addr, const u16 size)
{
	u16 i;
    eepromCmdAddr(0x03, addr);
	for (i = 0; i != size; i++)
        data[i] = eepromIn();
    eepromSetCS();
}

void eepromRead(u8* data, const u32 addr, const u16 size)
{
    voiceDisable();
    eepromReadUnsafe(data, addr, size);
    voiceEnable();
}

void eepromReadToDisplay(const u32 addr, const u16 size)
{
	u16 i;
    u16 dw;
    voiceDisable();
    eepromCmdAddr(0x03, addr);
	for (i = 0; i != size; i+=2)
    {
        C16(dw)->bytes.lo = eepromIn();
        C16(dw)->bytes.hi = eepromIn();
        lcdSend16(dw);
    }
    eepromSetCS();
    voiceEnable();
}



