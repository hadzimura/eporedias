
// Pinout
#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
// ----------
#define PIN4        4
#define SWITCH_UP   5
#define SWITCH_DOWN 6
#define STATUS_LED  7
// --- 4PortRelay ---
#define RELAY1      8
#define RELAY2      9
#define RELAY3      10
#define RELAY4      11
// ----------
#define MOSFET1     12
#define PIN13       13
#define PIN14       14

//int overall_brightness = 16;
//int max_repeats = 10;

void setup() {

    // Serial Console Init
    Serial.begin(9600);

    // --- Hardware Switch ---
    pinMode(SWITCH_UP, INPUT);
    pinMode(SWITCH_DOWN, INPUT);

    // --- Status LED ---
    pinMode(STATUS_LED, OUTPUT);

    // --- 4PortRelay ---
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);

    // --- MOSFET1 ---
    pinMode(MOSFET1, OUTPUT);

}

void loop() {

    // Set the Runtime Mode:
    if (digitalRead(SWITCH_UP) == HIGH) {
        // Running the Garden of the Day Mode
        garden();
    } else if (digitalRead(SWITCH_DOWN) == HIGH) {
        // Running the Guardian of the Night Mode
        guardian();
    }
}

void garden() {

}

void guardian() {

}



void simple() {
  for (int i = 0; i < 256; i++) {
    Serial.println(i);
    analogWrite(INNER_STAR, i);
    delay(10);
  }

  analogWrite(OUTER_STAR, 255);
  delay(1000);
  analogWrite(INNER_STAR, 0);
  for (int i = 255; i > 0; i--) {
    Serial.println(i);
    analogWrite(OUTER_STAR, i);
    delay(10);
  }
  analogWrite(OUTER_STAR, 0);
}


void swapper (int cycles, int duration, int max_level) {

  for (int cycle = 0; cycle < cycles; cycle++) {
      analogWrite(INNER_STAR, max_level);
      analogWrite(OUTER_STAR, 0);
      delay(duration * 1000);
      analogWrite(INNER_STAR, 0);
      analogWrite(OUTER_STAR, max_level);
      delay(duration * 1000);
    }
  analogWrite(INNER_STAR, 0);
  analogWrite(OUTER_STAR, 0);
   
}

void crossfade (int duration, int max_level) {

  float stepper = duration / max_level / 2;

  int outer_level = max_level;
  for (int inner_level = 0; inner_level < max_level; inner_level++) {
    analogWrite(INNER_STAR, inner_level);
    analogWrite(OUTER_STAR, outer_level - inner_level);
    delay(stepper);
  }
  int inner_level = max_level;
  for (int outer_level = 0; outer_level < max_level; outer_level++) {
    analogWrite(INNER_STAR, inner_level - outer_level);
    analogWrite(OUTER_STAR, outer_level);
    delay(stepper);
  }

  analogWrite(INNER_STAR, 0);
  analogWrite(OUTER_STAR, 0);
}

void inner_star (int duration, int max_level) {
  analogWrite(INNER_STAR, max_level);
  analogWrite(OUTER_STAR, 0);
  delay(duration);
  analogWrite(INNER_STAR, 0);
}

void outer_star (int duration, int max_level) {
  analogWrite(INNER_STAR, 0);
  analogWrite(OUTER_STAR, max_level);
  delay(duration);
  analogWrite(OUTER_STAR, 0);
}

void blink_star (int duration, int max_level) {

  float stepper = duration / max_level / 4;

  
  analogWrite(INNER_STAR, max_level);
  delay(stepper);
  analogWrite(INNER_STAR, 0);
  delay(stepper);
  analogWrite(OUTER_STAR, max_level);
  delay(stepper);
  analogWrite(OUTER_STAR, 0);
  delay(stepper);
}



void all_stars (int duration, int max_level, boolean ramp_up, boolean ramp_down) {

  int stepper = duration / max_level;
  if (ramp_up == true) {
    
  }
  
  for (int level = 0; level < max_level; level++) {
    analogWrite(INNER_STAR, level);
    analogWrite(OUTER_STAR, level);
    delay(stepper);
  }
  analogWrite(INNER_STAR, 0);
  analogWrite(OUTER_STAR, 0);
}

void jingle_bells (int takt_seconds, int max_brightness) {

  int takt = takt_seconds * 1000;
  int brightness = max_brightness;
  int inter_takt_delay = takt * 100;
  int inter_verse_delay = takt * 200;

  // jin-gle bells
  inner_star(takt, brightness);
  delay(inter_takt_delay);
  inner_star(takt, brightness);
  delay(inter_takt_delay);
  inner_star(takt, brightness);
  delay(inter_verse_delay);

  // jin-gle bells
  outer_star(takt, brightness);
  delay(inter_takt_delay);
  outer_star(takt, brightness);
  delay(inter_takt_delay);
  outer_star(takt, brightness);
  delay(inter_verse_delay);

  // Jin-gle all the way
  inner_star(takt / 2, brightness);
  delay(inter_takt_delay / 2);
  inner_star(takt / 2, brightness);
  delay(inter_takt_delay / 2);
  outer_star(takt / 2, brightness);
  delay(inter_takt_delay / 2);
  outer_star(takt / 2, brightness);
  delay(inter_takt_delay / 2);
  crossfade(takt, brightness);
  delay(inter_verse_delay);

}

void nesem_vam_noviny (int takt_seconds, int max_brightness) {

  int takt = takt_seconds * 1000;
  int brightness = max_brightness;
  int inter_takt_delay = takt * 100;
  int inter_verse_delay = takt * 200;

  // Ne-sem-vam
  inner_star(takt, brightness);
  delay(inter_takt_delay);
  outer_star(takt, brightness);
  delay(inter_takt_delay);
  crossfade(takt, brightness);
  delay(inter_verse_delay);

  // No-vi-ny
  crossfade(takt, brightness);
  delay(inter_takt_delay);
  crossfade(takt, brightness);
  delay(inter_takt_delay);
  crossfade(takt, brightness);
  delay(inter_verse_delay);

  // Po-slou-chej
  outer_star(takt, brightness);
  delay(inter_takt_delay);
  outer_star(takt, brightness);
  delay(inter_takt_delay);
  outer_star(takt, brightness);
  delay(inter_verse_delay);

  // teeeee
  crossfade(takt * 3, brightness);
  delay(inter_verse_delay);
}


//long light_adjust(int targetValue) {
//
//    while (currentValue != targetValue) {
//
//      if (currentValue > targetValue) {
//        currentValue--;  
//      } else {
//          currentValue++;  
//      }
//      analogWrite(LIGHT, currentValue);  
//      delay(5);
//    }
//    return (millis() / 1000);
//}
