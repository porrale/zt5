//medidor de impedancia ZT 5 25/10!22

#include <AD9850SPI.h>
#include <SPI.h>
#include "GFButton.h"
#include <LiquidCrystal_I2C.h>

//const int W_CLK_PIN = 13;
//const int FQ_UD_PIN = 8;
//const int RESET_PIN = 9;


#define VSPI_MOSI 23
#define VSPI_MOSI MOSI

// definiciones SPI



int amplitudCorrienteCS = 17;  // AmplitudI CS
int crucePorCero = 16;         // cruce por cero  CS
int corrienteHiLo = 4;         // corriente alta y baja
const int W_CLK_PIN = 18;
const int FQ_UD_PIN = 5;
const int RESET_PIN = 1;

double frecuencia = 1000;
double trimFrecuencia = 124999500;
int fase = 0;

// salidas

int cal = 27;
int value = 0;

// LCD
int lcdColumns = 20;
int lcdRows = 4;

int direccionLCD = 0x27;

//Serial
int velocidadSerie = 9600;

// Crear botones

bool boton[6] = { 1, 1, 1, 1, 1, 1 };


GFButton PULSADOR_1(15);
GFButton PULSADOR_2(2);
GFButton PULSADOR_3(0);
GFButton PULSADOR_4(13);

// Salidas
int GEN_STATE = 0;
int opt = 0;  // variable opt opciones del menu

//funciones personalizadas
LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows);

/////////////////// teclapresionada
int teclapresionada(void) {
  int retornar = 0;
  if (PULSADOR_1.wasPressed()) {

    retornar = 1;
  }

  if (PULSADOR_2.wasPressed()) {

    retornar = 2;
  }
  if (PULSADOR_3.wasPressed()) {

    retornar = 3;
  }
  if (PULSADOR_4.wasPressed()) {

    retornar = 4;
  }
  return retornar;
}



void setup() {
  //DDS.begin(W_CLK_PIN, FQ_UD_PIN, RESET_PIN);
  //DDS.calibrate(trimFrecuencia);

  SPI.begin();
  SPI.setFrequency(1000);
  //Serial.begin(velocidadSerie);
  //SPI.setDataMode(SPI_MODE1);
  LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows);
  lcd.init();

  pinMode(corrienteHiLo, OUTPUT);
  pinMode(amplitudCorrienteCS, OUTPUT);
  pinMode(crucePorCero, OUTPUT);
}

void loop() {

  opt = teclapresionada();
  if (opt != 0) {
    lcd.setCursor(0, 0);
    lcd.print("iniciando");
    // Serial.println("Generando");
    // generador();
    switch (opt) {
      case 1:  //
        generador();
        break;
      case 2:  //
        decadas();

        break;
      case 3:  //abajo
        for (int i = 1; i < 254; i++) {
          value = i;
          escribirPotenciometroDigitalCorriente(value);
          delay(100);
        }


        break;
      case 4:  //arriba


        break;
    }
  }
}

void escribirPotenciometroDigitalCorriente(int value) {
  lcd.setCursor(0, 1);
  lcd.print(value);
  digitalWrite(amplitudCorrienteCS, HIGH);
  delay(2);
  SPI.transfer(B00010001);    // Comand Byte, escribe en el primer potenciometro (único en este caso)
  SPI.transfer((byte)value);  // Data Byte, selecciona una de las 256 posiciones del cursor
  digitalWrite(amplitudCorrienteCS, LOW);
  delay(20);
  return;
}
void generador(void) {
  lcd.setCursor(0, 1);
  lcd.print("generador");
  delay(1000);
  DDS.up();
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  delay(3000);
  frecuencia = 2000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  delay(3000);
  delay(1);
  frecuencia = 3000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(3000);
  frecuencia = 2000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(3000);
  delay(1);
  frecuencia = 1000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1000);
  DDS.down();
  lcd.clear();

  return;
}

void decadas(void) {
  lcd.setCursor(0, 1);
  lcd.print("decadas");
  delay(500);
  frecuencia = 100;
  DDS.up();
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  delay(1500);
  frecuencia = 1000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1500);
  frecuencia = 10000;
  lcd.setCursor(0, 1);
  lcd.print(frecuencia);
  DDS.setfreq(frecuencia, fase);
  delay(1500);
  DDS.down();
  lcd.clear();

  return;
}
