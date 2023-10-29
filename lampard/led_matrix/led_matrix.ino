// LED matice s MAX7219

// připojení potřebné knihovny
#include "LedControl.h"
// nastavení propojovacích pinů
#define DIN 10
#define CS  11
#define CLK 12
// tato proměnná údává počet matic,
// počítání začíná od nuly
#define mojeMat 0
// inicializace LED matice z knihovny
LedControl ledMat=LedControl(DIN, CLK, CS, mojeMat);
// proměnná typu pole, 1 označují rozsvícené LED
byte pismenoA[8]={ B00000000,
                   B00011000,
                   B00100100,
                   B00100100,
                   B00111100,
                   B00100100,
                   B00100100,
                   B00000000};

void setup() {
  // probuzení matice pro zahájení komunikace
  ledMat.shutdown(mojeMat,false);
  // nastavení LED matice na střední svítivost (0-15)
  ledMat.setIntensity(mojeMat,7);
  // vypnutí všech LED diod na matici
  ledMat.clearDisplay(mojeMat);
}

void loop() {
  // vykreslení znaku z proměnné
  for(int i=0; i<8; i++) {
    ledMat.setRow(mojeMat,i,pismenoA[i]);
  }
  delay(1000);
  // vypnutí všech LED na matici
  ledMat.clearDisplay(mojeMat);
  // vykreslení LED diod v daném řádku, zde čtvrtý řádek
  // (řádky jsou číslovány od 0 do 7)
  ledMat.setRow(mojeMat,3,B10101010);
  delay(1000);
  // vykreslení LED diod v daném sloupci, zde šestý sloupec
  // (sloupce jsou číslovány od 0 do 7)
  ledMat.setColumn(mojeMat,5,B10111010);
  delay(1000);
  // vykreslení jedné zvolené LED diody, zde krajní dioda [8,8]
  ledMat.setLed(mojeMat,7,7,true);
  delay(1000);
  // ukázka změny intenzity svícení v celém rozsahu 0 až 15
  for(int i=0; i<16; i++) {
    ledMat.setIntensity(mojeMat,i);
    delay(200);
  }
  // nastavení intenzity na střední svit
  ledMat.setIntensity(mojeMat,7);
  // vypnutí všech LED na matici
  ledMat.clearDisplay(mojeMat);
}