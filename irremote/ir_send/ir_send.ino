// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  13;    // LED connected to digital pin 13

const int frequency = 38; // KHz

// Timings in microseconds
const int writeTime = 3;
const int interval = (1000/frequency-2*writeTime)/2;
const int signalPeriod = 2*(interval+writeTime);

int signalOnOff[] = {32386	,
8936	,
4356	,
616	,
494	,
614	,
468	,
642	,
470	,
612	,
500	,
608	,
474	,
638	,
470	,
612	,
502	,
604	,
476	,
638	,
1584	,
616	,
1584	,
614	,
1586	,
636	,
1588	,
612	,
1588	,
612	,
1584	,
640	,
1586	,
614	,
1584	,
612	,
498	,
612	,
474	,
636	,
472	,
612	,
500	,
610	,
472	,
638	,
472	,
610	,
1588	,
638	,
472	,
614	,
1586	,
636	,
1588	,
612	,
1586	,
612	,
1586	,
638	,
1584	,
612	,
1588	,
612	,
498	,
610	,
1590	,
610	,
39208	,
8904	,
2156	,
618	
};

int signalRed[] = {16760, 8900,  
4400, 580,  
540, 560,  
520, 580,  
540, 540,  
580, 520,  
560, 540,  
580, 500,  
600, 520,  
560, 540,  
1680, 520,  
1680, 520,  
1680, 540,  
1700, 500,  
1680, 520,  
1680, 560,  
1680, 500,  
1700, 500,  
600, 520,  
560, 540,  
580, 500,  
1700, 540,  
1680, 520,  
560, 540,  
1700, 500,  
580, 520,  
1700, 520,  
1680, 520,  
1680, 540,  
560, 520,  
600, 500,  
1700, 500,  
600, 520,  
1680, 520,  
39300, 8820,  
2260, 500};

int signalWhite[] = {43036, 8900,  
4400, 560,  
560, 560,  
520, 580,  
540, 540,  
580, 520,  
560, 540,  
560, 520,  
600, 520,  
560, 540,  
1680, 520,  
1680, 520,  
1680, 540,  
1680, 520,  
1680, 520,  
1680, 540,  
1700, 500,  
1700, 500,  
600, 520,  
560, 540,  
1700, 500,  
580, 540,  
560, 520,  
600, 500,  
1700, 500,  
600, 520,  
1680, 520,  
1680, 540,  
580, 500,  
1700, 540,  
1680, 520,  
1680, 500,  
600, 520,  
1680, 520,  
39320, 8820,  
2260, 500};
 
 
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);
  
//  Serial.print("Signal count: ");
//  Serial.println(sizeof(signalOnOff)/(sizeof(int)*2));
//  Serial.print("interval: ");
//  Serial.println(interval);
//  Serial.print("signalPeriod: ");  
//  Serial.println(signalPeriod);  
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  sendSignal(signalOnOff, sizeof(signalOnOff)/(sizeof(int)*2));
//  delay(5*1000);
// 
//  sendSignal(signalRed, sizeof(signalRed)/(sizeof(int)*2));
//  delay(5*1000);
//  
//  sendSignal(signalWhite, sizeof(signalWhite)/(sizeof(int)*2));
//  delay(5*1000);
//
//  sendSignal(signalOnOff, sizeof(signalOnOff)/(sizeof(int)*2));
 
  delay(5*1000);
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(signalPeriod);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(signalPeriod);         // hang out for 10 microseconds
 
   microsecs -= interval;
  }
 
  sei();  // this turns them back on
}

void sendSignal(int usec[], int periods)
{
  for(int i=0;i<periods;i++)
  {    
    delayMicroseconds(usec[2*i]);
    pulseIR(usec[2*i+1]);
  }
}
