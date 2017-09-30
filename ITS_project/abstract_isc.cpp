/**********************************************
*Project:main for ITS
*Author:GenieHan
*Email:hahahaha-oooo@163.com
*Date:2017/09
***********************************************/
#include <vector>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "Linklist.h"
using namespace std;


typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long       uint64_t;

typedef short int  int16_t;
typedef int        int32_t;

class Crossing
{
    public:
        Crossing(uint8_t directionNumb)
        {
            m_directionNumb = directionNumb;
            m_scheme = 1;
            printf("cross have %d\n",m_directionNumb);
        }
        Crossing()
        {
            m_directionNumb = 4 ;
            m_scheme = 1;
            printf("cross use %d\n",m_scheme);
        }
#if 0
        ~Crossing()
      {
            printf("this crossing is died\n");
        }
#endif
        uint8_t GetDirNumb()
        {
            return m_directionNumb;
        }
        uint8_t GetScheme()
        {
            return m_scheme;
        }
        virtual uint8_t setScheme(uint8_t) = 0;
        uint8_t m_directionNumb;
        uint8_t m_scheme;
};

class Chanel:public Crossing
{
    public:
        /* uint8_t m_ChAttribute; */
        uint8_t m_chanelNumb;
        uint8_t m_chStatus;
        Chanel(uint8_t chanelNumb,uint8_t directionNumb):Crossing(directionNumb)
        {
            m_chanelNumb = chanelNumb;
            printf("this Chanel start\n");
        }
        Chanel():Crossing()
        {
            m_chanelNumb = 8;
        }
        uint8_t setScheme(uint8_t newScheme)
        {
            m_scheme = newScheme;
            
        }
        enum ChAttribute{ns=0,nl,es,el,ss,sl,ws,wl}m_chId ;

        

#if 0
    ~Chanel()
    {
            printf("this Chanel died~\n");
    }
    void config_set(uint8_t Attribute )
    {
        m_ChAttribute = Attribute;
    }
    enum RYG {red=1,gree,yello} color;
    enum CSG {brighten,shine,close} status;
    vector<uint8_t *> sequence; 
    virtual uint8_t  *action();
#endif
   
};
struct LightMode
{
    uint8_t LModeNub;
    LinkList LModeObj;
};
class Traffic_Light 
{
    public:
        uint8_t tTime;//交通灯状态心跳
        LightMode defaultLM;
        LightMode nowLM;
        uint8_t maxLMNumb;
        Traffic_Light()
        {
            defaultLM.LModeNub = 0;
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
            printf("Insert test:\n"); 
            defaultLM.LModeObj.InsertHead(val1);  
            defaultLM.LModeObj.Insert(val3,1);  
            defaultLM.LModeObj.Insert(val4,2);  
            defaultLM.LModeObj.Insert(val2,3);  
            defaultLM.LModeObj.Insert(val4,4);  

        }
        bool create_lightMode(uint8_t LMNub,LightMode newLM)
        {

            nowLM.LModeNub = LMNub;
            Info val1,val2,val3,val4;  
            val1.id = 1,
                val1.name = Info::close,
                val1.dTime = 0,

                val2.id = 2,
                val2.name = Info::red,
                val2.dTime = 6,

                val3.id = 3,
                val3.name = Info::green,
                val3.dTime = 8,

                val4.id = 4,
                val4.name = Info::yellow,
                val4.dTime = 2;  

            //    测试插入功能  
            printf("Insert test:\n"); 
            nowLM.LModeObj.InsertHead(val1);  
            nowLM.LModeObj.Insert(val3,1);  
            nowLM.LModeObj.Insert(val4,2);  
            nowLM.LModeObj.Insert(val2,3);  
            nowLM.LModeObj.Insert(val4,4);  

        }
};

class Base_Phase:public Crossing
{
    public:
        uint8_t m_phID;
        uint8_t* action()
        {
            printf("I will create ringqueue in Base_phase~\n");
            
        }
        ~Base_Phase()
        {
            printf("this phase died~\n");
        }
        /* enum NSWE {north,south,west,east} direction; */
        /* enum O2O {straight,turnLight} router; */
        /* const int direction [2][2]={{1,0},{1,1},{0,1},{-1,1}};     */
        /* x系：东西直行，东西左转，y系：南北直行，南北左转 */
        /* stack<uint8_t *> split; */
        /* Base_Phase(void* arg = NULL,const std::string phaseName= "") */
            /* : arg_(arg) */
            /* , phaseName_(phaseName) */
        /* { */

        /* } */
        

        void setArg(void* arg)
        {
            arg_ = arg;
        }
        
    private:
    protected:
        void* arg_;
        std::string phaseName_;

};

class Base_traffic
{
    public:
        struct object
        {

            union
            {
                uint8_t people;
                uint16_t bicycle;
                uint32_t car;
            };
            uint8_t* action (uint8_t signal,uint32_t mode,long second); 
        };
        
    private:
       uint32_t flow;
        uint8_t occupancy;
        int8_t speed;
        uint16_t extent;
};



int main()
{
    Chanel* p = new Chanel(8,4);
    if(p != NULL)
    {
        printf("error");
    }
    delete p;
    
}
