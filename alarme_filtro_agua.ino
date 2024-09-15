// Definir os pinos do módulo RGB
const int pinR = 9; // Pino para a cor vermelha
const int pinG = 10; // Pino para a cor verde
const int pinB = 11; // Pino para a cor azul
int buzzer = 7;

// Definir os limites de contato
const int thresholdMagenta = 0.50 * 1023; // 50% do valor máximo
const int thresholdGreen = 0.10 * 1023;  // 10% para contato com a água em níveis baixos ou médios

// Armazenar o estado atual
int lastColor = -1;

void setup() {
  Serial.begin(9600);  // Inicializar comunicação serial

  // Configurar os pinos do módulo RGB como saída
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {
  
  int value = analogRead(A0);  // Ler o valor do sensor analógico na porta A0

  // Exibir o valor no Serial Monitor
  Serial.println(value);

  // Definir a cor com base no nível de água
  int newColor;
  if (value >= thresholdMagenta) {
    newColor = 2; // Magenta para alto contato com a água (50% ou mais)
  } else if (value > thresholdGreen) {
    newColor = 1; // Verde para contato com a água em níveis baixos ou médios
  } else {
    newColor = 0; // Vermelho para ausência de contato com a água
    tone(buzzer, 3000);  // Emite um som de 1000Hz
    delay(1000);         // Espera 1 segundo
    noTone(buzzer);      // Para o som
    delay(1000);         // Espera 1 segundo antes de repetir
  
  }

  // Alterar a cor apenas se o estado atual mudar
  if (newColor != lastColor) {
    if (newColor == 0) {
      setColor(255, 0, 0); // Vermelho
    } else if (newColor == 1) {
      setColor(0, 255, 0); // Verde
    } else if (newColor == 2) {
      setColor(255, 0, 255); // Magenta
    }
    lastColor = newColor;
  }

  delay(200); // Atraso para leitura estável
}

// Função para definir a cor do módulo RGB
void setColor(int red, int green, int blue) {
  analogWrite(pinR, red);   // Ajustar intensidade da cor vermelha
  analogWrite(pinG, green); // Ajustar intensidade da cor verde
  analogWrite(pinB, blue);  // Ajustar intensidade da cor azul
}
