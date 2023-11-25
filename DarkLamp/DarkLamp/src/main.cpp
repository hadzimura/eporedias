#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
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

#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

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

display_oled.begin();

  // test display
  display_segment.println("12.34.5.6");  
  /* u8g2.begin() is required and will sent the setup/init sequence to the display */
  u8g2.begin();


Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;


}

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


// Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }  
}