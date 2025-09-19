
typedef struct {
	confirm_state sequence_mode;
	confirm_state repeat_mode;
	uint8_t ordinary_channel_length;
	adc_ordinary_trig_select_type trigger_select;
} adc_init_ex_type;

volatile uint16_t gBatteryAdcValue;
uint8_t gBatteryVoltage;

//

static void adc_para_init_ex(adc_init_ex_type *init)
{
	init->sequence_mode = FALSE;
	init->repeat_mode = FALSE;
	init->trigger_select = ADC12_ORDINARY_TRIG_TMR1CH1;
	init->ordinary_channel_length = 1;
}

static void adc_base_config_ex(adc_type *adc, const adc_init_ex_type *init)
{
	adc->ctrl1_bit.sqen = init->sequence_mode;
	adc->ctrl2_bit.rpen = init->repeat_mode;
	adc->ctrl2_bit.octesel_l = init->trigger_select;
	// TODO: Ignoring octesel_h until Artery replies to issue.
	adc->osq1_bit.oclen = init->ordinary_channel_length - 1;
}

static void adc_ordinary_conversion_trigger_enable(adc_type *adc, confirm_state new_state)
{
	adc->ctrl2_bit.octen = new_state;
}

static void adc_software_trigger_enable(adc_type *adc, confirm_state new_state)
{
	adc->ctrl2_bit.ocswtrg = new_state;
	adc->ctrl2_bit.octen = new_state;
}

//

void BATTERY_Init(void)
{
	adc_init_ex_type init_adc;

	DMA1_CHANNEL1->ctrl_bit.chen = FALSE;
	DMA1_CHANNEL1->ctrl = 0;

	DMA1->clr |= 0xF;

	DMA1_CHANNEL1->ctrl &= 0xBFEF;
	DMA1_CHANNEL1->ctrl |= DMA_DIR_PERIPHERAL_TO_MEMORY;

	DMA1_CHANNEL1->ctrl_bit.chpl =  DMA_PRIORITY_HIGH;
	DMA1_CHANNEL1->ctrl_bit.mwidth = DMA_MEMORY_DATA_WIDTH_HALFWORD;
	DMA1_CHANNEL1->ctrl_bit.pwidth = DMA_PERIPHERAL_DATA_WIDTH_HALFWORD;
	DMA1_CHANNEL1->ctrl_bit.mincm = TRUE;
	DMA1_CHANNEL1->ctrl_bit.pincm = FALSE;
	DMA1_CHANNEL1->ctrl_bit.lm = TRUE;
	DMA1_CHANNEL1->dtcnt = 1;
	DMA1_CHANNEL1->paddr = (uint32_t)&ADC1->odt;
	DMA1_CHANNEL1->maddr = (uint32_t)&gBatteryAdcValue;

	DMA1_CHANNEL1->ctrl_bit.chen = TRUE;

	adc_para_init_ex(&init_adc);
	init_adc.sequence_mode = TRUE;
	init_adc.repeat_mode = FALSE;
	init_adc.trigger_select = ADC12_ORDINARY_TRIG_SOFTWARE;
	init_adc.ordinary_channel_length = 1;
	adc_base_config_ex(ADC1, &init_adc);

	ADC1->spt1 = (ADC1->spt1 & ~(7U << 3)) | (ADC_SAMPLETIME_28_5 << 3);
	ADC1->osq3 = (ADC1->osq3 & ~0x1FU) | ADC_CHANNEL_11;

	adc_ordinary_conversion_trigger_enable(ADC1, TRUE);

	ADC1->ctrl2_bit.ocdmaen = TRUE;
	ADC1->ctrl2_bit.adcen = TRUE;
}

void BATTERY_GetVoltage(void)
{
	ADC1->ctrl2_bit.adcalinit = TRUE;

	while (ADC1->ctrl2_bit.adcalinit) {
	}

	ADC1->ctrl2_bit.adcal = TRUE;

	while (ADC1->ctrl2_bit.adcal) {
	}

	adc_software_trigger_enable(ADC1, TRUE);

	battVolts = (u8)((gBatteryAdcValue * 4U) / 66U);
}

void batteryRead(void)
{
    BATTERY_GetVoltage();
    if(xmitActive)
        battXmit = gBatteryAdcValue;
    else
        battReceive = gBatteryAdcValue;
}

void batteryShow(const u8 x, const u8 y)
{
    s32 battDiff, ir;
    u16 col;
    u16 b;
    col = battVolts >= 80 ? COL_BATTHIGH : battVolts < 66 ? COL_BATTLOW : COL_BATTICONBODY;
    b = gBatteryAdcValue > 1386 ? 1386 : gBatteryAdcValue;
    if(b>924) b-=924; else b=0;

    switch(settings.battStyle)
    {
        default:
        case 1: // icon
            b /= 24;
            lcdFill(x+1, y,   23, 8, col); // batt body
            lcdFill(x+2, y+1, 21, 6, COL_BGROUND); // inner gap
            lcdFill(x+3, y+2,  b, 4, col); // batt level
            lcdFill(x  , y+2,  1, 4, col); // batt nipple
            return;
        case 2: // percentage
            b *= 13;
            b /= 60;
            SPRINT_NUMBER(TXT, b, 3, 255, 1, 0);
            TXT[3] = '%';
            break;
        case 3: // voltage
            SPRINT_NUMBER(TXT, battVolts/10, 1, 255, 0, 0);
            SPRINT_NUMBER(&TXT[2], battVolts%10, 1, 255, 0, 0);
            TXT[1] = '.';
            TXT[3] = 'V';
            break;
    }
    TXT[4] = 0;
    fontDraw6x8(TXT, x, y, col);
    if(settings.txCurrent && xmitActive)
    {

        // 240 - (batt / 6.6)

        battDiff = (s32)battReceive - (s32)battXmit;
        //ir = ((-60 * (s32)battReceive) + 275560) / 1000;
        ir = 240 - ( ((s32)battReceive*100)/660 );
        if(ir<30) ir=30;
        if(ir>100) ir=100;
        // 488
        battDiff *= 10000;
        battDiff /= ir;
        battDiff /= 177;
        if(battDiff<0) battDiff=0;
        if(battDiff>99) battDiff=99;

        SPRINT_NUMBER(TXT, battDiff, 1, 1, 1, 1);
        TXT[3]='A';
        TXT[4]=0;
        if(!(settings.pttMode & 1) && !VFO_CHANGERXFREQNOTBG) //VFO_CHANGERXFREQNOTBG
            COL_BGROUND = COL_VFOTX;        
        fontDraw6x8(TXT, VFO_POWERX, displayVfoPos(settings.activeVfo)+DIS(VFO_POWERY), COL_VFOPOWER);
        COL_BGROUND = COL_FWBGROUND;
    }
}