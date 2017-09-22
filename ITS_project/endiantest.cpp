#include <stdlib.h>
#include <stdio.h>
int check();
int main()
{
    int res = check();
    if(res)
    {
        printf("little_endian\n");
    }
    else
    {
        printf("big_endian\n");
    }

}
int check()
{

    union
    {
        int  a;
        char b;
    }t;

    t.a = 1;
    return (t.b == 1);
}
