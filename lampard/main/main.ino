#include "U8glib.h"

#define xxx 1
#define xxx 2
#define RELE1_PIN 3
#define RELE2_PIN 4
#define xxx 5
#define xxx 6
#define xxx 7
#define xxx 8
#define xxx 9
#define xxx 10
#define xxx 11
#define xxx 12
#define xxx 13

// inicializace OLED displeje z knihovny U8glib
U8GLIB_SSD1306_128X64 mujOled(U8G_I2C_OPT_NONE);

// proměnná pro uchování času poslední obnovy displeje
long int prepis = 0;


void setup() {
  pinMode(RELE1_PIN, OUTPUT);
  pinMode(RELE2_PIN, OUTPUT);
  // pro otočení displeje o 180 stupňů
  // stačí odkomentovat řádek níže
  // mujOled.setRot180();
}

void loop() {

  // digitalWrite(RELE1_PIN, HIGH);  //relé1 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, HIGH);  //relé2 rozepnuto (záleží také na typu)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE1_PIN, LOW);   //relé1 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání
  // digitalWrite(RELE2_PIN, LOW);   //relé2 sepnuto (záleží také na typu relé)
  // delay(1000);                    //1 s čekání

  // porovnání uloženého a aktuálního času
  // při rozdílu větším než 100 ms se provede
  // obnovení displeje, čas můžeme nastavit dle potřeby
  if (millis()-prepis > 100) {
    // následující skupina příkazů
    // obnoví obsah OLED displeje
    mujOled.firstPage();
    do {
      // funkce vykresli vykreslí žádaný obsah
      vykresli();
    } while( mujOled.nextPage() );
    // uložení posledního času obnovení
    prepis = millis();
  }
  
  // zde je místo pro další příkazy pro Arduino
  
  // volitelná pauza 10 ms pro demonstraci
  // vykonání dalších příkazů
  delay(10);
}
// funkce vykresli pro nastavení výpisu informací na OLED

void vykresli(void) {
  // nastavení písma, toto písmo umožní vypsat
  // přibližně 15x4 znaků
  mujOled.setFont(u8g_font_unifont);
  // nastavení pozice výpisu v pixelech
  // souřadnice jsou ve tvaru x, y
  // souřadnice 0, 0 je v levém horní rohu
  // OLED displeje, maximum je 128, 64
  mujOled.setPrintPos(0, 10);
  // výpis textu na zadanou souřadnici
  mujOled.print("Arduino navody");
  mujOled.setPrintPos(0, 25);
  mujOled.print("dratek.cz");
  mujOled.setPrintPos(0, 40);
  mujOled.print("Cas od zapnuti:");
  mujOled.setPrintPos(40, 55);
  mujOled.print(millis()/1000);
  mujOled.print(" vterin");

}