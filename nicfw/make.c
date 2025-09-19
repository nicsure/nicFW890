
extern const u8 StackVector[];
extern uint32_t __bss_start__[];
extern uint32_t __bss_end__[];
extern uint8_t flash_data_start[];
extern uint8_t sram_data_start[];
extern uint8_t sram_data_end[];

void Main(void)
{
	CRM_GetCoreClock();
	SCB->VTOR = (u32)StackVector;
	DELAY_Init();
	DELAY_WaitMS(200);
	CRM_InitPeripherals();
	InitGPIO();
	
	BATTERY_Init();
	lcdInit();
	timersEnable();
	keypadInit();
	PWM_Init();
	PWM_Reset();
	voiceInit();

	eepromRead((u8*)&SMETER_DPTT_YPOS, SKINPOSBASE, sizeof(SKINPOS)); // corrected : address
	eepromRead((u8*)&COL_SMETEROFF, SKINCOLBASE, sizeof(SKINCOL)); // corrected : address
	eepromRead(lpActionTable, LP0BASE, sizeof(lpActionTable));
	eepromRead(lpShiftActionTable, LP1BASE, sizeof(lpShiftActionTable));
	settingsLoad();
	calibLoad();

	radioInitLEDs();
	planStruct.planDummy_=0;
	
	if(settings.magic!=SETTINGSMAGIC)
	{
		memFill(&settings, 0, 128);
		settings.rxSplit = 2800;
		settings.txSplit = 2800;
		settings.squelch = 2;
		settings.step = 1250;
		settings.micGain = 25;
		settings.txDeviation = 64;
		settings.scanRange = 100;    
		settings.repeaterTone = 1750;
		settings.dtmfDev = 32;
		settings.sqNoiseLev = 47;
		settings.voxTail = 20;
		settings.pin = 1234;
		settings.stDev = 74;	
		settings.pcbVersion = 1;
		settings.lcdBrightness = 28;
		settings.asl = 0;
		bkResetAgcTables();
	}

	if(settings.asl>3) {
		settings.asl=0;
	}

	amFixGain = 40;
	if(settings.amFix>200) settings.amFix = 0;

	if(!settings.gain0 || settings.gain0>42 ||
	   !settings.gain1 || settings.gain1>42 ||
	   !settings.gain2 || settings.gain2>42 ||
	   !settings.gain3 || settings.gain3>42) {
		bkResetAgcTables();
	}

	if(!(settings.asl&1)) {
		UART_Init(115200);
	}

	step833Counter = 1;
	scopeBarWidth = 2;
	channelLoadMap();
    if(settings.pinAction==2)
    {
		settings.keyLock=1;
	}
	eepromRead(planMagic.array, BANDPLANBASE, 244); // corrected : address
    if(planIsValid())
    {
        planFindFMT();
    }
    bkReg[0x30].value = 0xBFF1;
    bkInit();	
    bkSet30(0);
    bkSetModulation(0, 0);
	scanDirection = 1;
    externalKey=KEY_NONE;

    keypadPressed = KEY_NONE;
    keypadShort = KEY_NONE;
    keypadLong = KEY_NONE;

	delay(1000);
    lcdBL(0);
    lcdCls();
	lcdGamma();
	//waterfall=1;
	lcdInvert(settings.lcdInverted);

    applyBankChange();

	lcdTimer = settings.lcdTimeout;
    displayRefreshGeneral();
    lcdBL(1);
    initComplete = 1;
	//lcdScrollTest();
	while(1)
	{
		UART_Tick();
        if(!(inputMode & INPUTMODE_SERIAL))
			timersTick();	
		bkAmFix();	
	}
}

void applyBankChange(void)
{
    settings.activeVfo = settings.activeVfo ? 0 : 1; // potential code shrink
    radioToggleVfoMode(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0);
    settings.activeVfo = settings.activeVfo ? 0 : 1;
    radioToggleVfoMode(ACTIVE_VFOSTATE.mode, ACTIVE_VFOSTATE.group, 0);
    displayRefreshFull();	
}

void BSS_Init(void)
{
	uint32_t *pBss;

	for (pBss = __bss_start__; pBss < __bss_end__; pBss++) {
		*pBss = 0;
	}
}


void DATA_Init(void)
{
	volatile uint32_t *pDataRam = (volatile uint32_t *)sram_data_start;
	volatile uint32_t *pDataFlash = (volatile uint32_t *)flash_data_start;
	uint32_t Size = ((uint32_t)sram_data_end - (uint32_t)sram_data_start) / 4;
	uint32_t i;

	for (i = 0; i < Size; i++) {
		*pDataRam++ = *pDataFlash++;
	}
}