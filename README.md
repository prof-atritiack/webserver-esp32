# Servidor Web ESP32 com Monitoramento de Temperatura e Umidade

Este projeto utiliza o ESP32 em conjunto com o sensor DHT11 para medir temperatura e umidade em tempo real.  
Os dados são exibidos em uma página web hospedada no próprio microcontrolador, acessível através do navegador via endereço IP local.

---

## Funcionalidades

- Conexão do ESP32 ao Wi-Fi.  
- Leitura contínua de temperatura (°C) e umidade relativa (%).  
- Página web responsiva com interface em HTML + CSS.  
- Atualização automática dos valores a cada 5 segundos via JavaScript (Fetch API).  
- Rotas dedicadas para acesso direto aos dados:  
  - `/` → Página principal com painel visual.  
  - `/temperature` → Retorna apenas a temperatura.  
  - `/humidity` → Retorna apenas a umidade.  

---

## Requisitos

- Placa ESP32 (DOIT ESP32 DEVKIT V1 ou similar).  
- Sensor DHT11 (ou DHT22, alterando a configuração no código).  
- Arduino IDE instalado e atualizado.  
- Bibliotecas necessárias:  
  - [WiFi](https://github.com/espressif/arduino-esp32) (já incluída no core ESP32).  
  - [WebServer](https://github.com/espressif/arduino-esp32) (já incluída no core ESP32).  
  - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library).  

---

## Estrutura do Projeto

```
ESP32-DHT-WebServer/
│
├── ESP32_DHT_WebServer.ino   # Código principal do projeto
└── README.md                 # Documentação
```

---

## Trechos Principais do Código

### Conexão ao Wi-Fi com informações detalhadas

```cpp
WiFi.begin(ssid, password);
Serial.println();
Serial.print("Conectando à rede Wi-Fi: ");
Serial.println(ssid);

while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
}

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
```

Esse trecho conecta o ESP32 à rede, mostra no monitor serial o **SSID**, o **endereço IP** atribuído e o **MAC address** do dispositivo.  
O IP exibido deve ser usado no navegador para acessar a página do servidor.  

### Definição das rotas do servidor

```cpp
server.on("/", handleRoot);         // Página principal com HTML formatado
server.on("/temperature", handleTemperature);   // Retorna apenas a temperatura
server.on("/humidity", handleHumidity);         // Retorna apenas a umidade
```

Essas rotas permitem acessar a interface completa ou obter apenas os valores de temperatura e umidade.  

### Página Web exibida pelo ESP32

```html
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
```

Os valores `%TEMPERATURE%` e `%HUMIDITY%` são substituídos dinamicamente pelos dados do sensor.  

---

## Observação Importante

Ao inicializar o código, é necessário abrir o **Monitor Serial** da Arduino IDE configurado em **115200 baud**.  
O endereço IP atribuído ao ESP32 pela rede Wi-Fi será exibido ali.  
Esse IP é essencial para acessar o servidor web no navegador.  

---

## Referências e Créditos

- [Random Nerd Tutorials – ESP32 DHT11/DHT22 Web Server](https://randomnerdtutorials.com/esp32-dht11-dht22-web-server-arduino-ide/)  
- [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)  
- [Documentação oficial ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)  
- ChatGPT (OpenAI) – apoio na documentação e organização do código.  

---

## Autor

Projeto desenvolvido por André Tritiack para fins didáticos em IoT e Web Servers com ESP32.  
