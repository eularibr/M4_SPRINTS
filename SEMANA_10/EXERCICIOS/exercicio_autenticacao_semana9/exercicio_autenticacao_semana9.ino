#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String senhaRegistro = "";
String senhaAutenticacao = "";

void registro() {
  lcd.clear();
  Serial.println("Digite uma senha de 4 dígitos:");
  while (Serial.available() == 0) {  
  } 
  senhaRegistro = Serial.readString();
  if ((senhaRegistro.length() - 1) != 4) {
    Serial.println("Senha inválida, a senha deve conter 4 dígitos!");
    registro();
  }
  else {
    Serial.println("Cadastro realizado!");
    Serial.println(" ");
    Serial.println("Autenticação");
    Serial.println(" ");
    autenticacao();
  }
}

void autenticacao() {
  lcd.clear();
  Serial.println("Insira a senha de 4 dígitos:");
  while (Serial.available() == 0) {  
  } 
  senhaAutenticacao = Serial.readString();
  if (senhaAutenticacao == senhaRegistro) {
    lcd.print("Senha correta!");
    neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0);
    delay(1000);
    digitalWrite(RGB_BUILTIN, LOW);
    Serial.println(" ");
    Serial.println("Cadastro");
    Serial.println(" ");
    registro();
  }
  else {
    lcd.print("Senha incorreta!");
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0);
    delay(2000);
    digitalWrite(RGB_BUILTIN, LOW);
    autenticacao();
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);
  pinMode(RGB_BUILTIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  digitalWrite(RGB_BUILTIN, LOW);
  Serial.println(" ");
  Serial.println("Cadastro");
  Serial.println(" ");
  registro();
}