#include <dos.h>
#include <conio.h>

void interrupt (*prevInterrupt)(...);

void interrupt newInterrupt(...) {
    unsigned char key = _bios_keybrd(_KEYBRD_READ);
    unsigned char randomKey = rand() % 256;
    
    if (key >= 32 && key < 127) {
        _AH = 0;
        _AL = randomKey;
        _interrupt(0x21);
    } else {
        _chain_intr(prevInterrupt);
    }
}

int main() {
    srand(time(NULL));

    prevInterrupt = _dos_getvect(0x09);
    _dos_setvect(0x09, newInterrupt);

    while (1) {
        if (kbhit()) {
            unsigned char ch = getch();
            if (ch == 27)
                break;
        }
    }

    _dos_setvect(0x09, prevInterrupt);
}