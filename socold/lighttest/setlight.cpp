#include <unistd.h>
#include <stdio.h>
#define BYTE unsigned char
union GRY
{
    BYTE c[4];
    int d;
};
int main()
{
    union GRY data;
    //set green
    //input:ChannalID
    //output:data.i
    int ChannelIDbuf[8]={1,2,3,4,5,6,7,8};
    int table1[4][2] = {{1,3},{2,4},{5,7},{6,8}};//[p][q]
    int table2[4][2] = {{5,2},{6,2},{7,2},{8,2}};//[u][v]
    int k = 0;
    int t = 0;
    int sT = 0;
    int color =0;
while(1)
{

    for(int u=0;u<4;u++)
    {
        data.d = 0;//清空
        for(int v=0;v<2;v++)
        {
            data.d = 0;//清空
            printf("Time_table2:[%d],[%d]:%d\n",u,v,table2[u][v]);
            sT = table2[u][v];
            for(int q=0;q<2;q++)
            {
                t = table1[u][q];
                printf("Phase_table1:[%d],[%d]:%d\n",u,q,table1[u][q]);
                if(v == 0)//绿灯
                {
                    data.d |= (1<<(3*t-3));//置绿
                }
                else//黄灯
                {
                    data.d |= (1<<(3*t-1));//置黄
                }    
            }
            while(sT != 0)
            {
                for(int i=0;i<8;i++)
                {
                    k = ChannelIDbuf[i];
                    if(!((data.d>>(3*k-3))&0x1) || (!(data.d>>(3*k-1))&0x1))//不为 绿 或 黄的通道
                    {
                        data.d |= (1<<(3*k-2));//置红
                    }
                    if(((data.d>>(3*k-3))&0x1))//绿
                    {
                        color = 42;
                    }
                    else if(((data.d>>(3*k-1))&0x1))//黄
                    {
                        color = 43;
                    }
                    else
                    {
                        color = 41;
                    }
                    printf("\033[%d;34m [ %d ] lightID .%ds]\033[5m",color,i+1,sT);
                    printf("\n");
                }
                    printf("\n");

                sleep(1);
                sT--;
            }
            printf("\n");
        }
    }
}
}

