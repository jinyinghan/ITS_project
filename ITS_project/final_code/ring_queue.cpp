/**********************************************
*Project:main for ITS
*Author:GenieHan
*Email:hahahaha-oooo@163.com
*Date:2017/09
********************************************/
#include "ring_queue.h"


Ring_Queue::ReadQ()
{
    u_char* g_p     = 0;
    TAG*    tag_p   = 0;
    u_char* user_data=0;
    g_p = queue_peek_nth(_queue_p,_read_now);
    tag_p = (TAG*)g_p;
    if(tag_p -> tag_value == CAN_READ)
    {
        user_data = (u_char*)g_p +sizeof(TAG);
        tag_p -> tag_value = READING;
    }
    return user_data;
}

Ring_Queue::Read_Over()
{
    u_char* g_p     = 0;
    TAG*    tag_p   = 0;
    g_p = queue_peek_nth(_queue_p,_read_now);
    tag_p = (TAG*)g_p;
    if(tag_p -> tag_value == READING)
    {
        tag_p -> tag_value = CAN_WRITE;
        _read_now = (_read_now + 1) % nmemb;
    }
}

Ring_Queue::WriteQ()
{
    u_char* g_p     = 0;
    TAG*    tag_p   = 0;
    u_char* user_data=0;
    g_p = queue_peek_nth(_queue_p,_write_now);
    tag_p = (TAG*)g_p;
    if(tag_p -> tag_value == CAN_WRITE)
    {
        user_data = (u_char*)g_p +sizeof(TAG);
        tag_p -> tag_value = WRITING;
    }
    return user_data;
    
}

Ring_Queue::Write_Over()
{
    u_char* g_p     = 0;
    TAG*    tag_p   = 0;
    g_p = queue_peek_nth(_queue_p,_write_now);
    tag_p = (TAG*)g_p;
    if(tag_p -> tag_value == WRITING)
    {
        tag_p -> tag_value = CAN_READ;
        _read_now = (_write_now + 1) % nmemb;
    }
}

Ring_Queue::queue_peek_nth(u_char* queue_p,int pos)
{
    u_char* rst = 0;
    if( queue_p && pos < _nmemb)
    {
        rst = queue_p + pos * (sizeof(TAG) + _size);
    }
    return rst;
}
