#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void interrupt (*prevInterrupt)(...);

void interrupt newInterrupt(...) {
    unsigned char keyState = inp(0x60);
    if ((keyState & 128) == 0) {
        unsigned char k = rand() % 256;
        
        putch(k);
    }
    (*oldInt09h)();
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