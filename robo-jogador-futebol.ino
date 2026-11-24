#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// Pinos da Ponte H L298N (mantendo as correções físicas já validadas)
const int IN1 = 8;   // Motor Esquerdo Frente
const int IN2 = 7;   // Motor Esquerdo Trás
const int IN3 = 9;   // Motor Direito Frente
const int IN4 = 10;  // Motor Direito Trás

void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moverFrente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moverRe() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Lógica de Giro validada para o robô virar à esquerda
void girarEsquerda() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Lógica de Giro validada para o robô virar à direita
void girarDireita() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(9600);
  
  // Inicializa o Dabble no BT05 nos pinos D2 (RX) e D3 (TX) a 9600 baud
  Dabble.begin(9600, 2, 3);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pararMotores();

  Serial.println(F("========================================"));
  Serial.println(F(" Robô de Futebol - Pronto no Dabble"));
  Serial.println(F(" Use o Gamepad (Digital Mode) no App"));
  Serial.println(F("========================================"));
}

void loop() {
  // Processa os pacotes recebidos do app Dabble
  Dabble.processInput();

  // Modo contínuo: mantém o movimento enquanto o botão for pressionado
  if (GamePad.isUpPressed()) {
    moverFrente();
  }
  else if (GamePad.isDownPressed()) {
    moverRe();
  }
  else if (GamePad.isLeftPressed()) {
    girarEsquerda();
  }
  else if (GamePad.isRightPressed()) {
    girarDireita();
  }
  else {
    // Para imediatamente assim que você solta o botão no app
    pararMotores();
  }
}
