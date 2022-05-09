#include "myoled.h"

void oled_entry(void *p)
{
    i2c_handle_set(p);
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 0, "www.taxing.com", 16);
    OLED_ShowCHinese(0, 4, 0);  //
    OLED_ShowCHinese(16, 4, 1); //
    OLED_ShowCHinese(32, 4, 2); //
    OLED_ShowCHinese(48, 4, 6); //
    OLED_ShowCHinese(0, 6, 3);  //
    OLED_ShowCHinese(16, 6, 4); //
    OLED_ShowCHinese(32, 6, 5); //
    OLED_ShowCHinese(48, 6, 6); //
    while (1)
    {
        rt_thread_mdelay(5000);
        rt_kprintf("oled thread\n");
    }
}

void oled_entry2(void *p, uint8_t * txt)
{
    i2c_handle_set(p);
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(0, 0, txt, 16);
}
