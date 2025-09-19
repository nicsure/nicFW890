
const u16 dtmfGetSpeed(void)
{
    return (((u16)(20-settings.dtmfSpeed))<<5)+100;
}

void dtmfPlay(const u8 digit)
{
    bkPlayTone(dtmfTableA[digit], dtmfTableB[digit]);
}

const u8 dtmfExtractDigit(const dtmfSequence* sequence, const u8 position)
{
    u8 byt = ((u8*)sequence)[position>>1];
    if(position&1) byt>>=4;
    return byt & 0xf;
}

void dtmfReplaceDigit(const dtmfSequence* sequence, const u8 position, const u8 newDigit)
{
    u8* bytePointer = &(((u8*)sequence)[position>>1]);
    if(position&1)
    {
        *bytePointer &= 0xf;
        *bytePointer |= newDigit<<4;
    }
    else
    {
        *bytePointer &= 0xf0;
        *bytePointer |= newDigit;
    }
}

void dtmfSeqToString(const dtmfSequence* sequence, const char fill)
{
    u8 i;
    u8 len;
    u8 digit;
    u8* digitPointer;
    len = dtmfExtractDigit(sequence, 0);
    if(len>9) len = 0;
    memFill(TXTEDIT, 9, fill);
    TXTEDIT[9] = 0;

    for(i=0; i!=len; i++)
    {
        digitPointer = (u8*)&TXTEDIT[i];
        digit = dtmfExtractDigit(sequence, i+1);
        if(digit<10) *digitPointer = digit+48; else
        if(digit==14) *digitPointer = '*'; else
        if(digit==15) *digitPointer = '#'; else
            *digitPointer = digit+55;
    }
}

void dtmfSeqFromString(void)
{
    u8* digitPointer;
    u8 i;
    u8 digit;
    i = 0;
    for(; 1; i++)
    {
        digitPointer = (u8*)&TXTEDIT[i];        
        if(*digitPointer>='0' && *digitPointer<='9') digit=*digitPointer-48; else
        if(*digitPointer>='A' && *digitPointer<='D') digit=*digitPointer-55; else
        if(*digitPointer=='*') digit=14; else
        if(*digitPointer=='#') digit=15; else break;
        dtmfReplaceDigit(&manualSeq, i+1, digit);
        if(i==9) break;      
    }
    dtmfReplaceDigit(&manualSeq, 0, i);
}



void dtmfPlaySeq(const dtmfSequence* sequence, const u8 id)
{
    u8 len;
    u8 i;
    len = dtmfExtractDigit(sequence, 0);
    if(!len || len>9) return;
    DELAY_WaitMS(id?200:2000);    
    for(i=0; i!=len; i++)
    {
        dtmfPlay(dtmfExtractDigit(sequence, i+1));
        DELAY_WaitMS(id?120:dtmfGetSpeed());
        bkStopTone();
        DELAY_WaitMS(id?60:(dtmfGetSpeed()>>1));
    }
}

const u32 dtmfPresetSeqAddress(const u8 seqNum)
{
    return DTMFPRESETBASE + ((u32)seqNum * 12); // corrected : address
}

const u32 dtmfPresetNameAddress(const u8 seqNum)
{
    return dtmfPresetSeqAddress(seqNum) + 5;
}

void dtmfGetPresetName(const u8 seqNum)
{
    eepromRead((u8*)TXT, dtmfPresetNameAddress(seqNum), 7);
    TXT[8]=0;
}


void dtmfGetPresetSeq(const u8 seqNum)
{
    eepromRead((u8*)&manualSeq, dtmfPresetSeqAddress(seqNum), 5);
}

const u8 dtmfSeek(u8 dir)
{
    u8 i;
    for(i=0; i!=20; i++)
    {
        lastDtmfPreset+=dir;
        if(dir==0) dir=1;
        if(lastDtmfPreset==20) lastDtmfPreset=0;
        if(lastDtmfPreset==0xff) lastDtmfPreset=19;
        dtmfGetPresetSeq(lastDtmfPreset);
        if(manualSeq.first.length && manualSeq.first.length<10)
        {
            dtmfGetPresetName(lastDtmfPreset);
            return 1;
        }
    }
    return 0;
}


void dtmfPlayPTTID(void)
{
    dtmfGetPresetSeq(19);
    dtmfPlaySeq(&manualSeq, 1);
}