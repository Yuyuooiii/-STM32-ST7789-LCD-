# STM32 ST7789 LCD Driver

[](https://opensource.org/licenses/MIT)

## 概述
这是一个针对ST7789驱动器的240x320 LCD屏幕的STM32驱动程序库，支持F103和F407系列MCU。提供了全面的图形功能，包括基本绘图、文本显示、图像渲染和DMA加速操作。

## 主要特性
- **硬件支持**：
  - 支持240x320分辨率RGB565显示
  - 硬件SPI通信（4线制）
  - DMA加速数据传输
  
- **图形功能**：
  - 基本绘图：点、线、矩形、圆形（填充/非填充）
  - 文本显示：8x16点阵ASCII字符集
  - 图像渲染：支持RGB565格式图像
  - 预定义200+ RGB565颜色
  
- **高级功能**：
  - 数字格式化输出（整数、浮点、十六进制、二进制）
  - printf风格文本输出
  - 多种显示模式（填充/透明）

## 硬件连接
| LCD引脚 | STM32引脚 | 功能说明 |
|---------|-----------|----------|
| DC      | PB0       | 数据/命令选择 |
| CS      | PB1       | 片选信号 |
| RST     | PB10      | 复位信号 |
| SCK     | PA5       | SPI时钟 |
| MOSI    | PA7       | SPI数据输出 |
| BL      | VCC       | 背光控制（默认高电平）|

## 快速开始
```c
#include "LCD.h"

int main(void) {
    // 初始化LCD
    LCD_Init();
    
    // 清屏为黑色
    LCD_Clear(LCD_COLOR_Black);
    
    // 绘制红色矩形框
    LCD_DrawRect(50, 50, 150, 100, LCD_COLOR_Red);
    
    // 显示绿色文本（填充模式）
    LCD_ShowString(60, 70, "Hello STM32!", 
                   LCD_COLOR_Green, LCD_COLOR_Black, 
                   DRAW_MODE_FILLED);
    
    // 显示浮点数（透明模式）
    LCD_ShowFloatNum(60, 90, 3.14159, 1, 5, 
                     LCD_COLOR_Yellow, LCD_COLOR_Blue, 
                     DRAW_MODE_TRANSPARENT);
    
    while(1) {
        // 主循环
    }
}
