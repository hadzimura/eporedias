#define MOVE  2
#define TOUCH 3
#define CUBE  8
#define LIGHT 9

// Typically global variables are used to pass data between an ISR and the main program. 
// To make sure variables shared between an ISR and the main program are updated correctly, 
// declare them as volatile.
// See: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
// More on interrupts: http://gammon.com.au/interrupts

volatile boolean touchState = false;
volatile long moveState     = false;

boolean cubeState    = false; 
boolean lightState   = false;
boolean dimState     = false;
long    runTimer     = 0;
int     elapsed      = 0;
int     powerDownSec = 20;
int     currentValue = 0;

int stepUp = 0;
int stepDown = 255;
int adjustState = 0;
int adjustUp = 0;
int adjustDown = 0;

long lastMove = 1;
long currentMove = 0;

volatile int touchLength = 0;
volatile int touchStart = 0;


void setup() {
  Serial.begin(9600);
  pinMode(MOVE, INPUT);
  pinMode(TOUCH, INPUT);
  pinMode(CUBE, OUTPUT);
  pinMode(LIGHT, OUTPUT);
//  attachInterrupt(0, feel_me, RISING);
  attachInterrupt(digitalPinToInterrupt(MOVE), feel_me, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TOUCH), touch_me, CHANGE);
}
 
void loop() {
 
  // When the Touch Button is pressed:
  if (touchState == true) {
    
    if (cubeState == false) {
      
      // Power Up the Cube
      cube_adjust(255);
      cubeState = true;
      dimState == false;
      
      // Power Up the Light-strip
      runTimer = light_adjust(255);
      
    } else {
      
      // Power Down the Light-strip
      cubeState = false;
      light_adjust(0);
      
      // Power Down the Cube
      cube_adjust(0);
      
    }
    // Wait a bit
    delay(500);

    // Clear state of the Touch Button
    touchState = false;
  }

  if (moveState == true) {
    if (millis() / 1000 - lastMove > 10) {
      lastMove = millis() / 1000;
      Serial.print("Move State: ");
      Serial.println(lastMove);
    }
    moveState == false;
  }


  // When the Light-strip is running:
  if (cubeState == true) {

    if (elapsed > powerDownSec) {
      
      // Automatic Power Down if Timer reached
      cubeState = false;
      light_adjust(0);
      elapsed = 0;
      dimState = false;
      
    } else if (elapsed > (powerDownSec / 2) and dimState == false) {
      
      // Test if we are halfway there
      light_adjust(32);
      dimState = true;
      
    } else {
      
      // Count the time only
      elapsed = (millis() / 1000) - runTimer;
      
    }
  }
}

// Move Sensor interrupt
void feel_me() {
  moveState = true;
}

// Touch Button interrupt
void touch_me() {
  touchState = true;
}

long cube_adjust(int targetValue) {
  // Power Down The Cube
  Serial.println("CUBE: targetValue");
  Serial.println(targetValue);
  if (targetValue == 0 or targetValue == 255) {
    Serial.println("case");
    switch (targetValue) {
      case 0:
        digitalWrite(CUBE, LOW);
        break;
      case 255:
        digitalWrite(CUBE, HIGH);
        break;
      default:
        Serial.println("ddd");
        break;
    }    
  } else {
    Serial.println("CUBE: targetValue adjusted");
  }
  return (millis() / 1000);
}

long light_adjust(int targetValue) {

    while (currentValue != targetValue) {

      if (currentValue > targetValue) {
        currentValue--;  
      } else {
          currentValue++;  
      }
      analogWrite(LIGHT, currentValue);  
      delay(5);
    }
    return (millis() / 1000);
}
