#include <RFduinoBLE.h>

#define BUF_SIZE 100

char buf[BUF_SIZE];
String str = String("");

#define MAX_SEGMENTS 1000

int segments[MAX_SEGMENTS];

int count;

void setup() {
  Serial.begin(9600);
  
  RFduinoBLE.advertisementData = "Solvek";
  RFduinoBLE.deviceName = "Solvek RF reader";
  RFduinoBLE.begin();   
 

 Serial.println("Initialied."); 
 
//  readSignal(2, defaultParser);
}

void loop() {
  count = readSignal(2, segments, MAX_SEGMENTS);
  
  if (count < 5) return;
  
  Serial.print("Detected ");
  Serial.print(count);
  Serial.println(" segments"); 
 
 outputCode(segments, count); 
}

void outputCode(int raw[], int s){
  for(int i=0;i<s;i++){
    Serial.print(i%2==0 ? "+" : "-");
    Serial.print(raw[i]);
  }
  Serial.println();
  
//  str = String("");
  
//    str = String(signal);
//    str.toCharArray(buf, BUF_SIZE);
//    springf(buf  
//   RFduinoBLE.send("Test2", 5);

}

#define HIGHT_THRESHOLD 100
#define MAX_READS 255
#define DELIMITER_DURATION 3000

int readSignal(int analogPin, int raw[], int buffSize)
{
  bool expectHigh = true;
  int counter, s;
  long startTime = micros(), endTime;
  
  for(int i=0;i<buffSize;i++){
    for(counter=0;counter<MAX_READS;counter++){
      s = analogRead(analogPin);
      if (expectHigh && s<HIGHT_THRESHOLD) break;
      if (!expectHigh && s>=HIGHT_THRESHOLD) break;
    }
    
    if (counter >= MAX_READS) return i;
    
    endTime = micros();
    raw[i] = (int)(endTime - startTime);
    startTime = endTime;
    
    expectHigh = !expectHigh;
  }
  
  return buffSize;
}
