#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

#define RELE1 3
#define RELE2 4

/* Constructor for OLED Display */
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  /* u8g2.begin() is required and will sent the setup/init sequence to the display */
  u8g2.begin();
}

/* draw something on the display with the `firstPage()`/`nextPage()` loop*/
void loop(void) {


  // digitalWrite(RELE1, HIGH);  //relé1 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, HIGH);  //relé2 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE1, LOW);   //relé1 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, LOW);   //relé2 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání


  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,20,"Hello World!");
    for (int i = 0; i <= 60; i++) {
      u8g2.drawCircle(60, 30, i);
      delay(100);
    }

  } while ( u8g2.nextPage() );
  delay(1000);
}