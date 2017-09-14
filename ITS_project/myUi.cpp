#include <ncurses.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;
#define NUM 60
#define LINE 10

void print_in_middle(WINDOW* win,int starty,int startx,int width,char* string);

void* head_refresh(void* arg);
void* background_refresh(void *arg);  

class ITS_window
{
	friend void* head_refresh(void *arg);
	friend void* background_refresh(void *arg);
	public:
    ITS_window()
    {	
		initscr();	
		getmaxyx(stdscr,y,x);
    }
	void create_head()
    {
		head_window = newwin(5,x,0,0);
		box(head_window,'|','#');
        print_in_middle(head_window,3,x/2,0,"[ Welcome to ITSC ]");
		/* box(head_window,'.','.');  */
	    /* mvwprintw(head_window,3,x/3,"[ Welcome to ITSC ]"); */
    }
    void _refresh(WINDOW* win)
    {
        wrefresh(win);
    }
    void create_background()
    {
    background_window = newwin(y-5,x,5,0);
    box(background_window,'|','#');
    mvwprintw(background_window,((y-5)/2),x/2,"background~~~happy ]");
    mvwprintw(background_window,0,0,"**********\n**********\n**********\n**********\n**********\n**********\n**********\n");
    mvwprintw(background_window,y-12,0,"**********\n**********\n**********\n**********\n**********\n**********\n**********\n");
    mvwprintw(background_window,0,x-12,"**********\v**********\v**********\v**********\v**********\v**********\v**********\v");
    mvwprintw(background_window,y-12,x-12,"**********\n**********\n**********\n**********\n**********\n**********\n**********\n");
    }

    ~ITS_window()
    {
        endwin();
    }

    private:
    WINDOW *head_window;
    WINDOW *background_window;
    int x;
    int y;
};

void* head_refresh(void *arg)
{
    ITS_window *win = (ITS_window*)arg;
    win->_refresh(win->head_window);
    return NULL;
}
void* background_refresh(void *arg)
{
    ITS_window *win = (ITS_window*)arg;
    win->_refresh(win->background_window);
    return NULL;
}
int main()
{
	
	ITS_window win;
    win.create_head();
    win.create_background();
    while(1)
    {
        sleep(3);
        head_refresh((void*)&win);
        background_refresh((void*)&win);
    }
//	return 0;
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
