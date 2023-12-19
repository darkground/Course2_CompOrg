#include <dos.h>
#include <conio.h>

int gchr() {
	union REGS r;

	r.h.ah = 0x00;
	int86(0x16, &r, &r);

	return r.h.ah;
}

void interrupt (*prevInterrupt)(...);

void interrupt newInterrupt(...) {
    unsigned char key = gchr()
    unsigned char randomKey = rand() % 256;
    
    if (key >= 32 && key < 127) {
        printf("%c", randomKey);
    } else {
        _chain_intr(prevInterrupt);
    }
}

void main() {
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