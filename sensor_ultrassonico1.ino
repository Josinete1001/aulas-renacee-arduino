const int pingPin = ; // Pino único de sinal (SIG)
const int ledPin = ;   // Pino do LED
const int buzzerPin = ;// Pino do Buzzer

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long duracao;
  long distancia;

  // 1. Configura o pino como SAÍDA para emitir o pulso de disparo (Trigger)
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  // 2. Configura o MESMO pino como ENTRADA para ler o tempo de retorno (Echo)
  pinMode(pingPin, INPUT);
  duracao = pulseIn(pingPin, HIGH);

  // Calcula a distância em centímetros (velocidade do som: ~343 m/s)
  distancia = duracao / 29 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Exemplo de acionamento do alarme (quando menor que 20 cm)
  if (distancia > 0 && distancia <= ) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000); // Emite som no buzzer
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);     // Desliga o buzzer
  }

  delay(100);
}
