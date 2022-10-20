#include <max6675.h>


// CONFIGURACION DE LOS PINES UTILIZADOS PARA LA COMUNICACIÓN CON EL MAX6675
#define CONFIG_TCDO_PIN       12
#define CONFIG_TCCS_PIN       11
#define CONFIG_TCSCK_PIN      10

#define A 2
#define B 3
#define C 4
#define D 5
#define T1 6
#define T2 7
#define T3 8

#define tonePin A0

//#define VarMan 9

int sensorPin = A1;
int valorAlarmaSaved=-1;
int valorAlarma;
 

// OBJETO UTILIZADO PARA LA COMUNICACION CON EL MAX6675
MAX6675 thermocouple(CONFIG_TCSCK_PIN, CONFIG_TCCS_PIN, CONFIG_TCDO_PIN);

void binario (int numero){
  digitalWrite(A,bitRead(numero,0));
  digitalWrite(B,bitRead(numero,1));
  digitalWrite(C,bitRead(numero,2));
  digitalWrite(D,bitRead(numero,3));
  }

int convertir (int sensorValue){ //CONVERTIR PARA EL ANALOGICO
  int sensorAnt;
   
  
  if (sensorValue<40)
   sensorAnt=20;
  else if(sensorValue>40 && sensorValue<80)
   sensorAnt=30;
  else if(sensorValue>80 && sensorValue<120)
   sensorAnt=40;
  else if(sensorValue>120 && sensorValue<160)
   sensorAnt=50;
  else if(sensorValue>160 && sensorValue<200)
   sensorAnt=60;
  else if(sensorValue>200 && sensorValue<240)
   sensorAnt=70;
  else if(sensorValue>240 && sensorValue<280)
   sensorAnt=80;
  else if(sensorValue>280 && sensorValue<320)
   sensorAnt=90;
  else if(sensorValue>320 && sensorValue<360)
   sensorAnt=100;
  else if(sensorValue>360 && sensorValue<400)
   sensorAnt=110;
  else if(sensorValue>400 && sensorValue<440)
   sensorAnt=120;
  else if(sensorValue>440 && sensorValue<480)
   sensorAnt=130;
   else if(sensorValue>480 && sensorValue<520)
   sensorAnt=140;
   else if(sensorValue>520 && sensorValue<560)
   sensorAnt=150;
   else if(sensorValue>560 && sensorValue<600)
   sensorAnt=160;
   else if(sensorValue>600 && sensorValue<640)
   sensorAnt=170;
   else if(sensorValue>640 && sensorValue<680)
   sensorAnt=180;
   else if(sensorValue>680 && sensorValue<760)
   sensorAnt=190;
   else if(sensorValue>760 && sensorValue<800)
   sensorAnt=200;
   else if(sensorValue>800 && sensorValue<840)
   sensorAnt=210;
   else if(sensorValue>840 && sensorValue<880)
   sensorAnt=220;
   else if(sensorValue>880 && sensorValue<920)
   sensorAnt=230;
   else if(sensorValue>920 && sensorValue<960)
   sensorAnt=240;
   else if(sensorValue>960)
   sensorAnt=250;

   return sensorAnt;
}

void setup() {
  // PREPARAR LA INTERFAZ SERIAL
  //Serial.begin(9600);

  // PROBAR DECODIFICADOR BCD A 7 SEG
  pinMode(A, OUTPUT); //digitalWrite(A, LOW);
  pinMode(B, OUTPUT); //digitalWrite(B, LOW);
  pinMode(C, OUTPUT); //digitalWrite(C, LOW);
  pinMode(D, OUTPUT); //digitalWrite(D, LOW);
  pinMode(T1, OUTPUT);// digitalWrite(T1, HIGH);
  pinMode(T2, OUTPUT);// digitalWrite(T2, HIGH);
  pinMode(T3, OUTPUT); //digitalWrite(T3, HIGH);
  pinMode(tonePin, OUTPUT);
 // pinMode(VarMan, INPUT);

 /* // IMPRIMR MENSAJE INICIAL A LA TERMINAL
  Serial.println(F("----------------------------------------------------"));
  Serial.println(F("      TUTORIAL TERMOPAR CON ARDUINO Y MAX6675       "));
  Serial.println(F("            http://www.geekfactory.mx               "));
  Serial.println(F("----------------------------------------------------"));*/

  // ESPERAR A QUE SE ESTABILICE LA ENERGIA
 
}

void loop() {
  int temperatura;
  int centena, decena, unidad;
  int i=0;
  int tempAlarma=190;
  int sensorPos;
  
  
  
  
sensorPos=analogRead(sensorPin);

valorAlarma=convertir(sensorPos);
//valorAlarmaSaved=valorAlarma;
if(valorAlarmaSaved != valorAlarma){ 
do{
  valorAlarma=convertir(sensorPos); 

  if(valorAlarmaSaved != valorAlarma)
  { 
   tone(tonePin,340);
  delay(30); 
  noTone(tonePin);
  delay(30); 
  tone(tonePin,440);
  delay(30);  
  noTone(tonePin);
  }
  
  unidad=valorAlarma%10;
  valorAlarma = valorAlarma/10;
  decena=valorAlarma%10;
  centena=valorAlarma/10;


  //delay(5);
  digitalWrite(T1,LOW);
  digitalWrite(T2,LOW);
  digitalWrite(T3,HIGH);
  binario(unidad);
  delay(4);

  digitalWrite(T1,LOW);
  digitalWrite(T2,HIGH);
  digitalWrite(T3,LOW);
  binario(decena);
  delay(4);

  digitalWrite(T1,HIGH);
  digitalWrite(T2,LOW);
  digitalWrite(T3,LOW);
  binario(centena);
  delay(4);

 valorAlarma=convertir(sensorPos);
 valorAlarmaSaved=valorAlarma;
 
  i=i+1;
  }while(i<80);
  
  digitalWrite(T1,LOW);
  digitalWrite(T2,LOW);
  digitalWrite(T3,LOW); 
  valorAlarmaSaved=valorAlarma;
    
  
  } 
 
 
 temperatura=thermocouple.readCelsius();

 if(thermocouple.readCelsius()>valorAlarmaSaved)
 tone(tonePin,820);
 else
 noTone(tonePin);

  unidad=temperatura%10;
  temperatura = temperatura/10;
  decena=temperatura%10;
  centena=temperatura/10;

do{
  //delay(5);
  digitalWrite(T1,LOW);
  digitalWrite(T2,LOW);
  digitalWrite(T3,HIGH);
  binario(unidad);
  delay(5);

  digitalWrite(T1,LOW);
  digitalWrite(T2,HIGH);
  digitalWrite(T3,LOW);
  binario(decena);
  delay(5);

  digitalWrite(T1,HIGH);
  digitalWrite(T2,LOW);
  digitalWrite(T3,LOW);
  binario(centena);
  delay(5);

 
  i=i+1;
  }while(i<100);

  digitalWrite(T1,LOW);
  noTone(tonePin);
 
  /*Serial.print(valorAlarmaSaved);
  Serial.print("-");
  Serial.print(valorAlarma);
  Serial.print("\n");*/
  
    
   
/*
  // IMPRIMIR LA TEMPERATURA EN LA TERMINAL SERIAL
  Serial.print("C = ");
  Serial.println(thermocouple.readCelsius());
  Serial.print(unidad);
  Serial.print("...");
  Serial.print(decena);
  Serial.print("...");
  Serial.print(centena);

  // ESPERAR UN SEGUNDO ENTRE LAS LECTURAS
  //delay(1000);
  */
}
