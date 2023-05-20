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
anchors = [1.03, 0.94, 1.41, 1.25, 1.59, 1.47, 1.94, 1.75, 1.22, 1.09]
task=kpu.load("/sd/model-40330.kmodel")
kpu.init_yolo2(task, 0.5, 0.3, 5, anchors)
#模型标签
classes = ['apple']
#定时器中断服务函数
def on_timer(timer):
    if ans:
        #print('\xff',end='')
        for i in ans:

            if i.y() > 152:
                print('4', end = '')
            elif i.y() > 132:
                print('3', end = '')
            elif i.y() < 72:
                print('2', end = '')
            elif i.y() < 92:
                print('1', end = '')
            elif i.x() > 132:
                print('5', end = '')
            elif i.x() > 72:
                print('6', end = '')
            else:
                print('0', end = '')

            
                
            #area=i.w()*i.h()
            #print(area,end='')
            #print(classes[i.classid()],end='')
        #print('\x00',end='')
    else:
        print('0', end = '')
#定时器初始化
tim = Timer(Timer.TIMER0, Timer.CHANNEL0, mode=Timer.MODE_PERIODIC, period=10, unit=Timer.UNIT_MS, callback=on_timer, arg=on_timer, start=False, priority=1, div=0)
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
    else:
        lcd.display(img)
a=kpu.deinit(task)


