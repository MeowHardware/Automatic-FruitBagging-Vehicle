#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <rtthread.h>
#include "stm32f4xx_hal.h"

//宏定义
#define FULL_SPEED 1000
#define RUN 0x00
#define LEFT 0x01
#define RIGHT 0x02
#define TURN_LEFT 0x03
#define TURN_RIGHT 0x04
#define BACK 0x05


void motor_tim_set(TIM_HandleTypeDef* i);

// 公共函数
//电机入口
void motor_entry(void *p);
//电机pwm启动
void motor_enable(void);
//电机pwm关闭
void motor_disable(void);
//小车停止
void motor_stop(void);
//小车刹车
void motor_break(void);
//小车指令
void motor_cmd(rt_uint8_t cmd, uint32_t speed);

//私有函数
void _motor_run(uint32_t speed);
void _motor_left(uint32_t speed);
void _motor_right(uint32_t speed);
void _motor_t_left(uint32_t speed);
void _motor_t_right(uint32_t speed);
void _motor_back(uint32_t speed);

//自定义控制函数
void __motor_super(uint32_t speed_channel_1, uint32_t speed_channel_2, uint32_t speed_channel_3, uint32_t speed_channel_4);

#ifdef __cplusplus
}
#endif
#endif
