/*
 * @brief  LCD ST7789VW 驱动代码(8脚4线SPI)
 *
 * 该文件包含LCD控制引脚的宏定义和相关函数声明。
 * 它使用SPI1进行通信，并支持通过DMA传输数据，静态数据不使用DMA。
 * LCD显示分辨率为240x320像素，使用RGB565颜色格式。
 * 当前程序版本: v1.0   日期: 2025年6月6日
 * 作者: Yuan_ANKORO
 *
 * 引脚定义：
 * - DC: 数据/命令选择 (PB0)
 * - CS: 片选 (PB1)
 * - RST: 复位 (PB10)
 * * SPI引脚：
 * - SCK: 时钟 (PA5)
 * - MOSI: 主输出从输入 (PA7)
 * - BL: 背光控制 (默认接高电平)
 *
 * * 使用SPI1进行数据传输，配置为主模式, 2分频F407为42MHZ。
 * * 使用DMA1的通道3进行数据传输。
 */

#include "stm32f4xx.h"
#include "LCD.h"
#include "Delay.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// LCD 控制引脚宏定义
#define LCD_DC_HIGH()  (GPIOB->BSRR = GPIO_Pin_0)
#define LCD_DC_LOW()   (GPIOB->BSRR = (uint32_t)GPIO_Pin_0 << 16)
#define LCD_CS_HIGH()  (GPIOB->BSRR = GPIO_Pin_1)
#define LCD_CS_LOW()   (GPIOB->BSRR = (uint32_t)GPIO_Pin_1 << 16)
#define LCD_RST_HIGH() (GPIOB->BSRR = GPIO_Pin_10)
#define LCD_RST_LOW()  (GPIOB->BSRR = (uint32_t)GPIO_Pin_10 << 16)

void SPI_Config(void)
{
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // 启用时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);  // SPI1时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // GPIOA时钟

    // 配置SCK(PA5)和MOSI(PA7)
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF; // 复用功能
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 推挽
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 配置复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

    // SPI参数配置
    SPI_InitStruct.SPI_Direction         = SPI_Direction_1Line_Tx; // 只发送模式
    SPI_InitStruct.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL              = SPI_CPOL_Low;            // CPOL=0
    SPI_InitStruct.SPI_CPHA              = SPI_CPHA_1Edge;          // CPHA=0 (模式0)
    SPI_InitStruct.SPI_NSS               = SPI_NSS_Soft;            // 软件控制CS
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // 42MHz @168MHz/4
    SPI_InitStruct.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStruct);

    SPI_Cmd(SPI1, ENABLE);
}

void DMA_Config(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); // SPI1的TX在DMA2

    DMA_DeInit(DMA2_Stream3); // SPI1_TX对应DMA2_Stream3, Channel 3

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_Channel            = DMA_Channel_3;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr    = 0; // 运行时再设置
    DMA_InitStructure.DMA_DIR                = DMA_DIR_MemoryToPeripheral;
    DMA_InitStructure.DMA_BufferSize         = 233; // 运行时再设置
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream3, &DMA_InitStructure);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
}

void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    // DC引脚 (PB0)
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;    // 输出模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;    // 推挽输出
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; // 无上拉下拉
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // CS引脚 (PB1)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    LCD_CS_HIGH(); // 默认不选中

    // RST引脚 (PB10)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    LCD_RST_HIGH(); // 先拉高
}

void LCD_WriteCommand(uint8_t cmd)
{
    LCD_DC_LOW(); // DC=0 (命令)
    LCD_CS_LOW(); // CS=0 (选中)

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // 等待发送缓冲区空
    SPI_I2S_SendData(SPI1, cmd);

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET); // 等待发送完成
    LCD_CS_HIGH();                                                // CS=1
}

void LCD_WriteData(uint8_t data)
{
    LCD_DC_HIGH(); // DC=1 (数据)
    LCD_CS_LOW();  // CS=0

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    LCD_CS_HIGH(); // CS=1
}

void LCD_Reset(void)
{
    LCD_RST_LOW();  // RST=0
    Delay_ms(10);   // 保持10ms
    LCD_RST_HIGH(); // RST=1
    Delay_ms(120);  // 等待120ms
}

// 设置默认绘图窗口（全屏）
void LCD_SetFullWindow(void)
{
    LCD_WriteCommand(0x2A); // CASET（列地址）
    LCD_WriteData(0x00);
    LCD_WriteData(0x00); // XS=0
    LCD_WriteData(0x00);
    LCD_WriteData(0xEF); // XE=239

    LCD_WriteCommand(0x2B); // RASET（行地址）
    LCD_WriteData(0x00);
    LCD_WriteData(0x00); // YS=0
    LCD_WriteData(0x01);
    LCD_WriteData(0x3F); // YE=319
}

void LCD_Init(void)
{
    /* 0. 底层配置 */
    SPI_Config();    // 配置SPI
    LCD_GPIO_Init(); // 初始化GPIO
    DMA_Config();    // 配置DMA

    /* 1. 硬件复位 */
    LCD_Reset();

    /* 2. 软件初始化 */
    LCD_WriteCommand(0x11); // SLPOUT（退出睡眠模式）
    Delay_ms(120);          // 必须等待120ms！

    LCD_WriteCommand(0x3A); // COLMOD（设置颜色格式）
    LCD_WriteData(0x55);    // 参数：0x55=RGB565，0x66=RGB666

    LCD_WriteCommand(0x36); // MADCTL（显示方向控制）
    LCD_WriteData(0x00);    // 参数：0x00=RGB，0x08=BGR

    LCD_WriteCommand(0x21); // INVON（开启颜色反转，TFT一般不用开，IPS屏要开）

    LCD_WriteCommand(0x29); // DISPON（开启显示）

    LCD_Clear(LCD_COLOR_Black); // 清屏，默认黑色
}

void LCD_SetAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    LCD_WriteCommand(0x2A); // 列地址设置 (CASET)
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0 & 0xFF);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xFF);

    LCD_WriteCommand(0x2B); // 行地址设置 (RASET)
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0 & 0xFF);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xFF);

    LCD_WriteCommand(0x2C); // 写内存（开始写数据）
}

void LCD_WriteColor(uint16_t color)
{
    LCD_WriteData(color >> 8);   // 先发高8位
    LCD_WriteData(color & 0xFF); // 再发低8位
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetAddress(x, y, x, y);
    LCD_WriteColor(color);
}

void LCD_DrawFillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint32_t totalPixels = (x1 - x0 + 1) * (y1 - y0 + 1);
    LCD_SetAddress(x0, y0, x1, y1);
    while (totalPixels--) {
        LCD_WriteColor(color);
    }
}

void LCD_Clear(uint16_t color)
{
    LCD_DrawFillRect(0, 0, 239, 319, color); // 填充所有屏幕区域
}

void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int dx  = abs(x1 - x0);
    int dy  = -abs(y1 - y0);
    int sx  = x0 < x1 ? 1 : -1;
    int sy  = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1) {
        LCD_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    LCD_DrawLine(x0, y0, x1, y0, color); // 上边
    LCD_DrawLine(x0, y1, x1, y1, color); // 下边
    LCD_DrawLine(x0, y0, x0, y1, color); // 左边
    LCD_DrawLine(x1, y0, x1, y1, color); // 右边
}

void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        LCD_DrawPixel(x0 + x, y0 + y, color);
        LCD_DrawPixel(x0 - x, y0 + y, color);
        LCD_DrawPixel(x0 + x, y0 - y, color);
        LCD_DrawPixel(x0 - x, y0 - y, color);
        LCD_DrawPixel(x0 + y, y0 + x, color);
        LCD_DrawPixel(x0 - y, y0 + x, color);
        LCD_DrawPixel(x0 + y, y0 - x, color);
        LCD_DrawPixel(x0 - y, y0 - x, color);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void LCD_DrawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        // 画每一对对称的水平线（8个对称方向）
        LCD_DrawLine(x0 - x, y0 - y, x0 + x, y0 - y, color);
        LCD_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        LCD_DrawLine(x0 - y, y0 - x, x0 + y, y0 - x, color);
        LCD_DrawLine(x0 - y, y0 + x, x0 + y, y0 + x, color);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void LCD_DrawChar_Filled(uint16_t x, uint16_t y, char chr, uint16_t Text_color, uint16_t Bg_Color)
{
    if (chr < 32 || chr > 126) chr = '?'; // 非法字符替换为问号
    const uint8_t *bitmap = LCD_F8x16[chr - 32];

    // 设置显示窗口：x ~ x+7, y ~ y+15
    LCD_SetAddress(x, y, x + 7, y + 15);

    for (uint8_t row = 0; row < 16; row++) {
        uint8_t bits = bitmap[row];
        for (uint8_t col = 0; col < 8; col++) {
            if (bits & (1 << (7 - col)))
                LCD_WriteColor(Text_color);
            else
                LCD_WriteColor(Bg_Color);
        }
    }
}

void LCD_DrawChar_Transparent(uint16_t x, uint16_t y, char chr, uint16_t color)
{
    if (chr < 32 || chr > 126) chr = '?'; // 非法字符统一处理
    const uint8_t *bitmap = LCD_F8x16[chr - 32];

    for (uint8_t row = 0; row < 16; row++) {
        uint8_t bits = bitmap[row];
        for (uint8_t col = 0; col < 8; col++) {
            if (bits & (1 << (7 - col))) {
                LCD_DrawPixel(x + col, y + row, color); // 只画字体像素，背景不画
            }
        }
    }
}

void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    switch (mode) {
        case DRAW_MODE_FILLED:
            LCD_DrawChar_Filled(x, y, chr, Text_color, Bg_Color);
            break;
        case DRAW_MODE_TRANSPARENT:
            LCD_DrawChar_Transparent(x, y, chr, Text_color);
            break;
        default:
            // 默认使用透明模式
            LCD_DrawChar_Transparent(x, y, chr, Text_color);
            break;
    }
}

void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    while (*str) {
        LCD_ShowChar(x, y, *str, Text_color, Bg_Color, mode);
        x += 8; // 每个字符宽度8像素
        str++;
    }
    return;
}

uint32_t LCD_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--) {
        Result *= X;
    }
    return Result;
}

void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    uint8_t i;
    for (i = 0; i < Length; i++) {
        LCD_ShowChar(x + i * 8, y, Number / LCD_Pow(10, Length - i - 1) % 10 + '0', Text_color, Bg_Color, mode);
    }
}

void LCD_ShowSignedNum(uint16_t x, uint16_t y, int32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    uint8_t i;
    uint32_t Number1;

    if (Number >= 0) // 数字大于等于0
    {
        LCD_ShowChar(x, y, '+', Text_color, Bg_Color, mode); // 显示+号
        Number1 = Number;                                    // Number1直接等于Number
    } else                                                   // 数字小于0
    {
        LCD_ShowChar(x, y, '-', Text_color, Bg_Color, mode); // 显示-号
        Number1 = -Number;                                   // Number1等于Number取负
    }

    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*Number1 / LCD_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        LCD_ShowChar(x + (i + 1) * 8, y, Number1 / LCD_Pow(10, Length - i - 1) % 10 + '0', Text_color, Bg_Color, mode);
    }
}

void LCD_ShowHexNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*以十六进制提取数字的每一位*/
        SingleNumber = Number / LCD_Pow(16, Length - i - 1) % 16;

        if (SingleNumber < 10) // 单个数字小于10
        {
            /*+ '0' 可将数字转换为字符格式*/
            LCD_ShowChar(x + i * 8, y, SingleNumber + '0', Text_color, Bg_Color, mode);
        } else // 单个数字大于10
        {
            /*+ 'A' 可将数字转换为从A开始的十六进制字符*/
            LCD_ShowChar(x + i * 8, y, SingleNumber - 10 + 'A', Text_color, Bg_Color, mode);
        }
    }
}

void LCD_ShowBinNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    uint8_t i;
    for (i = 0; i < Length; i++) // 遍历数字的每一位
    {
        /*Number / LCD_Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        LCD_ShowChar(x + i * 8, y, Number / LCD_Pow(2, Length - i - 1) % 2 + '0', Text_color, Bg_Color, mode);
    }
}

void LCD_ShowFloatNum(uint8_t x, uint8_t y, double Number, uint8_t IntLength, uint8_t FraLength, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode)
{
    uint32_t Temp;

    if (Number >= 0) // 数字大于等于0
    {
        LCD_ShowChar(x, y, '+', Text_color, Bg_Color, mode); // 显示+号
    } else                                                   // 数字小于0
    {
        LCD_ShowChar(x, y, '-', Text_color, Bg_Color, mode); // 显示-号
        Number = -Number;                                    // Number取负
    }

    /*显示整数部分*/
    LCD_ShowNum(x + 8, y, Number, IntLength, Text_color, Bg_Color, mode);

    /*显示小数点*/
    LCD_ShowChar(x + (IntLength + 1) * 8, y, '.', Text_color, Bg_Color, mode);

    /*将Number的整数部分减掉，防止之后将小数部分乘到整数时因数过大造成错误*/
    Number -= (uint32_t)Number;

    /*将小数部分乘到整数部分，并显示*/
    Temp = LCD_Pow(10, FraLength);
    LCD_ShowNum(x + (IntLength + 2) * 8, y, ((uint32_t)(Number * Temp)) % Temp, FraLength, Text_color, Bg_Color, mode);
}

void LCD_Printf(uint16_t x, uint16_t y, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode, char *format, ...)
{
    char String[30];                                          // 定义字符数组
    va_list arg;                                              // 定义可变参数列表数据类型的变量arg
    va_start(arg, format);                                    // 从format开始，接收参数列表到arg变量
    vsprintf(String, format, arg);                            // 使用vsprintf打印格式化字符串和参数列表到字符数组中
    va_end(arg);                                              // 结束变量arg
    LCD_ShowString(x, y, String, Text_color, Bg_Color, mode); // LCD显示字符数组（字符串）
}

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *image)
{
    uint32_t total = w * h;
    LCD_SetAddress(x, y, x + w - 1, y + h - 1); // 设置绘图窗口

    for (uint32_t i = 0; i < total; i++) {
        LCD_WriteData(image[2 * i]);     // 高8位
        LCD_WriteData(image[2 * i + 1]); // 低8位
    }
}

void LCD_SPI_Transmit_DMA(const uint8_t *data, uint32_t length)
{
    DMA_Cmd(DMA2_Stream3, DISABLE);
    DMA_SetCurrDataCounter(DMA2_Stream3, length); // 设置DMA传输长度
    DMA2_Stream3->M0AR = (uint32_t)data;          // 设置内存地址
    DMA_Cmd(DMA2_Stream3, ENABLE);

    while (DMA_GetFlagStatus(DMA2_Stream3, DMA_FLAG_TCIF3) == RESET);
    DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3);

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // 等待发送缓冲区空
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);   // 等待SPI传输完成
}

void LCD_FillScreen_DMA(const uint8_t *frame)
{
    LCD_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT); // 设置绘图窗口
    LCD_DC_HIGH();                               // DC=1 (数据)
    LCD_CS_LOW();                                // CS=0

    LCD_SPI_Transmit_DMA(frame, 51200);          // 启动DMA传输
    LCD_SPI_Transmit_DMA(frame + 51200, 51200);  // 启动DMA传输
    LCD_SPI_Transmit_DMA(frame + 102400, 51200); // 启动DMA传输

    LCD_CS_HIGH(); // CS=1
}
