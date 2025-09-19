

 void gpio_bits_flip(gpio_type *gpio, uint16_t pins)
 {
     if (gpio_output_data_bit_read(gpio, pins)) {
         gpio_bits_reset(gpio, pins);
     } else {
         gpio_bits_set(gpio, pins);
     }
 }
 
 void gpio_default_para_init_ex(gpio_init_type *init)
 {
     init->gpio_pins  = GPIO_PINS_ALL;
     init->gpio_mode = GPIO_MODE_INPUT;
     init->gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
     init->gpio_pull = GPIO_PULL_NONE;
     init->gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
 }
 
 void gpio_bits_set(gpio_type *gpio_x, uint16_t pins)
 {
     gpio_x->scr = pins;
 }
 
 void gpio_bits_reset(gpio_type *gpio_x, uint16_t pins)
 {
     gpio_x->clr = pins;
 }
 
 flag_status gpio_input_data_bit_read(gpio_type *gpio_x, uint16_t pins)
 {
     flag_status status = RESET;
 
     if (pins != (pins & gpio_x->idt)) {
         status = RESET;
     } else {
         status = SET;
     }
 
     return status;
 }
 
 void gpio_init(gpio_type *gpio_x, gpio_init_type *gpio_init_struct)
 {
     uint16_t pinx_value, pin_index = 0;
 
     pinx_value = (uint16_t)gpio_init_struct->gpio_pins;
 
     while (pinx_value > 0) {
         if (pinx_value & 0x01) {
             gpio_x->cfgr  &= (uint32_t)~(0x03 << (pin_index * 2));
             gpio_x->cfgr  |= (uint32_t)(gpio_init_struct->gpio_mode << (pin_index * 2));
 
             gpio_x->omode &= (uint32_t)~(0x01 << (pin_index));
             gpio_x->omode |= (uint32_t)(gpio_init_struct->gpio_out_type << (pin_index));
 
             gpio_x->odrvr &= (uint32_t)~(0x03 << (pin_index * 2));
             gpio_x->odrvr |= (uint32_t)(gpio_init_struct->gpio_drive_strength << (pin_index * 2));
 
             gpio_x->pull  &= (uint32_t)~(0x03 << (pin_index * 2));
             gpio_x->pull  |= (uint32_t)(gpio_init_struct->gpio_pull << (pin_index * 2));
         }
         pinx_value >>= 1;
         pin_index++;
     }
 }
 
 void gpio_pin_mux_config(gpio_type *gpio_x, gpio_pins_source_type gpio_pin_source, gpio_mux_sel_type gpio_mux)
 {
     uint32_t temp = 0x00;
     uint32_t temp_2 = 0x00;
 
     temp = ((uint32_t)(gpio_mux) << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
     if (gpio_pin_source >> 0x03) {
         gpio_x->muxh &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
         temp_2 = gpio_x->muxh | temp;
         gpio_x->muxh = temp_2;
     } else {
         gpio_x->muxl &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_pin_source & (uint32_t)0x07) * 4));
         temp_2 = gpio_x->muxl | temp;
         gpio_x->muxl = temp_2;
     }
 }
 
 flag_status gpio_output_data_bit_read(gpio_type *gpio_x, uint16_t pins)
 {
     flag_status status = RESET;
 
     if ((gpio_x->odt & pins) != RESET) {
         status = SET;
     } else {
         status = RESET;
     }
 
     return status;
 }
 
static void InitGPIO(void)
{
	gpio_init_type init;

	// GPIO A
	gpio_default_para_init_ex(&init);
	init.gpio_pins = BOARD_GPIOA_LCD_SCL | BOARD_GPIOA_SPEAKER | BOARD_GPIOA_LCD_SDA | BOARD_GPIOA_LCD_RESX | BOARD_GPIOA_KEY_COL3;
	init.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
	init.gpio_mode = GPIO_MODE_OUTPUT;

	gpio_init(GPIOA, &init);

	gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_RESX);
	gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_SDA);
	gpio_bits_reset(GPIOA, BOARD_GPIOA_SPEAKER);
	gpio_bits_reset(GPIOA, BOARD_GPIOA_LCD_SCL);

	// GPIO B
	init.gpio_pins = 0
		// SPI Flash
		| BOARD_GPIOB_SF_CS
		| BOARD_GPIOB_SF_MISO
		| BOARD_GPIOB_SF_CLK
		// BK4819
		| BOARD_GPIOB_BK4819_SDA
		| BOARD_GPIOB_BK4819_CS
		| BOARD_GPIOB_BK4819_SCL
		//
		| BOARD_GPIOB_TX_BIAS_LDO | BOARD_GPIOB_TX_AMP_SEL | BOARD_GPIOB_KEY_COL2 | BOARD_GPIOB_KEY_COL1 | BOARD_GPIOB_KEY_COL0;

	gpio_init(GPIOB, &init);

	gpio_bits_reset(GPIOB, BOARD_GPIOB_TX_AMP_SEL);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_TX_BIAS_LDO);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SCL);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_CS);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_BK4819_SDA);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_CLK);
	gpio_bits_reset(GPIOB, BOARD_GPIOB_SF_MISO);

	// GPIO C
	init.gpio_pins = BOARD_GPIOC_BK1080_SEN | BOARD_GPIOC_BK1080_SCL | BOARD_GPIOC_LCD_CS;

	gpio_init(GPIOC, &init);

	gpio_bits_reset(GPIOC, BOARD_GPIOC_LCD_CS);
	gpio_bits_reset(GPIOC, BOARD_GPIOC_BK1080_SCL);
	gpio_bits_set(GPIOC, BOARD_GPIOC_BK1080_SEN);

	// GPIO F
	init.gpio_pins = GPIO_PINS_0 | BOARD_GPIOF_LCD_DCX;

	gpio_init(GPIOF, &init);

	gpio_bits_reset(GPIOF, BOARD_GPIOF_LCD_DCX);
	gpio_bits_reset(GPIOF, GPIO_PINS_0);

	// GPIO A
	init.gpio_pins = BOARD_GPIOA_KEY_ROW3 | BOARD_GPIOA_KEY_ROW0 | BOARD_GPIOA_KEY_SIDE2;
	init.gpio_mode = GPIO_MODE_INPUT;
	init.gpio_pull = GPIO_PULL_UP;

	gpio_init(GPIOA, &init);

	init.gpio_pins = BOARD_GPIOA_SF_MOSI;
	init.gpio_pull = GPIO_PULL_NONE;

	gpio_init(GPIOA, &init);

	// GPIO B
	init.gpio_pins = BOARD_GPIOB_KEY_ROW1 | BOARD_GPIOB_KEY_ROW2;
	init.gpio_mode = GPIO_MODE_INPUT;
	init.gpio_pull = GPIO_PULL_UP;

	gpio_init(GPIOB, &init);

	// GPIO F
	init.gpio_pins = BOARD_GPIOF_KEY_SIDE1;

	gpio_init(GPIOF, &init);

	// GPIO B
	init.gpio_pins = BOARD_GPIOB_USART1_TX;
	init.gpio_mode = GPIO_MODE_MUX;
	init.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	init.gpio_pull = GPIO_PULL_NONE;

	gpio_init(GPIOB, &init);

	init.gpio_pins = BOARD_GPIOB_KEY_PTT;
	init.gpio_mode = GPIO_MODE_MUX;
	init.gpio_pull = GPIO_PULL_UP;

	gpio_init(GPIOB, &init);

	// PB6 -> USART1_TX
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE6, GPIO_MUX_0);
	// PB7 -> USART1_RX
	gpio_pin_mux_config(GPIOB, GPIO_PINS_SOURCE7, GPIO_MUX_0);

	init.gpio_pins = BOARD_GPIOB_BATTERY;
	init.gpio_mode = GPIO_MODE_ANALOG;

	gpio_init(GPIOB, &init);

	// GPIO A
	init.gpio_pins = GPIO_PINS_2;
	init.gpio_mode = GPIO_MODE_ANALOG;

	gpio_init(GPIOA, &init);

	init.gpio_pins = BOARD_GPIOA_AF_OUT;
	init.gpio_mode = GPIO_MODE_MUX;

	gpio_init(GPIOA, &init);

	// PA6 -> TMR3_CH1
	gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE6, GPIO_MUX_1);

	gpio_bits_set(GPIOA, BOARD_GPIOA_KEY_COL3);
	gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL0);
	gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL1);
	gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL2);
}

void POW_2822(const u8 on)
{
    if(on)
    {
		gpio_bits_set(GPIOA, BOARD_GPIOA_SPEAKER);
		if(!POW2822_)
			PWM_Reset();
	}
    else
    {
		gpio_bits_reset(GPIOA, BOARD_GPIOA_SPEAKER);
		voiceWait();
	}
    POW2822_ = on;
}

void MICROPHONE(const u8 on)
{
	if(on)
		gpio_bits_set(GPIOA, BOARD_GPIOA_AF_OUT);
	else
		gpio_bits_reset(GPIOA, BOARD_GPIOA_AF_OUT);
}