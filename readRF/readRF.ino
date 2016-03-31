#include <RFduinoBLE.h>

#define MAX_SEGMENTS 300
int segments[MAX_SEGMENTS];
int count;

void setup() {
  Serial.begin(9600);
  
  RFduinoBLE.advertisementData = "Solvek";
  RFduinoBLE.deviceName = "Solvek RF reader";
  RFduinoBLE.begin();   
 

 Serial.println("Initialied.");  
}

void loop() {
  count = readSignal(2, segments, MAX_SEGMENTS);
  
  if (count < 5) return;
  
  Serial.print("Detected ");
  Serial.print(count);
  Serial.println(" segments"); 
 
 outputCode(segments, count); 
 
 RFduinoBLE.send("Detected", 8);
 outputCodeToPhone(segments, count);
}

void outputCode(int raw[], int s){
  for(int i=0;i<s;i++){
    Serial.print(i%2==0 ? "+" : "-");
    Serial.print(raw[i]);
  }
  Serial.println();
}

#define BUF_SIZE 20
char buf[BUF_SIZE];

#define THRESHOLD_DELIMITER 5000
#define THRESHOLD_ONE 500

void outputCodeToPhone(int raw[], int s)
{
  String str;
  int pairs = s/2, pos, v,i;
  
  while(pos<pairs){
    for(;pos<pairs && raw[2*pos+1]<THRESHOLD_DELIMITER;pos++);
    v = 0;
    for(i=0;i<24;i++){
      pos++;
      if (pos>=pairs) return;
      v *= 2;
      if (raw[2*pos]>THRESHOLD_ONE) v++;
    }
    
    str = String(v, HEX);
    i = str.length()+1;
    str.toCharArray(buf, i);
    RFduinoBLE.send(buf, i);
    
    Serial.print("Decoded: ");
    Serial.println(v, HEX);
  }
}

#define HIGHT_THRESHOLD 100
#define DELIMITER_DURATION 15000

int readSignal(int analogPin, int raw[], int buffSize)
{
  bool expectHigh = true;
  int s;
  long startTime = micros(), endTime, duration;
  
  for(int i=0;i<buffSize;i++){
    do{
      s = analogRead(analogPin);
      endTime = micros();
      duration = endTime - startTime;
      if (duration > DELIMITER_DURATION) return i;
    } while((expectHigh && s>=HIGHT_THRESHOLD)
      || (!expectHigh && s<HIGHT_THRESHOLD));
    
    raw[i] = (int)duration;
    startTime = endTime;
    
    expectHigh = !expectHigh;
  }
  
  return buffSize;
}
