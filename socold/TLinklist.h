#ifndef __TLINKLIST_H__
#define __TLINKLIST_H__
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

template<class T>
struct Node
{
    T val;
    Node* next;
    Node(T x):val(x),next(NULL)
    {
    }
};

template<class T>
class LinkList  
{  
    public:  
        //构造函数  
        LinkList()
        {
            head = NULL;
            length = 0;
        }
        //在链表头部插入结点  
        void InsertHead(T val);  
        //插入结点  
        void Insert(T val,int pos);  
        //删除结点  
        void Remove(T val);  
        //得到链表长度  
        int Length();  
        //得到周期时间
        int GetCircleTime();
        //链表反序  
        void Reverse();  
        //查找结点位置  
        int Find(T  val);  
        //打印链表  
        void Print();  
        //析构函数  
        ~LinkList()
        {
            Node<T> * temp;
            for(int i=0;i<length;i++)
            {
            temp = head;
            head = head->next;
            delete temp;
            }
        }
    private:  
        Node<T> *head;  
        int length;  
};  


#endif // __LINKLIST_H__
