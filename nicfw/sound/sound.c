
void soundBeep(u8 duration, u32 waveLength)
{
    if(xmitActive) return; // don't sound key beeps while transmitting
    if(!POW2822_) duration+=3;
    POW_2822(1);
    beepWaveLength = waveLength << 1;
    beepDuration = duration;
}

/*
void soundBeep2(const u8 duration, u32 waveLength)
{    
    if(xmitActive) return; // don't sound key beeps while transmitting
    waveLength<<=1; // scale wavelength
    tmrTicks=0; 
    tmrTicks=0; // do it twice to defeat any race condition with the ISR
    bkSetModulation(0, 0); // mute the radio chip
    POW_2822(1); // ensure the audio amplifier is on
    while(tmrTicks < duration) // tmrTicks should increment every 1/60th of a second
    {
        PWM_Pulse(0); // set DAC to low state
        DELAY_WaitUS(waveLength); // pause to create wavelength
        PWM_Pulse(0x640); // set DAC to high state
        DELAY_WaitUS(waveLength); // pause again
    }
    PWM_Reset(); // reset DAC
    bkSetModulation(currentModulation, 1); // restore radio chip audio
}
*/

void soundBlip(const u8 duration, const u16 waveLength, const u8 twice)
{
    if(settings.keyTones)
    {
        soundBeep(duration, waveLength);
        if(twice)
        {
            delay(100);
            soundBeep(duration, waveLength);
        }
    }
}

void differentialKeyTone(const u8 duration, const u8 key)
{
    if((duration==12 || settings.keyTones) && key!=KEY_NONE)
    {
        
        if(settings.keyTones==3 && key<10 && !fmtActive && duration!=10)
        {
            voicePlay(key + 70);
        }
        else
        {
            soundBeep(duration, (settings.keyTones==1) ? 100 : ((15-key)<<3)+100);
        }
    }
}