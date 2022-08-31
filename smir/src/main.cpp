#include <Arduino.h>
//pinos da ponte H (IN1, IN2, IN3, IN4)
int pinsPonteH[4] = {8,9,10,11};

//pinos do infra (IR1, IR2, IR3)
int pinsInfra[2] = {6,5};
//outputs do infra (IR1, IR2, IR3)
int outputInfra[2] = {LOW, LOW};

//valores lógicos para os passos no sentido horário
int ponteHtableHorario[4][4] = {{1,0,0,1},{0,1,0,1},{0,1,1,0},{1,0,1,0}};

//valores lógicos para os passos no sentido anti-horário
int ponteHtableNHorario[4][4] = {{0,1,1,0},{0,1,0,1},{1,0,0,1},{1,0,1,0}};

//valores lógicos para parar o motor
//int ponteHstop[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

//pino do led do infra
int ledInfra = 13;
//variáveis auxiliares
int indexHtable, indexHPins, indexIR;
//variável para o delay em ms usada na rotina
int atraso =  5;
//resposta da condição da tag com um valor de controle
char answer = 99;

//setup
void setup(){
  Serial.begin(9600);
  pinMode(ledInfra, OUTPUT);
  
  //define os pinos da ponte H como output
  for(indexHPins = 0; indexHPins < sizeof(pinsPonteH); indexHPins++){
    pinMode(pinsPonteH[indexHPins], OUTPUT);
  }

  //define os pinos dos sensores IR como entrada
  for(indexIR = 0; indexIR < sizeof(pinsInfra); indexIR++){
    pinMode(pinsInfra[indexIR], INPUT);
  }
}

//função para mover o motor em função de theta (sentido horário == 1, antihorário == 0)
void steps (int k, int drct){

  if(drct == 1){
    for(indexHtable = 0; indexHtable < (4*k); indexHtable++){
      for(indexHPins = 0; indexHPins < 4; indexHPins++){
        //escreve os valores lógicos K vezes para girar o motor 
        digitalWrite(pinsPonteH[indexHPins], ponteHtableHorario[indexHtable%4][indexHPins]);
      } 
    delay(5);
    }
  }
  else if(drct == 0){
    for(indexHtable = 0; indexHtable < (4*k); indexHtable++){
      for(indexHPins = 0; indexHPins < 4; indexHPins++){
        //escreve os valores lógicos K vezes para girar o motor 
        digitalWrite(pinsPonteH[indexHPins], ponteHtableNHorario[indexHtable%4][indexHPins]);
      } 
    delay(5);
    }
  }
  else{
    return; 
  }
}

//função para parar o motor
void stopSteps (){
  for(indexHPins = 0; indexHPins < 4; indexHPins++){
    digitalWrite(pinsPonteH[indexHPins], 0);//escreve 0 em todos os pinos
  } 
  delay(10);
}

//função temporária para fazer o check na tag
bool tagCheck(){
  bool rtn;
  Serial.print("Os dados estão corretos? \n S/s ou  N/n \n");
  while(answer == 99){
    answer = Serial.read();//aguarda a resposta do usuário
    if(answer == 115 || answer == 83){//S ou s em unicode
      rtn = true;
      Serial.println(answer);
      answer = 99;
      break;
    }
    else if(answer == 110 || answer == 78){// N ou n em unicode
      rtn = false;
      Serial.println(answer);
      answer = 99;
      break;
    }
    answer = 99;//c em unicode (variável de controle)
  }
  return rtn;
}

//código a ser rodado em loop
void loop() {

  //verifica se o rolo está posicionado no sensor 
  outputInfra[0] = digitalRead(pinsInfra[0]);

  //se não houver rolo o motor permanece parado aguardando o posicionamento
  if(outputInfra[0] == HIGH){
    stopSteps();
  }
  //se houver rolo
  else if(outputInfra[0] == LOW){
    //garante que o motor esteja parado
    stopSteps();
    //leva o rolo de tags do ponto A até o ponto B (ponto B == camera)
    steps(200, 1);
    //Se no ponto B a tag estiver OK
    if(tagCheck()){
      //mude o passo para avançar de tag em tag
      while (1)
      {
        steps(100,1);
        delay(1000);
      }
    }
    //Se no ponto B a tag não estiver OK
    else{
      //garanta que o motor esta parado
      stopSteps();
      //rebobine para a posição inicial para trocar o rolo
      steps(200, 0);
    }
  }
}