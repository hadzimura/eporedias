#define INNER_STAR 10
#define OUTER_STAR 9

int overall_brightness = 128;
int max_repeats = 10;


void setup() {
  Serial.begin(9600);
  pinMode(INNER_STAR, OUTPUT);
  pinMode(OUTER_STAR, OUTPUT);
  analogWrite(INNER_STAR, 0);
  analogWrite(OUTER_STAR, 0);
}

void loop() {

// for (int repeats = 0; repeats < max_repeats; repeats++) {
  
    nesem_vam_noviny(1, overall_brightness);
    delay(2000);
    jingle_bells(1, overall_brightness);
    delay(2000);
//    
//    nesem_vam_noviny(10, overall_brightness);
//    delay(2000);
//    swapper(2, 20, overall_brightness);
//    delay(2000);
//    nesem_vam_noviny(60, overall_brightness);
//    delay(2000);
    
    
  // }

  // 5 hours
  // delay(18000000);
  
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
  int inter_takt_delay = takt_seconds * 100;
  int inter_verse_delay = takt_seconds * 200;

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
  int inter_takt_delay = takt_seconds * 100;
  int inter_verse_delay = takt_seconds * 200;

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
