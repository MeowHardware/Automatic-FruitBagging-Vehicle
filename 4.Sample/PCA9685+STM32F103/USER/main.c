#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "usmart.h"	 
#include "24cxx.h"	 
#include "pca9685.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验23
 IIC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

 				 	
//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"WarShipSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
	
 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u16 j=0;
	u8 datatemp[SIZE];
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	//LCD_Init();			   	//初始化LCD 	
	KEY_Init();	
	
			IIC_Init();//IIC初始化
      pca_write(pca_mode1,0x0);//写地址
			pca_setfreq(330);//写舵机频率，模拟电机给50HZ，数字电机330HZ
			while(1)
			{
				/*数值计算步骤：
				脉冲时间0.5ms-2.5ms(占空比5%-12.5%),频率330HZ（周期3.03ms），分辨率4096
				0°，0.5/3.03*4096=675
				90°，1.5/3.03*4096=2017
				180°，2.5/3.03*4096=3379
				*/
				for(j=600;j<2000;j++)//0路舵机，先回正，然后旋转90°（回正是瞬间动作）
				{
					pca_setpwm(0,0,j);//旋转90°
					delay_ms(3);//从0°到180°增长时缓慢增长，易于看到效果
				}
					delay_ms(300);//0路舵机转到180°后延迟一段时间，1路舵机开始转
				for(i=600;i<2000;i++)//同上理
				{	
					pca_setpwm(1,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
				for(i=600;i<3379;i++)
				{
					pca_setpwm(3,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
				for(i=600;i<2000;i++)
				{	
					pca_setpwm(7,0,i);
					delay_ms(3);	
				}
					delay_ms(300);
//				pca_setpwm(0,0,2000);//旋转90°
//				delay_ms(3000);
				
				
				
	}
}
