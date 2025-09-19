static void usart_reset_ex(usart_type *uart, uint32_t baudrate)
{
	crm_clocks_freq_type info;
	uint32_t high, low;

	uart->ctrl2_bit.stopbn = USART_STOP_1_BIT;
	uart->ctrl1_bit.ren = TRUE;
	uart->ctrl1_bit.ten = TRUE;
	uart->ctrl1_bit.dbn = USART_DATA_8BITS;
	uart->ctrl1_bit.psel = FALSE;
	uart->ctrl1_bit.pen = FALSE;
	uart->ctrl3_bit.rtsen = FALSE;
	uart->ctrl3_bit.ctsen = FALSE;

	crm_clocks_freq_get(&info);

	if (uart == USART1) {
		info.apb2_freq = info.apb1_freq;
	}

	baudrate = (uint32_t)((((uint64_t)info.apb2_freq * 1000U) / 16U) / baudrate);
	high = baudrate / 1000U;
	low = (baudrate - (1000U * high)) * 16;
	if ((low % 1000U) < 500U) {
		low /= 1000U;
	} else {
		low = (low / 1000U) + 1;
		if (low >= 16) {
			low = 0;
			high++;
		}
	}
	uart->baudr_bit.div = (high << 4) | low;
}

void HandlerUSART1(void) 
{
    u8 timeout;
    timeout = 0;
    while(1)
    {
        if (USART1->ctrl1_bit.rdbfien && USART1->sts & USART_RDBF_FLAG)
        {
            uartPendingBytes[uartWritePos++] = USART1->dt;
            timeout=200;
        }
        if(timeout)
        {
            timeout--;
            DELAY_WaitUS(30);
        }
        else
            break;
    }
} 

void UART_Tick(void)
{
    while(uartWritePos != uartReadPos)
    {
        protocolProcess(uartPendingBytes[uartReadPos++]);
		uartReset = 5;
    }
}

void UART_Init(uint32_t BaudRate)
{
    pState = 0;
    uartReadPos=0;
    uartWritePos=0;
	usart_reset_ex(USART1, BaudRate);
	PERIPH_REG((uint32_t)USART1, USART_RDBF_INT) |= PERIPH_REG_BIT(USART_RDBF_INT);
	USART1->ctrl1_bit.uen = TRUE;
}

void UART_SendByte(uint8_t Data)
{
	USART1->dt = Data;
	while (!(USART1->sts & USART_TDBE_FLAG)) { }
}

void UART_Send(const void *pBuffer, uint8_t Size)
{
	const uint8_t *pBytes = (const uint8_t *)pBuffer;
	uint8_t i;

	for (i = 0; i < Size; i++) {
		UART_SendByte(pBytes[i]);
	}
}
