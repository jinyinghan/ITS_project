#include <iostream>  
#include <string>  
#include "Linklist.h"  
using namespace std;
int main()  
{  
    LinkList head;  
    Info val1,val2,val3,val4;  
    val1.id = 1,
    val1.name = Info::close,
    val1.dTime = 3,
    
    val2.id = 2,
    val2.name = Info::red,
    val2.dTime = 4,
    
    val3.id = 3,
    val3.name = Info::green,
    val3.dTime = 5,
    
    val4.id = 4,
    val4.name = Info::yellow,
    val4.dTime = 2;  

//    测试插入功能  
    cout<<"Insert test:"<<endl;  
    head.InsertHead(val1);  
    head.Insert(val3,1);  
    head.Insert(val4,2);  
    head.Insert(val2,3);  
    head.Insert(val4,4);  
while(1)
{
    head.Print();  
    cout<<"CircleTime is "<<head.GetCircleTime()<<"s"<<endl;
}
#if 0
    head.InsertHead(val1);  
    head.Print();  
    head.Insert(val2,1);  
    head.Print();  
    head.Insert(val3,4);  
    head.Print();  
    head.InsertHead(val3);  
    head.Insert(val4,2);  
    head.Print();  

    //测试反序功能  
    cout<<"reverse test:"<<endl;  
    head.Reverse();  
    cout<<"reversed linklist is:"<<endl;  
    head.Print();  

    //测试删除功能  
    cout<<"remove test:"<<endl;  
    cout<<"the length of linklist is:"<<endl;  
    cout<<head.Length()<<endl;  
    head.Remove(val4);  
    head.Print();  
    cout<<"the length of linklist is:"<<endl;  
    cout<<head.Length()<<endl;  
    head.Remove(val4);  
    head.Print();  
#endif
    return 0;  
}  
