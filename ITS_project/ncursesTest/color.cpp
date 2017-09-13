#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define LINE 10


void print_in_middle(WINDOW* win,int starty,int startx,int width,char* string);

void* EWStraight_refresh(void* arg);
void* EWTurnleft_refresh(void* arg);
void* NSStraight_refresh(void* arg);
void* NSTurnleft_refresh(void* arg);

void* head_refresh(void* arg);
void* background_refresh(void* arg);
void* middle_num(void* arg);

class window
{
    friend void* ewstraight_refresh(void* arg);
    friend void* ewturnleft_refresh(void* arg);
    friend void* nsstraight_refresh(void* arg);
    friend void* nsturnleft_refresh(void* arg);

    friend void* head_refresh(void* arg);
    friend void* background_refresh(void* arg);
    friend void* middle_num(void* arg);
    
    public:
    window()
    {
        initser();

        getmaxyx(stdscr.y,x);
    }
};



int main()
{
    initscr();
    /* 启动 curses模式 */
    if(has_colors() == FALSE)
    {
        endwin();
        printf("You terminal does not support color\n");
        exit(1);
    }
    start_color();
    /* 启动 color机制 */
    init_pair(1,COLOR_RED,COLOR_BLACK);

    attron(COLOR_PAIR(1));
    print_in_middle(stdscr,LINE /2,0,0,"Viola !!!In color... ");
    attroff(COLOR_PAIR(1));
    getch();
    endwin();

}

void print_in_middle(WINDOW* win,int starty,int startx,int width,char* string)
{
    int length,x,y;
    float temp;
    if(win == NULL)
    {
        win = stdscr;
    }

    getyx(win,y,x);
    if(startx != 0)
    {
        x = startx;
    }
    if(starty != 0)
    {
        y = starty;
    }

    if(width == 0)
    {
        width = 80;
    }
    length = strlen(string);
    temp = (width + length)/2;
    x = startx + (int)temp;
    mvwprintw(win,y,x,"%s",string);
    refresh();
}
