extern uint32_t gSystemCoreClock;

void CRM_Init(void);
void CRM_GetCoreClock(void);
void CRM_InitPeripherals(void);

void crm_adc_clock_div_set(crm_adc_div_type div_value);
crm_sclk_type crm_sysclk_switch_status_get(void);
void crm_clocks_freq_get(crm_clocks_freq_type *clocks_struct);
void crm_periph_clock_enable(crm_periph_clock_type value, confirm_state new_state);
void crm_periph_reset(crm_periph_reset_type value, confirm_state new_state);
