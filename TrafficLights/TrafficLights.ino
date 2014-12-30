#define TL1_RED 13
#define TL1_YELLOW 12
#define TL1_GREEN 11
#define BASE 100

void setup() {
  pinMode(TL1_RED, OUTPUT);
  pinMode(TL1_YELLOW, OUTPUT);
  pinMode(TL1_GREEN, OUTPUT);  
}

void loop() {
  digitalWrite(TL1_RED, HIGH);
  delay(50*BASE);

  digitalWrite(TL1_YELLOW, HIGH);
  delay(5*BASE);
  digitalWrite(TL1_RED, LOW);
  delay(15*BASE);
  digitalWrite(TL1_YELLOW, LOW);

  digitalWrite(TL1_GREEN, HIGH);
  delay(40*BASE);
  digitalWrite(TL1_GREEN, LOW);
  
  digitalWrite(TL1_YELLOW, HIGH);
  delay(25*BASE);
  digitalWrite(TL1_YELLOW, LOW);
  
}
