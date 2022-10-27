//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 6;
int IN2 = 7;

int PinTrigger = 4; // Pino usado para disparar os pulsos do sensor
int PinEcho = 5; // pino usado para ler a saida do sensor
float TempoEcho = 0;
const float VelocidadeSom_mpors = 340; // em metros por segundo
const float VelocidadeSom_mporus = 0.000340; // em metros por microsegundo
  
void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(PinTrigger, OUTPUT);
 digitalWrite(PinTrigger, LOW);
 pinMode(PinEcho, INPUT); // configura pino ECHO como entrada
 Serial.begin(9600);
}

// Funçao para enviar o pulso de trigger
void DisparaPulsoUltrassonico(){
  // Para fazer o HC-SR04 enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10us de duraçao
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

// Função para calcular a distancia em metros
float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}
  
void loop()
{
  // Envia pulso para o disparar o sensor
  DisparaPulsoUltrassonico();
  // Mede o tempo de duração do sinal no pino de leitura(us)
  TempoEcho = pulseIn(PinEcho, HIGH);
  Serial.println(CalculaDistancia(TempoEcho)*100);
  if (CalculaDistancia(TempoEcho)*100 < 6.5){
    //Para o motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    //delay(50);
  }
  else{
    //Gira o Motor A no sentido anti-horario
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //delay(20);
  }
  //delay(50);
}
