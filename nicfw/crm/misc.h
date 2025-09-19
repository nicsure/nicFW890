void systick_clock_source_config(systick_clock_source_type source);
void nvic_irq_enable(IRQn_Type irqn, uint32_t preempt_priority, uint32_t sub_priority);
void nvic_irq_disable(IRQn_Type irqn);
