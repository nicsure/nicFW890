void memCpy2(const void* src, void* dest, u8 length)
{
    while(length--)
    {
        ((u8*)dest)[length]=((u8*)src)[length];
    }
}

void memCpySpc(const char* src, char* dest, u8 length)
{
    char c;
    dest[length--]=0;
    while(length!=0xff)
    {
        c = src[length];
        if(c<32 || c>126) c=32;
        dest[length] = c;
        length--;
    }
}

void memFill(const void* target, u8 length, const u8 value)
{
    while(length--)
        ((u8*)target)[length] = value;
}

void memBlank(const void* target, u8 length)
{
    memFill(target, length, 0);
}

