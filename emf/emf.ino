// EMF Detector for 7-Segment LED Display v1.0
//
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use w/ LED bargraph by Collin Cunningham - collin@makezine.com
// modified again by ComputerGeek for instructable & 7-segment display.

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

#define NUMREADINGS 15 // raise this number to increase data smoothing

int senseLimit = 50; // raise this number to decrease sensitivity (up to 1023 max)
int probePin = A3; // analog 3
int val = 0; // reading from probePin

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading

//CHANGE THIS TO affect the speed of the updates for numbers. Lower the number the faster it updates.
int updateTime = 100;

String printing;
int level;

void setup() {
  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0
    
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("EMF Level:");   
}

void loop() {
  val = analogRead(probePin);  // take a reading from the probe

  if(val >= 1){                // if the reading isn't zero, proceed
    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average

    Serial.println(average); // use output to aid in calibrating
    
    level = average / 61;
        
    lcd.setCursor(0,1);
    lcd.print(repeat('#', level)+repeat(' ', 16-level));
    
    delay(updateTime);
  }

}

String repeat(char symbol, int times){
  if (times == 0) return String("");
  String res = String(symbol);
  for(;res.length()<times;)
    res += symbol;
   return res;
}
