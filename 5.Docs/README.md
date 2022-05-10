
# 前言
受到全球疫情的影响，项目可能与计划中不同，但是不作为正式项目。
## 1. 核心研究内容
* 实时2维图像与6轴机械臂稳定闭系统研究
* 基于K210嵌入式设备CNN物体识别研究

## 2. 次要研究内容
* 刷式直流电机闭环化PID控制
* 灰线循迹定点定位防开环稳定系统研究
* 定点充电桩的设计

## 3. 存在待解决的问题
* 水果怎么自动套袋

# 架构
## 1. 应用架构

在不同产品的实际应用中，功能复用现象时有发生，故为了增强产品实用性，部件可替代性，设计了一种特殊的应用架构模型。

架构分为4层，从下之上分别为硬件层，驱动层，通讯层，逻辑层。

硬件层也是物理层，是应用的基本硬件设备。

驱动层负责将数字信号转换为硬件层需要的模拟信号，同时接收硬件层传输来的模拟信号转化为数字信号。

通讯层是一个虚层，其规定数字信号和逻辑层之间的协议以及规定。逻辑层是负责应用的一个完整的生命周期。

对于该项目，我们将基于该架构模型规划我们的应用。

![架构模型](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/20220510005121-2022-05-10-15-11-13.png)

基于该架构的硬件规划，可以生产出多可应用部署的结构性模块，节省资金以及研发费用。
 
### 2. 应用的生命周期
一个应用具有以下生命周期，初始化INIT，事件EVENT，销毁DESTROY。

![生命周期](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/20220510005151-2022-05-10-15-10-05.png)

初始化阶段，驱动层首先初始化硬件，初始化完毕后逻辑层挂载相关驱动层。
事件阶段，逻辑层按照业务逻辑进行计算。由初始化结束触发。
销毁阶段，停机，逻辑层离线保存相关数据或进入初始化。由事件产生中断触发。

# 2. 电路规划
## 2.1 前置驱动电路
 
### 2.1.1 前置驱动电路控制部分

![控制部分](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/MAIN-2022-05-10-15-09-46.png)

可以看出，这是一份临时随意的电路图，但是其功能完整性是不可否认的。

输入电压12V-功率输入 3.3V信号输入。可驱动2个刷式直流电机，6个舵机，8个灰度传感器模块。主控采用ST公司的STM32F103C8T6价格昂贵性价比不高。H桥芯片是AT8870，3.6A单通道刷式直流电机驱动IC。缓冲芯片选择SN74HC125PWR用作信号隔离。

通讯方式为UART串口通讯。带2个功能开关按键，1个可编程指示灯，3个电源指示灯。6个舵机通道输入，8个灰度传感器输入。提供一个IIC接口，设计接入0.96寸OLED显示屏。

ADC1，ADC2分别可采集12V输入电压，BUCK输出电压。提供SW调试接口。
 
### 2.1.2 前置驱动电路电源部分

![电源部分](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/pwr-2022-05-10-15-09-25.png)

BUCK降压芯片选择MP2236，6A峰值电流，输出电压可调。
输出电压由以下公式指出。

$$ R_{13} = \frac {R_{17}} {\frac{V_{out}}{0.6} - 1}$$

当R17为100K，R13为10K时，输出电压为6.6V。
  
### 2.1.3 前置驱动电路PCB透视图

![正面](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/httpss2.loli.net20220510vEx7642NWYHPFKI.png-2022-05-10-15-12-02.png)
![底面](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/底面-2022-05-10-15-13-36.png)

以上为PCB布局图，可以看出PCB的布局虽然随意，但还是有奥妙所在。PCB为4层板，叠层顺序为TOP-GND-POWER-BOTTOM。表层铜厚1oz，内层铜厚0.5oz，板厚1.6mm。设计最大输入功率72W，板耗<2W。电机接头采用两个KF2EDG 3.08mm拔插式接线端子，12V供电采用一个KF2EDG 5.08mm拔插式接线端子。串口以及烧录接口使用MX1.25mm卧式针座连接器。拔插式设计，作为模型机方便利于调试。背面丝印使用格罗皮，YoLi没有任何含义，由于该PCB属于测试阶段，稳定版本该丝印会换成KJ和版本号。

## 2.2 逻辑控制电路和无线射频电路
### 2.2.1 主控部分

### 2.2.2 电源部分

### 2.2.3 射频部分

# 2. 代码架构
## 2.1 前置驱动代码框架
### 2.1.1 主要框架

### 2.2.1 API文档

## 2.2 逻辑控制代码框架
### 2.2.1 主要框架

### 2.2.2 应用的生命周期规划

### 2.2.3 初始化部分

### 2.2.4 事件部分

### 2.2.5 销毁部分
## 2.3 射频芯片代码框架
### 2.3.1 主要框架
### 2.3.2 互联协议
### 2.3.3 API文档

# 3.物理结构
## 3.1 小车结构
### 3.1.1 小车主体结构
### 3.1.2 动力电机选型

## 3.2机械臂结构
### 3.2.1 机械臂主体结构
### 3.2.2 舵机选型

# 算法
>算法是实现应用的灵魂
## 1.舵机相关算法以及机械臂正逆运动学与坐标变换
### 1.1 舵机PD运动缓冲算法
在该应用环境中，舵机的运动具有定角度特点。传统的舵机控制算法只求角度，但是忽略了速度和加速度的影响，导致舵机突然启动或者突然暂停，受到惯性的印象，内部的减速组受瞬力过大，缓冲时间过短，导致经常有舵机出现断齿的现象，这里设计了一种PD算法，即P（比例），D（微分），微分环节参数设置得当的时候，可以提高舵机运行的动态性能指标，使超调减小，稳定性增加，动态误差减小。

$$ pwm=K_p*e(k)+K_d[e(k)-e(k-1)] $$

$e(k)代表本次偏差$

$e(k-1)代表上一次的偏差$

$pwm 代表输出$
```
/*函数功能：位置式PD控制器
入口参数：位置信息，目标位置
返回值：控制量
*/
float Position_PID1 (float Encoder,float Target)
{
static float Bias,Pwm,Integral_bias,Last_Bias;
Bias=Target-Encoder; //计算偏差
Integral_bias+=Bias;//求出偏差的积分
Pwm=Position_KP*Bias/100+Position_KI*Integral_bias/100+Position_KD*(Bia
s-Last_Bias)/100; //位置式 PID 控制器
Last_Bias=Bias; //保存上一次偏差
return Pwm; //控制量输出
}
```

### 1.2 机械臂的正运动学DH模型以及空间坐标变换
DH模型介绍：Denavit-Hartenberg(D-H)模型表示了对机器人连杆和关节进行建模的一种非常简单的方法，可用于任何机器人构型，也可用于表示在任何坐标中的变换。DH 模型通过限制原点位置和 X 轴的方向，人为减少了两个自由度，因此它只需要用四个参数即可表达关节之间原本是六自由度的坐标变换。DH 选的四个参数都有常明确的物理含义：

`link length`（连杆长度）：两个关节的轴（旋转关节的旋转轴，平移关节的平移轴）之间的公共法线长度。

`link twist`（连杆扭转）：一个关节的轴相对于另一个关节的轴绕它们的公共法线旋转的角度。

`link offset`（连杆偏移）：一个关节与下一个关节的公共法线和它与上一个关节的公共法线沿这个关节轴的距离。

`joint angle`（关节转角）：一个关节与下一个关节的公共法线和它与上一个关节的公共法线绕这个关节轴的转角。
由机械臂模型
![机械臂模型](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/c0f78c5f003bd15eb894ec0faf5e0e40-2022-05-10-21-08-13.jpeg)
得到机械臂的DH参数

|$i$|$\alpha_{i-1}$|$a_{i-1}$|$d_i$|$\theta_i$|
|:-:|:-:|:-:|:-:|:-:|
1|-90°|0|a|$\theta_0$
2|90°|0|0|$\theta_1$
3|0|b|0|$\theta_2$
4|0|c|0|$\theta_3$
5|0|d|0|0

根据以下转换公式：

$$ _i^{i-1} T=\left[ \begin{matrix}
   cos \theta _i & -sin \theta _i & 0 & a_{i-1} \\
   sin \theta _i cos \alpha _{i-1} & cos \theta _i cos \alpha _{i-1} & -sin \alpha _{i-1} & -sin \alpha _{i-1}d_i\\
   sin \theta _i sin \alpha _{i-1} & cos \theta _i sin \alpha _{i-1} & cos \alpha _{i-1} & cos \alpha _{i-1}d_i\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

把 DH 表带入转换公式，得到两个相邻关节之间的 T 矩阵

$$ _1^0 T=\left[ \begin{matrix}
   cos \theta _0 & -sin \theta _0 & 0 & 0 \\
   0 & 0 & 1 & d\\
   -sin \theta _0 & cos \theta _0 & 0 & 0\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

$$ _2^1 T=\left[ \begin{matrix}
   cos \theta _1 & -sin \theta _1 & 0 & 0 \\
   0 & 0 & -1 & 0\\
   sin \theta _1 & cos \theta _1 & 0 & 0\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

$$ _3^2 T=\left[ \begin{matrix}
   cos \theta _2 & -sin \theta _2 & 0 & l_0 \\
   sin \theta _2 & cos \theta _2 & 0 & 0\\
   0 & 0 & 1 & 0\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

$$ _4^3 T=\left[ \begin{matrix}
   cos \theta _3 & -sin \theta _3 & 0 & l_1 \\
   sin \theta _3 & cos \theta _3 & 0 & 0\\
   0 & 0 & 1 & 0\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

$$ _5^4 T=\left[ \begin{matrix}
   1 & 0 & 0 & l_2 \\
   0 & 1 & 0 & 0\\
   0 & 0 & 1 & 0\\
   0 & 0 & 0 & 1
\end{matrix} \right] $$

得到旋转矩阵后，根据下面的公式得到末端执行器姿态：
$$\left[\begin{matrix} 
x\\
y\\
z\\
1
\end{matrix}\right]
=
_1^0T
_2^1T
_3^2T
_4^3T
_5^4T
\left[\begin{matrix} 
0\\
0\\
0\\
1
\end{matrix}\right]
$$

### 1.3 机械臂的逆运动学解以及单片机计算速度优化算法
1.2由DH模型得出的模型过于复杂，如果求解的画，对于单片机等计算速度较慢的设备可能会导致宕机崩溃等事故，故针对性模型精简时非常有必要的。
对于该六轴机械臂，精简计算模型，去除下面的旋转关节，在二位的平面上进行几何学分析。

![模型](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/20220510204558-2022-05-10-20-45-58.png)

列出方程

$$x=l_0cos\theta _1 + l_1cos(\theta_1+\theta_2) + l_2cos(\theta_1+\theta_2+\theta$$
$$y=l_0sin\theta _1 + l_1sin(\theta_1+\theta_2) + l_2sin(\theta_1+\theta_2+\theta_3)$$
$$\alpha = \theta_1 + \theta_2 +\theta_3$$

化简
$$x=l_0cos\theta _1 + l_1cos(\theta_1+\theta_2) + l_2cos(\alpha)$$
$$y=l_0sin\theta _1 + l_1sin(\theta_1+\theta_2) + l_2sin(\alpha)$$
令
$$m=l_2cos(\alpha)-x$$
$$n=l_2sin(\alpha)-y$$
得
$$sin\theta _1 = (\frac{-b\pm \sqrt{b^2-4ac}}{2a})=$$
其中
$$k=\frac{^2_0-l^2_1-m^2-n^2}{2l_1}$$
$$a=m^2+n^2$$
$$b=-2nk$$
$$c=k^2-m^2$$

通过同样的方法，可求得$\theta_2$，这样就完成了逆运动学的计算。
经过精简，该简单的算法可以流畅的在32位单片机上运行。

### 1.3 机械臂的逆运动学多解取值问题

在方程$sin\theta _1 = (\frac{-b\pm \sqrt{b^2-4ac}}{2a})=$的中，用于是二元一次方程的实数解，故在$b^2-4ac>0$时存在2个不同的实数解。

![模型](https://cdn.jsdelivr.net/gh/kjook/images@main/img/vscode/20220510204558-2022-05-10-20-45-58.png)

如图所示，这两个解分别是虚线和实线所代表的点，而我们选择虚线点，也就是$\pm$取$+$时的解，这样使关节受力更小同时舵机做功也更少。

## 2. K210深度学习算法



## 3. 灰度传感器巡线与定位算法



