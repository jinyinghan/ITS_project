#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define LINE 10


void print_in_middle(WINDOW* win,int starty,int startx,int width,char* string);

/* void* EWStraight_refresh(void* arg); */
void* EWTurnleft_refresh(void* arg);
void* NSStraight_refresh(void* arg);
void* NSTurnleft_refresh(void* arg);

void* head_refresh(void* arg);
void* background_refresh(void* arg);
void* middleNub_refresh(void* arg);

class window
{
#if 0
    friend void* ewstraight_refresh(void* arg);
#endif
    friend void* ewturnleft_refresh(void* arg);
    friend void* nsstraight_refresh(void* arg);
    friend void* nsturnleft_refresh(void* arg);

    friend void* head_refresh(void* arg);
    friend void* background_refresh(void* arg);
    friend void* middle_num(void* arg);
    
    public:
    window()
    {
        initscr();

        getmaxyx(stdscr,y,x);
    }
    void create_head()
    {

        head_window = newwin(4,x,0,0);
        box(head_window,'.','.');
        mvwprintw(head_window,4/2,x/3,"|Welcome to ITSC |");
    }
    
    void _refresh(WINDOW* win)
    {
        wrefresh(win);
        wgetch(win);
    }
    
    void create_background()
    {
        background_window = newwin(y-5,x/2,5,0);
        box(background_window,'.','.');
        mvwprintw(background_window,1,0,"wahaha this is background:");
    }
    
    void create_middleNub()
    {
     middleNub_window = newwin((y-5)/2,x/2,5+(y-5)/2+1,x/2);
     box(middleNub_window,'.','.');
     mvwprintw(middleNub_window,1,0,"middle number window:");
    }

#if 0
    void create_EWStraight()
    {
     ews_window = newwin((y-5)/2,x/2,5,x/2);
     box(ews_window,'.','.');
     mvwprintw(ews_window,1,0,"EWStraight window:");
    }
#endif

    ~ window()
    {
        endwin();
    }
    
    private:
    WINDOW* middleNub_window;
    /* WINDOW* ews_window; */
    WINDOW* head_window;
    WINDOW* background_window;

    int x;
    int y;

};

#if 0
void* EWStraight_refresh(void* arg)
{
    window* win = (window*) arg;
    win->_refresh(win->ews_window);
    return NULL;
}
#endif

void* EWTurnleft_refresh(void* arg)
{
}

void* NSStraight_refresh(void* arg)
{
}

void* NSTurnleft_refresh(void* arg)
{
}

void* head_refresh(void* arg)
{
    window* win = (window*) arg;
    win->_refresh(win->head_window);
    return NULL;
}

void* background_refresh(void* arg)
{
    window* win = (window*) arg;
    win->_refresh(win->background_window);
    return NULL;
    
}

void* middleNub_refresh(void* arg)
{
    window* win = (window*) arg;
    win->_refresh(win->middleNub_window);
    return NULL;
}

int main()
{
    /* initscr(); */
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
    /* print_in_middle(stdscr,LINE /2,0,0,"Viola !!!In color... "); */
    window win;
    win.create_head();
    win.create_background();
    win.create_middleNub();
    pthread_t head_id,background_id,middleNub_id;

    pthread_create(&head_id,NULL,head_refresh,(void*)&win);
    pthread_create(&background_id,NULL,
background_refresh,(void*)&win);
    pthread_create(&middleNub_id,NULL,middleNub_refresh,(void*)&win);
    
    pthread_join(head_id,NULL);
    pthread_join(background_id,NULL);
    pthread_join(middleNub_id,NULL);
    /* pthread_join(right_id,NULL); */
    
    /* attroff(COLOR_PAIR(1)); */
    getch();
    /* endwin(); */

#if 0

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
#endif
}
