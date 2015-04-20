// This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  13;    // LED connected to digital pin 13
 
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  SendChannelUpCode();
 
  delay(10000);  // wait twenty seconds (20 seconds * 1000 milliseconds)
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void SendChannelUpCode() {
  // Sends a command
  
  delayMicroseconds(33632);
  pulseIR(8920);
  
  delayMicroseconds(4400);
  pulseIR(580);
  
  delayMicroseconds(540);
  pulseIR(560);
  
  delayMicroseconds(520);
  pulseIR(580);
  
  delayMicroseconds(540);
  pulseIR(540);
  
  delayMicroseconds(580);
  pulseIR(520);
  
  delayMicroseconds(560);
  pulseIR(560);
  
  delayMicroseconds(540);
  pulseIR(540);
  
  delayMicroseconds(580);
  pulseIR(520);
  
  delayMicroseconds(560);
  pulseIR(540);
  
  delayMicroseconds(1700);
  pulseIR(500);
  
  delayMicroseconds(1680);
  pulseIR(520);
  
  delayMicroseconds(1680);
  pulseIR(540);
  
  delayMicroseconds(1700);
  pulseIR(500);
  
  delayMicroseconds(1700);
  pulseIR(500);
  
  delayMicroseconds(1700);
  pulseIR(520);
  
  delayMicroseconds(1700);
  pulseIR(500);
  
  delayMicroseconds(1700);
  pulseIR(500);
  
  delayMicroseconds(600);
  pulseIR(520);
  
  delayMicroseconds(560);
  pulseIR(540);
  
  delayMicroseconds(580);
  pulseIR(520);
  
  delayMicroseconds(580);
  pulseIR(520);
  
  delayMicroseconds(580);
  pulseIR(540);
  
  delayMicroseconds(560);
  pulseIR(520);
  
  delayMicroseconds(1680);
  pulseIR(540);
  
  delayMicroseconds(560);
  pulseIR(520);
  
  delayMicroseconds(1700);
  pulseIR(540);
  
  delayMicroseconds(1680);
  pulseIR(520);
  
  delayMicroseconds(1680);
  pulseIR(500);
  
  delayMicroseconds(1700);
  pulseIR(540);
  
  delayMicroseconds(1680);
  pulseIR(520);
  
  delayMicroseconds(1680);
  pulseIR(520);
  
  delayMicroseconds(580);
  pulseIR(520);
  
  delayMicroseconds(1680);
  pulseIR(520);
}
