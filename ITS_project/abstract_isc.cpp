#include <vector>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;


typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;

typedef short int  int16_t;
typedef int        int32_t;

class Traffic_Chanel
{
public:
    enum RYG {red,gree,yello} color;
    enum CSG {brighten,shine,close} status;
    vector<uint8_t *> sequence; 

private:
  virtual uint8_t  *action();

    
};

class Base_Phase
{
    public:
        /* enum NSWE {north,south,west,east} direction; */
        /* enum O2O {straight,turnLight} router; */
        /* const int direction [2][2]={{1,0},{1,1},{0,1},{-1,1}};     */
        /* x系：东西直行，东西左转，y系：南北直行，南北左转 */
        /* stack<uint8_t *> split; */
        Base_Phase(void* arg = NULL,const std::string phaseName= "")
            : arg_(arg)
            , phaseName_(phaseName)
        {

        }
        
        virtual ~Base_Phase()
        {
        }

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

