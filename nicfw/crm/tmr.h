enum {
	TMR_CC_CHANNEL_MAPPED_OUTPUT = 0x00,
};

typedef struct {
	uint32_t period;
	uint16_t division;
	uint8_t repetition;
	tmr_count_mode_type count_mode;
	tmr_clock_division_type clock_division;
} tmr_para_init_ex0_type;

typedef struct {
	u8 ch1_enable;
	tmr_output_polarity_type ch1_polarity;
	u8 ch1_idle_output_state;

	u8 ch1_comp_enable;
	tmr_output_polarity_type ch1_comp_polarity;
	u8 ch1_comp_idle_output_state;

	tmr_input_direction_mapped_type ch1_config;

	tmr_output_control_mode_type ch1_output_control_mode;
	uint16_t ch1_digital_filter;
} tmr_para_init_ex1_type;

void tmr_para_init_ex0(tmr_para_init_ex0_type *init);
void tmr_para_init_ex1(tmr_para_init_ex1_type *init);

void tmr_reset_ex0(tmr_type *tmr, const tmr_para_init_ex0_type *init);
void tmr_reset_ex1(tmr_type *tmr, const tmr_para_init_ex1_type *init);

void tmr_output_channel_switch_set_ex(tmr_type *tmr, confirm_state new_state);