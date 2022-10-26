 // Controle de motor - CNC Shield

#include <string.h>
#include <Servo.h>
 
// Definição dos pinos 
#define stepPinX 2 //Passo eixo X
#define dirPinX 5 // Direção eixo X
#define stepPinY 3 //Passo eixo Y
#define dirPinY 6 // Direção eixo Y

const int pinoChave = 24; //PINO DIGITAL UTILIZADO PELA CHAVE FIM DE CURSO
int PIR1 = 0;
int flag_motor = 0;
int flagDir = 1;

// tag pequena = 0, tag grande = 1
int tagSize = 1;
int delta = 0; // erro dos espaços entre as tags
int flagFirstTag = 0;
String incomingByte; // for incoming serial data

Servo s1; // Variável SERVO ALÇAPÃO 1
Servo s2; // Variável SERVO ALÇAPÃO 2
int pos1; // Posição SERVO ALÇAPÃO 1
int pos2; // Posição SERVO ALÇAPÃO 2

 void setup() {
 // Definindo ambos os pinos acima como saída
   pinMode(stepPinX,OUTPUT); 
   pinMode(dirPinX,OUTPUT);
   pinMode(stepPinY,OUTPUT); 
   pinMode(dirPinY,OUTPUT);
   pinMode(A10, INPUT);
   pinMode(pinoChave, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
   s1.attach(51); //SERVO ALÇAPÃO 1
   s2.attach(50); //SERVO ALÇAPÃO 2
   s1.write(130); // Inicia SERVO ALÇAPÃO 1 FECHADO 
   s2.write(160); // Inicia SERVO ALÇAPÃO 2 FECHADO 
   Serial.begin(9600);
 }
 
 void loop() {

  if(digitalRead(pinoChave) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
      digitalWrite(dirPinY,LOW);
        for(int y = 0; y < 14800; y++) {
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
         }
  }
  
  PIR1 = analogRead(A10);
  // Se apenas o sensor 1 for low vai ativar a flag de rotação do motor 1
  if (PIR1 < 50 && flag_motor == 0){
    flag_motor = 1;
    Serial.println(flag_motor);
    digitalWrite(dirPinX,HIGH);
    for(int x = 0; x < 2570; x++) {
      digitalWrite(stepPinX,HIGH); 
      delayMicroseconds(300); 
      digitalWrite(stepPinX,LOW); 
      delayMicroseconds(300); 
     }
  }

 while (Serial.available()) {
    incomingByte = Serial.readString();
    //Serial.println(incomingByte);
     
    // Se for uma tag com problema vai rebobinar
    if (incomingByte == "PROBLEMA\n"){
      Serial.println("Rebobinar motor");
      digitalWrite(dirPinX,LOW);
      for(int x = 0; x < 2600; x++) {
        digitalWrite(stepPinX,HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPinX,LOW);
        delayMicroseconds(300);
      }
      //flag_motor = 0;
    }

    
    else if (incomingByte != "PROBLEMA\n" && tagSize == 0){
      Serial.println("Prosseguir");
      if (flagFirstTag == 0){
        delta = 740;
        Serial.println("Primeira tag");
        flagFirstTag = 1;
      }
      else{
        delta = 740;
      }
      digitalWrite(dirPinX,HIGH);
      Serial.println(delta);
      for(int x = 0; x < delta; x++) {
        digitalWrite(stepPinX,HIGH); 
        delayMicroseconds(300); 
        digitalWrite(stepPinX,LOW); 
        delayMicroseconds(300); 
       }

      /*digitalWrite(dirPinY,HIGH);
      for(int x = 0; x < 1600; x++) {
        digitalWrite(stepPinY,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPinY,LOW); 
        delayMicroseconds(500); 
       }*/
    }

    // Tag grande
    // Tag Boa
    else if (incomingByte == "BOA\n" && tagSize == 1){
      Serial.println("Prosseguir");
      digitalWrite(dirPinX,HIGH);
      Serial.println(delta);
      // Move uma tag
      for(int x = 0; x < 775; x++) {
        digitalWrite(stepPinX,HIGH); 
        delayMicroseconds(300); 
        digitalWrite(stepPinX,LOW); 
        delayMicroseconds(300); 
       }
       //Corte
      if (flagDir%2 != 0){
        digitalWrite(dirPinY,HIGH);
        for(int x = 0; x < 14800; x++) {
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
        }  
      }
      else{
        digitalWrite(dirPinY,LOW);
        for(int y = 0; y < 14800; y++) {
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
         }
      }
      flagDir++;
    }
    // Tag Qualidade
    else if (incomingByte == "QUALIDADE\n" && tagSize == 1){
      Serial.println("Prosseguir");
      digitalWrite(dirPinX,HIGH);
      Serial.println(delta);
      // Move uma tag
      for(int x = 0; x < 775; x++) {
        digitalWrite(stepPinX,HIGH); 
        delayMicroseconds(300); 
        digitalWrite(stepPinX,LOW); 
        delayMicroseconds(300); 
       }
       //Corte
      if (flagDir%2 != 0){
        digitalWrite(dirPinY,HIGH);
        for(int x = 0; x < 14800; x++) {
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
        }  
      }
      else{
        digitalWrite(dirPinY,LOW);
        for(int y = 0; y < 14800; y++) {
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
         }
      }
      flagDir++;
      delay(100);
      for(pos1 = 130; pos1 > 60; pos1--){
        s1.write(pos1);
        delay(10);
      }
      delay(1000);
      for(pos1 = 60; pos1 <= 130; pos1++){
        s1.write(pos1);
        delay(10);
      }
      
    }

    // Tag Descarte
    else if (incomingByte == "DESCARTE\n" && tagSize == 1){
      Serial.println("Prosseguir");
      digitalWrite(dirPinX,HIGH);
      // Move uma tag
      for(int x = 0; x < 775; x++) {
        digitalWrite(stepPinX,HIGH); 
        delayMicroseconds(300); 
        digitalWrite(stepPinX,LOW); 
        delayMicroseconds(300); 
       }
       //Corte
      Serial.print(flagDir);
      if (flagDir%2 != 0){
        digitalWrite(dirPinY,HIGH);
        for(int x = 0; x < 14800; x++) {
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
        }  
      }
      else{
        digitalWrite(dirPinY,LOW);
        for(int y = 0; y < 14800; y++) {
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
         }
      }
      flagDir++;
      delay(100); 
      for(pos2 = 160; pos2 > 100; pos2--){
        s2.write(pos2);
        delay(10);
      }
      delay(1000);
      for(pos2 = 100; pos2 <= 160; pos2++){
        s2.write(pos2);
        delay(10);
      }
    }
    
  }
  
  
}
