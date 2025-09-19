static void usart_reset_ex(usart_type *uart, uint32_t baudrate);
void UART_Init(uint32_t BaudRate);
void UART_SendByte(uint8_t Data);
void UART_Send(const void *pBuffer, uint8_t Size);
void UART_Tick(void);


