#ifndef __YURI_SENSOR_H
#define __YURI_SENSOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "yuri.h"

extern uint8_t track[5];
extern uint8_t track_flag;
extern uint16_t timeout;
extern uint16_t servo_data_init[6];


void left_motor_run(uint8_t speed);
void left_motor_back(uint8_t speed);
void left_motor_stop(void);
void right_motor_run(uint8_t speed);
void right_motor_back(uint8_t speed);
void right_motor_stop(void);

void motor_left(uint8_t speed);
void motor_right(uint8_t speed);
void motor_run(uint8_t speed);
void motor_turn_left(uint8_t speed);
void motor_turn_right(uint8_t speed);
void motor_back(uint8_t speed);
void motor_stop(void);

uint8_t track_check(uint8_t bit);
void track_check_while(uint8_t bit);
uint8_t is_out_track(void);
    
void yuri_sensor_read(void);
void auto_track(void);
void servo_set(uint8_t bit, uint16_t time);
void servo_set_angle(uint8_t bit, uint8_t angle);

#ifdef __cplusplus
}
#endif

#endif
