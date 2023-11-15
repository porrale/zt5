int corrienteHiLo = 4;  // corriente alta y baja

void setup() {
  // put your setup code here, to run once:
  pinMode(corrienteHiLo, OUTPUT);
}

void loop() {
  digitalWrite(corrienteHiLo, HIGH);  // 
  delay(1000);                      // 
  digitalWrite(corrienteHiLo, LOW);   // 
  delay(1000);                      // 
}