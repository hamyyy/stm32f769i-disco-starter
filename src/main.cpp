// #include "mbed.h"
// #include "Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.h"
// #include "stlogo.h"

// #define USE_LCD_HDMI

// uint32_t Xsize = 0;
// uint32_t Ysize = 0;

// /**
//  * @brief  Show LCD Features
//  * @param  feature : feature index
//  * @retval None
//  */
// static void LCD_Show_Feature(uint8_t feature)
// {
//   Point Points[] = {{20, 150}, {80, 150}, {80, 200}};
//   Point Points2[3];

//   Points2[0].X = Xsize - 80;
//   Points2[0].Y = 150;
//   Points2[1].X = Xsize - 20;
//   Points2[1].Y = 150;
//   Points2[2].X = Xsize - 20;
//   Points2[2].Y = 200;

//   BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
//   BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//   BSP_LCD_FillRect(12, 92, Xsize - 24, Ysize - 104);
//   BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

//   switch (feature) {
//     case 0:
//       /* Text Feature */

//       BSP_LCD_DisplayStringAt(14, 100, (uint8_t *)"Left aligned Text", LEFT_MODE);
//       BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"Center aligned Text", CENTER_MODE);
//       BSP_LCD_DisplayStringAt(14, 130, (uint8_t *)"Right aligned Text", RIGHT_MODE);
//       BSP_LCD_SetFont(&Font24);
//       BSP_LCD_DisplayStringAt(14, 180, (uint8_t *)"Font24", LEFT_MODE);
//       BSP_LCD_SetFont(&Font20);
//       BSP_LCD_DisplayStringAt(Xsize / 2 - 20, 180, (uint8_t *)"Font20", LEFT_MODE);
//       BSP_LCD_SetFont(&Font16);
//       BSP_LCD_DisplayStringAt(Xsize - 80, 184, (uint8_t *)"Font16", LEFT_MODE);
//       break;

//     case 1:

//       /* Draw misc. Shapes */
//       BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//       BSP_LCD_DrawRect(20, 100, 60, 40);
//       BSP_LCD_FillRect(100, 100, 60, 40);

//       BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
//       BSP_LCD_DrawCircle(Xsize - 120, 120, 20);
//       BSP_LCD_FillCircle(Xsize - 40, 120, 20);

//       BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
//       BSP_LCD_DrawPolygon(Points, 3);

//       BSP_LCD_SetTextColor(LCD_COLOR_RED);
//       BSP_LCD_DrawEllipse(130, 170, 30, 20);
//       BSP_LCD_FillEllipse(200, 170, 30, 20);

//       BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
//       BSP_LCD_DrawHLine(20, Ysize - 30, Xsize / 5);
//       BSP_LCD_DrawLine(100, Ysize - 20, 230, Ysize - 50);
//       BSP_LCD_DrawLine(100, Ysize - 50, 230, Ysize - 20);

//       BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
//       BSP_LCD_FillPolygon(Points2, 3);
//       break;

//     case 2:
//       /* Draw Bitmap */
//       BSP_LCD_DrawBitmap(20, 100, (uint8_t *)stlogo);
//       HAL_Delay(500);

//       BSP_LCD_DrawBitmap(Xsize / 2 - 40, 100, (uint8_t *)stlogo);
//       HAL_Delay(500);

//       BSP_LCD_DrawBitmap(Xsize - 100, 100, (uint8_t *)stlogo);
//       HAL_Delay(500);

//       BSP_LCD_DrawBitmap(20, Ysize - 80, (uint8_t *)stlogo);
//       HAL_Delay(500);

//       BSP_LCD_DrawBitmap(Xsize / 2 - 40, Ysize - 80, (uint8_t *)stlogo);
//       HAL_Delay(500);

//       BSP_LCD_DrawBitmap(Xsize - 100, Ysize - 80, (uint8_t *)stlogo);
//       HAL_Delay(500);
//       break;
//   }
// }

// int main()
// {
//   uint8_t LCD_Feature = 0;

//   BSP_LCD_Init();
//   // BSP_LCD_InitEx(LCD_ORIENTATION_PORTRAIT);
//   BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
//   BSP_LCD_SelectLayer(0);

//   Xsize = BSP_LCD_GetXSize();
//   Ysize = BSP_LCD_GetYSize();

//   BSP_LCD_Clear(LCD_COLOR_WHITE);
//   BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//   BSP_LCD_FillRect(0, 0, Xsize, 80);
//   BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//   BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
//   BSP_LCD_SetFont(&Font24);
//   BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"MBED LCD EXAMPLE", CENTER_MODE);
//   BSP_LCD_SetFont(&Font12);
//   BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"DISCOVERY STM32F769NI", CENTER_MODE);

//   BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
//   BSP_LCD_DrawRect(10, 90, Xsize - 20, Ysize - 100);
//   BSP_LCD_DrawRect(11, 91, Xsize - 22, Ysize - 102);

//   HAL_Delay(1000);

//   while (1) {
//     LCD_Show_Feature(LCD_Feature);
//     HAL_Delay(3000);

//     LCD_Feature++;
//     if (LCD_Feature == 3) {
//       LCD_Feature = 0;
//     }
//   }
// }

#include "mbed.h"
#include "Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery.h"
#include "Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_ts.h"
#include "Drivers/BSP/STM32F769I-Discovery/stm32f769i_discovery_lcd.h"

TS_StateTypeDef TS_State = {0};

static BufferedSerial pc(USBTX, USBRX, 115200);

int main()
{
  uint16_t x1, y1;

  printf("\n\n TOUCHSCREEN EXAMPLE FOR DISCO-F769NI START:\n");

  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(0);

  /* Touchscreen initialization */
  if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
    printf("BSP_TS_Init error\n");
  }

  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set Touchscreen Demo1 description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 40);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"Touchscreen basic example", CENTER_MODE);

  while (1) {
    BSP_TS_GetState(&TS_State);
    if (TS_State.touchDetected) {
      /* One or dual touch have been detected          */

      /* Get X and Y position of the first touch post calibrated */
      x1 = TS_State.touchX[0];
      y1 = TS_State.touchY[0];
      y1 = (y1 < 20) ? 20 : (y1 > BSP_LCD_GetYSize()) ? BSP_LCD_GetYSize() : y1;
      x1 = (x1 < 0) ? 0 : (x1 > BSP_LCD_GetXSize()) ? BSP_LCD_GetXSize() : x1;

      printf("Touch Detected x=%d y=%d\n", x1, y1);

      BSP_LCD_SetTextColor(LCD_COLOR_RED);
      BSP_LCD_FillCircle(x1, y1, 20);

      HAL_Delay(1);
    }
  }
}