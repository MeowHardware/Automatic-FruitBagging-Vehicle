#include <rtthread.h>
#include "mymotor.h"


void motor_entry(void *p)
{
    motor_enable();
    while(1){
        rt_thread_mdelay(1000);
        motor_cmd(RUN, 800);
        rt_thread_mdelay(1000);
        motor_cmd(LEFT, 800);
        rt_thread_mdelay(1000);
        motor_cmd(RIGHT, 800);
        rt_thread_mdelay(1000);
        motor_cmd(TURN_LEFT, 800);
        rt_thread_mdelay(1000);
        motor_cmd(TURN_RIGHT, 800);
        rt_thread_mdelay(1000);
        motor_cmd(BACK, 800);
        rt_thread_mdelay(1000);
        motor_stop();
        rt_thread_mdelay(1000);
    }    
}
