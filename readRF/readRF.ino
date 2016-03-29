void setup() {
  Serial.begin(9600);
}

void loop() {
  int signal = analogRead(2);
  if (signal > 6){
    Serial.println(signal);
  }
}
