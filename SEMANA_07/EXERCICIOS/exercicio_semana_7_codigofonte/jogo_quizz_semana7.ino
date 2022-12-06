#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define led_verde  7
#define led_vermelho 4

int ponto1 = 0;
int ponto2 = 0;

int qntperg = 0;

const char *ssid = "Teste.com.br"; //Digite o nome da sua rede aqui
const char *password = "SenhaForte"; //Digite a senha da rede, deve conter no mínimo 8 caractéres se não dá erro.

WebServer server(80);

void setup() {

  Serial.begin(115200);

  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  WiFi.softAP(ssid, password); // remova "password" caso não queria que o Wi-Fi tenha senha
  IPAddress ESP_IP = WiFi.softAPIP();
  Serial.print("Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("IP: "); // O IP que aparecer aqui coloque no navegador para acessar a página web do ESP32 que será criada logo abaixo.
  Serial.println(ESP_IP);
  server.begin();
  Serial.println("Servidor Iniciado.");
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
  void handleRoot(){
    String html = "";
    html += "<meta charset='UTF-8'>";
    html += "<body style='background: linear-gradient(90deg, rgba(91,30,159,1) 0%, rgba(77,39,182,1) 100%);'>";
    html += "<h1 style=' color: white; padding: 36px 50px; margin-top: 30px; margin-left: 50px;'>Jogador 1</h1>";
    html += "<h1 style=' color: white; padding: 36px 50px; margin-top: -60px; margin-left: 50px;'>Pontos: ";
    html += ponto1;
    html += "</h1>";
    html += "<h1 style=' color: white; padding: 36px 50px; margin-top: -200px; margin-left: 950px;'>Jogador 2</h1>";
    html += "<h1 style=' color: white; padding: 36px 50px; margin-top: -65px; margin-left: 950px;'>Pontos: ";
    html += ponto2;
    html += "</h1>";
    html += "<h1 style='color: white; padding: 36px 50px; margin-top: 30px; margin-left: 450px;'>Quizz matemático</h1>";
    html += "<h2 style='color: white; margin-left: 540px';> 1) Quanto é 2 X 8? </h2> <br><br><br>";
    html += "<h2><a href=\"/on\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 16</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 24</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 8</a></h2><br><br><br>";
    
    html += "<h2 style='color: white; margin-left: 540px';> 2) Quanto é 2 X 48? </h2> <br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 196</a></h2><br><br><br>";
    html += "<h2><a href=\"/on\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 96</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 156</a></h2><br><br><br>";

    html += "<h2 style='color: white; margin-left: 540px';> 3) Quanto é 4 X 12? </h2> <br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 42</a></h2><br><br><br>";
    html += "<h2><a href=\"/on\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 48</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 54</a></h2><br><br><br>";

    html += "<h2 style='color: white; margin-left: 540px';> 4) Quanto é 3 X 13? </h2> <br><br><br>";
    html += "<h2><a href=\"/on\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>A) 39</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>B) 33</a></h2><br><br><br>";
    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 550px;'>C) 49</a></h2><br><br><br>";

    html += "<h2><a href=\"/off\" style='background-color: gray; border: none; color: white; padding: 16px 40px; margin-left: 485px;'>Finalizar Partida</a></h2><br><br><br>";
    
    html += "<h3>Autores: Larissa </h3>";
    html += "</body>";
    server.send(200, "text/html", html);
  }

  void handleOn(){
    if(qntperg >= 4){
    digitalWrite(led_verde, HIGH);
    ponto2 += 1;
    qntperg += 1;
    delay(2000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    handleRoot();
    } else{    
    digitalWrite(led_verde, HIGH);
    ponto1 += 1;
    qntperg += 1;
    delay(2000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    handleRoot();
    }
  }
  void handleOff(){
    digitalWrite(led_vermelho, HIGH);
    delay(2000);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_verde, LOW);
    qntperg +=1;
    handleRoot();
  }
  void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; 
  }
  server.send(404, "text/plain", message);
}

void loop() {
  server.handleClient();
  if (qntperg >= 8){
    delay(2000);
    ponto1 = 0;
    ponto2 = 0;
    qntperg = 0;
    delay(2000); 
  }
  delay(2);
} 