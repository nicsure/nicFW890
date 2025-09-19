void channelLoadMap(void)
{
    u8 i;
    u32 addr;
    for(i=0; i<252; i++)
    {
        addr = CHANNELBANKBASE + (i<<5);
        eepromRead((u8*)&(channelMap[i]), addr, 4); // corrected : address
        eepromRead((u8*)&(groupMap[i]), addr+13, 2);
    }    
}

const u8 channelCheckGroup(const u8 channel, const u8 group)
{
    const U16* groupw = (U16*)&(groupMap[channel]);
    return groupw->nibbles.n0 == group || 
           groupw->nibbles.n1 == group ||
           groupw->nibbles.n2 == group ||
           groupw->nibbles.n3 == group;
}

void channelSprintName(const u8 channelNum)
{
    eepromRead((u8*)TXT, CHANNELBANKBASE +(channelNum<<5)+20, 12); // corrected : address
    memCpySpc(TXT, TXT, LARGE_CH_NAME ? 8:12);
}

const u8 channelValidateGroup(u8 candidate, const u8 dir)
{
    u8 j, i;
    for(j=0; j!=17; j++)
    {
        if(candidate>15) candidate=1;
        if(candidate<1) candidate=15;
        for(i = 2; i!=252; i++)
        {
            if( isValidFreq(&channelMap[i]) && channelCheckGroup(i, candidate) )
                return candidate;
        }
        candidate+=dir;
    }
    return 0;
}

const u8 channelValidateOrNext(u8 current, const u8 direction, const u8 group, const u8 next)
{
    // vfo a is channel 0, vfo b is channel 1. Pre programmed channels start from 2.
    // we don't want to check the VFOs only the pre programmed channels 2-200
    u8 i;
    u8 currentValid;
    currentValid = !next && current>1 && isValidFreq(&channelMap[current]);
    if(currentValid)
    {
        if(group==0 || channelCheckGroup(current, group))
            return current;
    }
    for(i=0; i<252; i++)
    {
        current+=direction;
        if(current<2 || current==0xff) current=251; else if(current>251) current=2;
        if(isValidFreq(&channelMap[current]) && (group==0 || channelCheckGroup(current, group)))
            return current;
    }
    if(clampFreq(&(channelMap[2])))
    {
        channelMap[2]=defaultFreq;
        memCpy2(&defaultFreq, TXT, 4);
        memCpy2(&defaultFreq, &TXT[4], 4);
        memBlank(&TXT[8], 24);
        eeprom_Write((u8*)TXT, CHANNELBANKBASE+64, 32); // to be corrected : address of ch 1, length
    }
    return 2;
}

void channelRead(const u8 channelNum, channelInfo* vfo)
{
    eepromRead((u8*)vfo, CHANNELBANKBASE+(channelNum<<5), 32); // corrected : address
}

void channelSaveActive(void)
{
    channelSave(settings.activeVfo);
}

void channelActiveToMenu(void)
{
    bandwidthMenuVal = ACTIVE_VFO.bits.bandwidth;
    modulationMenuVal = ACTIVE_VFO.bits.modulation;
    busyLockMenuVal = ACTIVE_VFO.bits.busyLock;
    pttIDMenuVal = ACTIVE_VFO.bits.pttID;
    txPowerMenuVal = ACTIVE_VFO.txPower;
    txMaxPowerMenuVal = planPower(&plans[ACTIVE_VFOX.txplan], 255); //  ACTIVE_VFOX.txPower;
    rxSubToneMenuVal = ACTIVE_VFO.rxSubTone.value;
    txSubToneMenuVal = ACTIVE_VFO.txSubTone.value;    
}

void channelActiveFromMenu(void)
{
    ACTIVE_VFO.bits.bandwidth = bandwidthMenuVal;
    ACTIVE_VFO.bits.modulation = modulationMenuVal;
    ACTIVE_VFO.bits.busyLock = busyLockMenuVal;
    ACTIVE_VFO.bits.pttID = pttIDMenuVal;
    ACTIVE_VFO.txPower = txPowerMenuVal;
    ACTIVE_VFO.rxSubTone.value = rxSubToneMenuVal;
    ACTIVE_VFO.txSubTone.value = txSubToneMenuVal;
}


void channelSave(const u8 vfoPosition)
{
    u32 addr;
    channelInfo* vfo = &VFO[vfoPosition];
    channelXtra* vfox = &VFOX[vfoPosition];
    addr = CHANNELBANKBASE+((vfox->number)<<5);
    eeprom_Write((u8*)vfo, addr, 32); // to be corrected : address, length
}

void channelLoad(const u8 channelNum, const u8 vfoPosition)
{
    channelInfo* vfo;
    channelXtra* vfox;
    vfo = &VFO[vfoPosition];
    channelRead(channelNum, vfo);
    if(clampFreq(&(vfo->rxFreq.value)))
    {
        memFill(vfo, 0, 32);
        vfo->rxFreq.value = defaultFreq;
        vfo->txFreq.value = defaultFreq;
    }
    memCpySpc(vfo->name, vfo->name, 11);
    vfox = &VFOX[vfoPosition];
    vfox->number = channelNum;
    validateVfo(vfoPosition);
    displayVfoRefresh(vfoPosition, !loopMode);
}

void channelGroupLabel(const u8 group)
{
    if(group)
    {
        eepromRead((u8*)TXTEDIT, GROUPLABELBASE + (u32)((group-1)*6), 6); // corrected : address
        memCpySpc(TXTEDIT, TXT, 5);      
        TXT[6]=0;
        if(TXT[0]==32 || TXT[0]==0)
        {
            memCpy2(GRPn, TXT, 6);
            TXT[4]=groupLetter(group);
        }
    }
    else
        memCpy2(&SPACE5, TXT, 6);
}