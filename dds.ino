  /**
Firmware Medidor de impedancia biologica de frecuencia variable 
*/
//Librerias

#include "GFButton.h"
#include <AD9850SPI.h>
#include <SPI.h>

#include <LiquidCrystal_I2C.h>

//const int W_CLK_PIN = 13;
//const int FQ_UD_PIN = 8;
//const int RESET_PIN = 9;

// pines SPI
#define VSPI_MOSI   23
#define VSPI_MOSI   MOSI

// pines generador DDS
const int W_CLK_PIN = 18;
const int FQ_UD_PIN = 5;
const int RESET_PIN = 1;

// variables generador DDS
double frecuencia = 1000;
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
int cal = 27;
int amplitudCorrienteCS = 16; // AmplitudI CS
int corrienteHiLo = 4; // corriente alta y baja

//Variables Globales
int menu_global =20;
int valorPorenciometroCorriente = 128;



void setup(){
  pinMode(cal, OUTPUT);
  pinMode(corrienteHiLo, OUTPUT);
  pinMode(amplitudCorrienteCS, OUTPUT);


  
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, RESET_PIN);
  DDS.calibrate(trimFrecuencia);
  SPI.begin();
  SPI.setFrequency(1000);
  //SPI.setDataMode(SPI_MODE1);
  // initialize LCD
  //https://github.com/johnrickman/LiquidCrystal_I2C/blob/master/LiquidCrystal_I2C.h
  LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows);  
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
 
  lcd.setCursor(0, 0);
  lcd.print("*******ZT*****");
 
 //LCD_printf_xy_4b(0, 0, datoamostrar);

 
  lcd.setCursor(0, 1);
  lcd.print("iniciando"); 
 
}
int opt=0; // variable opt opciones del menu


void loop(){
  String  datoamostrar;
  frecuencia = 1000;
  fase = 0;  

  DDS.up();

  
  menu_LCD(opt);

}

/**
   Declaración de funciones
*/
void LCD_presentacion(void);
void actualizarLCD(void);
int  teclapresionada(void);
void menu_LCD(int);
void iniciarGen(void);
void prender_generador(bool);
void sub_menu_medir(int);
void sub_menu_ingresar_electrodo(void);
void mostrar_parpadeando(long int *,int);//,byte*);
void limpiar_salidas(void);
void guardar_datos_iniciales(void);
void mandar_dato(void);
void setear_ganancia(unsigned long int);
LiquidCrystal_I2C lcd(direccionLCD, lcdColumns, lcdRows); 
/**
   funciones
*/

void iniciarGen(void)
{

 String  datoamostrar;
 word cant=20;
 byte erores;
 word menu=1;
 datoamostrar = "*******ZT*****";  
 lcd.setCursor(0, 0);
 lcd.print(datoamostrar);
 
 //LCD_printf_xy_4b(0, 0, datoamostrar);

 datoamostrar = "iniciando";
 lcd.setCursor(0, 1);
 lcd.print(datoamostrar); 

 // IFsh1_GetBlockFlash(0xe020, datoamostrar, cant);
 //lcd.print4b(0, 1, datoamostrar);
 lcd.setCursor(0, 1);
 lcd.print(datoamostrar); 
 datoamostrar = frecuencia;
 lcd.setCursor(1, 1);
 delay(1);
 lcd.print(datoamostrar);
 while(menu==1)
  {
    //if(PULSADOR_2 == 0)
    if(PULSADOR_2.wasPressed()){     
      Serial.println(F("PULSADOR_2"));
      menu=0;
      boton[1]=0;
      lcd.clear();
      menu=menu_global;
      //errono= IFsh1_SetBlockFlash(&menu,0xe2f8, sizeof(word));
      actualizarLCD();
    }
  } 
  //errono= IFsh1_SetBlockFlash(&menu,0xe2f8, sizeof(word));
  
  prender_generador (1);
  
  return;
}

  void escribirPotenciometroDigitalCorriente(int value) {
     
    digitalWrite(amplitudCorrienteCS,LOW);
    delay(500);
    SPI.transfer(B00010001);      // Comando Byte, escribe en el primer potenciometro (único en este caso)
    SPI.transfer((byte)value);    // Data Byte, selecciona una de las 256 posiciones del cursor
    digitalWrite(amplitudCorrienteCS,HIGH);
    
}


void prender_generador(bool state){

  GEN_STATE = state;
  DDS.setfreq(frecuencia, fase);

}


void actualizarLCD(void)
{
   Serial.println(F("Actualizar LCD"));
  String  datoamostrar;
  word cant=20;
  byte ererer;
  word menu;
  menu=menu_global;
  //ererer= IFsh1_GetBlockFlash(0xe2f8, &menu, sizeof(word));
  lcd.clear();
  //LCD_Control_4b(0x01);
  switch(menu%10) //CUAL SUBMENU DEL RAIZ
  {
    Serial.println(menu);
    case 0:
      switch(menu/10) //RAIZ (SIN SUBMENU)
        {
          case 1:
            //IFsh1_GetBlockFlash(0xe040, datoamostrar, cant); //Electrodo
            datoamostrar = "Electrodo";
            Serial.println(F("Electrodo"));
            break;
          case 2:
            //IFsh1_GetBlockFlash(0xe060, datoamostrar, cant);  //Muestra
            
            Serial.println(F("Medir Muestra"));

            
            lcd.print("Muestra");
            
            break;
          case 3:
            datoamostrar = "Download Data";
            Serial.println(F("Download"));
            //IFsh1_GetBlockFlash(0xe080, datoamostrar, cant);  //Download Data
            break;
          case 4:
            datoamostrar = " Setup";
            //IFsh1_GetBlockFlash(0xe140, datoamostrar, cant); //Setup
            Serial.println(F("Setup"));
            break;
        }
        lcd.setCursor(0,0);
        lcd.print(datoamostrar);
        //Serial.println(datoamostrar);
        //LCD_printf_xy_4b(0, 0, datoamostrar);
      break;
    case 1:
      switch(menu/10) //PRIMER SUBMENU
        {
          case 1:
            Serial.println(F("Medir"));
            //IFsh1_GetBlockFlash(0xe0a0, datoamostrar, cant);  //Medir
            break;
          case 2:
            Serial.println(F("Ingresar"));
            //IFsh1_GetBlockFlash(0xe0e0, datoamostrar, cant);  //Ingresar
            break;
          case 3:
            Serial.println("Preamp");
            //IFsh1_GetBlockFlash(0xe160, datoamostrar, cant);  //Preamp
            if (boton[5]==1)    //otra cosa
              {
              datoamostrar[17]='O';
              datoamostrar[18]='N';
              }
            break;
          case 4:
             Serial.println("Backlight");
            //IFsh1_GetBlockFlash(0xe180, datoamostrar, cant);  //Backlight
            
            /*if (LED2_N==1)
              {
              datoamostrar[17]='O';
              datoamostrar[18]='N';
              }
            break;
*/
        }
      lcd.setCursor(0,0);
      lcd.print(datoamostrar);
     // LCD_printf_xy_4b(0, 0, datoamostrar);
      break;
  }
}

void menu_LCD(int opt)
{
String datoamostrar;
byte ererer;
word menu;  
               
menu=menu_global;
//ererer= IFsh1_GetBlockFlash(0xe2f8, &menu,sizeof(word));                  

opt= teclapresionada();
    if (opt!=0)
    {
        //antirrebote();
        switch(opt)
        {
        case 1: //back
          if(menu%10==0) //si es raiz
          {

          }
          else //si no es raiz
          {
            menu=menu/10;
            menu=menu*10;
          }
          break;
        case 2: //ok
          if(menu%10==0) //si es raiz
          {
            if (menu==10||menu==40)
              menu++;
            else
              {
              if (menu==20)
                {
                lcd.setCursor(0,0);
                lcd.print("MEDIR MUESTRA");
                int valor = 254;  
                escribirPotenciometroDigitalCorriente(valor);
                lcd.print(valor);  
                
                frecuencia = 1500;
                DDS.setfreq(frecuencia, fase);
                digitalWrite(cal, HIGH);
                
                delay(3000);
                //prender_generador (0);
                //demora_ms(100);
                //sub_menu_medir(MUESTRA);
                //prender_generador (1);
                digitalWrite(cal, LOW);
                }
              else{
                lcd.setCursor(0,0);
                lcd.print(" mandar_dato");
                Serial.println("mandar_dato");
                //mandar_dato();
              }
              }
            
          }
          else  //si no es raiz
          {
            if (menu==11)
              {
                 lcd.setCursor(0,0);
                 lcd.print("MEDIR Electrodo");  
              //prender_generador (0);
              //demora_ms(100);
              //sub_menu_medir(ELECTRODO);
              //prender_generador (1);
              }
            else
              if (menu==21)
                {
                lcd.setCursor(0,0);
                lcd.print("Ingresar Electrodo");
                //sub_menu_ingresar_electrodo();           
                //menu=menu/10;
                //menu=menu*10;
                }
              else
                if (menu==41)
                  {
                    lcd.setCursor(0,0);
                    lcd.print("LED2-on");
                  //if (LED2_N==1)
                  //  LED2_N=0;
                  //else
                  //  LED2_N=1;
                  } 
              else{
                  if (menu==31)
                  {
                    lcd.setCursor(0,0);
                    lcd.print("boton[5]");
                  //if (boton[5]==1)
                  //  boton[5]=0;}
                  }
                  else{
                    lcd.setCursor(0,0);
                    lcd.print("boton[5]=1;");
                  // boton[5]=1;
                  
                  }
              }
          }
         
        
          break;
        case 3: //abajo
        
        if (menu%10==0)
          {
          if (menu==40)
            menu=10;
          else
            menu+=10;
          }
        else
          {
         
            if (menu==11)
              menu=21;
            else if (menu==21)
              menu=11;
            
            if (menu==31)
              menu=41;
            else if (menu==41)
              menu=31;
            
          }
             
          break;
        case 4: //arriba
          if (menu%10==0)
          {
            if (menu<=10)
              menu=40;
            else
              menu-=10;
            }
          else
          {
          
            if (menu==11)
              menu=21;
            else if (menu==21)
              menu=11;
            
            if (menu==31)
              menu=41;
            else if (menu==41)
              menu=31;
          }
          
          break;
      }
      menu_global = menu;
      //ererer= IFsh1_SetBlockFlash(&menu,0xe2f8, sizeof(word));
       
      actualizarLCD();
    } 
    return;
}

/////////////////// teclapresionada
int  teclapresionada(void)
{
  int retornar=0;
  if (PULSADOR_1.wasPressed())
    {
//    if (boton[1]==1)
//      boton[1]=0;
//    else
//      {
//      boton[1]=1;
      retornar=1;
//      }
    }

  if (PULSADOR_2.wasPressed())
    {
//    if (boton[2]==1)
//      boton[2]=0;
//    else
//      {
//      boton[2]=1;
      retornar=2;
//      }
    }
  if (PULSADOR_3.wasPressed())
    {
//    if (boton[3]==1)
//      boton[3]=0;
//    else
//      {
//      boton[3]=1;
      retornar=3;
//      }
    }
  if (PULSADOR_4.wasPressed())
    {
//    if (boton[4]==1)
//      boton[4]=0;
//    else
//      {
//      boton[4]=1;
      retornar=4;
//      }
    }
  return retornar;  
}