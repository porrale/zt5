#include <AD9850SPI.h>
#include <SPI.h>
#include "GFButton.h"
#include <LiquidCrystal_I2C.h>

//const int W_CLK_PIN = 13;
//const int FQ_UD_PIN = 8;
//const int RESET_PIN = 9;


#define VSPI_MOSI   23
#define VSPI_MOSI   MOSI


const int W_CLK_PIN = 18;
const int FQ_UD_PIN = 5;
const int RESET_PIN = 1;

double frecuencia = 10000;
double trimFrecuencia = 124999500;

int fase = 0;
// LCD
int lcdColumns = 20;
int lcdRows = 4;

int direccionLCD = 0x27;

//Serial 
int velocidadSerie = 115200;

// Crear botones

bool boton[6]={1,1,1,1,1,1};


GFButton PULSADOR_1(15);
GFButton PULSADOR_2(2);
GFButton PULSADOR_3(0);
GFButton PULSADOR_4(13);

// Salidas
int GEN_STATE =0;



void setup(){
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, RESET_PIN);
  DDS.calibrate(trimFrecuencia);
  SPI.begin();
  SPI.setFrequency(1000);
  //SPI.setDataMode(SPI_MODE1);
}

void loop(){
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 5000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 4000;
 DDS.setfreq(frecuencia, fase);
  DDS.setfreq(frecuencia, fase);
  delay(1);
  //DDS.down();
  //delay(3000);
  DDS.up();
  delay(1);
  DDS.setfreq(frecuencia + 500, fase);
  delay(1);
  frecuencia = 1000;
  DDS.setfreq(frecuencia, fase);

  delay(1);
 frecuencia = 1000;
 DDS.setfreq(frecuencia, fase);
  
  //DDS.down();
  while(1);
}