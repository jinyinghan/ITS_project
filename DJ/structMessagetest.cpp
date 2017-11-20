#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 4)
//倒计时接口获取命令：
typedef struct STRU_Extra_Param_Get_Phase_Counting_Down
{
    unsigned int     unExtraParamHead;               //标志头,0x6e6e
    unsigned int     unExtraParamID;               //类型,0x9E表示获取倒计时接口
}GET_PHASE_COUNTING_DOWN_PARAMS; 

//倒计时接口获取反馈：
typedef struct STRU_Extra_Param_Phase_Counting_Down_Feedback
{
    unsigned int     unExtraParamHead;             //标志头,0x6e6e
    unsigned int     unExtraParamID;                  //类型,0x9E表示上载
    unsigned short    stVehPhaseCountingDown[16][2];    //16个机动车相位的当前灯色及倒计时
    //第0列表示当前机动车相位的状态，0:灭灯， 1:绿灯，2:红灯，3:黄灯，4：绿闪，5：黄闪
    //第1列表示当前机动车相位所属相位倒计时时间
    unsigned short    stPedPhaseCountingDown[16][2];    //16个行人相位的当前灯色及倒计时
    //第0列表示当前机动车相位的状态，0:灭灯， 1:绿灯，2:红灯，3:黄灯，4：绿闪，5：黄闪
    //第1列表示当前行人相位所属相位倒计时时间
    unsigned char    ucPlanNo;//当前运行方æ            号
    unsigned short   ucCurCycleTime;//当前运行周期长!!!           !!!!!!!
    unsigned short   ucCurRunningTime;//当前运行时间             !!!!!!!!!!
    unsigned char    ucChannelLockStatus;//通道是否è    «锁定状态，1表示通道锁定，0表示通道未锁定
    unsigned char    ucCurPlanDsc[16];//当前运行方案描述
    unsigned short    ucOverlap[16][2];                    //跟随相位状态，0:灭灯， 1:绿灯，2:红灯，3:黄灯，4：绿闪，5：黄闪
    unsigned short    stPhaseRunningInfo[16][2];//各相位运行时间å绿信比
    //第0列表示该相位绿信比；第1列表示该相位运行时间，绿灯亮起后第1列才有数值，否则为0
    unsigned char    ucChannelStatus[32]; /*32个通道当前状态
0:不起效
1:绿灯
2:红灯
3:黄灯
4:绿闪
5:黄闪
6:全红
7:灭灯
8:红闪
9:红黄
*/
    unsigned short ucChannelCountdown[32];//实际ç通道倒计时++++++
    unsigned char  ucIsStep;    //是否步è    ¿，0:不步进,1:正在步进++++++
    unsigned char  ucMaxStageNum;   //最大阶段号++++++
}PHASE_COUNTING_DOWN_FEEDBACK_PARAMS;                          

#pragma pack(pop)

int main()
{
  STRU_Extra_Param_Phase_Counting_Down_Feedback test;
  int i = sizeof(test);
  
  printf("size = %d,len = ",i);
}
