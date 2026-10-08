const byte PIN_TRIG = ;   // Pino de disparo (trigger)
const byte PIN_ECO  = ;   // Pino de eco (echo)
const byte PIN_LED  = ;    // Pino do LED
const byte PIN_BUZ  = ;    // Pino da buzina (buzzer)

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZ, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Geração do pulso ultrassônico
  digitalWrite(PIN_TRIG, HIGH);
  delay(1);
  digitalWrite(PIN_TRIG, LOW);

  // Leitura do eco e conversão para centímetros
  long duracao = pulseIn(PIN_ECO, HIGH);
  int distancia = duracao / 58.2;

  // Exibição no monitor serial
  Serial.print("DISTANCIA: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(200);

  // Alerta proporcional (entre 0 e 40 cm)
  if (distancia >= 0 && distancia <= ) {
    int tempoEspera = distancia * 10;

    // Liga LED e Buzina juntos
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_BUZ, HIGH);
    delay(tempoEspera);

    // Desliga LED e Buzina juntos
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZ, LOW);
    delay(tempoEspera);
  }
}
