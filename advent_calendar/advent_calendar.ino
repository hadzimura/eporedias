#include "matrix.h"

// 2-dimensional array of row pin numbers:
const int matrix_row[4] = { 16, 17, 18, 19 };

// 2-dimensional array of column pin numbers:
const int matrix_col[5] = { 2, 3, 4, 5, 6 };

const int buttonPin = 8;     // the number of the pushbutton pin
int buttonState = 0;  
int today = 17;


void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  
  for (int thisPin = 0; thisPin < 5; thisPin++) {
    // initialize the output pins:
    pinMode(matrix_col[thisPin], OUTPUT);
    pinMode(matrix_row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(matrix_col[thisPin], HIGH);
  }

  stripes(2, 1);
}

void loop() {

//  buttonState = digitalRead(buttonPin);
//  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//  if (buttonState == HIGH) {
//
//    config_mode();
//    
//    int exit_timer = 0;
//    unsigned long tick = millis();
//
//    // after 5 seconds exit the configuration
//    while (exit_timer < 5000) {
//      buttonState = digitalRead(buttonPin);
//      exit_timer = millis() - tick;
//      if (buttonState == HIGH) {
//        today = today + 1;
//        delay(100);
//        tick = 0;  
//      }
//      tick = millis();
//      // Throttle a bit
//      delay(100);
//   }
//   config_mode();
//  }

  // Animate and shine
  advent(today, 300);
  // Do some X-mass blinkings
  random_lights(40);
}

void advent (int today, int today_time_sec) {
  
  // Traverse the days from December 1-st until yesterday
  for (int day_gone = 1; day_gone < today; day_gone++) {
    // send: day number, total blink time (secs), blinks per second
    day_blink(day_gone, 1, 3);    
  }

  // The loop above ended yesterday
  day_blink(today, today_time_sec, 0.7);
  
}

void random_lights (int duration_secs) {
  
    for (int cycles=1; cycles < duration_secs; cycles++) {
      int some_day = random(1, 21);
      day_blink(random(1, 21), 1, 4);        
    }  

}

void stripes(int total_cycles, int cycle_duration) {
  
  // cycle = down and up
  int passthrough = 0;
  int startrow = 3;
  
  for (int seq = 0; seq < total_cycles; seq++) {

    // do not double-light the first row if running more than once
    if (passthrough != 0) {
      startrow = 2;
    }
    
    // Go down
    for (int rowUp = startrow; rowUp > 0; rowUp--) {
      Serial.println("* ROW DOWN");
      light_row(rowUp, 0.3);
    }

    // Go up
    for (int rowDown = 0; rowDown < 3; rowDown++) {
      Serial.println("* ROW UP");
      light_row(rowDown, 0.3);
    }
  }

  for (int thisPin = 0; thisPin < 5; thisPin++) {
    digitalWrite(matrix_col[thisPin], HIGH);
  }
  
}

void light_row (int line_row, float duration_sec) {

  for (int col = 0; col < sizeof(matrix_col); col++) {
      Serial.print("** LIGHT ROW (matrix_row[line_row]) === ");
      Serial.println(matrix_row[line_row]);
      digitalWrite(matrix_row[line_row], HIGH);
      digitalWrite(matrix_col[col], LOW);    
  }
  delay(duration_sec * 1000);
  for (int col = 0; col < sizeof(matrix_col); col++) {
    digitalWrite(matrix_col[col], LOW);
  }
  
}

void all_lights (boolean set_state) {
  // To lighgt or blank the matrix (all LEDs)
  // To turn off diode: take the COL pins (i.e. the cathodes) HIGH
  // Use the defined arrays
  for (int row = 0; row < sizeof(matrix_row); row++) {
    for (int col = 0; col < sizeof(matrix_col); col++) {

      if (set_state == true) {
        // True: turn all on
        digitalWrite(matrix_row[row], HIGH);
        digitalWrite(matrix_col[col], LOW);
      } else {
        // False: turn all on
        digitalWrite(matrix_row[row], LOW);
        digitalWrite(matrix_col[col], HIGH);
        
      }
    }
  }
}

void config_mode () {
  // Enter/exit the config mode (3x blink all)
  for (int signal = 0; signal < 3; signal++) {
      all_lights(true);
      delay(250);
      all_lights(false);
      delay(250);
  }
}
