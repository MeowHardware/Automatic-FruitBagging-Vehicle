import sensor, image, lcd, time
import KPU as kpu
import gc, sys
from machine import UART
from machine import Timer
from fpioa_manager import fm
lcd.init()
lcd.rotation(2)
#摄像头初始化
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_windowing((224, 224))
sensor.run(1)
#模型的加载
anchors = [1.625, 3.53125, 3.34375, 2.625, 3.6875, 1.78125, 1.53125, 3.03125, 1.9062499999999998, 3.40625]
task=kpu.load("/sd/m.kmodel")
kpu.init_yolo2(task, 0.5, 0.3, 5, anchors)
#模型标签
classes = ['e']
#定时器中断服务函数
def on_timer(timer):
    if ans:
        print("R%3d,%3d,%3d,%3d,%c" % (i.x(), i.y(), i.w(), i.h(), classes[i.classid()]))
#定时器初始化
tim = Timer(Timer.TIMER0, Timer.CHANNEL0, mode=Timer.MODE_PERIODIC, period=400, unit=Timer.UNIT_MS, callback=on_timer, arg=on_timer, start=False, priority=1, div=0)
tim.start()
while(True):
    img=sensor.snapshot()
    ans=kpu.run_yolo2(task,img)
    if ans:
        for i in ans:
            #画矩形框
            img.draw_rectangle(i.rect())
            lcd.display(img)
            for i in ans:
            #打印类标签（根据bbox位置)
                lcd.draw_string(i.x(), i.y(), classes[i.classid()], lcd.RED, lcd.WHITE)
                lcd.draw_string(i.x(), i.y()+12, '%f1.3'%i.value(), lcd.RED, lcd.WHITE)
    else:XW
        lcd.display(img)
a=kpu.deinit(task)


