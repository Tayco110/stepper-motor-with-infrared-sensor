 // Controle de motor - CNC Shield

#include <string.h>
 
// Definição dos pinos 
#define stepPin 2 //Passo eixo X
#define dirPin 5 // Direção eixo X

int PIR1 = 0;
int flag_motor = 0;

// tag pequena = 0, tag grande = 1
int tagSize = 1;
String incomingByte; // for incoming serial data

 void setup() {
 // Definindo ambos os pinos acima como saída
   pinMode(stepPin,OUTPUT); 
   pinMode(dirPin,OUTPUT);
   pinMode(A10, INPUT);
   Serial.begin(9600);
 }
 
 void loop() {
  PIR1 = analogRead(A10);
  
  // Se apenas o sensor 1 for low vai ativar a flag de rotação do motor 1
  if (PIR1 < 50 && flag_motor == 0){
    //Serial.println(flag_motor);
    digitalWrite(dirPin,HIGH);
    for(int x = 0; x < 630; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(1500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(1500); 
     }
    flag_motor = 1;
  }

  // Se o sensor 1 for high vai desativar a flag de rotação do motor 1
  /*else if (PIR1 > 50){
    //Serial.println(flag_motor);
    flag_motor = 0;
  }*/

 while (Serial.available()) {
    incomingByte = Serial.readString();
    //Serial.println(incomingByte);
     
    // Se for uma tag com problema vai rebobinar
    if (incomingByte == "PROBLEMA\n"){
      Serial.println("Rebobinar motor");
      digitalWrite(dirPin,LOW);
      for(int x = 0; x < 650; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
      }
      //flag_motor = 0;
    }

    
    else if (incomingByte != "PROBLEMA\n" && tagSize == 0){
      Serial.println("Prosseguir");
      digitalWrite(dirPin,HIGH);
      for(int x = 0; x < 150; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(1000); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(500); 
       }
    }

    else if (incomingByte != "PROBLEMA\n" && tagSize == 1){
      Serial.println("Prosseguir");
      digitalWrite(dirPin,HIGH);
      for(int x = 0; x < 150; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(1000); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(500); 
       }
    }
  }
  
  
}
