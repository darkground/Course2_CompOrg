#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <locale.h>

int x1 = 25;
int y1 = 8;
int x2 = 55;
int y2 = 18;
int t = 150;
int s = 1;

const int direction = 7; // 6 Up 7 Down

const char COLORS_AS_TEXT[][16] = {
    "Чёрный",
    "Синий",
    "Зелёный",
    "Бирюзовый",
    "Красный",
    "Пурпурный",
    "Коричневый",
    "Св. серый",
    "Тём. серый",
    "Св. синий",
    "Св. зелёный",
    "Св. бирюзовый",
    "Св. красный",
    "Св. пурпурный",
    "Жёлтый",
    "Белый"
};

void scroll(int direction, char l_row, char l_col, char r_row, char r_col, char attr) {
	union REGS r;
	if (direction)
	{ r.h.al = 1; r.h.ah = direction; }
	else
	{ r.h.al = 0; r.h.ah = 6; }
	r.h.ch = l_row; r.h.cl = l_col; r.h.dh = r_row;
	r.h.dl = r_col; r.h.bh = attr;
	int86(0x10,&r,&r);
}

void main()
{
    enum SCREEN_COLORS {
	/* Black         */ BLACK = 0,
	/* Blue          */ BLUE = 1,
	/* Green         */ GREEN = 2,
	/* Cyan          */ CYAN = 3,
	/* Red           */ RED = 4,
	/* Magenta       */ MAGENTA = 5,
	/* Brown         */ BROWN = 6,
	/* Light Gray    */ LIGHTGRAY = 7,
	/* Dark Gray     */ DARKGRAY = 8,
	/* Light Blue    */ LIGHTBLUE = 9,
	/* Light Green   */ LIGHTGREEN = 10,
	/* Light Cyan    */ LIGHTCYAN = 11,
	/* Light Red     */ LIGHTRED = 12,
	/* Light Magenta */ LIGHTMAGENTA = 13,
	/* Yellow        */ YELLOW = 14,
	/* White         */ WHITE = 15
    };
	SCREEN_COLORS background;
	SCREEN_COLORS text;

    /* Initialize window for textcolor(), textbackground(), textattr() */
	window(x1, y1, x2, y2);
	for (int i = 0; i < 16; i++) {
		background = SCREEN_COLORS(i);
		/* Set text background */
		textbackground(background);
		for (int j = 0; j < 16; j++) {
			text = SCREEN_COLORS(j);
			/* Set text foreground */
			textcolor(text);
			/* Make empty line */
			for (int k = 1; k < s; k++) {
				insline();
				if (direction == 7)
					cprintf("\n");
			}
			insline();
			cprintf("T: %s B: %d\r", COLORS_AS_TEXT[text], background);
			if (direction == 7)
				cprintf("\n");

			delay(t);
			scroll(direction, x1 - 1, y1 - 1, x2 - 1, y2 - 1, background);
		}
	}
	getch();
}