static u8 keyCol;
static KEY keys[19];

const u8 keyCode[] =
{
    KEY_MENU,
    KEY_1,
    KEY_4,
    KEY_7,
    KEY_UP,
    KEY_2,
    KEY_5,
    KEY_8,
    KEY_DOWN,
    KEY_3,
    KEY_6,
    KEY_9,
    KEY_EXIT,
    KEY_STAR,
    KEY_0,
    KEY_HASH,
};


void keypadInit(void)
{
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL0);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL1);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL2);
    gpio_bits_set(GPIOA, BOARD_GPIOA_KEY_COL3);
    keypadShort = KEY_NONE;
    keypadLong = KEY_NONE;
}

const u8 keypadReadRow(void)
{
    u8 i;
    for(i=0; i!=4; i++)
    {
        if (!gpio_input_data_bit_read(GPIOA, BOARD_GPIOA_KEY_ROW0))
            return 0;
        if (!gpio_input_data_bit_read(GPIOB, BOARD_GPIOB_KEY_ROW1))
            return 1;
        if (!gpio_input_data_bit_read(GPIOB, BOARD_GPIOB_KEY_ROW2))
            return 2;
        if (!gpio_input_data_bit_read(GPIOA, BOARD_GPIOA_KEY_ROW3))
            return 3;
        switch (keyCol) 
        {
            case 0:
                gpio_bits_reset(GPIOB, BOARD_GPIOB_KEY_COL0);
                gpio_bits_set(GPIOA, BOARD_GPIOA_KEY_COL3);
                keyCol = 1;
                break;
            case 1:
                gpio_bits_reset(GPIOB, BOARD_GPIOB_KEY_COL1);
                gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL0);
                keyCol = 2;
                break;
            case 2:
                gpio_bits_reset(GPIOB, BOARD_GPIOB_KEY_COL2);
                gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL1);
                keyCol = 3;
                break;
            default: // case 3:
                gpio_bits_reset(GPIOA, BOARD_GPIOA_KEY_COL3);
                gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL2);
                keyCol = 0;
                break;
        }
        DELAY_WaitMS(1);
    }    
    return 0xff;
}

const u8 keypadSinglePress(void)
{
    u8 key;
    differentialKeyTone(3, keypadShort); // to be implemented : sounds
    key = keypadShort;
    keypadShort = KEY_NONE;
    return key;
}

const u8 keypadKeyTick(const u8 key, const u8 pressed, const u8 ticks)
{
    KEY* keyPtr;
    keyPtr = (KEY*)&(keys[key]);    
    if(pressed)
    { 
        if(keyPtr->latch==2)
        {
            if(keypadLong == KEY_NONE)
            {
                if(keypadLong!=key) {
                    differentialKeyTone(10, key);                
                }
                lcdBL(1);
                keypadLong = key;
            }
        }
        else
        {
            keyPtr->tank += ticks;
            if(keyPtr->tank > 3)
            {
                keyPtr->latch = keyPtr->tank > 75 ? 2 : 1;
                if(key==16 ||  key==17)
                    lcdBL(1);
            }
        }
    }
    else
    {
        if(keyPtr->tank > 3) keyPtr->tank = 4;
        if(subCounter(&(keyPtr->tank), ticks) && keyPtr->latch)
        {
            if(keyPtr->latch == 1)
            {
                if(KEY_LED)
                    keypadShort = key;
                lcdBL(1);
            }
            keyPtr->latch = 0;
            keypadLong = KEY_NONE;
        }
    }
    return keyPtr->latch;  
}


void keypadTick(const u8 ticks)
{
    u8 i, key, j;
    key = keypadReadRow();
    if(key!=0xff)
    {
        key = keyCode[key+(keyCol<<2)];
        if(settings.keyLock && lpActionTable[key]!=LP_KEYLOCK && !enteringPin)
        {
            key=0xff;
        }
    }
    keypadPressed=KEY_NONE;
    anyKeyInUse=0;
    for(i=0; i!=16; i++)
    {
        j = keypadKeyTick(i, i==key, ticks);
        anyKeyInUse ^= j;
        if(j) keypadPressed = i;
    }
    if(!settings.keyLock || !settings.pinAction)
    {
        anyKeyInUse ^= keypadKeyTick(16, !gpio_input_data_bit_read(GPIOB, BOARD_GPIOB_KEY_PTT), ticks);
        anyKeyInUse ^= keypadKeyTick(17, !gpio_input_data_bit_read(GPIOF, BOARD_GPIOF_KEY_SIDE1), ticks);
    }
    if(settings.keyLock) return;
    j = keypadKeyTick(18, !gpio_input_data_bit_read(GPIOA, BOARD_GPIOA_KEY_SIDE2), ticks);
    anyKeyInUse ^= j;
    if(j) keypadPressed = 18;
}

const u8 keypadPTTA(void)
{
    return keys[16].latch;
}

const u8 keypadPTTB(void)
{
    return keys[17].latch;
}

const u8 keypadPTT(void)
{
    return keypadPTTB() | keypadPTTA();
}


/*
void keypadInit(void)
{
    keyColPin = BOARD_GPIOB_KEY_COL2;
    keyColType = GPIOB;    
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL0);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL1);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL2);
    gpio_bits_set(GPIOA, BOARD_GPIOA_KEY_COL3);
}

void keypadSetCol(const u8 col)
{
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL0);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL1);
    gpio_bits_set(GPIOB, BOARD_GPIOB_KEY_COL2);
    gpio_bits_set(GPIOA, BOARD_GPIOA_KEY_COL3);  
    switch(col)
    {
        case 0:
            keyColPin = BOARD_GPIOB_KEY_COL0;
            keyColType = GPIOB;
            break;
        case 1:
            keyColPin = BOARD_GPIOB_KEY_COL1;
            keyColType = GPIOB;
            break;
        case 2:
            keyColPin = BOARD_GPIOB_KEY_COL2;
            keyColType = GPIOB;
            break;
        default: // case 3:
            keyColPin = BOARD_GPIOA_KEY_COL3;
            keyColType = GPIOA;
            break;
    }
    gpio_bits_reset(keyColType, keyColPin);
}

const u8 keypadScanRows(void)
{
    u16 keyRowPin;
    gpio_type* keyRowType;
    u8 row;
    for(row=0; row!=4; row++)
    {
        switch(row)
        {
            case 0:
                keyRowPin = BOARD_GPIOA_KEY_ROW0;
                keyRowType = GPIOA;
                break;
            case 1:
                keyRowPin = BOARD_GPIOB_KEY_ROW1;
                keyRowType = GPIOB;
                break;
            case 2:
                keyRowPin = BOARD_GPIOB_KEY_ROW2;
                keyRowType = GPIOB;
                break;
            default: // case 3
                keyRowPin = BOARD_GPIOA_KEY_ROW3;
                keyRowType = GPIOA;
                break;
        }
        if(!gpio_input_data_bit_read(keyRowType, keyRowPin))
            return row;
    }
    return 0xff;
}

void keypadScan(void)
{
    u8 row, col, i;
    for(col=0; col!=4; col++)
    {
        keypadSetCol(col);
        row = keypadScanRows();
        if(row!=0xff)
        {
            row++;
            col++;
            for(i=0; i!=col; i++)
            {
                gpio_bits_set(GPIOA, BOARD_GPIOA_LED_GREEN);
                DELAY_WaitMS(150);
                gpio_bits_reset(GPIOA, BOARD_GPIOA_LED_GREEN);
                DELAY_WaitMS(150);
            }
            DELAY_WaitMS(250);
            for(i=0; i!=row; i++)
            {
                gpio_bits_set(GPIOA, BOARD_GPIOA_LED_RED);
                DELAY_WaitMS(150);
                gpio_bits_reset(GPIOA, BOARD_GPIOA_LED_RED);
                DELAY_WaitMS(150);
            }
            return;
        }
    }
}

void keypadTick(const u8 ticks)
{
    keypadScan();
}

*/