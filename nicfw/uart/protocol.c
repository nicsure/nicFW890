
void protocolIdle(const u8 b)
{
    switch(b)
    {
        case 1:
        case 2: // pings
            UART_SendByte(b);
            break;
        case 0x10: // reak 4k
        case 0x20: // write 4k
        case 0x30: // read
        case 0x40: // write
        case 0x7f: // change baud
            pAddr = 0;
            pState = b;
            break;
        case 0x50: // reset
            eeprom_Commit();
            NVIC_SystemReset();
            break;
    }
}

void protocolProcess(const u8 b)
{
    u8 i, j, byt;
    switch(pState)
    {
        case 0: // IDLE
            protocolIdle(b);
            return;
        case 0x7f: // change baud // byte 0
            customBaud.bytes.byte0 = b;
            pState--;
            return;
        case 0x7e: // change baud // byte 1
            customBaud.bytes.byte1 = b;
            pState--;
            return;
        case 0x7d: // change baud // byte 2
            customBaud.bytes.byte2 = b;
            pState--;
            return;
        case 0x7c: // change baud // byte 3
            customBaud.bytes.byte3 = b;
            UART_Init(customBaud.value);
            return;
        case 0x30: // READ low addr byte
        case 0x40: // WRITE low addr byte
            C32(pAddr)->bytes.byte0 = b;
            break;
        case 0x31: // READ high addr byte
        case 0x41: // WRITE high addr byte
            C32(pAddr)->bytes.byte1 = b;
            pAddr <<= 7;
            pCS=0;
            if(pState==0x31) // READ specifically
            {
                UART_SendByte(0x30);
                eepromRead(eepromBuffer, pAddr, 128);
                for(i=0; i!=128; i++)
                {
                    byt = eepromBuffer[i];
                    pCS += byt;
                    UART_SendByte(byt);
                }
                UART_SendByte(pCS);
                pState=0;
                return;
            }
            else
            {
                pCnt=0;
                break;
            }
        case 0x42: // WRITE data
            pCS+=b;
            eepromBuffer[pCnt++] = b;
            if(pCnt==128) break;
            return;
        case 0x43: // WRITE checksum
            if(b==pCS)
            {
                eeprom_Write(eepromBuffer, pAddr, 128);
                UART_SendByte(0x40);
            }
            else
                UART_SendByte(0x41);
            pState=0;
            return;

        case 0x10: // READ low addr byte 4k
            C32(pAddr)->bytes.byte0 = b;
            break;
        case 0x11: // READ high addr byte 4k
            C32(pAddr)->bytes.byte1 = b;
            pAddr <<= 12;
            pCS=0;
            UART_SendByte(0x10);
            for(j=0; j!=32; j++)
            {
                eepromRead(eepromBuffer, pAddr, 128);
                for(i=0; i!=128; i++)
                {
                    byt = eepromBuffer[i];
                    pCS += byt;
                    UART_SendByte(byt);
                }
                pAddr += 128;
            }
            UART_SendByte(pCS);
            pState=0;
            return;
    }
    pState++;
}

