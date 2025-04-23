#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço do display I2C

const int botaoJanelaPin = 2; // Pino do 1º botão que simula janela aberta
const int botaoPortaPin = 3; // Pino do 2º botão que simula porta aberta
const int piezoPin = 8; // Pino do Piezo
const int ledPin = 9; // Pino do LED

const int sensorPirPin = A0; // Pino analógico do sensor PIR
const int fotorresistorPin = A1; // Pino analógico do fotorresistor

bool alarmeStatus = false; // Variável para controlar se o alarme está ativo

void setup() {
  lcd.init(); // Inicializa o display LCD
  lcd.backlight(); // Liga a luz do display
  
  pinMode(sensorPirPin, INPUT); // Configura o pino do sensor PIR como entrada
  pinMode(piezoPin, OUTPUT); // Configura o pino do Piezo como saída
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
  pinMode(fotorresistorPin, INPUT); // Configura o pino do fotorresistor como entrada
  pinMode(botaoJanelaPin, INPUT_PULLUP); // Configura o pino do botão Janela como entrada com pull-up interno
  pinMode(botaoPortaPin, INPUT_PULLUP); // Configura o pino do botão Porta como entrada com pull-up interno
}

void loop() {
  int sensorStatus = digitalRead(sensorPirPin);
  int alertaJanela = digitalRead(botaoJanelaPin);
  int alertaPorta = digitalRead(botaoPortaPin);
  
  // Verifica se é noite
  bool noite = verificacaoDoPeriodo();
  if(noite){
    ligarAlarme();
  } else {
  	desligarAlarme();
  }
  
  // Verifica o sensor de movimento
  if (sensorStatus == HIGH && noite) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ATENCAO!");
    lcd.setCursor(0, 1);
    lcd.print("Mov. Detectado"); 
  	soarAlarme();
    delay(1000);
    lcd.clear();
  }
  // Verifica alerta da janela
  if (alertaJanela == LOW && noite) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ATENCAO!");
    lcd.setCursor(0, 1);
    lcd.print("Janela Aberta");
    soarAlarme();
    lcd.clear();
  }
  // Verifica alerta da Porta
  if (alertaPorta == LOW && noite) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ATENCAO!");
    lcd.setCursor(0, 1);
    lcd.print("Porta Aberta");
  	soarAlarme();
    lcd.clear();
  }
  
  // Delay para estabilizar leituras
  delay(100);
}

void ligarAlarme(){
    alarmeStatus = true;
    lcd.setCursor(0, 0);
    lcd.print("Alarme ligado!  ");
    lcd.setCursor(0, 1);
    lcd.print("Operando..."); 
}

void desligarAlarme() {
    alarmeStatus = false;
    lcd.setCursor(0, 0);
    lcd.print("Alarme Desligado");
    lcd.setCursor(0, 1);
    lcd.print("Inoperante "); 
}

void soarAlarme() {
  if (alarmeStatus) {
    tone(piezoPin, 2000); // Ativar som
    digitalWrite(ledPin, HIGH); // Ativar LED
    delay(1000); // Duração do alarme
    noTone(piezoPin); // Desativar som
    digitalWrite(ledPin, LOW); // Desativar LED
  }
}

bool verificacaoDoPeriodo() {
  // Lê o valor do fotorresistor
  int sensorLuz = analogRead(fotorresistorPin);
  
  // Se o valor lido for menor que um determinado limite, é considerado noite
  // Este limite pode ser ajustado conforme necessário
  return (sensorLuz > 500);
}
