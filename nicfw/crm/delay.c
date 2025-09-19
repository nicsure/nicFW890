
static uint32_t gCyclesPer100NanoSec;
static uint32_t gCyclesPerMicroSec;
static uint32_t gCyclesPerMilliSec;

void DELAY_Init(void)
{
	systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
	gCyclesPer100NanoSec = gSystemCoreClock / 10000000;
	gCyclesPerMicroSec = gSystemCoreClock /   1000000;
	gCyclesPerMilliSec = (gSystemCoreClock / 1000000) * 1000;
}

void DELAY_Wait100NS(uint32_t Delay)
{
	uint32_t Control;

	SysTick->LOAD = gCyclesPer100NanoSec * Delay;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do {
		if(feedDimmer) {
			HandleLCDDimming();
		}
		Control = SysTick->CTRL;
	} while (Control & SysTick_CTRL_ENABLE_Msk && (Control & SysTick_CTRL_COUNTFLAG_Msk) == 0);

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0;
}

void DELAY_WaitUS(uint32_t Delay)
{
	uint32_t Control;

	SysTick->LOAD = gCyclesPerMicroSec * Delay;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do {
		if(feedDimmer) {
			HandleLCDDimming();
		}
		Control = SysTick->CTRL;
	} while (Control & SysTick_CTRL_ENABLE_Msk && (Control & SysTick_CTRL_COUNTFLAG_Msk) == 0);

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0;
}

static void WaitMS(uint16_t Delay)
{
	uint32_t Control;

	while (1) {
		if (Delay == 0) {
			return;
		}
		if (Delay > 50) {
			SysTick->LOAD = gCyclesPerMilliSec * 50;
			Delay -= 50;
		} else {
			SysTick->LOAD = gCyclesPerMilliSec * Delay;
			Delay = 0;
		}
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

		do {
			//HandleLCDDimming();
			Control = SysTick->CTRL;
		} while (Control & SysTick_CTRL_ENABLE_Msk && (Control & SysTick_CTRL_COUNTFLAG_Msk) == 0);

		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
		SysTick->VAL = 0;
	}
}

void DELAY_WaitMS(uint16_t Delay)
{
	uint16_t i;

	for (i = 0; i < (Delay / 500); i++) {
		WaitMS(500);
		DELAY_WaitUS(13000);
	}
	WaitMS(Delay % 500);
}
