#ifndef __LINKLIST_H__
#define __LINKLIST_H__
/**********************************************
 *Project:Linklist for ITS
 *Author:GenieHan
 *Email:hahahaha-oooo@163.com
 *Date:2017/09
 ***********************************************/
#include <string>
using namespace std;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;

struct Info
{
    uint8_t id;//若1个通道对应一组3个灯，则id=chId；
    /* enum light{close=40,red,green,yellow} name;//三选一 */
//    enum lightcolor{close=0,red=2,green=1,yellow=4}status;
    uint16_t dTime;
    uint16_t dTimeY;//该颜色状态持续多久
    uint16_t dTimeG;//该颜色状态持续多久
//    bool onOroff;//亮1，灭0；
};
struct Node
{
    Info val;
    Node* next;
    Node(Info x):val(x),next(NULL)
    {
    }
};

class LinkList  
{  
    public:  
        //构造函数  
        LinkList();   
        //在链表头部插入结点  
        void InsertHead(Info val);  
        //插入结点  
        void Insert(Info val,int pos);  
        //删除结点  
        void Remove(Info val);  
        //得到链表长度  
        int Length();  
        //得到周期时间
        int GetCircleTime();
        //链表反序  
        void Reverse();  
        //查找结点位置  
        int Find(Info val);  
        //打印链表  
        void Print();  
        //析构函数  
        ~LinkList();  
    private:  
        Node *head;  
        int length;  
};  


#endif // __LINKLIST_H__
