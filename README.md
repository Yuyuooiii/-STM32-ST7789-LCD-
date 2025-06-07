概述
这是一个针对ST7789驱动器的240x320 LCD屏幕的STM32驱动程序库，支持F103和F407系列MCU。提供了全面的图形功能，包括基本绘图、文本显示、图像渲染和DMA加速操作。

主要特性
支持240x320分辨率RGB565显示
硬件SPI通信（4线制）
DMA加速数据传输
丰富的图形API：点、线、矩形、圆形（填充/非填充）
多种字体显示模式（填充/透明）
数字格式化输出（整数、浮点、十六进制、二进制）
printf风格文本输出
图像渲染功能
预定义RGB565颜色表（200+颜色）
硬件连接
LCD引脚	STM32引脚
DC	PB0
CS	PB1
RST	PB10
SCK	PA5
MOSI	PA7
BL	VCC (默认)
快速开始
#include "LCD.h"

int main() {
    LCD_Init();  // 初始化LCD
    LCD_Clear(LCD_COLOR_Black);  // 清屏为黑色
    
    // 绘制红色矩形框
    LCD_DrawRect(50, 50, 150, 100, LCD_COLOR_Red);
    
    // 显示绿色文本
    LCD_ShowString(60, 70, "Hello STM32!", LCD_COLOR_Green, LCD_COLOR_Black, DRAW_MODE_FILLED);
    
    // 显示浮点数
    LCD_ShowFloatNum(60, 90, 3.14159, 1, 5, LCD_COLOR_Yellow, LCD_COLOR_Blue, DRAW_MODE_TRANSPARENT);
    
    while(1);
}
API功能分类
初始化与控制
void LCD_Init(void);
void LCD_Reset(void);
void LCD_SetAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_Clear(uint16_t color);
基本绘图
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawFillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void LCD_DrawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
文本显示
void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint16_t color, uint16_t bg, DrawMode mode);
void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg, DrawMode mode);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint16_t color, uint16_t bg, DrawMode mode);
void LCD_ShowFloatNum(uint8_t x, uint8_t y, double num, uint8_t intLen, uint8_t fracLen, ...);
void LCD_Printf(uint16_t x, uint16_t y, uint16_t color, uint16_t bg, DrawMode mode, char *format, ...);
高级功能
void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *image);
void LCD_FillScreen_DMA(const uint8_t *frame);  // DMA全屏填充
颜色定义
200+预定义RGB565颜色（LCD_Data.h）：

#define LCD_COLOR_Red       0xF800
#define LCD_COLOR_Green     0x07E0
#define LCD_COLOR_Blue      0x001F
#define LCD_COLOR_White     0xFFFF
#define LCD_COLOR_Black     0x0000
// ...完整列表见LCD_Data.h
资源占用
SPI接口：SPI1 (PA5/PA7)
DMA通道：DMA1通道3
字体：8x16点阵ASCII字符集
ROM占用：~3KB (代码) + 2KB (字体数据)
移植说明
根据目标MCU调整SPI和DMA配置
修改引脚定义（LCD.h中的宏）
提供精确延时函数（当前使用Delay_ms）
调整SPI时钟分频以适应不同主频
示例图片
版本信息
当前版本：v1.0
更新日期：2025-06-06
作者：Yuan_ANKORO
许可证
MIT License - 自由用于个人和商业项目，需保留版权声明
