

void settingsLoad(void)
{
    eepromRead((u8*)&settings, SETTINGSBASE, 2); // corrected : address
    if(settings.magic==SETTINGSMAGIC)
    {
        eepromRead((u8*)&settings, SETTINGSBASE, sizeof(settings)); // corrected : address
        eepromRead((u8*)&settings2, SETTINGSBASE, sizeof(settings)); // corrected : address
    }
}

void settingsWrite(void)
{
    u8 i, diff;
    diff=0;
    for(i=0; i!=sizeof(settings); i++)
    {
        if(  ((u8*)&settings)[i] != ((u8*)&settings2)[i]   )
        {
            diff=1;
        }
        ((u8*)&settings2)[i] = ((u8*)&settings)[i];
    }
    if(diff)
    {
        settings.magic=SETTINGSMAGIC;
        eeprom_Write((u8*)&settings, SETTINGSBASE, sizeof(settings)); // corrected : address
    }
    calibSave();
}
