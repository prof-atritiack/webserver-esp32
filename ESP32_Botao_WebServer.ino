/***********************************************************************
 * Projeto: Servidor Web ESP32 com Controle de GPIO (GPIO 2)
 * Autor: André Tritiack
 * Repositório: github.com/prof-atritiack/webserver-esp32
 * 
 * Este projeto demonstra como conectar o ESP32 a uma rede Wi-Fi
 * e controlar o estado do pino GPIO 2 através de uma interface web
 * com botões ON/OFF.
 * 
 * Baseado em exemplos do WiFiServer do core ESP32
 * e tutoriais da Random Nerd Tutorials.
 ***********************************************************************/

// Biblioteca já instalada
#include <WiFi.h>

// Credenciais da rede Wi-Fi
const char* ssid = "";
const char* password = "";

// Servidor Web rodando na porta 80
WiFiServer server(80);

// Estado inicial do LED
String estadoLED = "off";

// Pino do LED
const int pinoLED = 2;

// Controle de timeout da conexão
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  // Configura o pino como saída
  pinMode(pinoLED, OUTPUT);
  digitalWrite(pinoLED, LOW);

  // Conectar ao Wi-Fi
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Exibir dados da conexão
  Serial.println("");
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
  Serial.println("Acesse o IP acima no navegador");
  Serial.println("enquanto estiver na mesma rede local.");
  Serial.println("================================");

  // Inicia o servidor
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Novo cliente conectado.");
    String header = "";
    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Resposta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Controle do LED
            if (header.indexOf("GET /2/on") >= 0) {
              estadoLED = "on";
              digitalWrite(pinoLED, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              estadoLED = "off";
              digitalWrite(pinoLED, LOW);
            }

            // Página HTML estilizada
            client.println("<!DOCTYPE HTML><html lang=\"pt-br\">");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>");
            client.println("body { margin:0; font-family: Arial; background: linear-gradient(135deg,#74ebd5 0%,#ACB6E5 100%); text-align:center;}");
            client.println("h1 { color:#fff; margin:20px 0; font-size:2.5rem; text-shadow:1px 1px 4px rgba(0,0,0,0.3);}");
            client.println(".card { display:inline-block; background:#fff; padding:20px 40px; margin:20px; border-radius:15px; box-shadow:0 4px 15px rgba(0,0,0,0.2); min-width:200px;}");
            client.println(".card h2 { margin:10px 0; font-size:2rem; color:#444;}");
            client.println(".state { font-size:2rem; margin:15px 0;}");
            client.println(".button { background-color:#4CAF50; border:none; color:white; padding:16px 40px; font-size:20px; cursor:pointer; border-radius:10px;}");
            client.println(".button2 { background-color:#555555;}");
            client.println("</style></head><body>");
            client.println("<h1>Servidor Web ESP32 - Controle de LED</h1>");

            // Card LED
            client.println("<div class=\"card\">");
            client.println("<h2>LED no GPIO 2</h2>");
            client.println("<div class=\"state\">" + estadoLED + "</div>");
            if (estadoLED == "off") {
              client.println("<a href=\"/2/on\"><button class=\"button\">LIGAR</button></a>");
            } else {
              client.println("<a href=\"/2/off\"><button class=\"button button2\">DESLIGAR</button></a>");
            }
            client.println("</div>");

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
