

void bkDataMode(const gpio_mode_type mode)
{
    gpio_init_type init;
    gpio_default_para_init_ex(&init);
    init.gpio_pins = BOARD_GPIOB_BK4819_SDA;
    init.gpio_mode = mode;
    init.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init(GPIOB, &init);
}

void bkDelay(void)
{
    volatile u8 delay;
    delay = 10;
	while (delay--) {
	}
}

void bkSend(const u8 data)
{
	u8 m;
    bkDataMode(GPIO_MODE_OUTPUT);
	for (m = 128; m; m>>=1)
    {
		gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
		if (data & m)
			gpio_bits_set(GPIOB, BOARD_GPIOB_BK4819_SDA);
        else
			gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SDA);
        bkDelay();
		gpio_bits_set(GPIOB, BOARD_GPIOB_BK4819_SCL);
		bkDelay();
	}
}

const u16 bkRecv(void)
{
	u16 m;
	u16 data;
    data = 0;
	bkDataMode(GPIO_MODE_INPUT);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
    bkDelay();
	for (m = 32768; m; m>>=1)
    {
		gpio_bits_set(GPIOB, BOARD_GPIOB_BK4819_SCL);
		if (gpio_input_data_bit_read(GPIOB, BOARD_GPIOB_BK4819_SDA))
			data |= m;
		bkDelay();
		gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
		bkDelay();
	}
	return data;
}

U16* bkGetReg(const u8 reg)
{
    U16* bk;
    bk = &bkReg[reg];
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_CS);
	bkSend(reg|0x80);
	bkDelay();
	bk->value = bkRecv();
	gpio_bits_set(GPIOB, BOARD_GPIOB_BK4819_CS);
	return bk;
}

void bkSetReg(const u8 reg, const u16 data)
{
    bkReg[reg].value = data;
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_CS);
	bkSend(reg);
	bkSend(C16(data)->bytes.hi);
	bkSend(C16(data)->bytes.lo);
	gpio_bits_set(GPIOB, BOARD_GPIOB_BK4819_CS);
}

void bkAndReg(const u8 reg, const u16 and)
{
    bkSetReg(reg, bkGetReg(reg)->value & and);
}

void bkOrReg(const u8 reg, const u16 or)
{
    bkSetReg(reg, bkGetReg(reg)->value | or);
}

void bkSendSeq(const u8* sequence)
{
    u8 cnt = 0, reg;
    U16 val;
    while(1)
    {
        reg = sequence[cnt++];
        switch(reg)
        {
            case 0xff:
                return;
            case 0xfe:
                DELAY_WaitMS(sequence[cnt++] * 10);
                break;
            default:
                val.bytes.hi = sequence[cnt++];
                val.bytes.lo = sequence[cnt++];
                bkSetReg(reg, val.value);
                break;
        }
    }
}

void bkSet30(const u16 reg30)
{
    bkSetReg(0x30, reg30);
}

void bkAfDacOn(void)
{
    bkSet30(0xBFF1); 
}

void bkAfDacOff(void)
{
    bkSet30(0xBDF1); 
}


void bkSetFreqRegs(s32 freq)
{
    if(!(freq%2600000))
        freq+=1000;
    freq += ((freq >> 17) * (s32)tuning.xtal671) >> 9;
    bkSetReg(0x39, C32(freq)->words.hi);
    bkSetReg(0x38, C32(freq)->words.lo); 
}

void bkSetFreq(const u32* freq)
{
    bkSet30(0);
    bkSetFreqRegs(*freq);    
    if(squelchOpen)
        bkAfDacOn();
    else
        bkAfDacOff();
}

void bkResetAgcTables(void)
{
    settings.gain0 = 24;
    settings.gain1 = 32;
    settings.gain2 = 37;
    settings.gain3 = 40;
}

void bkSetGain(const u8 agc)
{    
    //u16 gain;
    //gain = gainTable[agc];
    bkSetReg(0x14, 0x0019);
    bkSetReg(0x13, gainTable[agc ? agc : settings.gain3]);
    bkSetReg(0x12, gainTable[agc ? agc : settings.gain2]);
    bkSetReg(0x11, gainTable[agc ? agc : settings.gain1]);
    bkSetReg(0x10, gainTable[agc ? agc : settings.gain0]);
    //bkSetReg(0x13, agc?0x03be:gain);
    //bkSetReg(0x12, agc?0x037b:gain);
    //bkSetReg(0x11, agc?0x027b:gain);
    //bkSetReg(0x10, agc?0x007a:gain);
}

void bkSetBandwidth(const u8 narrow)
{
    bkSetReg(0x43, currentModulation==2?0x0028:(narrow?0x4048:0x3028));
}

void bkSetTxDeviation(u16 deviation, const u8 narrow)
{
    deviation*=19;
    if(narrow) deviation--;;
    deviation|=0x3000;
    bkSetReg(0x40, deviation);    
}

const u16 bkGetRssi(void)
{
    U16* reg = bkGetReg(0x67);
    reg->bytes.hi &= 1;
    return reg->value;
}

const u8 bkGetExNoise(void)
{
    U16* reg = bkGetReg(0x65);
    reg->bytes.hi = 0;
    reg->bytes.lo &= 0x7f;
    return reg->bytes.lo;
}

void bkSetMicGain(const u8 micGain)
{
    bkSetReg(0x7d, 0xe940 | micGain);  
}

void bkSetRxExpanderAndVox(const u8 exp, const u8 vox)
{
    U16 bkTemp;
    if(vox)
    {
        u8 v = 16-vox;
        bkTemp.bytes.hi = 0xa0;
        bkTemp.bytes.lo = 0x08 * v;
        bkSetReg(0x46, bkTemp.value);
        bkTemp.bytes.hi = 0x18;
        bkTemp.bytes.lo = 0x04 * v;        
        bkSetReg(0x79, bkTemp.value);
    }
    bkTemp.bytes.hi = 0;
    bkTemp.bytes.lo = (vox?4:0)|(exp?8:0); 
    bkSetReg(0x31, bkTemp.value);
    bkTemp.bytes.hi = 0x2b | (exp<<6);
    bkTemp.bytes.lo = 0x38;
    bkSetReg(0x28, bkTemp.value);
}

void bkSetAfFilters(const u8 aff)
{
    U16 bkTemp;
    bkTemp.bytes.hi = aff==8?7:aff;
    bkTemp.bytes.lo = aff==8?7:0;
    bkSetReg(0x2b, bkTemp.value); 
}

void bkSetModulation(const u8 mod, const u8 remember)
{
    U16 bkTemp;
    if(remember)
        currentModulation = mod;
    bkTemp.bytes.lo = 0x40;
    switch(mod)
    {
        default: bkTemp.bytes.hi = 0x60; break; // mute
        case 1: bkTemp.bytes.hi = 0x61; break; // fm
        case 2: bkTemp.bytes.hi = 0x67; break;// am    
        case 3: bkTemp.bytes.hi = 0x65; break;// usb
        case 4: bkTemp.bytes.hi = 0x63; break;// tones
    }
    bkSetReg(0x47, bkTemp.value); 
}

void bkInit(void)
{
    bkSendSeq(bkInitSeq);
}

void bkToneFreq(const u16 fr, const u8 channel)
{
    bkTone[channel].value = (u32)fr;
    bkTone[channel].value *= 103244l;
    bkTone[channel].value += 5000l;
    bkTone[channel].value /= 10000l;
}

void bkPlayTone(const u16 lefthz, const u16 righthz)
{
    tonePlaying = 1;
    bkSetModulation(4, 1);
    DELAY_WaitMS(5);
    POW_2822(0);
    bkToneFreq(lefthz, 1);
    bkToneFreq(righthz, 0);
    bkSetReg(0x71, bkTone[0].words.lo); 
    bkSetReg(0x72, bkTone[1].words.lo); 
    bkSetReg(0x70, settings.dtmfDev | (((u16)settings.dtmfDev*180)&0x7f00) | 0x8080);
    bkSetReg(0x30, 0xc3fa);
    DELAY_WaitMS(5);
    POW_2822(1);
}

void bkStopTone(void)
{
    tonePlaying = 0;
    bkSetModulation(0, 1);
    DELAY_WaitMS(5);
    POW_2822(0);
    DELAY_WaitMS(5);
    bkToneFreq(0,0);
    bkToneFreq(0,1);
    bkSetReg(0x70, 0);
    bkSetReg(0x30, 0xc1fe); 
}

void bkApplyActiveVfo(void)
{
    bkApplyVfo(settings.activeVfo);
}

void bkApplyVfo(const u8 vfoPosition)
{
    channelInfo* vfo;
    channelXtra* vfox;
    appliedVfo = vfoPosition;
    vfo = &(VFO[vfoPosition]);
    vfox = &(VFOX[vfoPosition]);
    if(!settings.disableFmt && plans[vfox->rxplan].bits.bandwidth==5)
    {
        bkSet30(0);
        bkSetFreqRegs(deadFreq);
        bkSetGain(1);
        squelchOpen=0;
        if(!fmtActive)
        {
            displayVfoRefresh(vfoPosition, 1);
        }
        POW_2822(1);
        fmtStart(0); // to be implemented : fmtuner
        fmtSetFreq(vfo);
        vfox->isFmTuner=1;
        return;
    }
    else
    {
        if(vfoPosition == settings.activeVfo && fmtActive)
        {
            fmtDisable(); // to be implemented : fmtuner
        }
        vfox->isFmTuner=0;
    }
    bkSendSeq(bkReceiveSeq);    
    bkSetBandwidth(vfox->rxBandwidth);
    bkSetModulation(vfox->modulation, 1);
    bkSetAfFilters(settings.afFilters);
    radioSetFilters(1, vfox->rxIsVhf);
    bkSetRxExpanderAndVox(0, settings.vox);
    bkSetGain(settings.rfGain);
    if(vfox->modulation == 1) // FM
    {
        bkAndReg(0x73, 0xc7ef); // clear bit 4, enable AFC
        bkOrReg(0x73, 0x3800); // set min range
    }
    else // AM, USB
        bkOrReg(0x73, 0x0010); // set bit 4, disable AFC
    bkSetReg(0x3D, vfox->modulation==3 ? 0x0000:ifTable[settings.ifFreq]); // gain
    bkSetReg(0x4A, vfox->modulation==2 ? 0x5448:0x5450);
    stSetTone(vfo->rxSubTone.value);
    bkSetReg(0x37, 0x1F0F);
    rssiGetFloor(&(vfo->rxFreq.value));
    bkSetFreq(&(vfo->rxFreq.value));
}

void bkPaBias(u8 bias)
{
    U16 bkTemp;
    bkTemp.bytes.hi = bias; //bias;
    bkTemp.bytes.lo = 0x86;// | ((bias+1)&63);
	bkSetReg(0x36, bkTemp.value);
}

void bkInitXmit(void)
{
    radioSetLED(1,0);
    xmitActive=1;
    txTimer = settings.txTimeout;
    squelchOpen=0;
    if(!wlCloneTrigger)
    {
        displayVfo(settings.activeVfo, 1);
    }
    displayDrawMeter(ACTIVE_VFOX.txPower, 1);
    displayDrawExNoise(0, 1);
    radioSetFilters(0, ACTIVE_VFOX.txIsVhf);
    POW_2822(0);
    DELAY_WaitMS(5);
    bkSendSeq(transSeq);
    bkSetBandwidth(ACTIVE_VFOX.txBandwidth);
    bkSetMicGain(settings.micGain);
    bkSetTxDeviation(settings.txDeviation, ACTIVE_VFOX.txBandwidth);
    stSetTone(ACTIVE_VFO.txSubTone.value);
    bkSetFreqRegs(ACTIVE_VFO.txFreq.value);
    actualPower = ACTIVE_VFOX.txPower-1;
    if(actualPower)
    {
        gpio_bits_set(GPIOB, BOARD_GPIOB_TX_BIAS_LDO);
        bkPaBias(actualPower);
    }
    DELAY_WaitMS(10);
    bkSet30(0xC1FE);        
    bkSetReg(0x50, 0x3B20);
    DELAY_WaitMS(5);
    if(playDtmfOnPTT)
    {
        dtmfPlaySeq(&manualSeq, 0);
    }
    else
    if(ACTIVE_VFO.bits.pttID&1)
    {
        dtmfPlayPTTID();
    }
    playDtmfOnPTT=0;
    MICROPHONE(1);
}

void bkEndXmit(void)
{
    MICROPHONE(0);
    if(ACTIVE_VFO.bits.pttID&2)
    {
        dtmfPlayPTTID();
    }    
    if(settings.ste & 2)
    {
        stSetTone(550);
        DELAY_WaitMS(500);
    }
    radioSetLED(0, 0);

    bkPaBias(0);
    gpio_bits_reset(GPIOB, BOARD_GPIOB_TX_BIAS_LDO);
    bkSet30(0);
    xmitActive=0;
    displayVfo(settings.activeVfo, 1);
    displayDrawMeter(0, 3);
    displayDrawExNoise(0, 0); 
    bkApplyActiveVfo();
}

void bkXmitTick(void)
{
    u8 modLevel;
    u8 key;
    if(settings.txModMeter)
    {
        modLevel = bkGetReg(0x6f)->bytes.lo & 0x7f;
        modLevel = modLevel > 55 ? modLevel - 55 : 0;
        modLevel = modLevel < 40 ? modLevel*3 : 120;
        displayDrawExNoise(modLevel, 1);         
    }
    key = keypadPressed;
    if(tonePlaying)
    {
        if(key==KEY_NONE)
            bkStopTone();
    }
    else
    {
        if(key<16)
            dtmfPlay(key);
        else
        if(key==KEY_FLSH)
            bkPlayTone(settings.repeaterTone, 0);        
    }
}


const u8 bkSubToneDetected(void)
{
    return bkGetReg(0x0c)->bytes.hi & 0x44;
}

const u8 bk55Detected(void)
{
    return bkGetReg(0x0c)->bytes.hi & 0x08;
}

void bkAmFix(void)
{
    u16 rssi;
    u16 amf;
    if(currentModulation==2 && settings.amFix)
    {
        amf = settings.amFix>6 ? (u16)settings.amFix*2 : 12;
        rssi = bkGetRssi();
        if(rssi>amf+10) { amFixGain--; }
        else if(rssi<amf-10)  { amFixGain++; }
        if(!amFixGain) { amFixGain = 1; }
        else if(amFixGain>42) { amFixGain = 42; }
        bkSetGain(amFixGain);
    }
}
