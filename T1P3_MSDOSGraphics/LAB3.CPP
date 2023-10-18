#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>

const float pi = 3.1415;

const float graph_start = 3 * pi / 2;
const float graph_end = 8 * pi;
const float scale = 150;

const float x1 = 20;
const float y1 = 20;
const float x2 = 620;
const float y2 = 450;

float func(float x) {
    return sin(x)*sin(x)*sin(x)+cos(x)*cos(x);
}

int main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TurboC\\BGI");

    int midy = (y1 + y2) / 2;

    float x_incr = (graph_end - graph_start) / (x2 - x1);
    float y_incr = 2 * scale / (y2 - y1);

    int screen_x = x1;
    int screen_y = y1;

    setcolor(WHITE);

    outtextxy(x2 - 2, midy - 10, "X");
    outtextxy(x1 + 4, y1 + 6, "Y");

    setcolor(LIGHTGRAY);
    line(x1, midy, x2, midy);
    line(x1, y1, x1, y2);

    setcolor(DARKGRAY);
    outtextxy(x1 + 4, midy + 4, "0");

    float max_y = func(graph_start);

    int last_x = screen_x;
    int last_y = midy - scale * func(graph_start);
    for (float x = graph_start; x < graph_end; x += x_incr) {
        float ry = func(x);
        if (ry > max_y)
            max_y = ry;

        int y = midy - scale * ry;
        setcolor(WHITE);
        line(last_x, last_y, screen_x, y);
        last_x = screen_x;
        last_y = y;
        
        if (screen_x % 50 == 0) { //(x + x_incr <= graph_end)
            setcolor(LIGHTGRAY);
            line(screen_x, midy - 2, screen_x, midy + 2);
            setcolor(DARKGRAY);
            char label_x[10];
            sprintf(label_x, "%.2f", x);
            outtextxy(screen_x, midy + 4, label_x);
        }
        screen_x++;
    }
    
    for (float y = 0; y < (midy - y1); y += y_incr) {
        if (screen_y % 50 == 0) { //
            setcolor(LIGHTGRAY);
            line(x1, midy - y, x1 + 4, midy - y);
            line(x1, midy + y, x1 + 4, midy + y);
            
            setcolor(DARKGRAY);
            char label_up[10];
            sprintf(label_up, "%.1f", y / scale);
            outtextxy(x1 + 6, midy - y - 3, label_up);

            char label_down[10];
            sprintf(label_down, "%.1f", -y / scale);
            outtextxy(x1 + 6, midy + y - 3, label_down);
        }
        screen_y++;
    }

    int r_left = getmaxx() - 200;
    int r_top = 10; 
    int r_right = r_left + 190;
    int r_bottom = 55;

    setcolor(YELLOW);
    rectangle(r_left, r_top, r_right, r_bottom);
    floodfill((r_left + r_right) / 2, (r_top + r_bottom) / 2, BLACK);

    setcolor(WHITE);
    char label_mv[20];
    sprintf(label_mv, "Max Value: %.2f", max_y);
    outtextxy(r_left + 10, r_top + 10, label_mv);
    outtextxy(r_left + 10, r_top + 30, "sin(x)^3 + cos(x)^2");

    getch();
    closegraph();

    return 0;
}
