

void eepromWriteMode(void);
const u8 eepromStatus(void);
void eepromWait(void);
void eepromSendAddr(const u32 addr);
void eepromInit(void);
void eeprom_Burn(const u8 *data, u32 addr);
void eepromRead(u8* data, const u32 addr, const u16 size);
//void eepromWrite(const u8 *data, const u32 addr, const u8 size);
void eepromReadToDisplay(const u32 addr, const u16 size);
//void eepromOverlay(const u8 *data, const u32 addr, const u8 size);
void eeprom_Write(const u8 *data, const u32 addr, u16 size);
void eeprom_Commit(void);
//void eepromCheckJournal(void);
void eepromReadUnsafe(u8* data, const u32 addr, const u16 size);

