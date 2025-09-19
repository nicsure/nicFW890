const u16 dtmfTableA[] = {
    941,
    697,
    697,
    697,
    770,
    770,
    770,
    852,
    852,
    852,
    697,
    770,
    852,
    941,
    941,
    941
};

const u16 dtmfTableB[] = {
    1336,
    1209,
    1336,
    1477,
    1209,
    1336,
    1477,
    1209,
    1336,
    1477,
    1633,
    1633,
    1633,
    1633,
    1209,
    1477
};       



void dtmfPlaySeq(const dtmfSequence* sequence, const u8 id);
void dtmfPlayPTTID(void);
void dtmfPlay(const u8 digit);



