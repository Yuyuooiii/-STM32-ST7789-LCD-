#ifndef __LCD_DATA_H
#define __LCD_DATA_H

#include <stdint.h>

//---------------------RGB565颜色表--------------------
#define LCD_COLOR_LightPink            0xFDB8 // 浅粉红
#define LCD_COLOR_Pink                 0xFE19 // 粉红
#define LCD_COLOR_Crimson              0xD8A7 // 猩红
#define LCD_COLOR_LavenderBlush        0xFF9E // 脸红的淡紫色
#define LCD_COLOR_PaleVioletRed        0xDB92 // 苍白的紫罗兰红色
#define LCD_COLOR_HotPink              0xFB56 // 热情的粉红
#define LCD_COLOR_DeepPink             0xF8B2 // 深粉色
#define LCD_COLOR_MediumVioletRed      0xC0B0 // 适中的紫罗兰红色
#define LCD_COLOR_Orchid               0xDB9A // 兰花的紫色
#define LCD_COLOR_Thistle              0xDDFB // 蓟
#define LCD_COLOR_plum                 0xDD1B // 李子
#define LCD_COLOR_Violet               0xEC1D // 紫罗兰
#define LCD_COLOR_Magenta              0xF81F // 洋红
#define LCD_COLOR_Fuchsia              0xF81F // 灯笼海棠(紫红色)
#define LCD_COLOR_DarkMagenta          0x8811 // 深洋红色
#define LCD_COLOR_Purple               0x8010 // 紫色
#define LCD_COLOR_MediumOrchid         0xBABA // 适中的兰花紫
#define LCD_COLOR_DarkVoilet           0x901A // 深紫罗兰色
#define LCD_COLOR_DarkOrchid           0x9999 // 深兰花紫
#define LCD_COLOR_Indigo               0x4810 // 靛青
#define LCD_COLOR_BlueViolet           0x895C // 深紫罗兰的蓝色
#define LCD_COLOR_MediumPurple         0x939B // 适中的紫色
#define LCD_COLOR_MediumSlateBlue      0x7B5D // 适中的板岩暗蓝灰色
#define LCD_COLOR_SlateBlue            0x6AD9 // 板岩暗蓝灰色
#define LCD_COLOR_DarkSlateBlue        0x49F1 // 深岩暗蓝灰色
#define LCD_COLOR_Lavender             0xE73F // 熏衣草花的淡紫色
#define LCD_COLOR_GhostWhite           0xFFDF // 幽灵的白色
#define LCD_COLOR_Blue                 0x001F // 纯蓝
#define LCD_COLOR_MediumBlue           0x0019 // 适中的蓝色
#define LCD_COLOR_MidnightBlue         0x18CE // 午夜的蓝色
#define LCD_COLOR_DarkBlue             0x0011 // 深蓝色
#define LCD_COLOR_Navy                 0x0010 // 海军蓝
#define LCD_COLOR_RoyalBlue            0x435C // 皇家蓝
#define LCD_COLOR_CornflowerBlue       0x64BD // 矢车菊的蓝色
#define LCD_COLOR_LightSteelBlue       0xB63B // 淡钢蓝
#define LCD_COLOR_LightSlateGray       0x7453 // 浅石板灰
#define LCD_COLOR_SlateGray            0x7412 // 石板灰
#define LCD_COLOR_DoderBlue            0x1C9F // 道奇蓝
#define LCD_COLOR_AliceBlue            0xF7DF // 爱丽丝蓝
#define LCD_COLOR_SteelBlue            0x4416 // 钢蓝
#define LCD_COLOR_LightSkyBlue         0x867F // 淡蓝色
#define LCD_COLOR_SkyBlue              0x867D // 天蓝色
#define LCD_COLOR_DeepSkyBlue          0x05FF // 深天蓝
#define LCD_COLOR_LightBLue            0xAEDC // 淡蓝
#define LCD_COLOR_PowDerBlue           0xB71C // 火药蓝
#define LCD_COLOR_CadetBlue            0x5CF4 // 军校蓝
#define LCD_COLOR_Azure                0xF7FF // 蔚蓝色
#define LCD_COLOR_LightCyan            0xE7FF // 淡青色
#define LCD_COLOR_PaleTurquoise        0xAF7D // 苍白的绿宝石
#define LCD_COLOR_Cyan                 0x07FF // 青色
#define LCD_COLOR_Aqua                 0xD79C // 水绿色
#define LCD_COLOR_DarkTurquoise        0x067A // 深绿宝石
#define LCD_COLOR_DarkSlateGray        0x2A69 // 深石板灰
#define LCD_COLOR_DarkCyan             0x0451 // 深青色
#define LCD_COLOR_Teal                 0x0410 // 水鸭色
#define LCD_COLOR_MediumTurquoise      0x4E99 // 适中的绿宝石
#define LCD_COLOR_LightSeaGreen        0x2595 // 浅海洋绿
#define LCD_COLOR_Turquoise            0x471A // 绿宝石
#define LCD_COLOR_Auqamarin            0x7FF5 // 绿玉\碧绿色
#define LCD_COLOR_MediumAquamarine     0x07D3 // 适中的碧绿色
#define LCD_COLOR_MediumSpringGreen    0x07EF // 适中的春天的绿色
#define LCD_COLOR_MintCream            0xF7FF // 薄荷奶油
#define LCD_COLOR_SpringGreen          0x3D8E // 春天的绿色
#define LCD_COLOR_SeaGreen             0x2C4A // 海洋绿
#define LCD_COLOR_Honeydew             0xF7FE // 蜂蜜
#define LCD_COLOR_LightGreen           0x9772 // 淡绿色
#define LCD_COLOR_PaleGreen            0x9FD3 // 苍白的绿色
#define LCD_COLOR_DarkSeaGreen         0x8DF1 // 深海洋绿
#define LCD_COLOR_LimeGreen            0x3666 // 酸橙绿
#define LCD_COLOR_Lime                 0x07E0 // 酸橙色
#define LCD_COLOR_ForestGreen          0x2444 // 森林绿
#define LCD_COLOR_Green                0x0400 // 纯绿
#define LCD_COLOR_DarkGreen            0x0320 // 深绿色
#define LCD_COLOR_Chartreuse           0x7FE0 // 查特酒绿
#define LCD_COLOR_LawnGreen            0x7FE0 // 草坪绿
#define LCD_COLOR_GreenYellow          0xAFE5 // 绿黄色
#define LCD_COLOR_OliveDrab            0x5345 // 橄榄土褐色
#define LCD_COLOR_Beige                0xF7BB // 米色(浅褐色)
#define LCD_COLOR_LightGoldenrodYellow 0xFFDA // 浅秋麒麟黄
#define LCD_COLOR_Ivory                0xFFFE // 象牙
#define LCD_COLOR_LightYellow          0xFFFC // 浅黄色
#define LCD_COLOR_Yellow               0xFFE0 // 纯黄
#define LCD_COLOR_Olive                0x8400 // 橄榄
#define LCD_COLOR_DarkKhaki            0xBDAD // 深卡其布
#define LCD_COLOR_LemonChiffon         0xFFD9 // 柠檬薄纱
#define LCD_COLOR_PaleGodenrod         0xEF55 // 灰秋麒麟
#define LCD_COLOR_Khaki                0xF731 // 卡其布
#define LCD_COLOR_Gold                 0xFEA0 // 金
#define LCD_COLOR_Cornislk             0xFFDB // 玉米色
#define LCD_COLOR_GoldEnrod            0xDD24 // 秋麒麟
#define LCD_COLOR_FloralWhite          0xFFDE // 花的白色
#define LCD_COLOR_OldLace              0xFFBC // 老饰带
#define LCD_COLOR_Wheat                0xF6F6 // 小麦色
#define LCD_COLOR_Moccasin             0xFF36 // 鹿皮鞋
#define LCD_COLOR_Orange               0xFD20 // 橙色
#define LCD_COLOR_PapayaWhip           0xFF7A // 番木瓜
#define LCD_COLOR_BlanchedAlmond       0xFF59 // 漂白的杏仁
#define LCD_COLOR_NavajoWhite          0xFEF5 // 纳瓦霍白
#define LCD_COLOR_AntiqueWhite         0xFF5A // 古代的白色
#define LCD_COLOR_Tan                  0xD5B1 // 晒黑
#define LCD_COLOR_BrulyWood            0xDDD0 // 结实的树
#define LCD_COLOR_Bisque               0xFF38 //(浓汤)乳脂, 番茄等
#define LCD_COLOR_DarkOrange           0xFC60 // 深橙色
#define LCD_COLOR_Linen                0xFF9C // 亚麻布
#define LCD_COLOR_Peru                 0xCC27 // 秘鲁
#define LCD_COLOR_PeachPuff            0xFED7 // 桃色
#define LCD_COLOR_SandyBrown           0xF52C // 沙棕色
#define LCD_COLOR_Chocolate            0xD343 // 巧克力
#define LCD_COLOR_SaddleBrown          0x8A22 // 马鞍棕色
#define LCD_COLOR_SeaShell             0xFFBD // 海贝壳
#define LCD_COLOR_Sienna               0xA285 // 黄土赭色
#define LCD_COLOR_LightSalmon          0xFD0F // 浅鲜肉(鲑鱼) 色
#define LCD_COLOR_Coral                0xFBEA // 珊瑚
#define LCD_COLOR_OrangeRed            0xFA20 // 橙红色
#define LCD_COLOR_DarkSalmon           0xECAF // 深鲜肉(鲑鱼) 色
#define LCD_COLOR_Tomato               0xFB08 // 番茄
#define LCD_COLOR_MistyRose            0xFF3C // 薄雾玫瑰
#define LCD_COLOR_Salmon               0xFC0E // 鲜肉(鲑鱼) 色
#define LCD_COLOR_Snow                 0xFFDF // 雪
#define LCD_COLOR_LightCoral           0xF410 // 淡珊瑚色
#define LCD_COLOR_RosyBrown            0xBC71 // 玫瑰棕色
#define LCD_COLOR_IndianRed            0xCAEB // 印度红
#define LCD_COLOR_Red                  0xF800 // 纯红
#define LCD_COLOR_Brown                0xA145 // 棕色
#define LCD_COLOR_FireBrick            0xB104 // 耐火砖
#define LCD_COLOR_DarkRed              0x8800 // 深红色
#define LCD_COLOR_Maroon               0x8000 // 栗色
#define LCD_COLOR_White                0xFFFF // 纯白
#define LCD_COLOR_WhiteSmoke           0xF7BE // 白烟
#define LCD_COLOR_Gainsboro            0xDEFB // 亮灰色
#define LCD_COLOR_LightGrey            0xD69A // 浅灰色
#define LCD_COLOR_Silver               0xC618 // 银白色
#define LCD_COLOR_DarkGray             0xAD55 // 深灰色
#define LCD_COLOR_Gray                 0x8410 // 灰色
#define LCD_COLOR_DimGray              0x6B4D // 暗淡的灰色
#define LCD_COLOR_Black                0x0000 // 纯黑

//---------------------点阵字符数据--------------------
extern const uint8_t LCD_F8x16[][16]; // 8x16点阵字符数据

//---------------------图像数据--------------------
extern const uint8_t test_image[];
extern const uint8_t test_image2[];

#endif
