#include <nds32_intrinsic.h>
#include "WT58F2C9.h"
#include "gpio.h"
#include "lcm.h"


void delay1(unsigned int nCount)
{
   volatile unsigned int i;
   for (i=0;i<nCount;i++);
}


/* Intrrupt memory address */
#define INT_MEM_ADDR_BASE			(0x00200D00)
#define rINT0_IE0_ENABLE			(INT_MEM_ADDR_BASE+0x00)
#define rINT0_IE1_ENABLE			(INT_MEM_ADDR_BASE+0x04)
#define rINT0_IE2_ENABLE			(INT_MEM_ADDR_BASE+0x08)
#define rINT1_IE0_ENABLE			(INT_MEM_ADDR_BASE+0x10)
#define rINT1_IE1_ENABLE			(INT_MEM_ADDR_BASE+0x14)
#define rINT1_IE2_ENABLE			(INT_MEM_ADDR_BASE+0x18)

#define rINT0_IE0_FLAG				(INT_MEM_ADDR_BASE+0x20)
#define rINT0_IE1_FLAG				(INT_MEM_ADDR_BASE+0x24)
#define rINT0_IE2_FLAG				(INT_MEM_ADDR_BASE+0x28)
#define rINT1_IE0_FLAG				(INT_MEM_ADDR_BASE+0x30)
#define rINT1_IE1_FLAG				(INT_MEM_ADDR_BASE+0x34)
#define rINT1_IE2_FLAG				(INT_MEM_ADDR_BASE+0x38)


inline void GIE_ENABLE();

#define rSYS_OPTION1	(0x00200004)
//-----  UART Functions  -----
#define UART3_ADDR_BASE		(0x0020B400)
#define UART3_CR1			(UART3_ADDR_BASE+0x00)
#define UART3_CR2			(UART3_ADDR_BASE+0x04)

//0:1 Start bit/8 Data bits/1 Stop bit,
#define	UART_FORMAT_N81	0
//1:1 Start bit/9 Data bits/1 Stop bit
#define	UART_FORMAT_N91	1

#define UART_EN				(1<<17)	//0:Disable, 1:Enable
#define UART_TX_EN			(1<<15)
#define UART_RX_EN			(1<<14)
#define UART_OVER8			(1<<13)
#define UART_OVER16			(0<<13)
#define UART_WORD_LENGTH	(UART_FORMAT_N81<<12)//	//0:1 Start bit/8 Data bits/1 Stop bit, //1:1 Start bit/9 Data bits/1 Stop bit
#define UART_TX_DMA_EN		(1<<11) //0:Disable, 1:Enable
#define UART_RX_DMA_EN		(1<<10)	// 0:Disable, 1:Enable
#define UART_RX_WAKEUP		(0<<9)	// 0:In active mode, 1:In mute mode
#define UART_WAKEUP_METHOD	(0<<8)	// 0:Idle mode, 1:Address mark
#define UART_UART_ADDR_NODE	(0x5<<4)	//Data 0x0=xxxx0000b ~ 0xF=xxxx1111b,
#define UART_PARITY_EN		(0<<2)//SET_BIT1//(n<<1) //0:Disable, 1:Enable
#define UART_PARITY_SEL		(1<<1)// O:Even 1:Odd
#define UART_STOP_BIT	0// O:1-bit 1:2-bit

#define UART_SET_CTL_PARA	UART_EN|UART_TX_EN|UART_RX_EN|UART_WORD_LENGTH\
							|UART_RX_WAKEUP|UART_WAKEUP_METHOD|UART_UART_ADDR_NODE\
							|UART_PARITY_EN|UART_PARITY_SEL|UART_STOP_BIT

//HXTAL = HXTAL_24M (OVER8=0)
//9600 = 156.25
#define BUARRATE_9600_MANTISSA_24MHZ	156
#define BUARRATE_9600_FRACTION_24MHZ	4
//19200 = 78.125
#define BUARRATE_19200_MANTISSA_24MHZ	78
#define BUARRATE_19200_FRACTION_24MHZ	2
//38400 = 39.0625
#define BUARRATE_38400_MANTISSA_24MHZ	39
#define BUARRATE_38400_FRACTION_24MHZ	1
//57600 = 26.0625
#define BUARRATE_57600_MANTISSA_24MHZ	26
#define BUARRATE_57600_FRACTION_24MHZ	1
//115200 = 13.0
#define BUARRATE_115200_MANTISSA_24MHZ	13
#define BUARRATE_115200_FRACTION_24MHZ	0
//230400 = 6.5
#define BUARRATE_230400_MANTISSA_24MHZ	6
#define BUARRATE_230400_FRACTION_24MHZ	8
//921600 = 1.625
#define BUARRATE_921600_MANTISSA_24MHZ	1
#define BUARRATE_921600_FRACTION_24MHZ	10


#define FALSE 0
#define TRUE  1
#define UART_TXD_BUFFER_SIZE	24
#define _EOS_	'\0' //End of string

#include<assert.h>
//#include<math.h>
#define BIT(x) (1<<(x))

unsigned int index_7LED_NUM[17] = {Number_0, Number_1, Number_2, Number_3, Number_4, Number_5, Number_6, Number_7,
			Number_8, Number_9, Number_A, Number_b, Number_C, Number_d, Number_E, Number_F, Number_Dot, };
unsigned int digit[8] = {Digit_1, Digit_2, Digit_3, Digit_4, Digit_5, Digit_6, Digit_7, Digit_8};
unsigned int dip[8] = {0};
int numbers[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int result_arr[4] = {-1, -1, -1, -1};
int v1, v2, i, result, stay, j;

unsigned char dip_read(){
	return (GPIO_PTC_PADIN >> 2) & (BIT(8)-1);
}

unsigned char dip_check(int idx){
	assert(idx >= 0 && idx < 8);
	return (dip_read() & BIT(idx)) >> idx;
}

void read_dip_switch(){
	for (i = 0; i < 8; ++i){
		if(dip_check(i))	dip[i] = 1;
	}
}

int pow(int a, int x){
	if(x == 0)	return 1;
	else	return a*pow(a, x-1);
}

// 0: light, 1: dark
void LED_display(){
	GPIO_PTB_GPIO = 0;
	for (i = 0; i < 8; ++i){
		GPIO_PTB_GPIO = (GPIO_PTB_GPIO << 1);
		GPIO_PTB_GPIO |= (dip[i] == 1 ? 0 : 1);
	}

	for (i = 0; i < 8; ++i){
		GPIO_PTB_GPIO = (GPIO_PTB_GPIO << 1);
		GPIO_PTB_GPIO |= dip[i];
	}

	unsigned int last;
	for (i = 0; i < 16; i++){
		last = (GPIO_PTB_GPIO & 0x8000) >> 15;
		GPIO_PTB_GPIO = (GPIO_PTB_GPIO << 1);
		GPIO_PTB_GPIO |= last;
		delay1(100000);
	}
}
// set v1, v2, result, and put them into arr
void set_num(){
	v1 = v2 = 0;
	for (i = 0; i < 4; ++i) {
		if(dip[3-i])	v1 += pow(2, i);
		if(dip[7-i])	v2 += pow(2, i);
	}
	result = v1*v2*abs(v1-v2);

	for(i = 0; i < 2; i++) {
		if(i == 1){
			if (v1)	numbers[i] = v1%10;	
			if (v2) numbers[i+2] = v2%10;
		}
		else{
			numbers[i] = v1%10;
			v1 /= 10;
			numbers[i+2] = v2%10;
			v2 /= 10;
		}
	}

	int cnt, tmp = result, flag = 0;
	if(tmp == 0){
		flag = 1;
		cnt = 1;
	}	

	for (i = 0; i < 4; ++i){
		if(flag == 1)	break;
		if(tmp == 0){
			cnt = i;
			break;
		}
		tmp /= 10;
	}
	for (i = 0; i < cnt; ++i){
		result_arr[i] = result % 10;
		result /= 10;
	}
}

// put result_arr into numbers arr
void adjust_result(int a){
	switch (a){
		case 0:
			numbers[7] = result_arr[0];
			break;
		case 1:
			numbers[7] = result_arr[1];
			numbers[6] = result_arr[0];
			break;
		case 2:
			numbers[7] = result_arr[2];
			numbers[6] = result_arr[1];
			numbers[5] = result_arr[0];
			break;
		case 3:
			numbers[7] = result_arr[3];
			numbers[6] = result_arr[2];
			numbers[5] = result_arr[1];
			numbers[4] = result_arr[0];
			break;
	}
}

// show 7SEG
void set_7SEG() {
	set_num();

	for(i = 0; i < 4; i++){	// four slide
		adjust_result(i);
		for(stay = 0; stay < 100; stay++){
			for(j = 0; j < 8; j++){
				if (numbers[j] != -1)
					GPIO_PTD_GPIO = index_7LED_NUM[numbers[j]];
				else
					GPIO_PTD_GPIO = 0;

				GPIO_PTA_GPIO = digit[j];	//pos
				delay1(500);
			}
		}
	}
}

// show last 7SEG
void display_7SEG(){

	for(i = 0; i < 8; i++){
		for(stay = 0; stay <= 100; stay++){
			if(i >= 4){
				if(result_arr[i] != -1)
					GPIO_PTD_GPIO = index_7LED_NUM[result_arr[i-4]];
				else
					GPIO_PTD_GPIO = 0;

				GPIO_PTA_GPIO = digit[i];	//pos
			}
			else{
				if(numbers[i] != -1)
					GPIO_PTD_GPIO = index_7LED_NUM[numbers[i]];
				else
					GPIO_PTD_GPIO = 0;

				GPIO_PTA_GPIO = digit[i];	//pos
			}
		}
		delay1(100);
	}
}


int main() {
	// DIP init
	GPIO_PTC_FS = 0x0000;
	GPIO_PTC_PADINSEL = 0x0000;
	GPIO_PTC_DIR = 0xFFFF;
	GPIO_PTC_CFG = 0x0000;
	read_dip_switch();

	// LED init
	GPIO_PTB_DIR = 0x0000;	//for GPIO
	GPIO_PTB_CFG = 0xFFFF;	//for push pull
	LED_display();

	// Setting for 7LED select
	GPIO_PTA_DIR = 0x0000;
	GPIO_PTA_CFG = 0x0000;
	GPIO_PTA_GPIO = Digit_1;
	// Setting for 7LED number
	GPIO_PTD_DIR = 0x0000;
	GPIO_PTD_CFG = 0x0000;
	GPIO_PTD_GPIO = 0xFFFF;
	set_7SEG();

	while(1) {
		display_7SEG();	
	}
	return 0;
}
