/**
  Firmware Medidor de impedancia biologica de frecuencia variable reducido 25-10-22
*/

//Librerias

#include "GFButton.h"
#include <AD9850SPI.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>


// pines SPI
#define VSPI_MOSI 23
#define VSPI_MOSI MOSI

// pines generador DDS
const int W_CLK_PIN = 18;
const int FQ_UD_PIN = 5;
const int RESET_PIN = 1;

int amplitudCorrienteCS = 17;  // AmplitudI CS
int crucePorCero = 16;         // cruce por cero  CS


// Salidas
int GEN_STATE = 0;
int cal = 27;
int corrienteHiLo = 4;  // corriente alta y baja
//Variables Globales
int menu_global = 20;
int value = 0;
bool backEncendido = 1;

// variables generador DDS
double frecuencia = 1000;
double trimFrecuencia = 124999500;
int fase = 0;

// LCD
int lcdColumns = 20;
int lcdRows = 4;

int direccionLCD = 0x27;

//Serial
int velocidadSerie = 57600;

bool boton[6] = { 1, 1, 1, 1, 1, 1 };

GFButton PULSADOR_1(15);
GFButton PULSADOR_2(2);
GFButton PULSADOR_3(0);
GFButton PULSADOR_4(13);

int opt = 0;  // variable opt opciones del menu

/**
   Declaración de funciones
*/
void LCD_presentacion(void);
void actualizarLCD(void);
int teclapresionada(void);
void menu_LCD(int);
void iniciarGen(void);
void prender_generador(bool);
void sub_menu_medir(int);
void sub_menu_ingresar_electrodo(void);
void mostrar_parpadeando(long int *, int);  //,byte*);
void limpiar_salidas(void);
void guardar_datos_iniciales(void);
void mandar_dato(void);
void setear_ganancia(unsigned long int);
void escribirPotenciometroDigitalCorriente(int value);
LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows);
// int generador(void);

int generador(void) {
  int retornar1 = 0;
  DDS.setfreq(frecuencia, fase);
  delay(1);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(3000);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
  frecuencia = 5000;
  DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  delay(3000);

  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 10000;
  DDS.setfreq(frecuencia, fase);
  delay(3000);
  frecuencia = 5000;
  DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);
  delay(1000);
  retornar1 = 10;
  return retornar1;
}

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

void medirMuestra(void) {
  frecuencia = 2000;
  fase = 0;
  DDS.setfreq(frecuencia, fase);
  delay(1);
  DDS.up();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("midiendo");
  delay(2000);
}



void setup() {
  // put your setup code here, to run once:
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, RESET_PIN);
  DDS.calibrate(trimFrecuencia);

  // Serial.begin(velocidadSerie);
  SPI.begin();
  
  SPI.setFrequency(1000);
  pinMode(cal, OUTPUT);
  pinMode(corrienteHiLo, OUTPUT);
  pinMode(amplitudCorrienteCS, OUTPUT);
  pinMode(crucePorCero, OUTPUT);
  // initialize LCD
  //https://github.com/johnrickman/LiquidCrystal_I2C/blob/master/LiquidCrystal_I2C.h
  LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows);
  lcd.init();

  // turn on LCD backlight
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("*******ZT*****");
  lcd.setCursor(0, 1);
  lcd.print("iniciando");
  // Serial.println("caso 1");

  digitalWrite(cal, HIGH);

  delay(2000);
  digitalWrite(cal, LOW);
  lcd.noBacklight();
}

void loop() {
  // put your main code here, to run repeatedly:

  opt = teclapresionada();
  if (opt != 0) {

    switch (opt) {
      case 1:
        Serial.println("Medir Muestra");
        lcd.setCursor(0, 1);
        DDS.up();
        delay(1);
        DDS.setfreq(frecuencia, fase);
        delay(1);
        DDS.up();
        delay(1);
        delay(2000);
        break;
      case 2:
        Serial.print("Contador: 2");
        lcd.setCursor(0, 1);
        lcd.print("**2**");
        break;
      case 3:
        Serial.print("Contador:3 ");
        lcd.setCursor(0, 1);
        lcd.print("**3**");
        break;
      case 4:
        Serial.print("Contador:4 ");
        lcd.setCursor(0, 1);
        lcd.print("**4**");
        break;
    }
  }
}