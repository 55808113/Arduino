# Tetris俄罗斯方块通用类
[![博客](https://camo.githubusercontent.com/85a04ac4953a80940570b5c86ce73a1d34ff1542/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6373646e2d4353444e2d7265642e737667)](https://blog.csdn.net/sunxdd)

Tetris类是arduino用来开发俄罗斯方块的通用类

目前支持四种设备显示俄罗斯方块

- SSD1306 : 屏幕为SSD1306_128_64时
- LED8X8 : 屏幕为8*8LED时，使用LEDMatrixDriver类库使用这个。
- WS2812B : 屏幕为多彩的WS2812B的灯时使用这个配置
- NOKIA5110 : 屏幕为NOKIA5110时，使用这个配置

参数配置例子

```
//当屏幕为128X64的时候选择这个
//#define SSD1306_TYPE
//当屏幕为LED8X8的时候选择这个
//#define LED8X8_TYPE
//当屏幕为WS2812B5X20的时候选择这个
//#define WS2812B_TYPE
//当屏幕为NOKIA5110的时候选择这个
//#define NOKIA5110_TYPE
```

根据你自己的显示设备来配置相关参数就行了！