#include <stdio.h>
#include <dos.h>
#include <conio.h>

const int x1 = 25;
const int y1 = 8;
const int x2 = 55;
const int y2 = 18;

void drawWindow() {
    window (x1-1, y1-1, x2+1, y2+2);
    textbackground(BLACK);
    clrscr();
    textcolor(WHITE);

    for (int i = 0; i < x2 - x1 + 3; i++)
		cprintf("o");

	for(int j = 0; j < (y2 - y1 + 1); j++)
	{
		cprintf("o");
	    for(int k = 0; k < (x2 - x1 + 1); k++)
			cprintf(" ");

		cprintf("o");
	};

	for (int p = 0; p < x2 - x1 + 3; p++)
		cprintf("o");

    window(x1,y1,x2,y2);
    textbackground(BLACK);
    clrscr();
    textcolor(WHITE);
}

int gchr() {
	union REGS r;

	r.h.ah = 0x00;
	int86(0x16, &r, &r);

	return r.h.ah == 0x00 ? r.h.al : r.h.ah;
}

int move(int& x, int& y, int& state, int freplace = 0)
{
    if (kbhit()) {
		int k = freplace ? gchr() : getch();
		switch (k) {
			case 77:
				x++;
				break;
			case 75:
				x--;
				break;
			case 72:
				y--;
				break;
			case 80:
				y++;
				break;
			case 1:
			case 27:
				state = 0;
				break;
		}
		return 1;
    }
    return 0;
}

void main() {
    clrscr();
    textbackground(BLACK);

	int state = 1;
	int x = (x2 - x1) / 2;
	int y = (y2 - y1) / 2;

    drawWindow();
    _setcursortype(_NOCURSOR);

    gotoxy(x,y);
    cprintf("*");

    while (state) {
		if (move(x, y, state, 1))
		{
			if (x == 0)
				x = x2 - x1 + 1;
			if (x == x2 - x1 + 2)
				x = 1;
			if (y == 0)
				y = y2 - y1 + 1;
			if (y == y2 - y1 + 2)
				y = 1;
			
			clrscr();
			gotoxy(x,y);
			cprintf("*");
		}
    }
}

