#include "yuri_sensor.h"

uint8_t yuri_sensor_read()
{
    uint8_t track_temp = 0x01;
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
    {
        track |= (track_temp << 0);
    }
    else
    {
        track &= ~(track_temp << 0);
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
    {
        track |= (track_temp << 1);
    }
    else
    {
        track &= ~(track_temp << 1);
    }
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15))
    {
        track |= (track_temp << 2);
    }
    else
    {
        track &= ~(track_temp << 2);
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
    {
        track |= (track_temp << 3);
    }
    else
    {
        track &= ~(track_temp << 3);
    }
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))
    {
        track |= (track_temp << 4);
    }
    else
    {
        track &= ~(track_temp << 4);
    }
    return track;
}

void motor_left(uint8_t speed)
{
}

void motor_right(uint8_t speed)
{
}

void motor_trun_left(uint8_t speed)
{
}

void motor_trun_right(uint8_t speed)
{
}

void motor_run(uint8_t speed)
{
}

void motor_back(uint8_t speed)
{
}

void motor_stop()
{
}

uint8_t is_out_track(void)
{
    return 0;
    // if(~track)
}

//如果该位在黑线上，返回1
uint8_t track_check(uint8_t bit)
{
    return track & 1 << bit;
}

void track_check_while(uint8_t bit)
{
    timeout = TRUN_TIMEOUT;
    while (track_check(bit) && track_flag)
    {
        if (timeout == 0)
            break;
    }
}

//|LEFTB|LEFTA|MIDDLE|RIGHTA|RIGHTB|

void auto_track(void)
{
    if (track_check(MIDDLE))
    // 中间为1，没有偏离
    {
        motor_run(RUN_SPEED);
    }
    else
    //中间为0，偏离轨道
    {
        if (track_check(LEFTB))
        {
            //左B位黑线，大幅偏离轨道，旋转至左A位在黑线上
            motor_right(TURN_SPEED);
            track_check_while(LEFTA);
        }

        if (track_check(LEFTA))
        {
            //第一位为1，小幅偏离轨道，转弯至中位为0
            motor_trun_left(TURN_SPEED);
            track_check_while(MIDDLE);
        }

        if (track_check(RIGHTB))
        {
            //右B位黑线，大幅偏离轨道，旋转至右A位在黑线上
            motor_trun_left(TURN_SPEED);
            track_check_while(RIGHTA);
        }

        if (track_check(RIGHTA))
        {
            //第一位为1，小幅偏离轨道，转弯至中位为0
            motor_left(TURN_SPEED);
            track_check_while(MIDDLE);
        }

        if (track)
        {
            //没有一个在黑线上，出大问题
            motor_back(RUN_SPEED);
            //后退
        }
    }
}
