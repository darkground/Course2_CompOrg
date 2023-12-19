#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void interrupt (*prevInterrupt)(...);

void interrupt newInterrupt(...) {
    unsigned char keyState = inp(0x60);
    if ((keyState & 128) == 0) {
        unsigned char k = rand() % 95 + 32;
        
        putch(k);
    }
    (*prevInterrupt)();
}

void main() {
    srand(time(NULL));

    prevInterrupt = _dos_getvect(0x09);
    _dos_setvect(0x09, newInterrupt);

    while (1) {
        if (kbhit() && getch() == 27) {
            _dos_setvect(0x09, prevInterrupt);
            return;
        }
    }    
}