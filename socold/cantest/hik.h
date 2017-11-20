/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ���ݺ����������ּ����ɷ����޹�˾

 ******************************************************************************
  �� �� ��   : hik.h
  �� �� ��   : ����
  ��    ��   : Jicky
  ��������   : 2014��11��27��
  ����޸�   :
  ��������   : ���õ�ͷ�ļ���������һЩ��ӡ�ĺ궨���Լ�һЩͨ�õ����Ͷ���
			   ���ļ�ֻ������linuxϵͳ��gcc��������������ļ�Ҳ�����ڱ�дlinux����ʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��27��
    ��    ��   : Jicky
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HIK_H__
#define __HIK_H__

#ifndef __linux__	//�˺���gcc����������ģ������ǰ�ı��뻷������gcc��������ֹͣ������
#error	"You can't use it in other system, only linux system gcc can compile it!"
#endif	//end of __linux__
/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#ifdef __KERNEL__
#include <linux/kernel.h>
#else
#include <stdio.h>
#include <stddef.h>
#endif	//end of __KERNEL__

#ifdef __cplusplus
extern "C" {
#endif	//end of __cplusplus

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
/*���º궨����printfʱ��һЩ��ɫ��ӡ�����Ը����Լ���ϲ�ý���ѡ�� */
#define COL_DEF "\033[m"			//ϵͳĬ�ϵĴ�ӡ��ɫ��һ���ǰ�ɫ
#define COL_RED "\033[0;32;31m"		//��ɫ��ӡ
#define COL_GRE "\033[0;32;32m"		//��ɫ��ӡ
#define COL_BLU "\033[0;32;34m"		//��ɫ��ӡ
#define COL_YEL "\033[1;33m"		//��ɫ��ӡ


#define GET_BIT(v, bit) 	(((v) >> (bit)) & 0x1)	//ȡv��ĳһbitλ
#define SET_BIT(v, bit) 	({(v) |= (1 << (bit));})	//����v��ĳһbitλ
#define CLR_BIT(v, bit)		({(v) &= (~(1 << (bit)));})	//����v��ĳһbitλ


/* ����Ҫ��ӡ��Ϣ����ʹ�����º궨�壬����������ɫ�����ҿ��Ժܷ����ȥ����ӡ��Ϣ
	ERR����ӡ�������Ϣ						eg: ERR("This is a error message!");
	INFO:��ӡ�������й����е�һЩ������Ϣ	eg: INFO("The udp server process has init!");
	DBG: ��ӡ������Ϣ������ͨ������ʱ���-DDEBUG���������ƴ�ӡ�ĵ�����Ϣ
���������궨��Ĵ�ӡĩβ��Ĭ������˻��з�\n  */
#ifdef __KERNEL__	//for linux driver
	#define ERR(fmt, ...) printk(KERN_ERR COL_RED "driver error function[%s]:"\
				COL_YEL fmt COL_DEF "\n", __func__, ##__VA_ARGS__)
	#define INFO(fmt, ...) printk(KERN_INFO COL_GRE "driver information:"\
				COL_YEL	fmt COL_DEF "\n", ##__VA_ARGS__)

	#ifdef DEBUG
	#define DBG(fmt, ...) printk(KERN_DEBUG COL_BLU "debug function[%s]:"\
				COL_DEF	fmt, __func__, ##__VA_ARGS__)
	#else
	#define DBG(fmt, ...) //({0;})
	#endif	// end of DEBUG
#else		//for linux application
	#define ERR(fmt, ...) fprintf(stderr, COL_RED "error function[%s]:"\
				COL_YEL fmt COL_DEF "\n", __func__, ##__VA_ARGS__)
	#define INFO(fmt, ...) fprintf(stderr, COL_GRE "information:"\
				COL_YEL	fmt COL_DEF "\n", ##__VA_ARGS__)

	#ifdef DEBUG
	#define DBG(fmt, ...) printf(COL_BLU "debug function[%s]:"\
				COL_DEF	fmt "\n", __func__, ##__VA_ARGS__)
	#else
	#define DBG(fmt, ...)
	#endif	// end of DEBUG			
	
	/*�����ں˾����õ���һ���궨�壬��˼��ͨ���ṹ���һ����Ա�����ĵ�ַ�ҵ�����ṹ��������׵�ַ 
	  �����õ���offsetof��ȡһ���ṹ������س�Ա��λ��ƫ�ƣ��������stddef.h�����ˣ�����ֱ��������*/
	#define container_of(ptr, type, member) ({          \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		(type *)( (char *)__mptr - offsetof(type,member) );})
		
	#define min(x, y) ({                \
		typeof(x) _min1 = (x);          \
		typeof(y) _min2 = (y);          \
		(void) (&_min1 == &_min2);      \
		_min1 < _min2 ? _min1 : _min2; })

	#define max(x, y) ({                \
		typeof(x) _max1 = (x);          \
		typeof(y) _max2 = (y);          \
		(void) (&_max1 == &_max2);      \
		_max1 > _max2 ? _max1 : _max2; })
	
#endif	//end of __KERNEL__

extern int gOftenPrintFlag;
#define OFTEN(fmt, ...) do {\
	if (gOftenPrintFlag) \
		fprintf(stderr, COL_BLU "[%s]" COL_YEL fmt COL_DEF "\n", __func__, ##__VA_ARGS__);\
} while (0)
/*----------------------------------------------*
 * �����ض����Լ��ṹ�嶨��                     *
 *----------------------------------------------*/
/*˵����
		1.����ʹ�������ض�����������ͣ�������ò�Ҫʹ��long���ͣ���Ϊlong��������ϵ������أ�32λ��4�ֽڣ�64λ��8�ֽ�
		2.����float��double���ڲ�����ʹ�ã��������û�о��嶨�壬ʹ��ʱ���Լ����弴�ɡ�
*/
typedef signed char 		Int8;	//Int8 	cValue;	Ϊ�˱���ͳһ�����鲻ʹ��ch���ζ���Ϊc����
typedef signed short 		Int16;	//Int16	sValue;
typedef signed int			Int32;	//Int32 iValue;
typedef signed long long	Int64;	//Int64	lValue;

typedef unsigned char 		UInt8;	//UInt8  ucValue;
typedef unsigned short 		UInt16;	//UInt16 usValue;
typedef unsigned int		UInt32;	//UInt32 uiValue;
typedef unsigned long long	UInt64;	//UInt64 ulValue;


typedef signed char 		INT8;	//Int8 	cValue;	Ϊ�˱���ͳһ�����鲻ʹ��ch���ζ���Ϊc����
typedef signed short 		INT16;	//Int16	sValue;
typedef signed int			INT32;	//Int32 iValue;
typedef signed long long	INT64;	//Int64	lValue;

typedef unsigned char 		UINT8;//UInt8  ucValue;
typedef unsigned short 		UINT16;//UInt16 usValue;
typedef unsigned int		UINT32;	//UInt32 uiValue;
typedef unsigned long long	UINT64;	//UInt64 ulValue;

typedef unsigned int        DWORD; // 4, same as long
typedef unsigned short      WORD;  // 2
typedef unsigned char       BYTE;  // 1

/*˵����
		1.������ڷ���ֵΪ��ȷ���ĺ�����ͳһʹ�����ö�٣����ɹ�����1��ʧ�ܷ���0.
		2.������صĴ����űȽ϶࣬�����Զ���һ��ö�����ͣ��Ѵ�����һ�������г�����ʱӦ����ȷ����0�����󷵻�����
*/
#if !defined(TRUE) && !defined(FALSE)
typedef enum
{
	FALSE = 0,
	TRUE,
} Boolean;
#endif

/*----------------------------------------------*
 * �ӿں���                                     *
 *----------------------------------------------*/
/*��ʱû���뵽��ʲô���Թ���ʹ�õĺ������������뵽�˿���������ӵ���һ�� */


#ifdef __cplusplus
}
#endif	//end of __cplusplus

#endif	//end of __HIK_H__
