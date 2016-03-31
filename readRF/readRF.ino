#include <RFduinoBLE.h>

struct Parser
{
  int maxSignalLength = 255;
  int upperThreshod;
};

typedef struct Parser Parser;

#define BUF_SIZE 100

#define STATUS_UNDEFINED -1
#define STATUS_IDLE 0
#define STATUS_HIGH 1
#define STATUS_LOW 2

#define HIGHT_THRESHOLD 500
#define LONG_PAUSE 5000

byte st = STATUS_UNDEFINED;

char buf[BUF_SIZE];
String str = String("");

long lastTime, curTime, duration;

int analog;
bool lastHigh, curHigh;

Parser defaultParser;

void setup() {
  Serial.begin(9600);
  
  RFduinoBLE.advertisementData = "Solvek";
  RFduinoBLE.deviceName = "Solvek RF reader";
  RFduinoBLE.begin();   
 

 Serial.println("Initialied."); 
 
//  readSignal(2, defaultParser);
}

void loop() {
  analog = analogRead(2);
  lastHigh = curHigh;
  curHigh = (analog > HIGHT_THRESHOLD);
  curTime = micros();
  
  if (st == STATUS_UNDEFINED){
    st = curHigh ? STATUS_HIGH : STATUS_LOW;
    lastTime = curTime;
    return;
  }
    
  duration = curTime - lastTime;
  
//  Serial.print("Signal: ");  
//  Serial.print(analog);
//  Serial.print(", duration: ");
//  Serial.print(duration); 
//  Serial.print(", status: ");
//  Serial.println(st); 
  
  if (lastHigh == curHigh){
    if (st != STATUS_IDLE && duration > LONG_PAUSE){
      st = STATUS_IDLE;
      outputCode();
    }
    return;
  }
  
  lastTime = curTime;
  
  if (st != STATUS_IDLE){
    str += (lastHigh ? "+" : "-");
    str += duration;
  }

  st = curHigh ? STATUS_HIGH : STATUS_LOW;
}

void outputCode(){
  if (str.length() == 0){
    Serial.println("No code");
    return;
  }
  
  Serial.print("New code: ");  
  Serial.println(str);
  
  str = String("");
  
//    str = String(signal);
//    str.toCharArray(buf, BUF_SIZE);
//    springf(buf  
//   RFduinoBLE.send("Test2", 5);

}

int readSignal(int analogPin, struct Parser p)
{
  Serial.print("max length: ");
  Serial.println(p.maxSignalLength);
  return 10;
}
