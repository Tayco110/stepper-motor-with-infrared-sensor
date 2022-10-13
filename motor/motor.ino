 // Controle de motor - CNC Shield

#include <string.h>
 
// Definição dos pinos 
#define stepPinX 2 //Passo eixo X
#define dirPinX 5 // Direção eixo X
#define stepPinY 3 //Passo eixo Y
#define dirPinY 6 // Direção eixo Y

int PIR1 = 0;
int flag_motor = 0;
int flagDir = 1;

// tag pequena = 0, tag grande = 1
int tagSize = 1;
int delta = 0; // erro dos espaços entre as tags
int flagFirstTag = 0;
String incomingByte; // for incoming serial data

 void setup() {
 // Definindo ambos os pinos acima como saída
   pinMode(stepPinX,OUTPUT); 
   pinMode(dirPinX,OUTPUT);
   pinMode(stepPinY,OUTPUT); 
   pinMode(dirPinY,OUTPUT);
   pinMode(A10, INPUT);
   Serial.begin(9600);
 }
 
 void loop() {
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
    }

    // Tag Descarte
    else if (incomingByte == "DESCARTE\n" && tagSize == 1){
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
      Serial.print(flagDir);
      if (flagDir%2 == 0){
        Serial.print("Par");
        digitalWrite(dirPinY,HIGH);
        for(int x = 0; x < 14800; x++) {
          digitalWrite(stepPinY,HIGH); 
          delayMicroseconds(100); 
          digitalWrite(stepPinY,LOW); 
          delayMicroseconds(100); 
        }  
      }
      else if (flagDir%2 != 0){
        Serial.print("Impar");
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
    
  }
  
  
}
