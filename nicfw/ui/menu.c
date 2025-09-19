
const MENU squelchMenu = {
    VALUE8,
    0,
    9,
    VOICE_ID_SQ_LEVEL,
    &settings.squelch,
    "Squelch",
};

const MENU squelchNoiseMenu = {
    VALUE8,
    15,
    55,
    VOICE_NONE,
    &settings.sqNoiseLev,
    "Sq Noise Lev"
};

const MENU txPowerMenu = {
    VALUE8ZO,
    0,
    255,
    VOICE_ID_TX_POWER,
    &txPowerMenuVal,
    "TX Power",
};

const MENUOPTS2 bandwidthMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_BANDWIDTH,
    &bandwidthMenuVal,
    "Bandwidth",
    { optionWide, optionNarrow }
};

const MENUOPTS2 dualWatchMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_DUALSTANDBY,
    &settings.dualWatch,
    "Dual Watch",
    { optionOff, optionOn }
};

const MENUOPTS2 busyLockMenu = {
    OPTION,
    0,
    1,
    VOICE_ID_TX_BUSYLOCK,
    &busyLockMenuVal,
    "Busy Lock",
    { optionOff, optionOn }
};

const MENUOPTS4 modulationMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &modulationMenuVal,
    "Modulation",
    { AUTO, FM, AM, USB }
};

const MENU16 txCtcssMenu = {
    VALUECTS,
    0,
    3000,
    1,
    VOICE_ID_TX_PRIVACY_CODE,
    &txSubToneMenuVal,
    "TX CTCSS",
};

const MENU16 txDcsMenu = {
    VALUEDCS,
    0,
    0x1ff,
    0,
    VOICE_ID_TX_PRIVACY_CODE,
    &txSubToneMenuVal,
    "TX DCS",
};

const MENU16 rxCtcssMenu = {
    VALUECTS,
    0,
    3000,
    1,
    VOICE_ID_RX_PRIVACY_CODE,
    &rxSubToneMenuVal,
    "RX CTCSS",
};

const MENU16 rxDcsMenu = {
    VALUEDCS,
    0,
    0x1ff,
    0,
    VOICE_ID_RX_PRIVACY_CODE,
    &rxSubToneMenuVal,
    "RX DCS",
};

const MENU16 stepMenu = {
    VALUE16,
    1,
    50000,
    2,
    VOICE_ID_FREQUENCY_STEP,
    &settings.step,
    "Step",
};

const MENUOPTS3 pttModeMenu = {
    OPTION,
    0,
    2,
    VOICE_ID_DUAL_DISPLAY,
    &settings.pttMode,
    "PTT Mode",
    { DUAL, SINGLE, HYBRID }
};

const MENUOPTS2 txModMeterMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.txModMeter,
    "TX Mod Meter",
    { optionOff, optionOn }
};

const MENU micGainMenu = {
    VALUE8,
    0,
    31,
    VOICE_NONE,
    &settings.micGain,
    "Mic Gain"
};

const MENU txDeviationMenu = {
    VALUE8,
    0,
    99,
    VOICE_NONE,
    &settings.txDeviation,
    "TX Deviation"
};

const MENU16 xtal671Menu = {
    VALUE16S,
    0,
    65535,
    0,
    VOICE_NONE,
    (u16*)&tuning.xtal671,
    "XTAL 671"
};

const MENU16 rxSplitMenu = {
    VALUE16,
    2000,
    4000,
    1,
    VOICE_NONE,
    &settings.rxSplit,
    "RX VHF->UHF"
};

const MENU16 txSplitMenu = {
    VALUE16,
    2000,
    4000,
    1,
    VOICE_NONE,
    &settings.txSplit,
    "TX VHF->UHF"
};

const MENUOPTS3 toneMonitorMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.toneMonitor,
    "Tone Monitor",
    { optionOff, optionOn, CLONE }
};

const MENUOPTS4 battStyleMenu = {
    OPTION,
    0,
    3,
    VOICE_ID_VOLTAGE_DISPLAY,
    &settings.battStyle,
    "Batt Style",
    { optionOff, ICON, PERCENT, VOLTS }
};

const MENUOPTS4 keyTonesMenu = {
    OPTION,
    0,
    3,    
    VOICE_ID_KEY_BEEP,
    &settings.keyTones,
    "Key Tones",
    { optionOff, optionOn, DIFFERENTIAL, VOICE }
};

const MENU16 scanRangeMenu = {
    VALUE16,
    1,
    60000,
    2,
    VOICE_NONE,
    &settings.scanRange,
    "VFO Scan Range"
};

const MENU16 scanPersistMenu = {
    VALUE16,
    0,
    200,
    1,
    VOICE_NONE,
    &settings.scanPersist.value,
    "Scan Persist"
};

const MENU scanResumeMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_NONE,
    &settings.scanResume,
    "Scan Resume"
};

const MENU ultraScanMenu = {
    VALUE8ZO,
    0,
    20,
    VOICE_NONE,
    &settings.ultraScan,
    "Scan Ultra"
};

const MENUOPTS2 lcdInvertMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.lcdInverted,
    "LCD Inverted",
    { optionOff, optionOn }
};

const MENU lcdTimeoutMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_ID_DISPLAY_TIMER,
    &settings.lcdTimeout,
    "LCD Timeout"
};

const MENU breatheMenu = {
    VALUE8ZO,
    0,
    30,
    VOICE_NONE,
    &settings.breathe,
    "Heartbeat"
};

const MENU dtmfDevMenu = {
    VALUE8,
    0,
    127,
    VOICE_NONE,
    &settings.dtmfDev,
    "DTMF Volume"
};

const MENU16 repeaterToneMenu = {
    VALUE16,
    100,
    4000,
    0,
    VOICE_ID_REPEATER_MODE,
    &settings.repeaterTone,
    "Repeater Tone",
};

const MENU gammaMenu = {
    VALUE8,
    0,
    3,
    VOICE_NONE,
    &settings.gamma,
    "LCD Gamma"
};

const MENU powerMenu = {
    VALUE8ZO,
    0,
    20,
    VOICE_NONE,
    &settings.powerSave,
    "Power Save"
};

const MENUOPTS4 steMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &settings.ste,
    "Sq Tail Elim",
    { optionOff, RX_LABEL, TX_LABEL, BOTH }
};

const MENUOPTS3 sBarStyleMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.sBarStyle,
    "S-Bar Style",
    { SEGMENT, STEPPED, SOLID }
};

const MENU rfGainMenu = {
    VALUE8ZO,
    0,
    42,
    VOICE_NONE,
    &settings.rfGain,
    "RF Gain"
};

const MENU gain0Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain0,
    "AGC Table 0"
};

const MENU gain1Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain1,
    "AGC Table 1"
};
const MENU gain2Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain2,
    "AGC Table 2"
};
const MENU gain3Menu = {
    VALUE8,
    1,
    42,
    VOICE_NONE,
    &settings.gain3,
    "AGC Table 3"
};

const MENU amFixMenu = {
    VALUE8ZO,
    0,
    200,
    VOICE_NONE,
    &settings.amFix,
    "AM AGC Level",
};


const MENU addGroupMenu = {
    VALUE8L,
    0,
    15,
    VOICE_NONE,
    &addGroupTrigger,
    "Add Group"
};

const MENU delGroupMenu = {
    VALUE8L,
    0,
    15,
    VOICE_NONE,
    &delGroupTrigger,
    "Remove Group"
};

const MENU voxMenu = {
    VALUE8ZO,
    0,
    15,
    VOICE_ID_VOX_LEVEL,
    &settings.vox,
    "VOX",
};

const MENU16 voxTailMenu = {
    VALUE16,
    5,
    50,
    1,
    VOICE_ID_VOX_DELAY,
    &settings.voxTail,
    "VOX Tail",
};

const MENU txTimeoutMenu = {
    VALUE8ZO,
    0,
    250,
    VOICE_ID_TIMEOUT_TIMER,
    &settings.txTimeout,
    "TX Timeout",
};

const MENU brightnessMenu = {
    VALUE8,
    0,
    28,
    VOICE_NONE,
    &settings.lcdBrightness,
    "LCD Brightness",
};

const MENU dimmerMenu = {
    VALUE8ZO,
    0,
    28,
    VOICE_NONE,
    &settings.dimmer,
    "Dim Brightness",
};

const MENU dtmfSpeedMenu = {
    VALUE8,
    0,
    20,
    VOICE_NONE,
    &settings.dtmfSpeed,
    "DTMF Speed",
};

const MENUOPTS2 noiseGateMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.noiseGate,
    "Noise Gate",
    { optionOff, optionOn }
};

const MENU scanUpdateMenu = {
    VALUE8ZO,
    0,
    50,
    VOICE_NONE,
    &settings.scanUpdate,
    "Scan Update",
};

const MENUOPTS4 aslMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &settings.asl,
    "ASL Support",
    { optionOff, &COSI[2], USB, COSI }
};

const MENUOPTS3 wlCloneMenu = {
    OPTION,
    0,
    2,
    VOICE_ID_RECORD_SETTINGS,
    &wlCloneTrigger,
    "Wireless Copy",
    { CANCEL, RECEIVE, SEND }
};

const MENUOPTS2 disableFmtMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.disableFmt,
    "Disable FMT",
    { optionNo, optionYes }
};

const MENU16 pinMenu = {
    VALUE16,
    1000,
    9999,
    0,
    VOICE_NONE,
    &settings.pin,
    "PIN",
};

const MENUOPTS3 pinActionMenu = {
    OPTION,
    0,
    2,
    VOICE_NONE,
    &settings.pinAction,
    "PIN Action",
    { optionOff, optionOn, POWERON }
};

const MENU afFiltersMenu = {
    VALUE8,
    0,
    8,
    VOICE_NONE,
    &settings.afFilters,
    "AF Filters",
};

const MENUOPTS2 sBarAlwaysOnMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.sBarAlwaysOn,
    "SBar AlwaysOn",
    { optionOff, optionOn }
};

const MENUOPTS4 pttIDMenu = {
    OPTION,
    0,
    3,
    VOICE_NONE,
    &pttIDMenuVal,
    "PTT ID",
    { optionOff, BOT, EOT, BOTH }
};

const MENU dwDelayMenu = {
    VALUE8,
    1,
    30,
    VOICE_NONE,
    &settings.dwDelay,
    "DualWatch Delay",
};

const MENUOPTS ifFreqMenu = {
    OPTION,
    0,
    6,
    VOICE_NONE,
    &settings.ifFreq,
    "IF (kHz)",
    { IF1, IF2, IF3, IF4, IF5, IF6, IF7 }
};

const MENU stDevMenu = {
    VALUE8,
    0,
    127,
    VOICE_NONE,
    &settings.stDev,
    "SubTone Dev",
};

const MENUOPTS2 vfoLockMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.vfoLock,
    "VFO DW Lock",
    { optionOff, optionOn }
};

//const MENUOPTS2 bluetoothMenu = {
//    OPTION,
//    0,
//    1,
//    VOICE_NONE,
//    &settings.bluetooth,
//    "Bluetooth",
//    { optionOff, optionOn }
//};

const MENU channelBankMenu = {
    VALUE8,
    0,
    3,
    VOICE_NONE,
    &settings.channelBank,
    "Channel Bank",
};


const MENUOPTS2 txCurrentMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.txCurrent,
    "TX Current",
    { optionOff, optionOn }
};

const MENUOPTS2 pcbVersionMenu = {
    OPTION,
    0,
    1,
    VOICE_NONE,
    &settings.pcbVersion,
    "PCB Version",
    { option2_0, option2_1 }
};

const MENU rfiCompMenu = {
    VALUE8ZO,
    0,
    255,
    VOICE_NONE,
    &settings.rfiCompAmount,
    "RFI Comp Value",
};



void menuDrawPin(void)
{
    fontDraw8x8(pinMenu.title, 40, 44, COL_MENU, 1); // enable later
}

const void* menus[] = {
    &squelchMenu,
    &squelchNoiseMenu,
    &stepMenu,

    &bandwidthMenu,
    &txPowerMenu,
    &modulationMenu,
    &busyLockMenu,
    &txCtcssMenu,
    &txDcsMenu,
    &rxCtcssMenu,
    &rxDcsMenu,
    &addGroupMenu,
    &delGroupMenu,
    &pttIDMenu,

    &scanRangeMenu,
    &scanPersistMenu,
    &scanResumeMenu,
    &ultraScanMenu,
    &scanUpdateMenu,

    &txDeviationMenu,
    &txTimeoutMenu,
    &txModMeterMenu,
    &pttModeMenu,    
    &micGainMenu,    
    &dtmfDevMenu,
    &dtmfSpeedMenu,
    &repeaterToneMenu,
    &voxMenu,
    &voxTailMenu,

    &toneMonitorMenu,
    &dualWatchMenu,
    &dwDelayMenu,
    &vfoLockMenu,
    &noiseGateMenu,
    &xtal671Menu,
    &rxSplitMenu,
    &txSplitMenu,


    &battStyleMenu,
    &lcdInvertMenu,
    &brightnessMenu,
    &dimmerMenu,
    &lcdTimeoutMenu,
    &breatheMenu,
    &gammaMenu,
    &sBarStyleMenu,
    &sBarAlwaysOnMenu,
    &powerMenu,



    &stDevMenu,
    &steMenu,
    &rfGainMenu,
    &gain0Menu,
    &gain1Menu,
    &gain2Menu,
    &gain3Menu,
    &amFixMenu,

    &keyTonesMenu,
    &aslMenu,
    &wlCloneMenu,
    &disableFmtMenu,
    &pinMenu,
    &pinActionMenu,
    &afFiltersMenu,
    &ifFreqMenu,
    //&bluetoothMenu,
    &channelBankMenu,
    &txCurrentMenu,

    &rfiCompMenu,
    &pcbVersionMenu,
};

static u8 oldBank;

void menuInit(void)
{
    menuTens = 0;
    menuEdit = 0;
    inputMode |= INPUTMODE_MENU;
    channelActiveToMenu();
    menuDraw(NEWVALUE_1ST);
    oldBank = settings.channelBank;
    // voicePlay(VOICE_ID_MENU, 0); // to be implemented : voice
}

void menuTick(void)
{
    u32 newVal;
    u8 key, nm, tens, units;
    void* menu;    
    key = keypadSinglePress();
    if(keypadLong==KEY_UP || keypadLong==KEY_DOWN) key=keypadLong;
    if(menuEdit)
    {
        if(inputState==INPUT_CANCELLED)
        {
            newVal = menuTemp;
        }
        else
        if(inputState==INPUT_APPLIED)
        {
            newVal = inputValue;
        }
        else
        if(key<10)
        {
            lcdFill(0, 65, 128, 16, menuBG);
            inputPrepare(menuUnits, menuDecimals, 13, 65, FONT8X16NUM);
            inputParseKey(key);
            return;
        }
        else
        switch(key)
        {
            case KEY_HASH:
                if(octalInput) {
                    newVal = NEWVALUE_KEEPOLD;
                }
                else {
                    newVal = NEWVALUE_NEGATE;
                }
                //return;
                break;
            case KEY_EXIT:
                newVal = menuTemp;                
                menuEdit = 0;
                //voicePlay(VOICE_ID_OFF, 0); // to be implemented : voice
                break;                
            case KEY_MENU:
                newVal = NEWVALUE_1ST;
                menuEdit = 0;
                // voicePlay(VOICE_ID_CONFIRM, 0); // to be implemented : voice                
                break;
            case KEY_UP:
                newVal = NEWVALUE_ADD1;
                break;            
            case KEY_DOWN:
                newVal = NEWVALUE_SUB1;
                break;            
            default:
                return;
        } 
        inputState=INPUT_IDLE;      
        menuDraw(newVal);
    }
    else
    {
        if(key<10)
        {
            nm = key;
            if(menuTens)
            {
                nm+=(menuNumber*10);
                menuTens=0;
            }
            else
                menuTens=1;
            if(nm>MENU_COUNT) 
            {
                nm = key;
                menuTens=0;
            }
            menuNumber=nm;
        }
        else    
        switch(key)
        {
            case KEY_FLSH:
                fontDraw6x8(CRC, 39, 86, COL_MENU);
                fontDraw6x8(crc32()?OK:BAD, 60, 86, COL_MENU); // to be implemented : CRC
                return;
            case KEY_EXIT:
                //voicePlay(VOICE_ID_MENU, 1); // to be implemented : voice
                voicePlay(VOICE_ID_OFF); // to be implemented : voice
                voiceWait();
                octalInput=0;
                inputMode &= ~INPUTMODE_MENU;
                lcdCls();
                settingsWrite();
                if(oldBank != settings.channelBank)
                {
                    channelLoadMap();
                    applyBankChange();
                }
                else                
                {
                    channelActiveFromMenu();
                    validateVfo(settings.activeVfo);
                    bkApplyActiveVfo();
                    displayRefreshFull();
                }
                return;
            case KEY_MENU:
                if(menuUnits)
                {
                    // to be implemented : voice
                    menuEdit=1;
                    menuTens=0;
                    if(menuVoice != 0xff)
                    {
                        menu = (void*)menus[menuNumber];
                        if(menu == &txCtcssMenu || menu == &txDcsMenu) // enable later
                        {
                            //voicePlay(VOICE_ID_TRANSMIT_OVER_TIME, 0x40);
                        }
                        if(menu == &voxTailMenu)
                        {
                            //voicePlay(VOICE_ID_OFF, 1);
                        }
                        voicePlay(menuVoice);
                        break;
                    }
                    //voicePlay(VOICE_ID_MENU, 1);
                    if(menuNumber<21)
                    {
                        voicePlay(menuNumber+70);
                    }
                    else
                    {
                        tens = menuNumber/10;
                        units = menuNumber%10;
                        tens+=88;
                        if(units) units+=70;
                        voicePlay3(tens, units, 0);
                    }
                }
                break;
            case KEY_UP:
                menuNumber++;
                break;
            case KEY_DOWN:
                menuNumber--;
                break;
            default:
                return;
        }
        if(menuNumber==0xFF) menuNumber=MENU_COUNT;
        if(menuNumber>MENU_COUNT) menuNumber=0;
        menuDraw(NEWVALUE_1ST);
    }
}

void menuDraw(const u32 newValue)
{
    
    void* menu;
    char* title;
    char* value;
    u8 zeroIsOff;
    MENU* ms;
    MENU16* ms16;
    u8 v, max;
    menuBG = menuEdit?COL_MENUEDITBG:COL_MENUBG;
    // COL_MENUEDITBG
    octalInput = 0;
    lcdFill(0, 34, 128, 25, COL_MENU);
    lcdFill(0, 59, 128, 37, menuBG);
    menu = (void*)menus[menuNumber];
    zeroIsOff = 0;
    switch(MENU_TYPE)
    {
        default: return;
        case VALUEDCS:
            {
                ms16 = (MENU16*)menu;
                title = ms16->title;
                menuVoice = ms16->voicePrompt;
                if(MENU_VAR16 && !(MENU_VAR16 & 0x8000))
                {
                    MENU_VAR16 &= 0xbfff;
                    menuUnits=0;
                    value=(char*)NA;
                    break;
                }
                octalInput = 1;
                menuDecimals=0;
                menuUnits=3;
                switch(newValue)
                {
                    case NEWVALUE_NEGATE: break;
                    case NEWVALUE_KEEPOLD:
                        if(MENU_VAR16)
                            MENU_VAR16 ^= 0x4000;
                        break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR16;
                        break;
                    case NEWVALUE_ADD1: 
                        MENU_VAR16 = nextDcs(1, MENU_VAR16); 
                        break;
                    case NEWVALUE_SUB1:
                        MENU_VAR16 = nextDcs(0, MENU_VAR16); 
                        break;
                    default: MENU_VAR16 = (u16)(newValue & 0xffff);
                }
                sprint_dcs(MENU_VAR16);
                value=TXT;
            }
            break;

        case VALUECTS:
        case VALUE16ZO:
            zeroIsOff = 1;
            goto VALUE16JUMP;
        case VALUE16:
        case VALUE16S:
            VALUE16JUMP:
            {
                ms16 = (MENU16*)menu;
                title = ms16->title;
                menuVoice = ms16->voicePrompt;
                if(MENU_TYPE == VALUECTS && (MENU_VAR16 & 0x8000))
                {
                    menuUnits=0;
                    value=(char*)NA;
                    break;
                }
                switch(newValue)
                {
                    case NEWVALUE_NEGATE:
                        if(MENU_TYPE==VALUE16S)
                        {
                            MENU_VAR16 = (u16)0 - MENU_VAR16;
                        }
                        break;
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST: menuTemp = MENU_VAR16; break;
                    case NEWVALUE_ADD1:
                        if(MENU_TYPE == VALUECTS)
                            MENU_VAR16 = nextCtcss(1, MENU_VAR16); 
                        else
                            (MENU_VAR16)++; 
                        break;
                    case NEWVALUE_SUB1:
                        if(MENU_TYPE == VALUECTS)
                            MENU_VAR16 = nextCtcss(0, MENU_VAR16); 
                        else
                            (MENU_VAR16)--;
                        break;
                    default: MENU_VAR16 = (u16)(newValue & 0xffff);
                }           
                menuDecimals=ms16->decimals;
                menuUnits=countDigits(ms16->max/(u16)Pow10(ms16->decimals));
                if(MENU_VAR16 == 0xFFFF || MENU_VAR16 < ms16->min) MENU_VAR16=ms16->max; else
                if(MENU_VAR16 > ms16->max) MENU_VAR16=ms16->min;
                if(!zeroIsOff || MENU_VAR16)
                {
                    if(MENU_TYPE==VALUE16S)
                    {
                        if(MENU_VAR16>32767)
                        {
                            TXT[0]='-';
                            SPRINT_NUMBER(&TXT[1], (u16)((u16)0-(u16)MENU_VAR16), menuUnits, menuDecimals?menuDecimals:255, 1, 1);                        
                        }
                        else
                        {
                            TXT[0]='+';
                            SPRINT_NUMBER(&TXT[1], (u16)MENU_VAR16, menuUnits, menuDecimals?menuDecimals:255, 1, 1);                        
                        }                        
                    }
                    else
                    {
                        SPRINT_NUMBER(TXT, MENU_VAR16, menuUnits, menuDecimals?menuDecimals:255, 1, 1);
                    }
                    value = TXT;
                }
                else
                    value = (char*)optionOff;                
            }          
            break;
        case VALUE8ZO:
            zeroIsOff = 1;
            goto VALUE8JUMP;
        case VALUE8:
        case VALUE8S:
        case VALUE8L:
            VALUE8JUMP:
            {
                ms = (MENU*)menu;
                switch(newValue)
                {
                    case NEWVALUE_NEGATE: break;
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR;
                        break;
                    case NEWVALUE_ADD1: (MENU_VAR)++; break;
                    case NEWVALUE_SUB1: (MENU_VAR)--; break;
                    default: MENU_VAR = (u8)(newValue & 0xff);
                }
                if(MENU_VAR == 0xFF && ms->max!=0xff) MENU_VAR=ms->max; else
                if(MENU_VAR < ms->min) MENU_VAR=ms->max; else
                if(MENU_VAR > ms->max) MENU_VAR=ms->min;
                title = ms->title;
                menuVoice = ms->voicePrompt;
                menuUnits = countDigits(ms->max);
                menuDecimals = 0;
                if(menu == &gammaMenu)
                {
                    lcdGamma(); // to be implemented : gamma
                }
                if(!zeroIsOff || MENU_VAR)
                {
                    if(MENU_TYPE==VALUE8S)
                    {
                        v = (u8)(MENU_VAR&0xff);
                        TXT[0] = (v&0x80) ? '-':'+';
                        TXT[1] = 0;
                        SPRINT_NUMBER(&TXT[1], TXT[0]=='-'?(v^0xff)+1:v, menuUnits, 255, 1, 1);
                    }
                    else
                    if(MENU_TYPE==VALUE8L)
                    {
                        if(!ACTIVE_VFOSTATE.mode)
                            memCpy2(NA, TXT, 4);
                        else
                        if(!MENU_VAR)
                            memCpy2(CANCEL, TXT, 7);
                        else
                        {
                            TXT[0]=MENU_VAR+64;
                            TXT[1]=0;
                        }
                    }
                    else
                    {
                        SPRINT_NUMBER(TXT, MENU_VAR, menuUnits, 255, 1, 1);                    
                    }
                    value = TXT;
                }
                else
                    value = (menu==&rfGainMenu)?(char*)AGC:(char*)optionOff;
            }
            break;
        case OPTION:
            {
                ms = (MENU*)menu;
                switch(newValue)
                {
                    case NEWVALUE_NEGATE: break;
                    case NEWVALUE_KEEPOLD: break;
                    case NEWVALUE_1ST:
                        menuTemp = MENU_VAR;
                        if(menu==&wlCloneMenu && MENU_VAR)
                        {
                            fskWlClone(MENU_VAR==2);
                            MENU_VAR=0;
                            return;
                        }                        
                        break;
                    case NEWVALUE_ADD1: (MENU_VAR)++; break;
                    case NEWVALUE_SUB1: (MENU_VAR)--; break;
                    default: MENU_VAR = (u8)(newValue & 0xff);
                }
                menuUnits = 1;
                menuDecimals = 0;
                if(menu == &lcdInvertMenu)
                    lcdInvert(settings.lcdInverted);                
                if(MENU_VAR == 0xFF) MENU_VAR=ms->max; else
                if(MENU_VAR > ms->max) MENU_VAR=0;
                title = ms->title;
                menuVoice = ms->voicePrompt;


                value = (char*) ((MENUOPTS*)menu)->opts[MENU_VAR];
            }
            break;
    }
    COL_BGROUND = menuBG;
    fontDrawText(value, &font8x16, 13, 65, menuEdit?COL_MENUEDIT:COL_MENU, COL_BGROUND);
    if(menu==&txPowerMenu)
    {
        ms = (MENU*)menu;
        max = MENU_VAR;
        if(txMaxPowerMenuVal<max)
            max=txMaxPowerMenuVal;
        sprint_power(max, ACTIVE_VFOX.txIsVhf);
        fontDraw8x16(TXT, 82, 65, COL_MENUEDIT);
    }    

    TXT[2]='/';
    SPRINT_NUMBER(TXT, menuNumber, 2, 255, 0, 0);    
    SPRINT_NUMBER(&TXT[3], MENU_COUNT, 2, 255, 0, 1);    
    
    
    fontDrawText(TXT, &font6x8, 5, 86, COL_MENU, COL_BGROUND);
    fontDrawText(VERSION, &font6x8, 80, 86, COL_MENU, COL_BGROUND);
    COL_BGROUND = COL_MENU;
    fontDrawText(title, &font8x16, 5, 40, menuBG, COL_BGROUND);
    COL_BGROUND = COL_FWBGROUND; 
    
}



