/**********************************************
*Project:main for ITS
*Author:GenieHan
*Email:hahahaha-oooo@163.com
*Date:2017/09
********************************************/
#ifndef __RING_QUEUE_H__
#define __RING_QUEUE_H__

#include <assert.h>
#include <string.h>
#define CAN_WRITE   0x00 
#define CAN_READ    0x01
#define READING     0x02
#define WRITING     0x03

typedef unsigned char u_char;
typedef struct tag
{
    u_char tag_value;
}TAG;

class Ring_Queue
{
    public:
        Ring_Queue(int nmemb,int size):_nmemb(nmemb),_size(size),_read_now(0),_write_now(0)
    {
        if (nmemb <= 0 || size <= 0)
        {
            assert(0);
        }
        _queue_p = NULL;
        _queue_p = new u_char[ nmemb * (sizeof(TAG) + size)];
        memset(_queue_p,0,nmemb * (sizeof(TAG) + size));

    }
        ~Ring_Queue()
        {
            if(_queue_p) delete []_queue_p;
        }
        
        u_char* ReadQ();
        void Read_Over();
        u_char* WriteQ();
        void Write_Over();

    private:
        u_char* queue_peek_ntk(u_char* queue_p,int pos);
        u_char* _queue_p;
        int     _nmemb;
        int     _size;
        volatile int _read_now;
        volatile int _write_now;

};

#endif // __RING_QUEUE_H__
