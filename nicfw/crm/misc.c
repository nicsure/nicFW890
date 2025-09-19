void systick_clock_source_config(systick_clock_source_type source)
{
	if (source == SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV) {
		SysTick->CTRL |= SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV;
	} else {
		SysTick->CTRL &= ~(uint32_t)SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV;
	}
}

void nvic_irq_enable(IRQn_Type irqn, uint32_t preempt_priority, uint32_t sub_priority)
{
	uint32_t temp_priority = 0;

	/* encode priority */
	temp_priority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), preempt_priority, sub_priority);
	/* set priority */
	NVIC_SetPriority(irqn, temp_priority);
	/* enable irqn */
	NVIC_EnableIRQ(irqn);
}

void nvic_irq_disable(IRQn_Type irqn)
{
	NVIC_DisableIRQ(irqn);
}
