int ledverm = 10;
int ledamar = 9;
int ledverd = 8;
int ledazul = 6;
int buzzer = 20;
int ldr = 13;
int botao1 = 1;
int botao2 = 48;

int normalizedValue;
int contadorNum = 0;

int binarioArray[4] = {0, 0, 0, 0};
int numerosCompletos[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  pinMode(ledverm, OUTPUT);
  pinMode(ledamar, OUTPUT);
  pinMode(ledverd, OUTPUT);
  pinMode(ledazul, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
}

void tom(char BUZZER, int freq, int duracao) {
  float tempo = 1000.0/freq;
  for (int i = 0; i < duracao/(tempo); i++){
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(tempo*500);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(tempo*500);
  }
}

int normalize(int valorAtual) {
  int valorNovo = (valorAtual * 15)/ 2670;
  return valorNovo;
}

void binario(int decimal) {
  for(int i = 0; decimal>0; i++)
  {
    binarioArray[i] = decimal%2;
    decimal = decimal/2;
  }
}
void som(int valor) {
  switch(valor)
  {
    case 0:
      tom(buzzer, 500, 500);
      break;
    case 1:
      tom(buzzer, 750, 500);
      break;
    case 2:
      tom(buzzer, 1000, 500);
      break;
    case 3:
      tom(buzzer, 1250, 500);
      break;
    case 4:
      tom(buzzer, 1500, 500);
      break;
    case 5:
      tom(buzzer, 1750, 500);
      break;
    case 6:
      tom(buzzer, 2000, 500);
      break;
    case 7:
      tom(buzzer, 2250, 500);
      break;
    case 8:
      tom(buzzer, 2500, 500);
      break;
    case 9:
      tom(buzzer, 2750, 500);
      break;
    case 10:
      tom(buzzer, 3000, 500);
      break;
    case 11:
      tom(buzzer, 3250, 500);
      break;
    case 12:
      tom(buzzer, 3500, 500);
      break;
    case 13:
      tom(buzzer, 3750, 500);
      break;
    case 14:
      tom(buzzer, 4000, 500);
      break;
    case 15:
      tom(buzzer, 4250, 500);
      break;
  }
}

void ligarLeds()
{
  digitalWrite(ledverm, binarioArray[3]);
  digitalWrite(ledamar, binarioArray[2]);
  digitalWrite(ledverd, binarioArray[1]);
  digitalWrite(ledazul, binarioArray[0]);
  delay(200);
  digitalWrite(ledverm, LOW);
  digitalWrite(ledamar, LOW);
  digitalWrite(ledverd, LOW);
  digitalWrite(ledazul, LOW);
  binarioArray[0] = 0;
  binarioArray[1] = 0;
  binarioArray[2] = 0;
  binarioArray[3] = 0;
}

void loop() {
  int BOTAO1INPUT = digitalRead(botao1);
  int BOTAO2INPUT = digitalRead(botao2);
  if (BOTAO1INPUT == 1)
  {
    if (contadorNum < 10)
    {
      Serial.println("lido");
      int ldrValor = analogRead(ldr);
      normalizedValue = normalize(ldrValor);
      numerosCompletos[contadorNum] = normalizedValue;
      contadorNum += 1;
      binario(normalizedValue);
      som(normalizedValue);
      ligarLeds();
    }
    else
    {
      tom(buzzer, 5000, 500);
      delay(250);
      tom(buzzer, 5000, 500);
      delay(250);
      tom(buzzer, 5000, 500);
    }
  }
  if (BOTAO2INPUT == 1)
  {
    Serial.println("tocou som");
    executar();
  }
}

void executar() {
  for (int i = 0; i < (contadorNum); i++)
  {
    som(numerosCompletos[i]);
    binario(numerosCompletos[i]);
    ligarLeds();
  }
  contadorNum = 0;
}