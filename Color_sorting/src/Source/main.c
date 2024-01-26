#include "Color_sorting.h"

int main(void) {
  float colorTemp, lux;
  portConfig();
  I2C_Configuration();
  TCS34725_Init();
  configInterruptTIM2();
  Timer_Configuration();
  lcd_init();
  homeServo();

  while (1) {
    directServo();
    feedMaterial();
    TCS34725_ReadColor(&red, &green, &blue);

    /* 
      * Describle: caculate another color parameter
      * Using in special situations red, blue, green variable aren't enough
    uint16_t clear = (red + green + blue) / 3;
    colorTemp = 1856 * red - 1206 * green - 403 * blue + 32768;
    colorTemp /= 4096;
    lux = (0.136 * clear - 0.070 * clear * (red + green + blue) / 3) / 1.8432;*/

    // Sort object base on green, blue and another color
    sortColor();
    display();

    delayMs(1000);
  }
}


