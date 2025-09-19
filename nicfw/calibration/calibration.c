
const u8 calibPwmToPower(const u8 dutyCycle, const u8 isVhf)
{
    u16 ratio, interp;
    u8 actualDutyCycle;
    u8 peakPower, peakSetting;
    peakSetting = isVhf ? tuning.vhfPeakSetting : tuning.uhfPeakSetting;
    peakPower = isVhf ? tuning.vhfPeakWatts : tuning.uhfPeakWatts;
    actualDutyCycle = peakSetting > dutyCycle ? dutyCycle : peakSetting;
    ratio = ((u16)peakSetting*100) / (u16)peakPower;
    interp = ((u16)actualDutyCycle*100) / ratio;
    return C16(interp)->bytes.lo;
}

static s16 xtalCheck;

void calibLoad(void)
{
    eepromRead((u8*)&tuning, TUNINGBASE, sizeof(tuning)); // corrected : address
    xtalCheck = tuning.xtal671;
}

void calibSave(void)
{
    if(xtalCheck!=tuning.xtal671) {
        eeprom_Write((u8*)&tuning, TUNINGBASE, sizeof(tuning)); // to be corrected : address, length
    }
    xtalCheck = tuning.xtal671;
}