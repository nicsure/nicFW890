
static u16 scopeFloor;
static u16 scopeAvg[160];

void scopeDraw(void)
{
    u8 x, vpos, sig, t, bw, vheight;
    u32 freq;
    u16 sig16, lowSig, highSig;
    squelchOpen = 0;
    if(skipNextScope)
    {
        skipNextScope--;
        return;
    }
    if(inputMode) {
        return;
    }
    vheight=VFO_HEIGHT-1;
    bw = scopeBarWidth;// SCOPE_SOLID?2:1;
    vpos = displayVfoPos(settings.activeVfo^1);
    freq = ACTIVE_VFO.rxFreq.value;
    freq -= (u32)settings.step * (80/bw); //<< 5;
    SPRINT_NUMBER(TXT, freq, 4, 5, 1, 1);
    fontDraw6x8(TXT, 0, SBAR_DPTT_YPOS, COL_VFORXFREQ);
    lowSig=0xffff;
    highSig=0;

    keypadTick(10);
    if(anyKeyInUse)
    {
        skipNextScope = 25;
        return;
    }
    for(x = 0; x!=160; x+=bw)
    {
        bkSet30(0);
        bkSetFreqRegs(freq);
        bkAfDacOff();
        DELAY_WaitUS(1000);
        sig16 = bkGetRssi();
        if(sig16<lowSig) {
            lowSig=sig16;
        }
        if(sig16>highSig) {
            topFreq=freq;
            highSig=sig16;
        }
        if(sig16>scopeFloor) {
            sig16-=scopeFloor;
        } else {
            sig16=scopeFloor-sig16;
        }
        scopeAvg[x] += sig16;
        scopeAvg[x] >>= 1;
        sig16 = scopeAvg[x];
        sig = sig16&0xff;
        if(!sig) sig=1;        
        if(sig>vheight) sig=vheight;
        t = vheight-sig;
        lcdFill(x, vpos, bw, t, COL_FWBGROUND);
        lcdFill(x, vpos+t, bw, sig, x==80 ? COL_SCOPEBARMID : COL_SCOPEBAR);
        freq+=settings.step;
    }
    tmrTicks=0;
    scopeFloor=lowSig;
    hiFreq=topFreq;
    if(!anyKeyInUse && !skipNextScope)
    {
        SPRINT_NUMBER(TXT, freq, 4, 5, 1, 1);
        fontDraw6x8(TXT, 68, SBAR_DPTT_YPOS, COL_VFORXFREQ);    
        SPRINT_NUMBER(TXT, topFreq, 4, 5, 1, 1);
        fontDraw8x8(TXT, 24, SMETER_DPTT_YPOS, COL_VFOTXFREQ, 0);          
    }
}

void scopeStop(void)
{
    scopeActive=0;
    bkApplyVfo(settings.activeVfo);
    displayRefresh(1);
}