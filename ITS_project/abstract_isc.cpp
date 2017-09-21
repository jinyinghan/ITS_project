#include <vector>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <string>
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
        Crossing(uint8_t directionNumb):      m_directionNumb(directionNumb)
        {
            printf("cross have %d\n",m_directionNumb);

        }
        Crossing()
        {
            m_directionNumb = 4 ;
            printf("cross have %d\n",m_directionNumb);
        }
        ~Crossing()
        {
            printf("this crossing is died\n");
        }

        uint8_t m_directionNumb;
};

class Traffic_Chanel
{
public:
    uint8_t m_ChAttribute;
    uint8_t m_ChStatus;
    string name;
    Traffic_Chanel();
    Traffic_Chanel(string n)
    {
        name = n;
        printf("this Chanel start\n");
    }
    ~Traffic_Chanel()
    {
            printf("this Chanel died~\n");
    }
    void set(uint8_t Attribute,uint8_t Status )
    {
        m_ChAttribute = Attribute;
        m_ChStatus = Status;
        

    }
#if 0
    enum RYG {red,gree,yello} color;
    enum CSG {brighten,shine,close} status;
    vector<uint8_t *> sequence; 
#endif

  virtual uint8_t  *action();

    
};

class Base_Phase:public Traffic_Chanel
{
    public:
        uint8_t m_phID;
        Base_Phase(uint8_t ID,string name):    Traffic_Chanel(name){m_phID = ID;};
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
    Base_Phase* p = new Base_Phase(12,"aaa");
    if(p != NULL)
    {
        printf("error");
    }
    p -> action();
    p ->set(11,12);
    delete p;
    
}
