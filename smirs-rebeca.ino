#include <AccelStepper.h>
#include <IRremote.h>

int IN1 = 8;   // seta os pinos da ponte h
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int isObstacle = HIGH; // define obstáculo
int isObstaclePin = 6; // define pino para obstáculo
int LED = 13;
void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT); // declara cada pino como saída
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}
int tempo = 10;// define tempo para movimentação do eixo
void loop()
{
isObstacle = digitalRead(isObstaclePin);
  //Passo 1
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo); 
  //Passo 2
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);
  //Passo 3
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);
  //Passo 4
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);

  if(isObstacle == LOW){ // verifica se há um obstáculo (tag) se aproximando e interrompe o funcionamento do motor
      
  //Serial.print("TAG DETECTADA");
  digitalWrite(LED, HIGH);
  //Passo 1
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(tempo); 
  //Passo 2
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(tempo);
  //Passo 3
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(tempo);
  //Passo 4
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(tempo);
  
  
        
    
}
  
    
}



**********************************************************************************

Sentido anti-horário

#include <AccelStepper.h>
#include <IRremote.h>

int IN1 = 8;   // seta os pinos da ponte h
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int isObstacle = HIGH; // define obstáculo
int isObstaclePin = 6; // define pino para obstáculo
int LED = 13;
void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT); // declara cada pino como saída
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}
int tempo = 10;// define tempo para movimentação do eixo
void loop()
{
isObstacle = digitalRead(isObstaclePin);
  //Passo 1
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo); 
  //Passo 2
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);
  //Passo 3
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);
  //Passo 4
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //delay(tempo);

  if(isObstacle == LOW){ // verifica se há um obstáculo (tag) se aproximando e interrompe o funcionamento do motor
      
  //Serial.print("TAG DETECTADA");
  digitalWrite(LED, HIGH);

// inverter 
  //Passo 3
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(tempo);
  //Passo 2
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(tempo);
  
  //Passo 1
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  delay(tempo); 
 
   //Passo 4
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  delay(tempo);
  } 
}
