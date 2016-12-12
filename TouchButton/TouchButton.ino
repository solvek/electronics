#define PIN_TOUCH 8
#define PIN_LED 13

int val;

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_TOUCH, INPUT);
  pinMode(PIN_LED, OUTPUT);

  for(int i=0;i<5;i++){
   digitalWrite(PIN_LED, HIGH);
   delay(500);
   digitalWrite(PIN_LED, LOW);
   delay(200);   
  }
}

void loop() {
  val = digitalRead(PIN_TOUCH);
  Serial.println(val);
  digitalWrite(PIN_LED, val);
  delay(100);
}
