#include <Arduino.h>
#include <SPI.h>
#include <TM1638Anode.h>
#include <TM16xxDisplay.h>
#include <U8g2lib.h>

// -----------------------------------------

/* PINOUT */
#define RELE1  3
#define RELE2  4
#define LK_STB 7
#define LK_DIO 8
#define LK_CLK 9

/* Variables */
#define LK_DIGITS 8

// -----------------------------------------

/* Key&LED Module */
//TM1638Anode module1(25, 26, 27, true, 7); // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM1638Anode ledkey(25, 26, 27, true, 7);
TM16xxDisplay display_segment(&ledkey, LK_DIGITS);    // TM16xx object, 8 digits

/* OLED Display */
U8G2_SH1106_128X64_NONAME_1_HW_I2C display_oled(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// -----------------------------------------

void setup(void) {

  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  /* u8g2.begin() is required and will sent the setup/init sequence to the display */
  display_oled.begin();

  // test display
  display_segment.println("12.34.5.6");

}

int nCount=0;

/* draw something on the display with the `firstPage()`/`nextPage()` loop*/
void loop(void) {

  /* L&K Display */ 
  // delay(1000);
  //  ledkey_display.println((String)"Count:" + nCount);
  //  nCount++;

  /* Relays */
  // digitalWrite(RELE1, HIGH);  //relé1 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, HIGH);  //relé2 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE1, LOW);   //relé1 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, LOW);   //relé2 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání

  /* OLED display */
  display_oled.firstPage();
  do {
    display_oled.setFont(u8g2_font_ncenB14_tr);
    display_oled.drawStr(0,20,"Hello World!");
    for (int i = 0; i <= 60; i++) {
      display_oled.drawCircle(60, 30, i);
      delay(100);
    }

  } while ( display_oled.nextPage() );
  delay(1000);
}