
struct LED {
    int col;
    int row;
};


struct LED coord(int day_number) {
  
  struct LED day;

  // Base numbers for calculations
  float row_definition = 20 / day_number;
  int col_definition = day_number;
  int row = 16;
  int col;

  // Print Base numbers  
  Serial.print("ROW def:");
  Serial.println(row_definition);
  Serial.print("COL def:");
  Serial.println(col_definition);

  if (day_number < 6) {
    row = 19;
    } else if (day_number < 11) {
    row = 18;
    } else if (day_number < 16) {
    row = 17;
    }
  // Calculate ROW number
//  if (row_definition >= 4 ) {
//    row = 19;
//  } else if (row_definition >= 2 ) {
//    row = 18;
//  } else if (row_definition >= 1.3333 ) {
//    row = 17;
//  }
  
  // Calculate COL number
  while (col_definition > 6) {
    col_definition = col_definition - 5;
  }
  col = 7 - col_definition;

  // Print Calculated numbers  
  Serial.print("ROW calc:");
  Serial.println(row);
  Serial.print("COL calc:");
  Serial.println(col);

  // Assign object attrs
  day.col = col;
  day.row = row;

  // return object
  return day;
}

void day_blink (int day, int blink_total_secs, float blinks_per_sec) {

  struct LED blinkie;
  blinkie = coord(day);

  // Value for blink cycle: microseconds / blinks per sec / on+off state
  int blink_delay = 1000 / blinks_per_sec / 2;
  Serial.print("BLINK DELAY:");
  Serial.println(blink_delay);
  Serial.print("BLINKS PER SEC:");
  Serial.println(blinks_per_sec);
  // Main cycle for total duration (seconds)

  for (int blink_time = 0; blink_time < blink_total_secs; blink_time++) {

    // Within main cycle do the 1 second loop
    for (int blink_second = 0; blink_second < blinks_per_sec; blink_second++) {
      // LED ON for ...
      Serial.print("> LED ON:");
      Serial.println(blinkie.row);
      digitalWrite(blinkie.row, HIGH);
      digitalWrite(blinkie.col, LOW);
      delay(blink_delay);
    
      // LED OFF for...
      Serial.println("> LED OFF");
      digitalWrite(blinkie.row, LOW);
      digitalWrite(blinkie.col, HIGH);
      delay(blink_delay);
    }    
    // Cycle duration: 2*bs
    // Every cycle ends with LED OFF
  }
}

void day_light (int day) {

  struct LED lightme;
  lightme = coord(day);

  digitalWrite(lightme.row, HIGH);
  digitalWrite(lightme.col, LOW);
}


//void light_col (int line_col, int duration_sec) {
//
//  for (int col = 0; col < sizeof(matrix_col); col++) {
//      digitalWrite(matrix_row[line_row], HIGH);
//      digitalWrite(matrix_col[col], LOW);    
//  }
//  delay(duration_sec * 1000);
//  digitalWrite(matrix_row[line_row], LOW);
//  
//}

//
//void full(int how_long_sec) {
//  // Blank the matrix (all off)
//  // take the col pins (i.e. the cathodes) high to ensure that
//  // the LEDS are off:
//
//  for (int thisRow = 19; thisRow > 15; thisRow--) {
//    for (int thisCol = 2; thisCol < 7; thisCol++) {
//      digitalWrite(thisRow, HIGH);
//      digitalWrite(thisCol, LOW);
//    }
//  }
//  delay(how_long_sec * 1000);
//  blank();
//}
//void lines(int cycles, int speed) {
//
//  for (int seq = 1; seq < cycles; seq++) {
//
//    // Go down
//    for (int thisRow = 19; thisRow > 15; thisRow--) {
//      for (int thisCol = 2; thisCol < 7; thisCol++) {
//        digitalWrite(thisRow, HIGH);
//        digitalWrite(thisCol, LOW);
//      }
//      delay(speed);
//      digitalWrite(thisRow, LOW);
//    }
//  // Go up
//    for (int thisRow = 17; thisRow < 20; thisRow++) {
//      for (int thisCol = 2; thisCol < 7; thisCol++) {
//        digitalWrite(thisRow, HIGH);
//        digitalWrite(thisCol, LOW);
//      }
//      if (thisRow != 19) {
//        delay(speed);
//      }
//      digitalWrite(thisRow, LOW);
//    } 
//  }
//}
