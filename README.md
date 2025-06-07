# ST7789 LCD Driver for STM32 (F103C8T6 / F407ZGT6)

这是一个基于 STM32 微控制器的 ST7789 240x320 全彩 IPS 屏幕驱动库，分别适配 STM32F103C8T6 和 STM32F407ZGT6 版本。使用硬件 SPI 通信，支持 DMA 加速绘图，适合需要高刷新率显示效果的嵌入式项目。

---

## 📁 项目结构

本项目包含两个版本：

* `f103/`：基于 STM32F103C8T6，使用标准外设库 (StdPeriph Library)
* `f407/`：基于 STM32F407ZGT6，使用标准外设库 (StdPeriph Library)

每个版本均包含以下核心文件：

| 文件名              | 功能描述                   |
| ---------------- | ---------------------- |
| `lcd.c`          |   LCD 初始化与基础操作函数         |
| `lcd.h`          |   LCD 函数声明与定义            |
| `lcd_data.c`     |   字库 图像数据           |
| `lcd_data.h`     |   图形绘制函数声明               |

---

## ✅ 功能特性

* ST7789 初始化与全彩显示支持
* 支持硬复位引脚
* 硬件 SPI 通信（速度高，配置简单）
* 字符显示支持透明与非透明模式
* 图形绘制支持：

  * 单点绘制
  * 直线、矩形、圆
  * 填充区域
* 显示整数/浮点数据
* DMA 加速刷屏

---

## 📷 效果演示

> (https://www.bilibili.com/video/BV1RqTgzpEaZ/?spm_id_from=333.1387.homepage.video_card.click)

---

## 🚀 快速开始

### 硬件连接

| ST7789 引脚 | STM32F103C8T6 | 说明         |
| --------- | ------------- | ---------- |
| SCL       | PA5           | SPI1\_SCK  |
| SDA       | PA7           | SPI1\_MOSI |
| RES       | PB0 (GPIO)    | 硬复位        |
| DC        | PB1 (GPIO)    | 数据/命令切换    |
| CS        | GND / GPIO    | 切换选通       |
| BLK       | VCC / GPIO    | 背光控制       |

> 若使用 F407ZGT6，请根据实际连接修改 `lcd.c` 中 GPIO 初始化配置或者直接使用发布的f407版本

---

### 软件配置

* 使用 **标准外设库 (StdPeriphLib)**
* 可自定义 `lcd.h` 中的显示尺寸：

```c
#define LCD_WIDTH  240
#define LCD_HEIGHT 320
```

---

### 使用示例

```c
LCD_Init(); // 初始化 LCD

LCD_Clear(BLACK); // 清屏

LCD_ShowString(10, 10, "Hello, ST7789!", WHITE, BLACK, DRAW_MODE_FILLED);

LCD_DrawRectangle(20, 50, 100, 120, RED);
```

---

## ⚙️ DMA 支持 (可选)

项目已预留 DMA 支持，如使用 STM32F103，默认使用 DMA1\_Channel3，可扩展实现非阻塞式刷屏：

```c
void LCD_WriteData_DMA(uint8_t* data, uint32_t length);
```

建议在 `LCD_Clear()` 和 `LCD_DrawPicture()` 类大量绘图函数中使用 DMA 以提升刷新效率。

---

## 🛠 开发环境

* IDE：Keil / STM32CubeIDE / EIDE / VS Code
* 编译器：ARM MDK / GCC
* 官方库：STM32 StdPeriphLib

---

## 📌 注意事项

* DMA 需配置中断优先级并确保 SPI 与 DMA 配合合理
* 若字符显示乱码，请检查 `lcd_data.h` 字符字模是否完整
* 如果屏幕无显示，请检查 GPIO 引脚连线是否正确，需要时增加延时

---

## 📜 许可协议

MIT License - 可自由使用和修改
