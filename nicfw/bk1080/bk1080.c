
static const uint16_t InitTable[] = {
	0x0008, 0x1080, 0x0201, 0x0000,
	0x40C0, 0x0A10, 0x302E, 0x02FF,
	0x5B11, 0x0000, 0x411E, 0x0000,
	0xCE00, 0x0000, 0x0000, 0x1000,
	0x3197, 0x8000, 0x13FF, 0x9852,
	0x0000, 0x0000, 0x0008, 0x0000,
	0x51E1, 0x28DC, 0x2645, 0x00E4,
	0x1CD8, 0x3A50, 0xEAF0, 0x3000,
	0x0000, 0x0000,
};

static void SDA_SetMode(const u8 mode)
{
	gpio_init_type init;
	gpio_default_para_init_ex(&init);
	init.gpio_pins = BOARD_GPIOB_BK1080_SDA;
	init.gpio_mode = mode ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
    if(mode)
	    init.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	init.gpio_pull = GPIO_PULL_DOWN;
	gpio_init(GPIOB, &init);

}

static void SDA_SetOutput(void)
{
    SDA_SetMode(1);
}

static void SDA_SetInput(void)
{
    SDA_SetMode(0);
}

static void fmtPutByte(const u8 byt)
{
    u8 m;
	for (m = 128; m; m>>=1) {
		if (byt & m) {
			gpio_bits_set(GPIOB, BOARD_GPIOB_BK1080_SDA);
		} else {
			gpio_bits_reset(GPIOB, BOARD_GPIOB_BK1080_SDA);
		}
		gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
		gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);
	}
}


static void SendCommand(uint8_t Command, uint8_t Mode)
{
	SDA_SetOutput();

	gpio_bits_set(GPIOB, BOARD_GPIOB_BK1080_SDA);
	gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK1080_SDA);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);

    fmtPutByte(0x80);

	gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);

    fmtPutByte((Command<<1)|Mode);
}

static void fmtToggle(void)
{
	SDA_SetOutput();

	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK1080_SDA);
	DELAY_WaitUS(1);
	gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
	DELAY_WaitUS(1);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);    
}


static uint8_t RecvByte(void)
{
	uint8_t Value;
	uint8_t i;

    fmtToggle();
	gpio_bits_set(GPIOB, BOARD_GPIOB_BK1080_SDA);
	DELAY_WaitUS(1);

	SDA_SetInput();

	Value = 0;
	for (i = 128; i; i>>=1) {
		gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);
		DELAY_WaitUS(1);
		if (gpio_input_data_bit_read(GPIOB, BOARD_GPIOB_BK1080_SDA)) {
			Value |= i;
		}
		gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
		DELAY_WaitUS(1);
	}


	SDA_SetOutput();

	gpio_bits_set(GPIOB, BOARD_GPIOB_BK1080_SDA);
	DELAY_WaitUS(1);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);
	DELAY_WaitUS(1);

	return Value;
}

static void SendByte(uint8_t Value)
{
    fmtToggle();
    fmtPutByte(Value);
}

static void StopI2C(void)
{
	gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SCL);
	DELAY_WaitUS(1);
	gpio_bits_set(GPIOB, BOARD_GPIOB_BK1080_SDA);
}

static void RenameLater(void)
{
    fmtToggle();

	DELAY_WaitUS(1);

	StopI2C();
}

//

void BK1080_Init(void)
{
	uint8_t Values[68];
	uint8_t i;
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SEN);
	DELAY_WaitMS(125);
	for (i = 0; i < 34; i++) {
        ((U16*)Values)[i].bytes.lo = ((U16*)InitTable)[i].bytes.hi;
        ((U16*)Values)[i].bytes.hi = ((U16*)InitTable)[i].bytes.lo;
	}
	BK1080_WriteRegisters(0x00, Values, sizeof(Values));
	DELAY_WaitMS(125);
	Values[(0x19 * 2) + 1] &= 0x7F;
	BK1080_WriteRegisters(0x19, &Values[0x19 * 2], 2);
	Values[(0x19 * 2) + 1] |= 0x80;
	BK1080_WriteRegisters(0x19, &Values[0x19 * 2], 2);
	DELAY_WaitMS(60);
}

void BK1080_Tune(u32 freq)
{
    uint8_t Values[4];
    freq /= 10000;
    C32(freq)->words.lo -= 760;    
	Values[0] = 0x0A;
    Values[1] = 0x50;
	BK1080_WriteRegisters(0x05, Values, 2);
	BK1080_ReadRegisters(0x02, Values, 4);	
	Values[0] &= 0xFE; // Clear Seek bit
	Values[2] = 0;
	Values[3] = (C32(freq)->words.lo >> 0) & 0xFF;
	BK1080_WriteRegisters(0x02, Values, 4);
	Values[2] = 0x80 | ((C32(freq)->words.lo >> 8) & 0xFF);
	Values[3] = (C32(freq)->words.lo >> 0) & 0xFF;
	BK1080_WriteRegisters(0x02, Values, 4); 
}

void BK1080_WriteRegisters(uint8_t Index, const uint8_t *pValues, uint8_t Size)
{
	uint8_t i;

	SendCommand(Index, 0);

	for (i = 0; i < Size; i++) {
		SendByte(pValues[i]);
	}

	RenameLater();
}

void BK1080_ReadRegisters(uint8_t Index, uint8_t *pValues, uint8_t Size)
{
	uint8_t i;

	SendCommand(Index, 1);

	for (i = 0; i < Size; i++) {
		pValues[i] = RecvByte();
	}

	StopI2C();
}

void fmtSaveLast(channelInfo* vfo)
{
    settings.lastFmtFreq = vfo->rxFreq.value;
}

const planInfo* getFmtPlan(void)
{
    return &plans[fmtPlan];
}

const u8 testBeforeStart(const channelInfo* vfo)
{
    return vfo->rxFreq.value<getFmtPlan()->startFreq;
}

const u8 testPastEnd(const channelInfo* vfo)
{
    return vfo->rxFreq.value>=getFmtPlan()->endFreq;
}

void fmtMute(const u8 mute)
{
	uint8_t Values[2];
	Values[0] = 0x0A;
	Values[1] = mute ? 0x10 : 0x1F; //Volume | 0x10;
	BK1080_WriteRegisters(0x05, Values, 2);
	if(!mute) POW_2822(1);
}

void fmtEqualize(channelInfo* vfo)
{    
    if(testBeforeStart(vfo)) 
    {
        vfo->rxFreq.value = getFmtPlan()->endFreq;
        vfo->rxFreq.value--;
    }
    else
    if(testPastEnd(vfo))
    {
        vfo->rxFreq.value = getFmtPlan()->startFreq;
    }
    vfo->rxFreq.value /= 10000;
    vfo->rxFreq.value *= 10000;
    vfo->txFreq.value = vfo->rxFreq.value;    
}

void fmtSetFreq(const channelInfo* vfo)
{
    fmtMute(1);
    fmtEqualize((channelInfo*)vfo);
    fmtSaveLast((channelInfo*)vfo);
    BK1080_Tune(vfo->rxFreq.value);
    delay(50);
    fmtTick();
}

static u8 fmtSNR;

const u8 fmtCheckSignal(void)
{
	uint8_t Values[8];
	uint16_t Deviation;

	BK1080_ReadRegisters(0x07, Values, 8);

	Deviation = (Values[0] << 4) | ((Values[1] >> 4) & 0xF);

	// AFC railed
	if (Values[6] & 0x10U) {
		return 0;
	}


    fmtSNR=Values[1] & 0xF;
	// SNR < 2
	if (fmtSNR < 2) {
		return 0;
	}

	if (Deviation >= 280 && Deviation < 3816) {
		return 0;
	}

	return Values[7];
}


void fmtStart(const u8 stealth)
{	
    if(!fmtActive && !fmtStealth)
    {
		if(stealth)
		{
			if(!VFOX[!settings.activeVfo].isFmTuner)
			{
				return;
			}
		}		
        fmtActive = !stealth;
		fmtStealth = stealth;
        BK1080_Init();
		if(stealth)
		{
			fmtSetFreq(&VFO[!settings.activeVfo]);
		}
		else
		{
        	fmtMute(settings.squelch);
		}
    }
}

void fmtTick(void)
{
    u8 sig;
    if(!POW2822_)
        POW_2822(1);
    sig = fmtCheckSignal();

    radioSetLED(0, sig); // led lag
    displayDrawMeter( sig , 2);
    displayDrawExNoise((15-fmtSNR)<<3 , 0);

    if(settings.squelch)
        fmtMute(!sig);
}

void fmtDisable(void)
{
    if(fmtActive || fmtStealth)
    {
        fmtMute(1);
        fmtActive=0;
        gpio_bits_reset(GPIOB, BOARD_GPIOB_BK1080_SDA);
        gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);
        gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SEN);        
		if(!fmtStealth) {
        	displayDrawMeter(0, 3);
		}
		fmtStealth = 0;
    }
}
