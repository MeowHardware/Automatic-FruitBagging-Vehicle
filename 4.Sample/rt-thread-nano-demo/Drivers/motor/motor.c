#include "motor.h"
#define MOTOR_LOG
const uint32_t CHANNEL_LIST[4] = {TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4};
TIM_HandleTypeDef* motor_tim;

void motor_tim_set(TIM_HandleTypeDef* i){
    motor_tim = i;
}

void motor_enable(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        HAL_TIM_PWM_Start(motor_tim, CHANNEL_LIST[i]);
    }
}
void motor_disable(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        HAL_TIM_PWM_Stop(motor_tim, CHANNEL_LIST[i]);
    }
}
void motor_stop(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[i], 0);
    }
}
void motor_break(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[i], FULL_SPEED);
    }
}

void motor_cmd(uint8_t cmd, uint32_t speed)
{
    #ifdef MOTOR_LOG
    rt_kprintf("motor cmd get %02x\n", cmd);
    #endif
    switch (cmd)
    {
    case RUN:
        _motor_run(speed);
        break;
    case LEFT:
        _motor_left(speed);
        break;
    case RIGHT:
        _motor_right(speed);
        break;
    case TURN_LEFT:
        _motor_t_left(speed);
        break;
    case TURN_RIGHT:
        _motor_t_right(speed);
        break;
    case BACK:
        _motor_back(speed);
        break;
    default:
        motor_stop();
        break;
    }
}

void _motor_run(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], speed);
}
void _motor_left(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], 0);
}
void _motor_right(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], speed);
}
void _motor_t_left(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], 0);
}
void _motor_t_right(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], speed);
}
void _motor_back(uint32_t speed)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], 0);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], speed);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], 0);
}

void __motor_super(uint32_t speed_channel_1, uint32_t speed_channel_2, uint32_t speed_channel_3, uint32_t speed_channel_4)
{
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[0], speed_channel_1);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[1], speed_channel_2);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[2], speed_channel_3);
    __HAL_TIM_SetCompare(motor_tim, CHANNEL_LIST[3], speed_channel_4);
}
