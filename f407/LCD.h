#ifndef __LCD_H
#define __LCD_H

#include "LCD_Data.h"
#include <stdint.h>

//---------------------LCD参数--------------------
#define LCD_WIDTH  240
#define LCD_HEIGHT 320

//---------------------枚举类型--------------------
typedef enum {
    DRAW_MODE_FILLED,     // 填充模式
    DRAW_MODE_TRANSPARENT // 透明模式
} DrawMode;

//---------------------函数声明--------------------

//================== 基础配置与初始化 ==================
void LCD_Init(void);
void LCD_GPIO_Init(void);
void SPI_Config(void);
void DMA_Config(void);
void LCD_Reset(void);
void LCD_SetFullWindow(void);
void LCD_SetAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

//================== 基础绘图函数 ==================
void LCD_Clear(uint16_t color);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawFillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void LCD_DrawFillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);

//================== 显示相关函数 ==================
void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowString(uint16_t x, uint16_t y, const char *str, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowSignedNum(uint16_t x, uint16_t y, int32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowHexNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowBinNum(uint16_t x, uint16_t y, uint32_t Number, uint8_t Length, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_ShowFloatNum(uint8_t x, uint8_t y, double Number, uint8_t IntLength, uint8_t FraLength, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode);
void LCD_Printf(uint16_t x, uint16_t y, uint16_t Text_color, uint16_t Bg_Color, DrawMode mode, char *format, ...);

//================== 图像与DMA相关 ==================
void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *image);
void LCD_SPI_Transmit_DMA(const uint8_t *data, uint32_t length);
void LCD_FillScreen_DMA(const uint8_t *frame);

//================== 低级操作/工具函数 ==================
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteData(uint8_t data);
void LCD_WriteColor(uint16_t color);
uint32_t LCD_Pow(uint32_t X, uint32_t Y);

//================== 字体绘制内部函数（如需外部用可声明） ==================
void LCD_DrawChar_Filled(uint16_t x, uint16_t y, char chr, uint16_t Text_color, uint16_t Bg_Color);
void LCD_DrawChar_Transparent(uint16_t x, uint16_t y, char chr, uint16_t color);

#endif
