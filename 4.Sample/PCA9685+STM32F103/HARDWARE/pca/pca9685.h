#ifndef __PCA9685_H
#define __PCA9685_H
#include "myiic.h"

#define PCA9685_SUBADR1 0x2 
#define PCA9685_SUBADR2 0x3 
#define PCA9685_SUBADR3 0x4 
#define pca_adrr 0x80
//#define pca_adrr 0x40
#define pca_mode1 0x0 
#define pca_pre 0xFE //控制周期的寄存器
#define LED0_ON_L 0x6 //第0路
#define LED0_ON_H 0x7 
#define LED0_OFF_L 0x8 
#define LED0_OFF_H 0x9 
#define ALLLED_ON_L 0xFA 
#define ALLLED_ON_H 0xFB 
#define ALLLED_OFF_L 0xFC 
#define ALLLED_OFF_H 0xFD 

void pca_write(u8 adrr,u8 data);
u8 pca_read(u8 adrr);
void pca_setfreq(float freq);
void pca_setpwm(u8 num, u32 on, u32 off);
void PCA_MG9XX_Init(float hz,u8 angle);//函数1
void PCA_MG9XX(u8 num,u8 start_angle,u8 end_angle,u8 mode,u8 speed);//函数2
/*函数1和2，我这里并没有用到，此程序是在前人的基础上进行修改的，这两个函数实现的功能大致是
能够实现直接给角度参数达到旋转固定角度的目的，但是具体公式我不知道从何处得来的，
所以我就直接通过计算off值的方式修改旋转角度*/



#endif