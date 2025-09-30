/***********************************************************************
 * Projeto: Servidor Web ESP32 com Monitoramento de Temperatura e Umidade
 * Autor: André Tritiack
 * Repositório: github.com/prof-atritiack/esp32-dht-webserver
 * 
 * Este projeto exemplifica como conectar o ESP32 a uma rede Wi-Fi,
 * ler dados do sensor DHT11 (temperatura e umidade) e exibi-los
 * em uma página web hospedada no próprio microcontrolador.
 * 
 * Baseado em exemplos do WebServer do core ESP32,
 * tutoriais da Random Nerd Tutorials e documentação da Adafruit DHT.
 ***********************************************************************/

// Bibliotecas já incluídas
#include <WiFi.h>           // Biblioteca para conectar o ESP32 ao Wi-Fi
#include <WebServer.h>      // Biblioteca do servidor web nativo do ESP32

// Biblioteca a instalar
#include <DHT.h>            // Biblioteca do sensor DHT

// Configuração da rede Wi-Fi
const char* ssid = "";       
const char* password = "";  

// Configuração do sensor DHT
#define DHTPIN 27        // Pino de dados conectado ao ESP32
#define DHTTYPE DHT11    // Tipo do sensor (DHT11 ou DHT22)
DHT dht(DHTPIN, DHTTYPE);

// Criação do servidor web na porta 80
WebServer server(80);

// Função para ler a temperatura do sensor
String readDHTTemperature() {
  // float t = dht.readTemperature();   // Lê a temperatura em Celsius
  // float t = random(200, 500)/ 10.0;
  Serial.print("Temperatura: ");
  Serial.println(t);                 
  return String(t);                  // Retorna como string
}

// Função para ler a umidade do sensor
String readDHTHumidity() {
  // float h = dht.readHumidity();      // Lê a umidade relativa (%)
  // float h = random(0, 800)/ 10.0;
  Serial.print("Umidade: ");
  Serial.println(h);                 
  return String(h);
}

// Página HTML que será exibida no navegador
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="pt-br">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      margin: 0;
      font-family: Arial, Helvetica, sans-serif;
      background: linear-gradient(135deg, #74ebd5 0%, #ACB6E5 100%);
      color: #333;
      text-align: center;
    }
    h1 {
      margin: 20px 0;
      font-size: 2.5rem;
      color: #fff;
      text-shadow: 1px 1px 4px rgba(0,0,0,0.3);
    }
    .card {
      display: inline-block;
      background: #fff;
      padding: 20px 40px;
      margin: 20px;
      border-radius: 15px;
      box-shadow: 0 4px 15px rgba(0,0,0,0.2);
      min-width: 200px;
    }
    .card h2 {
      margin: 10px 0;
      font-size: 2rem;
      color: #444;
    }
    .value {
      font-size: 3rem;
      font-weight: bold;
      color: #059e8a;
    }
    .units {
      font-size: 1.2rem;
      color: #777;
    }
  </style>
</head>
<body>
  <h1>Servidor ESP32 - Monitor de Temperatura e Umidade</h1>

  <div class="card">
    <h2>Temperatura</h2>
    <div class="value" id="temperature">%TEMPERATURE%</div>
    <div class="units">&deg;C</div>
  </div>

  <div class="card">
    <h2>Umidade</h2>
    <div class="value" id="humidity">%HUMIDITY%</div>
    <div class="units">%</div>
  </div>

<script>
// Atualiza a temperatura a cada 5 segundos
setInterval(function () {
  fetch("/temperature")
    .then(r => r.text())
    .then(data => document.getElementById("temperature").innerHTML = data);
}, 5000);

// Atualiza a umidade a cada 5 segundos
setInterval(function () {
  fetch("/humidity")
    .then(r => r.text())
    .then(data => document.getElementById("humidity").innerHTML = data);
}, 5000);
</script>
</body>
</html>
)rawliteral";

// Página principal "/"
void handleRoot() {
  String html = index_html;
  html.replace("%TEMPERATURE%", readDHTTemperature());
  html.replace("%HUMIDITY%", readDHTHumidity());
  server.send(200, "text/html", html);
}

// Rota que devolve apenas a temperatura
void handleTemperature() {
  server.send(200, "text/plain", readDHTTemperature());
}

// Rota que devolve apenas a umidade
void handleHumidity() {
  server.send(200, "text/plain", readDHTHumidity());
}

void setup() {  
  Serial.begin(115200);   // Inicializa o monitor serial
  dht.begin();            // Inicializa o sensor DHT
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Conectando à rede Wi-Fi: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Informações da conexão
  Serial.println();
  Serial.println("================================");
  Serial.println(" ESP32 conectado à rede Wi-Fi ");
  Serial.println("================================");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("--------------------------------");
  Serial.println("Acesse o IP acima no seu navegador");
  Serial.println("enquanto estiver na mesma rede local.");
  Serial.println("================================");

  // Define as rotas
  server.on("/", handleRoot);
  server.on("/temperature", handleTemperature);
  server.on("/humidity", handleHumidity);

  // Inicia o servidor
  server.begin();
}

void loop() {
  server.handleClient();  // Mantém o servidor respondendo
}
