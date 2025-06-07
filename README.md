ST7789 LCD 驱动代码（基于 STM32F103C8T6）
一、项目说明
本仓库包含基于 STM32F103C8T6 的 ST7789 LCD 驱动代码，同时提供兼容 STM32F407ZGT6 的版本（代码结构大同小异）。代码实现了 LCD 初始化、绘图、字符显示、DMA 传输等功能，适用于 240x320 分辨率的 RGB565 格式显示。
二、文件结构
文件	功能描述
LCD.h	头文件，包含函数声明、枚举类型（DrawMode）、LCD 参数定义（分辨率、引脚宏等）
LCD.c	驱动实现文件，包含 LCD 初始化、SPI/DMA 配置、绘图及显示功能函数
LCD_Data.h	颜色表定义（RGB565颜色宏）、点阵字符数据声明、图像数据声明
LCD_Data.c	8x16 点阵字符数据实现（LCD_F8x16）、图像数据存储
三、功能特性
3.1 核心功能
硬件初始化
LCD_Init()：完成 SPI、GPIO、DMA 初始化，LCD 硬件复位及软件配置（如颜色格式、显示方向）。
支持 8 位 4 线 SPI 通信，主模式，时钟频率 36MHz（SPI_BaudRatePrescaler_2）。
使用 DMA1 通道 3 进行数据传输，提升大块数据显示效率。
绘图功能
基础图形：
LCD_DrawPixel(x,y,color)：画像素点。
LCD_DrawLine(x0,y0,x1,y1,color)：Bresenham 算法画直线。
LCD_DrawRect(x0,y0,x1,y1,color)：画空心矩形；LCD_DrawFillRect()：画实心矩形。
LCD_DrawCircle(x0,y0,r,color)：画空心圆；LCD_DrawFillCircle()：画实心圆。
清屏：LCD_Clear(color)用指定颜色填充全屏。
显示功能
字符显示：
LCD_ShowChar(x,y,chr,fg,bg,mode)：显示单个字符，支持DRAW_MODE_FILLED（填充）和DRAW_MODE_TRANSPARENT（透明）模式。
LCD_ShowString(x,y,str,fg,bg,mode)：显示字符串，字符间距自动计算（8 像素 / 字符）。
数值显示：
支持十进制（LCD_ShowNum）、带符号数（LCD_ShowSignedNum）、十六进制（LCD_ShowHexNum）、二进制（LCD_ShowBinNum）及浮点数（LCD_ShowFloatNum）显示。
图像显示：LCD_DrawImage(x,y,w,h,image)支持原始 RGB565 格式图像数据显示。
DMA 加速
LCD_FillScreen_DMA(frame)：通过 DMA 传输整屏数据，支持分块传输（如 3 次传输 153600 字节数据）。
3.2 关键参数
分辨率：240×320 像素
颜色格式：RGB565（16 位色，LCD_COLOR_XXX宏定义见LCD_Data.h）
控制引脚：
DC：PB0，CS：PB1，RST：PB10（硬件复位）
SPI 引脚：SCK=PA5，MOSI=PA7
字库：内置 8x16 点阵字符库（LCD_F8x16，支持 ASCII 32~126 字符）。
四、快速上手
4.1 硬件接线
STM32F103C8T6 引脚	ST7789 引脚	说明
PB0	DC	数据 / 命令选择
PB1	CS	片选
PB10	RST	复位（低电平有效）
PA5	SCK	SPI 时钟
PA7	MOSI	SPI 数据输出
3.3V	VCC	电源
GND	GND	地
4.2 软件配置
包含头文件
c
运行
#include "LCD.h"

初始化 LCD
c
运行
LCD_Init(); // 完成SPI、GPIO、DMA配置及LCD参数初始化
LCD_Clear(LCD_COLOR_Black); // 清屏（黑色背景）

示例：显示字符串与图形
c
运行
// 显示白色字符串（填充模式）
LCD_ShowString(10, 10, "STM32 ST7789 Demo", LCD_COLOR_White, LCD_COLOR_Black, DRAW_MODE_FILLED);

// 画红色实心圆
LCD_DrawFillCircle(120, 160, 50, LCD_COLOR_Red);

// 显示十进制数字（透明模式）
LCD_ShowNum(10, 30, 12345, 5, LCD_COLOR_Green, LCD_COLOR_Black, DRAW_MODE_TRANSPARENT);

五、函数说明
5.1 初始化相关
函数名	功能描述
LCD_Init()	主初始化函数，调用 SPI/GPIO/DMA 配置及 LCD 复位
SPI_Config()	配置 SPI1 为主模式，设置波特率、数据格式等
DMA_Config()	配置 DMA1 通道 3，用于 SPI 数据传输
LCD_Reset()	硬件复位 LCD（拉低 RST 引脚 10ms 后拉高）
5.2 绘图函数
函数名	参数说明
LCD_DrawPixel(x,y,c)	画像素点，坐标 (x,y)，颜色 c（RGB565 格式）
LCD_DrawLine(x0,y0,x1,y1,c)	画直线，两点坐标，颜色 c
LCD_DrawFillRect(x0,y0,x1,y1,c)	画实心矩形，左上角 / 右下角坐标，颜色 c
5.3 显示函数
函数名	参数说明
LCD_ShowChar(x,y,chr,fg,bg,mode)	显示字符，chr为 ASCII 码，fg前景色，bg背景色，mode为显示模式
LCD_Printf(x,y,fg,bg,mode,format,...)	格式化输出（类似 C 语言printf）
六、注意事项
时序要求：
初始化过程中需严格等待延迟（如退出睡眠模式后等待 120ms）。
DMA 传输时确保数据长度与 LCD 窗口匹配，避免越界。
颜色格式：
使用LCD_COLOR_XXX宏（如LCD_COLOR_Red）或自定义 RGB565 值（如0xF800为红色）。
坐标系统：
原点 (0,0) 位于屏幕左上角，x 范围 0~239，y 范围 0~319。
七、兼容性说明
STM32F407ZGT6 版本：需修改 SPI 和 DMA 外设编号（如使用 SPI3、DMA2），引脚映射可参考 F4 系列 IO 复用表。
扩展功能：如需支持更多字体或更高分辨率，可修改LCD_F8x16点阵数据或调整绘图函数逻辑。
八、代码示例（完整主函数）
c
运行
#include "stm32f10x.h"
#include "LCD.h"
#include "Delay.h"

int main(void) {
    Delay_Init(); // 初始化延迟函数
    LCD_Init();   // 初始化LCD

    // 清屏并显示测试内容
    LCD_Clear(LCD_COLOR_Black);
    LCD_ShowString(10, 10, "ST7789 Test", LCD_COLOR_White, LCD_COLOR_Black, DRAW_MODE_FILLED);
    LCD_DrawFillRect(10, 50, 230, 150, LCD_COLOR_LightBlue);
    LCD_DrawCircle(120, 160, 80, LCD_COLOR_Red);
    LCD_ShowNum(10, 280, 2025, 4, LCD_COLOR_Green, LCD_COLOR_Black, DRAW_MODE_TRANSPARENT);

    while (1) {
        // 循环刷新显示（如需动态效果）
    }
}




九、联系方式
如有问题可通过仓库 Issue 反馈，或联系邮箱：your-email@example.com。
欢迎提交 Pull Request 优化代码！
