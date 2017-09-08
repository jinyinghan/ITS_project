#include <vector>
#include <stack>
using namespace std;


typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;

typedef char       int8_t;
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
        enum NSWE {north,south,west,east} direction;
        enum O2O {straight,turnLight} router;
        stack<uint8_t *> split;

    private:

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

