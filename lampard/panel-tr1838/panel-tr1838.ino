// Ovládací panel s TM1638

// připojení knihovny
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
  long cas = millis()/1000;
  // rozsvícení LED diody s příslušným tlačítkem
  // fungující pro více tlačítek najednou
  panel.setLEDs(((panelTlac & 0xF0) << 8) | (panelTlac & 0xF));
  // pro rozsvícení jednotlivých LED slouží tento příkaz a příklad:
  // setLED(0 pro vypnutí/1 pro zapnutí), číslo LED 
  /// panel.setLED(1, 4); // zapnutí 4. LED diody

  // překlad čisté formy na rozsah 1-8
  switch(panelTlac) {
    case 1:
      tlacitko = 1;
      break;
    case 2:
      tlacitko = 2;
      break;
     case 4:
      tlacitko = 3;
      break;
    case 8:
      tlacitko = 4;
      break;
     case 16:
      tlacitko = 5;
      break;
    case 32:
      tlacitko = 6;
      break;
     case 64:
      tlacitko = 7;
      break;
    case 128:
      tlacitko = 8;
      break;
    default:
      tlacitko = 0;
  }
  // v případě, že bylo stisknuto tlačítko,
  // vypiš jeho číslo po sériové lince
  // a na displej vypiš ukázku znaků
  if (tlacitko > 0) {
    Serial.print("Stisk tlacitka: ");
    Serial.println(tlacitko);
    // výpis ukázky znaků v hex formátu,
    // 1 znamená tečku v prvním znaku
    panel.setDisplayToHexNumber(0x1234ABCD, 1);
  }
  // pokud nebylo stisknuto žádné tlačítko,
  // vypiš na displej aktuální čas od spuštění
  else {
    // výpis čísla ve tvaru: číslo, tečka u druhého znaku, 
    //  0 pro výpis bez nul/ 1 výpis s nulami
    panel.setDisplayToDecNumber(cas, 2, 0);
  }
  // pauza pro přehlednější výpis
  delay(500);
}