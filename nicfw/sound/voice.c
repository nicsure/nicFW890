
void voiceInit(void)
{
    tmr_para_init_ex0_type init;
	tmr_para_init_ex0(&init);
	init.period = 450;
	init.division = 18;
	init.clock_division = TMR_CLOCK_DIV1;
	init.count_mode = TMR_COUNT_UP;
	tmr_reset_ex0(TMR1, &init);
	tmr_output_channel_switch_set_ex(TMR1, 1);
	TMR1->iden |= TMR_OVF_INT;
	TMR1->ctrl1_bit.tmren = 1;
    nvic_irq_enable(TMR1_BRK_OVF_TRG_HALL_IRQn, 2, 2);
}

void voicePlay(const u8 id)
{
    voicePlay3(id, 0, 0);
}

void voicePlay3(const u8 id1, const u8 id2, const u8 id3)
{
    if(xmitActive || fmtActive || settings.keyTones != 3) return;
    POW_2822(1);
    sampleAddress1=(u32)id1 << 14;  
    if(!sampleAddress1) sampleAddress1=1;
    sampleAddress2=(u32)id2 << 14;  
    sampleAddress3=(u32)id3 << 14;  
    samplePlaying = 1;
}

static u8 dimCount;
// lcdBrightness dimmer
void HandleLCDDimming(void)
{
    if(KEY_LED)
    {
        if(dimCount <= settings.lcdBrightness) {
            gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_RESX);
        } else {
            gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_RESX);
        }
    }
    else
    {
        if(settings.dimmer && dimCount <= (settings.dimmer-1)) {
            gpio_bits_set(GPIOA, BOARD_GPIOA_LCD_RESX);
        } else {
            gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_RESX);
        }
    }
    dimCount++;
    if(dimCount>=29) {
        dimCount = 0;
    }
}

void HandlerTMR1_BRK_OVF_TRG_HALL(void)
{
    u8 samp;
    u32 beepCounter, beepUS;
    volatile u32* cSample;
    TMR1->ists = ~TMR_OVF_FLAG;
    
    HandleLCDDimming();

    if(vtimerDisable) return;

    if(beepDuration)
    {
        beepCounter = 0;
        beepUS = (u32)beepDuration << 14;
        feedDimmer=1;
        while(beepCounter < beepUS)
        {
            PWM_Pulse(200); // set DAC to low state
            DELAY_WaitUS(beepWaveLength); // pause to create wavelength
            PWM_Pulse(0); // set DAC to high state
            DELAY_WaitUS(beepWaveLength); // pause again
            beepCounter += beepWaveLength<<1;
        }
        feedDimmer=0;
        beepDuration = 0;
    }

    cSample=&sampleAddress1;
    if(!(*cSample)) {
        cSample=&sampleAddress2;
        if(!(*cSample)) {
            cSample=&sampleAddress3;
        }
    }

    if(*cSample)
    {
        samplePlaying = 1;
        eepromReadUnsafe(&samp, (*cSample)++, 1);
        if(!samp)
        {
            (*cSample)=0;
            previousSamp = 0x80u;
        }
        else
        {
            if(previousSamp!=samp)
            {
                PWM_Pulse((samp*165)/50);
                previousSamp = samp;
            }
        }
    }
    else
    {
        samplePlaying = 0;
    }
}

void voiceDisable(void)
{
    vtimerDisable = 1;
}

void voiceEnable(void)
{
    vtimerDisable = 0;
}


void voiceWait(void)
{
    while(samplePlaying) { }
}