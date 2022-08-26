#include <AccelStepper.h>
#include <IRremote.h>

int pins[] = {8,9,10,11}; //pinos da ponte H

//valores lógicos para os passos no sentido horário
int bobinasHorario[4][4] = {{1,0,0,1},
                            {0,1,0,1},
                            {0,1,1,0},
                            {1,0,1,0}};

//valores lógicos para os passos no sentido anti-horário
int bobinasNhorario[4][4]= {{0,1,1,0},
                            {0,1,0,1},
                            {1,0,0,1},
                            {1,0,1,0}};
                            
int isObstacle = HIGH, isObstaclePin = 6, index, aux, atraso =  10;
//define obstaculo, pino no obstaculo, variável de índice 
int LED = 13;

//setup do programa
void setup(){
    Serial.begin(9600);
    pinMode(isObstaclePin, INPUT);
    pinMode(LED, OUTPUT);
    for(index = 0; index < 4; index ++){
      pinMode(pins[index], OUTPUT);//seta os pinos da ponte H como saídas
    }
}

//execução do programa
void loop() {
  
  isObstacle = digitalRead(isObstaclePin);
  
  if(isObstacle == LOW){
     for(index = 0; index < 4; index++){
       digitalWrite(pins[index], 0);
       delay(atraso);
     }
     
     Serial.print("TAG NO SENSOR");
     digitalWrite(LED, HIGH);
     //varia os valores nos terminais das bobinas
     //cada linha da matriz 'bobinas' representa um passo
     for(index = 0; index < 4; index++){
      //varia os pinos de IN1 -> IN4
      for(aux = 0; aux < 4 ; aux ++){
        digitalWrite(pins[aux], bobinasHorario[index][aux]);
      }
      delay(atraso);
     }
  }
  else{
     for(index = 0; index < 4; index++){
       digitalWrite(pins[index], 0);
       delay(atraso);
     };
     
     Serial.print("NÃO HÁ TAG NO SENSOR");
     digitalWrite(LED, LOW);
     //varia os valores nos terminais das bobinas
     //cada linha da matriz 'bobinas' representa um passo
     for(index = 0; index < 4; index++){
      //varia os pinos de IN1 -> IN4
      for(aux = 0; aux < 4 ; aux ++){
        digitalWrite(pins[aux], bobinasNhorario[index][aux]);
      }
      delay(atraso);
     }
  }
}
