#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
typedef struct
{/* 24      bytes */
    struct in_addrv4;                       ///< IPv4地址
    struct in6_addr v6;                         ///< IPv6地址
    unsigned charres[4];
}U_IN_ADDR;

typedef struct /* 132 bytes */
{
    DWORD dwLength;/*报文总                          长度*/
    BYTE byRes1[2];/* 保留 */
    BYTE byCommand;/* è                                                  ·求命令 0x98*/
    BYTE byIPType;/*IP类型 0-IPV4 1-IPV6 */
    DWORD dwVersion;/* 设备版本信息 */
    BYTE sDVRName[32];           /* è                        ®¾备名称 */
    BYTE sSerialNumber[48];/* 设备序列号 */
    U_IN_ADD        RstruIPAddr;                /*设备IP地址*/
    WORD wPort;/* 设备端å                                    £号 */
    BYTE byMacAddr[6];/* 设备MAC地址*/
    BYTE byRes3[8];                                                  /* 保留 */
}INTER_DVR_REQUEST_HEAD_V30;


int main()
{
    U_IN_ADDR test2;
    INTER_DVR_REQUEST_HEAD_V30 test1;
    int i =sizeof(test2);
    int j = sizeof(test1);
    printf("head = %d,in_addr = %d",test1,test2);
}
