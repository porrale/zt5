#include <SPI.h>

int cal = 27;
int amplitudCorrienteCS = 17;  // AmplitudI CS
int crucePorCero = 16;         // cruce por cero  CS
int corrienteHiLo = 4;         // corriente alta y baja
int value = 0;

void setup() {
  SPI.begin();
  SPI.setFrequency(1000);
  pinMode(corrienteHiLo, OUTPUT);
  pinMode(amplitudCorrienteCS, OUTPUT);
  pinMode(crucePorCero, OUTPUT);

  // put your setup code here, to run once:
}

void loop() {
  for (int i = 1; i < 254; i++) {
    value = i;
    escribirPotenciometroDigitalCorriente(value);
    delay(100);
  }
}

void escribirPotenciometroDigitalCorriente(int value) {
  // digitalWrite(cal, HIGH);
  digitalWrite(amplitudCorrienteCS, HIGH);
  delay(2);

  //digitalWrite(crucePorCero, HIGH);
  SPI.transfer(B00010001);    // Comand Byte, escribe en el primer potenciometro (único en este caso)
  SPI.transfer((byte)value);  // Data Byte, selecciona una de las 256 posiciones del cursor
  digitalWrite(amplitudCorrienteCS, LOW);
  //digitalWrite(crucePorCero, LOW);
  delay(20);
  // digitalWrite(cal, LOW);
  return;
}