// Teploměr a vlhkoměr DHT11/22
// připojení knihovny DHT
#include "DHT.h"
// nastavení čísla pinu s připojeným DHT senzorem
#define pinDHT 52
// odkomentování správného typu čidla
#define typDHT11 DHT11 // DHT 11
//#define typDHT22 DHT22 // DHT 22 (AM2302)
// inicializace DHT senzoru s nastaveným pinem a typem senzoru
DHT mojeDHT(pinDHT, typDHT11);
void setup() {
// komunikace přes sériovou linku rychlostí 9600 baud
Serial.begin(9600);
// zapnutí komunikace s teploměrem DHT
mojeDHT.begin();
pinMode(pinDHT, INPUT_PULLUP);
}
void loop() {
// pomocí funkcí readTemperature a readHumidity načteme
// do proměnných tep a vlh informace o teplotě a vlhkosti,
// čtení trvá cca 250 ms
float tep = mojeDHT.readTemperature();
float vlh = mojeDHT.readHumidity();
// kontrola, jestli jsou načtené hodnoty čísla pomocí funkce isnan