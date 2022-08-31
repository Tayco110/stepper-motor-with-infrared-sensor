#include <Arduino.h>
// #include <AccelStepper.h>
// #include <IRremote.h>

int pinsPonteH[] = {8,9,10,11}; //pinos da ponte H
int outputInfra = 6; //pino de retorno do infra
int ledInfra = 13; //pino do led do infra

int obstacle; //variável que recebe o valor lógico do IR
int indexOut, indexIn; //variáveis auxiliares
int atraso =  10; //variável para delay em ms usada na rotina
int isObstacle = HIGH; // define obstáculo
int isObstaclePin = 6; // define pino para obstáculo
int LED = 13;

char answer = 99; //resposta da tag posicionada

int debuguer = 1; //variável para debugar

//valores lógicos para os passos no sentido horário
int ponteHtableHorario[4][4] = {{0,1,1,0},{0,1,0,1},{1,0,0,1},{1,0,1,0}};

//valores lógicos para os passos no sentido anti-horário
int ponteHtableNHorario[4][4]= {{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0}};
                            
//setup
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  pinMode(obstacle, INPUT);
  pinMode(ledInfra, OUTPUT);
  for(indexOut = 0; indexOut < 4; indexOut ++){
    pinMode(pinsPonteH[indexOut], OUTPUT);//seta os pinos de saída para a ponte H
  }
}

//código a ser rodado em loop
void loop() {

  Serial.println("ENTREI NO LOOP PRINCIPAL");
  isObstacle = digitalRead(isObstaclePin);

  //Serial.println(debuguer);
  //obstacle = digitalRead(outputInfra);
  if(isObstacle == LOW){
    Serial.println(isObstacle);
    Serial.println("ENTREI NO LOOP DO LOW");
    for(indexOut = 0; indexOut < 800; indexOut ++){
      for(indexIn = 0; indexIn < 4; indexIn ++){
        digitalWrite(pinsPonteH[indexIn], ponteHtableHorario[indexOut%4][indexIn]);
        
      } 
      delay(atraso);
      
    }
   
  }
  Serial.print("Os dados estão corretos? \n 1 == S ou 0 == N \n");
  while(answer == 99){
    char answer = Serial.read();
    if(answer == 115 || answer == 83){
      Serial.println(answer);
      for(indexOut = 1; indexOut < 800; indexOut ++){
        for(indexIn = 0; indexIn < 4; indexIn ++){
        digitalWrite(pinsPonteH[indexIn], ponteHtableHorario[indexOut%4][indexIn]);
        }
        delay(atraso);
      }
      break;
    }
    if(answer == 110 || answer == 78){
      Serial.println(answer);
      Serial.println("to aqui");
      for(indexOut = 1; indexOut < 800; indexOut ++){
        for(indexIn = 0; indexIn < 4; indexIn ++){
        digitalWrite(pinsPonteH[indexIn], ponteHtableNHorario[indexOut%4][indexIn]);
        }
        delay(atraso);
      }
        
      break;
    }
    answer == 99;
  }
   //Serial.print("Os dados estão corretos? \n 1 == S ou 0 == N \n");
   //int resposta = Serial.read();
}
