 // Controle de motor - CNC Shield
// Definição dos pinos 
#define stepPin 2 //Passo eixo X
#define dirPin 5 // Direção eixo X

int PIR1 = 0;
int PIR2 = 0;
int flag_motor = 0;
int flag_stopMotor = 0;
 
 void setup() {
 // Definindo ambos os pinos acima como saída
   pinMode(stepPin,OUTPUT); 
   pinMode(dirPin,OUTPUT);
   pinMode(22, INPUT);
   pinMode(23, INPUT);
   Serial.begin(9600);
 }
 void loop() {
  PIR1 = digitalRead(22);
  PIR2 = digitalRead(23);
  if (PIR1 == LOW && PIR2 == HIGH){
    Serial.println(flag_motor);
    flag_motor = 1;
  }
  else if (PIR1 == HIGH){
    Serial.println(flag_motor);
    flag_motor = 0;
  }
  else if (PIR1 == LOW && PIR2 == LOW){
    Serial.println(flag_motor);
    flag_motor = 0;
    flag_stopMotor = 1;
  }
  if (flag_motor == 1 && flag_stopMotor == 0){
    digitalWrite(dirPin,HIGH);
    for(int x = 0; x < 1600; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
     }
  }
  
}
