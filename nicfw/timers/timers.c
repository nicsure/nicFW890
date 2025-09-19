void timersSECS(const u8 secs)
{
    if(subCounter(&uartReset, 1)) {
        UART_Init(115200);
    }

    if(subCounter(&eepromTimer, 1)) {
        eeprom_Commit();
    }

    subCounter(&dualWatchStartTimer, 1);
    subCounter(&powerSaveSuspend, 1);
    //if(subCounter(&remoteDisableTimer, 1))
    //{
        //remoteActive = 0; // to be implemented : remote
        //externalKey = KEY_NONE;
    //}

    if(scanActivityMode)
    {
        UART_SendByte(0x2b);
    }

    if(txTimer!= 0xff && subCounter(&txTimer, secs) && xmitActive)
    {
        txTimer = 0xff;
    }

    if(!inputMode)
    {
        subCounter(&scanningSkip, secs);
        if(loopMode==LOOPMODE_SCANMONITOR && settings.scanResume && !skipMeter)
            displayVfoRefreshActiveNoDrawBG();
    }

    if(subCounter(&heardToneCounter, secs))
    {
        heardTone=0;
        displayToneMonitor();
    }

    if(subCounter(&fmtResume, 1))
    {
        if(VFOX[settings.activeVfo^1].isFmTuner)
        {
            radioSwapVfo();
            bkApplyActiveVfo();
        }
    }

    if(!xmitActive && !squelchOpen && KEY_LED && !inputMode && subCounter(&lcdTimer, 1))
    {
        lcdBL(0);
    }

    if(settings.breathe && !KEY_LED)
    {
        if(!breatheTimer) breatheTimer++;
        if(subCounter(&breatheTimer, secs))
        {
            breatheTimer=settings.breathe;
            radioSetLED(1,1);
            delay(50);
            radioSetLED(0,0);
        }
    }

    if(!inputMode && settings.battStyle)
    {
        batteryRead();
        batteryShow(FLAGS_BATTX, flagsYPOS());
    }    
}


void timersDECISECS(const u8 decs)
{
    u8 otherVfo;
    if(loopMode==LOOPMODE_SCAN && subCounter(&updateTimer, 1))
    {
        updateTimer = settings.scanUpdate;
        if(!inputMode)
        {
            vposTemp = displayVfoPos(settings.activeVfo);
            if(settings.pttMode!=1 && !VFO_CHANGERXFREQNOTBG) COL_BGROUND = COL_VFOSCAN;
            if(!ACTIVE_VFOSTATE.mode)
            {
                SPRINT_NUMBER(&TXT[5], scanFreq, 4, 5, 1, 1);
                memCpy2(scanActivityMode?ACIV_LABEL:SCAN_LABEL, TXT, 5);
                fontDraw6x8(TXT, VFO_CH_NAMEX, vposTemp+DIS(VFO_CH_NAMEY), COL_VFOCHNAME);
            }
            else
            {
                displayFreq(&scanFreq, VFO_RXXPOS, vposTemp+DIS(VFO_RXYPOS), COL_VFORXFREQ, 5, 1);
                channelSprintName(updateScanChannel);
                fontDraw8x8(TXT, VFO_CH_NAMEX, vposTemp+DIS(VFO_CH_NAMEY), COL_VFOCHNAME, LARGE_CH_NAME);
                SPRINT_NUMBER(TXT, updateScanChannel, 3, 255, 0, 1);
                fontDraw6x8(TXT,VFO_NAMEX+12,vposTemp+DIS(VFO_NAMEY),COL_VFOCORNER);
            }
            COL_BGROUND = COL_FWBGROUND;
        }
    }
    subCounter(&squelchOpenPause, 1);
    subCounter(&voxTank, decs);
    subCounter(&voxIgnore, 1);
    subCounter(&steTimer, 1);
    if(subCounter(&voxTailTimer, decs))
    {
        xmitRequest = 0;
    }
    if(fmtResume && (inputMode || loopMode || fmtActive))
        fmtResume = 0;    
    if(squelchOpen)
    {
        lcdBL(1);
    }    
    if(rssiTrigger) rssiTrigger--;
    if(scanningResume) scanningResume--;
    //if(fmtActive) fmtTick(); // to be implemented : fm tuner tick

    if(settings.dualWatch && !xmitActive && !loopMode && !inputMode && !squelchOpen && !dualWatchStartTimer)
    {
        
        otherVfo = settings.activeVfo ^ 1;
        if(!ACTIVE_VFOX.isFmTuner)
        {
            if(!VFOX[otherVfo].isFmTuner)
            {
                bkApplyVfo(otherVfo);
                delay(20);
                rssiTick();
                if(squelchOpen)
                {
                    settings.activeVfo = otherVfo;
                    displayRefreshFull();
                }
                else
                {
                    bkApplyActiveVfo();
                    delay(20);
                    rssiTick();                    
                }
            }
        }
        else
        {
            if(!VFOX[otherVfo].isFmTuner && appliedVfo != otherVfo)
                bkApplyVfo(otherVfo);
        }
    }
    if(settings.dualWatch && ACTIVE_VFOX.isFmTuner)
    {
        if(squelchOpen)
        {
            settings.activeVfo ^= 1;
            displayRefreshFull();
            if(fmtActive) fmtDisable(); // to be implemented : fm tuner disable
            fmtResume = 5;
        }
    }    
}


void timersTICKS(const u8 ticks)
{
    if(!xmitActive)
    {
        if(!loopMode || loopMode==LOOPMODE_SCANMONITOR)
            rssiTick();
    }
    keypadTick(ticks&0x7f);
    if(inputMode & INPUTMODE_INPUT)
    {
        inputTick();
    }
    else
    if(inputMode & INPUTMODE_MENU)
    {
        menuTick();
    }
    else
    if(!loopMode)
    {
        radioLoopTick();
    }    
}




void HandlerTMR6_GLOBAL(void)
{
    TMR6->ists = ~TMR_OVF_FLAG;
    if(timerDisable) return;    
    if(tmr6tick++>=10)
    {
        tmrTicks++;
        tmr6tick=0;
    }
    if(tmr6decisec++>=110)
    {    
        tmrDeciseconds++;
        tmr6decisec=0;
    }
    if(tmr6sec++>=1100)
    {
        tmrSeconds++;
        tmr6sec=0;
    }
}

void timersEnable(void)
{
    nvic_irq_enable(TMR6_GLOBAL_IRQn, 2, 2);
	TMR6->iden |= TMR_OVF_INT;
	TMR6->ctrl1_bit.tmren = TRUE;
    timerDisable = 0;
}

void timersTick(void)
{
    u8 ticks, decs, secs;
    timerDisable = 1;
    ticks = tmrTicks;
    decs = tmrDeciseconds;
    secs = tmrSeconds;
    tmrTicks = 0;
    tmrDeciseconds = 0;
    tmrSeconds = 0;
    timerDisable = 0;
    if(ticks) timersTICKS(ticks);
    if(decs) timersDECISECS(decs);
    if(secs) timersSECS(secs);

    if(!inputMode)
    {
        if((loopMode & (LOOPMODE_SCAN | LOOPMODE_SCANMONITOR | LOOPMODE_SCANFMT)))
            scanTick();
        else
        if(loopMode==LOOPMODE_FREQCOUNTER)
            scanFreqCountTick();
    }    

    if(settings.noiseGate && squelchOpen && loopMode!=LOOPMODE_SCAN && !squelchOverride)
    {
        if(bkGetExNoise()>HI_NOISE_LEVEL && !rxToneDetected)
        {
            noiseLimited = 10;
            bkSetModulation(0, 0);
        }
        else
        {
            if(subCounter(&noiseLimited, 1))
                bkSetModulation(currentModulation, 1);
        }
    }
    else
        noiseLimited = 0;

}