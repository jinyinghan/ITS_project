#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/can.h>
#include <linux/if.h>
#include <stdlib.h>
#include <string.h>
#include "libsocketcan.h"
#include "hik.h"

#define HARDWARE_MODEL 300

static int canfd = -1;

void CanInit()
{
	struct sockaddr_can addr;
    struct ifreq ifr;
	struct timeval timeout = {2, 0};
#ifdef HARDWARE_MODEL
#if (HARDWARE_MODEL == 500)		//TSC500
	UInt32 bitrate = 600000;
#elif (HARDWARE_MODEL == 300)	//TSC300
	UInt32 bitrate = 500000;
#endif
#endif
	can_do_stop("can0");
	if (can_set_bitrate("can0", bitrate) < 0)
	{
		ERR("set can0 bitrate(%u) fail!", bitrate);
		exit(1);
	}
	if (can_do_start("can0") < 0)
	{
		ERR("can0 start fail!");
		exit(1);
	}
    canfd = socket(AF_CAN, SOCK_RAW, CAN_RAW);
	if (canfd == -1)
	{
		perror("create can socket fail!");
		exit(1);
	}
    strcpy(ifr.ifr_name, "can0");
    if (ioctl(canfd, SIOCGIFINDEX, &ifr) == -1)
	{
		perror("ioctl get can index fail!");
		exit(1);
	}
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(canfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("bind can socket fail!");
		exit(1);
	}
	//设置接收超时时间为2s
	setsockopt(canfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
}

int main(int argc, char const *argv[])
{
	CanInit();

	struct can_frame sframe;
	memset(&sframe, 0, sizeof(sframe));
	sframe.can_id = 0x101;
	sframe.can_dlc = 7;
	sframe.data[0] = 1;
	sframe.data[1] = 0;
	sframe.data[2] = 0x10;
	sframe.data[3] = 0x29;

	while (1)
	{
		write(canfd, &sframe, sizeof(struct can_frame));
		usleep(250000);
	}
	return 0;
}
