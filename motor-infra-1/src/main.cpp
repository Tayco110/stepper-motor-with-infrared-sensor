#include <Arduino.h>
// #include <AccelStepper.h>
// #include <IRremote.h>

int pinsPonteH[] = {8,9,10,11}; //pinos da ponte H
int outputInfra = 6; //pino de retorno do infra
int ledInfra = 13; //pino do led do infra

int obstacle; //variável que recebe o valor lógico do IR
int indexOut, indexIn; //variáveis auxiliares
int atraso =  100; //variável para delay em ms usada na rotina

char answer; //resposta da tag posicionada

int debuguer = 1; //variável para debugar

//valores lógicos para os passos no sentido horário
int ponteHtableHorario[4][4] = {{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0}};

//valores lógicos para os passos no sentido anti-horário
int ponteHtableNHorario[4][4]= {{0,1,1,0},{0,1,0,1},{1,0,0,1},{1,0,1,0}};
                            
//setup
void setup() {
  Serial.begin(9600);
  pinMode(obstacle, INPUT);
  pinMode(ledInfra, OUTPUT);
  for(indexOut = 0; indexOut < 4; indexOut ++){
    pinMode(pinsPonteH[indexOut], OUTPUT);//seta os pinos de saída para a ponte H
  }
}

//código a ser rodado em loop
void loop() {

  //Serial.println(debuguer);
  //obstacle = digitalRead(outputInfra);
  if(debuguer){
    for(indexOut = 0; indexOut < 4; indexOut ++){
      for(indexIn = 0; indexIn < 4; indexIn ++){
        digitalWrite(pinsPonteH[indexIn], ponteHtableNHorario[indexOut][indexIn]);
       
      }  
      delay(atraso);
    }
  }
}
