void DELAY_Init(void);
void DELAY_WaitUS(uint32_t Delay);
void DELAY_WaitMS(uint16_t Delay);
void DELAY_Wait100NS(uint32_t Delay);

#define delay(x) DELAY_WaitMS(x)