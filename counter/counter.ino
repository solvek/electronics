// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int speakerPin = 9;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600);  
  pinMode(speakerPin, OUTPUT);
}

unsigned int last;
float distance;

void loop() {
//  delay(3000);
//  Serial.println("$data:1");
//  Serial.println(sonar.ping());
  
  while(sonar.ping() == 0){}
  
  if (pingConfirms(12, 3))
  {
    playTone(map(last, 700, 4700, 1000, 2000), 300);
    
    distance = last/US_ROUNDTRIP_CM;
  
    Serial.print("$data:");
    Serial.println(distance);
    
    while(sonar.ping() > 0){}
    delay(50);
  }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

boolean pingConfirms(int period, int times){
  for(int i=0;i<times;i++){
    delay(period);
    if ((last=sonar.ping()) == 0)
      return false;
  }
      
  return true;
}
