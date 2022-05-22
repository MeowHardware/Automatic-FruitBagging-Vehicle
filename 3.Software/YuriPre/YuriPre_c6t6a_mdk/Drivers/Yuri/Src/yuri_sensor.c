#include "yuri_sensor.h"
#include "tim.h"
#include "math.h"

void yuri_sensor_read()
{
    track[0] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
    track[1] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
    track[2] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);
    track[3] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
    track[4] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);

    // uint8_t track_temp = 0x01;
    // if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))
    // {
    //     track |= (track_temp << 0);
    // }
    // else
    // {
    //     track &= ~(track_temp << 0);
    // }
    // if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))
    // {
    //     track |= (track_temp << 1);
    // }
    // else
    // {
    //     track &= ~(track_temp << 1);
    // }
    // if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15))
    // {
    //     track |= (track_temp << 2);
    // }
    // else
    // {
    //     track &= ~(track_temp << 2);
    // }
    // if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
    // {
    //     track |= (track_temp << 3);
    // }
    // else
    // {
    //     track &= ~(track_temp << 3);
    // }
    // if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11))
    // {
    //     track |= (track_temp << 4);
    // }
    // else
    // {
    //     track &= ~(track_temp << 4);
    // }
    // return track;
}

void left_motor_run(uint8_t speed)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, speed);
}

void left_motor_back(uint8_t speed)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, speed);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
}

void left_motor_stop()
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0);
}

void right_motor_run(uint8_t speed)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 0);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, speed);
}

void right_motor_back(uint8_t speed)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, speed);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, 0);
}

void right_motor_stop()
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 0);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, 0);
}

void motor_left(uint8_t speed)
{
    right_motor_run(speed);
    left_motor_stop();
}

void motor_right(uint8_t speed)
{
    left_motor_run(speed);
    right_motor_stop();
}

void motor_turn_left(uint8_t speed)
{
    right_motor_run(speed);
    left_motor_back(speed);
}

void motor_turn_right(uint8_t speed)
{
    left_motor_run(speed);
    right_motor_back(speed);
}

void motor_run(uint8_t speed)
{
    left_motor_run(speed);
    right_motor_run(speed);
}

void motor_back(uint8_t speed)
{
    left_motor_back(speed);
    right_motor_back(speed);
}

void motor_stop()
{
    left_motor_stop();
    right_motor_stop();
}

uint8_t is_out_track(void)
{
    return 0;
    // if(~track)
}

//如果该位在黑线上，返回1
uint8_t track_check(uint8_t bit)
{
    return track[bit];
    // return track & 1 << bit;
}

void track_check_while(uint8_t bit)
{
    timeout = TRUN_TIMEOUT;
    // HAL_GPIO_WritePin();
    while (track_check(bit) && track_flag && timeout)
        ;
}

//|LEFTB|LEFTA|MIDDLE|RIGHTA|RIGHTB|

void auto_track(void)
{
    //    if (!track_flag)
    //    {
    //        motor_stop();
    //        return;
    //    }

    if (track_check(MIDDLE))
    // 中间为1，没有偏离
    {
        motor_run(RUN_SPEED);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
        return;
    }
    else
    //中间为0，偏离轨道
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
        if (track_check(LEFTB))
        {
            //左B位黑线，大幅偏离轨道，旋转至左A位在黑线上
            motor_turn_right(TURN_SPEED);

            // track_check_while(LEFTA);
            return;
        }

        if (track_check(RIGHTB))
        {
            //右B位黑线，大幅偏离轨道，旋转至右A位在黑线上
            motor_turn_left(TURN_SPEED);
            // track_check_while(RIGHTA);
            return;
        }

        if (track_check(LEFTA))
        {
            //第一位为1，小幅偏离轨道，转弯至中位为0
            motor_right(TURN_SPEED);
            // track_check_while(MIDDLE);
            return;
        }

        if (track_check(RIGHTA))
        {
            //第一位为1，小幅偏离轨道，转弯至中位为0
            motor_left(TURN_SPEED);
            // track_check_while(MIDDLE);
            return;
        }

        motor_back(RUN_SPEED);
        //后退
    }
}

void servo_set(uint8_t bit, uint16_t time)
{
    switch (bit)
    {
    case 0:
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, time);
        break;
    case 1:
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, time);
        break;
    case 2:
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, time);
        break;
    case 3:
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, time);
        break;
    case 4:
        __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, time);
        break;
    default:
        break;
    }
}

void servo_set_angle(uint8_t bit, float angle)
{
    switch (bit)
    {
    case 0:
        servo_set(bit, 500 + 11.11 * angle);
        break;
    case 1:
        servo_set(bit, 1900 - 11.11 * angle);
        break;
    case 2:
        servo_set(bit, 1800 - 11.11 * (-angle));
        break;
    case 3:
        servo_set(bit, 1150 + 11.11 * (-angle));
        break;
    case 4:
        //__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, time);
        break;
    default:
        break;
    }
}

float l0 = 1.03;
float l1 = 1.25;
float l2 = 0;
#define PI 3.14
void Kinematic_Analysis(float x, float y, float Beta, float Alpha)
{
    if( x * x + y * y > 5.2){
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
        return;
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    float m, n, k, a, b, c, theta1, theta2, theta3, s1ps2;
    m = l2 * cos(Alpha * PI / 180) - x;
    n = l2 * sin(Alpha * PI / 180) - y;
    k = (l1 * l1 - l0 * l0 - m * m - n * n) / 2 / l0;
    a = m * m + n * n;
    b = -2 * n * k;
    c = k * k - m * m;
    theta1 = (-b + sqrt(b * b - 4 * a * c)) / 2 / a;
    theta1 = asin(theta1) * 180 / PI;
    
    if (theta1 < 0)
        theta1 = 0;

    k = (l0 * l0 - l1 * l1 - m * m - n * n) / 2 / l1;
    a = m * m + n * n;
    b = -2 * n * k;
    c = k * k - m * m;
    s1ps2 = (-b - sqrt(b * b - 4 * a * c)) / 2 / a;
    s1ps2 = asin(s1ps2) * 180 / PI;

    if (s1ps2 > 90)
        theta2 = 90;
    if (s1ps2 < -90)
        theta2 = -90;

    theta2 = s1ps2 - theta1;

    if (theta2 > 0)
        theta2 = 0;
    if (theta2 < -110)
        theta2 = -110;

    theta3 = Alpha - theta1 - theta2;

    servo_set_angle(1, theta1);
    servo_set_angle(2, theta2);
    servo_set_angle(3, theta3);
}
