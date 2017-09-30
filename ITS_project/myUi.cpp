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

/* void print_in_middle(WINDOW* win,int starty,int startx,int width,char* string); */
int setTicker(int);
void showInformation();
void show();
void* head_refresh(void* arg);
void* background_refresh(void *arg);  
void* middleNub_refresh(void* arg);
void* EWStraight_refresh(void* arg);
void* EWTurnleft_refresh(void* arg);
void* NSStraight_refresh(void* arg);
void* NSTurnleft_refresh(void* arg);
int hour,minute,second;
int tTime;
int ch;


class ITS_window
{
    friend void* head_refresh(void* arg);
    friend void* background_refresh(void *arg);  
    friend void* middleNub_refresh(void* arg);
    friend void* EWStraight_refresh(void* arg);
    friend void* EWTurnleft_refresh(void* arg);
    friend void* NSStraight_refresh(void* arg);
    friend void* NSTurnleft_refresh(void* arg);
	public:
    ITS_window()
    {	
		initscr();	
		getmaxyx(stdscr,y,x);
        this->create_head();
        this->create_background();
        this->_refresh(this->m_head_window);
        this->_refresh(this->m_background_window);
        /* hour = minute = second = tTime = 0; */
    }
    
    void _refresh(WINDOW* win)
    {
        wrefresh(win);
    }
	
    void create_head()
    {
		m_head_window = newwin(5,x,0,0);
		box(m_head_window,'|','#');
	    mvwprintw(m_head_window,3,x/3,"[ Welcome to ITSC ]");
    }
    
    void create_background()
    {
        m_background_window = newwin(y-5,x,5,0);
        box(m_background_window,'|','#');
        /* mvwprintw(m_background_window,((y-5)/2),x/2,"background~~~happy ]"); */
        for(int i = 0;i < 8;i++)
        {
            mvwprintw(m_background_window,i+2,4,"***************************\t\t\t\t\t\t\t\t\t\t\t***************************");
            mvwprintw(m_background_window,(y-15+i),4,"***************************\t\t\t\t\t\t\t\t\t\t\t***************************");
        }
    }

    
    void create_middleNub()
    {
		m_middleNub_window = newwin(10,20,(y-5)/2,x/2-5);
		box(m_middleNub_window,'.','.');
	    mvwprintw(m_middleNub_window,((y-5)/2),x/2,"[ middle ]");
    }

    ~ITS_window()
    {
        endwin();
    }

    private:
    WINDOW *m_head_window;
    WINDOW *m_background_window;
    WINDOW *m_middleNub_window;
    WINDOW *m_ews_window;
    WINDOW *m_ewt_window;
    WINDOW *m_nss_window;
    WINDOW *m_nst_window;
    int x;
    int y;
};

void* head_refresh(void *arg)
{
    ITS_window *win = (ITS_window*)arg;
    win->_refresh(win->m_head_window);
    return NULL;
}
void* background_refresh(void *arg)
{
    ITS_window *win = (ITS_window*)arg;
    win->_refresh(win->m_background_window);
    return NULL;
}
void* middleNub_refresh(void *arg)
{
    ITS_window *win = (ITS_window*)arg;
    win->_refresh(win->m_middleNub_window);
    return NULL;
}
int main()
{
	
	ITS_window win;
    win.create_head();
    win.create_background();
    win.create_middleNub();
    /* cbreak();                    //把终端的CBREAK模式打开 */
    /* noecho();                    //关闭回显 */
    curs_set(0);                //把光标置为不可见
    /* keypad(stdscr, true);        //使用用户终端的键盘上的小键盘 */
    hour = minute = second = tTime = 0;
    /* setTicker(20); */
    /* signal(SIGALRM, show); */
    while(1)
    {
        /* sleep(1); */
        ch = getch(); 
        head_refresh((void*)&win);
        background_refresh((void*)&win);
        /* refresh();     */
        /* if(KEY_LEFT == ch) */
        /* { */
            middleNub_refresh((void*)&win);
        /* } */
        /* setTicker(20); */
    }
//	return 0;
}

int setTicker(int n_msecs)
{
    struct itimerval new_timeset;
    long    n_sec, n_usecs;

    n_sec = n_msecs / 1000 ;
    n_usecs = ( n_msecs % 1000 ) * 1000L ;
    new_timeset.it_interval.tv_sec  = n_sec;        
    new_timeset.it_interval.tv_usec = n_usecs;      
    n_msecs = 1;
    n_sec = n_msecs / 1000 ;
    n_usecs = ( n_msecs % 1000 ) * 1000L ;
    new_timeset.it_value.tv_sec     = n_sec  ;      
    new_timeset.it_value.tv_usec    = n_usecs ;     
    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void showInformation()
{
    tTime++;
    if(tTime >= 1000000)                //
        tTime = 0;
    if(1 != tTime % 50)
        return;
    move(0, 3);   
    //显示时间
    printw("time: %d:%d:%d %c", hour, minute, second);
    second++;
    if(second > NUM)
    {
        second = 0;
        minute++;
    }
    if(minute > NUM)
    {
        minute = 0;
        hour++;
    }

    move(1, 0);
    int i;
    for(i=0;i<COLS;i++)
        addstr("-");

}

void show()
{
    /* signal(SIGALRM, show);        //设置中断信号 */
    showInformation();
    refresh();                    //刷新真实屏幕
}

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

