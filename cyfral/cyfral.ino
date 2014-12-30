#define CELLS 200
volatile int pos = 0;
volatile unsigned long cells[CELLS];

void setup()
{                                                                            
  Serial.begin(9600);
  attachInterrupt(0, blink, FALLING);
  Serial.print("Started ");
  Serial.println(micros());  
}

void loop()
{
  delay(3000);
  for(int i=1;i<CELLS;i++){
    Serial.print(cells[i]-cells[i-1]);
    Serial.print("; ");
  }
  Serial.println(pos);
}

void blink()
{
  pos = (pos+1)%CELLS;
  cells[pos] = micros();
}
