#include <TM1638.h>
// nastavení čísel pinů pro propojení s Arduinem
#define DATA 2
#define CLOCK 3
#define STROBE 4
// vytvoření instance panel z knihovny TM1638
TM1638 panel(DATA, CLOCK, STROBE);

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
}

void loop() {
  // vytvoření proměnné pro uložení stavu tlačítka
  // v čisté formě (panelTlac) a do rozsahu 1-8 (tlacitko)
  byte panelTlac = panel.getButtons();
  int tlacitko = 0;
  // vytvoření proměnné cas a uložení
  // aktuálního času od zapnutí Arduina
  // v sekundách
  long cas = millis() / 1000;
  // rozsvícení LED diody s příslušným tlačítkem
  // fungující pro více tlačítek najednou
  panel.setLEDs(((panelTlac & 0xF0) << 8) | (panelTlac & 0xF));
  
  // pro rozsvícení jednotlivých LED slouží tento příkaz a příklad:
  // setLED(0 pro vypnutí/1 pro zapnutí), číslo LED
  /// panel.setLED(1, 4); // zapnutí 4. LED diody
  // překlad čisté formy na rozsah 1-8
  switch (panelTlac) {
    case 1:
      tlacitko = 1;
      panel.setDisplayToHexNumber(0x10000000, 0);
      break;
    case 2:
      tlacitko = 2;
  }
}