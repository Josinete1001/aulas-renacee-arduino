
/*
  JOGO DA MEMORIA 
*/

const int LED_R = 2;
const int LED_G = 3;
const int LED_B = 4;

const int BOTAO_R = 8;
const int BOTAO_G = 9;
const int BOTAO_B = 10;

const int POTENCIOMETRO = A0;

const int MAX_SEQUENCIA = 50;

int sequencia[MAX_SEQUENCIA];
int rodada = 1;

int leds[3] = {LED_R, LED_G, LED_B};
int botoes[3] = {BOTAO_R, BOTAO_G, BOTAO_B};

int tempoLED;
int tempoPausa;

// Configura os componentes
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A1));

  // Apresentacao inicial
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], HIGH);
  }

  delay(700);

  apagarLEDs();
}

// Repete o jogo continuamente
void loop() {
  if (rodada > MAX_SEQUENCIA) {
    rodada = 1;
  }

  // Sorteia uma nova cor para esta rodada
  sequencia[rodada - 1] = random(0, 3);

  // Mostra a sequencia
  mostrarSequencia();

  // Recebe e confere as respostas
  for (int i = 0; i < rodada; i++) {
    int resposta = esperarBotao();

    if (resposta != sequencia[i]) {
      fimDeJogo();
      rodada = 1;
      delay(500);
      return;
    }
  }

  // Acertou: aumenta a dificuldade
  rodada++;

  delay(500);
}

// Apaga todos os LEDs
void apagarLEDs() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// Acende uma cor por determinado tempo
void piscarLED(int cor) {
  int valorPot = analogRead(POTENCIOMETRO);

  // Ajusta a velocidade pelo potenciometro
  tempoLED = map(valorPot, 0, 1023, 150, 1000);
  tempoPausa = tempoLED / 2;

  digitalWrite(leds[cor], HIGH);
  delay(tempoLED);

  digitalWrite(leds[cor], LOW);
  delay(tempoPausa);
}

// Mostra a sequencia atual
void mostrarSequencia() {
  delay(500);

  for (int i = 0; i < rodada; i++) {
    piscarLED(sequencia[i]);
  }
}

// Espera o jogador pressionar um botao
int esperarBotao() {
  while (true) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        delay(30);

        if (digitalRead(botoes[i]) == LOW) {
          piscarLED(i);

          // Espera o botao ser solto
          while (digitalRead(botoes[i]) == LOW) {
            delay(10);
          }

          return i;
        }
      }
    }
  }
}

// Indica que o jogador errou
void fimDeJogo() {
  for (int repeticao = 0; repeticao < 3; repeticao++) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], HIGH);
    }

    delay(300);
    apagarLEDs();
    delay(300);
  }
}
