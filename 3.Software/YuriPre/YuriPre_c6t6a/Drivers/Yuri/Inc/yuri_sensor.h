#ifndef __YURI_SENSOR_H
#define __YURI_SENSOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "yuri.h"

extern uint8_t track;
extern uint8_t track_last;
extern uint8_t track_flag;
extern uint16_t timeout;
extern uint8_t track_flag;

void motor_left(uint8_t speed);
void motor_right(uint8_t speed);
void motor_run(uint8_t speed);
void motor_trun_left(uint8_t speed);
void motor_trun_right(uint8_t speed);
void motor_back(uint8_t speed);
void motor_stop(void);

uint8_t track_check(uint8_t bit);
void track_check_while(uint8_t bit);
uint8_t is_out_track(void);
    
uint8_t yuri_sensor_read(void);
void auto_track(void);


#ifdef __cplusplus
}
#endif

#endif
