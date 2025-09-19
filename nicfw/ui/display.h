void displayVfoRefresh(const u8 vfoNumber, const u8 drawBG);
void displayFreq(const u32* freq, const u8 x, const u8 y, const u16 col, u8 decimals, const u8 dp) ;
void displayVfo(const u8 vfoNumber, const u8 drawBG);
void displayDrawMeter(const u8 sig, const u8 mode);
void displayDrawExNoise(const u8 value, const u8 txMod);
void displayToneMonitor(void);
const u8 flagsYPOS(void);
void displayBlankSBarDPTT(void);
void displayRefreshFull(void);
void displayRefresh(const u8 drawBG);
void displayRefreshGeneral(void);
void displayVfoRefreshActiveNoDrawBG(void);
void displayVfoRefreshActiveDrawBG(void);
const char* getModName(const u8 modulation);
const u8 displayVfoPos(const u8 vfoNumber);
const u8 DIS(const u8 val);




