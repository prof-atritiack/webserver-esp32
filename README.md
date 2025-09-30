# WebServer ESP32

Este repositório reúne exemplos práticos de uso do **ESP32** como servidor web em diferentes aplicações.  
Os códigos `.ino` estão totalmente comentados e foram escritos com foco em fins **didáticos**, ideais para quem está aprendendo **IoT com ESP32**.

---

## Exemplos disponíveis

### 1. Servidor Web ESP32 com Monitoramento de Temperatura e Umidade (`ESP32_Sensor_WebServer.ino`)

Este exemplo mostra como usar o sensor **DHT11** com o ESP32 para medir temperatura e umidade.  
O ESP32 cria um servidor web que exibe os valores em tempo real em uma página HTML com atualização automática.

#### Estrutura do código

1. **Importação de bibliotecas**
   ```cpp
   #include <WiFi.h>
   #include <WebServer.h>
   #include <DHT.h>
   ```
   - `WiFi.h` → conexão do ESP32 com a rede Wi-Fi.  
   - `WebServer.h` → criação do servidor HTTP.  
   - `DHT.h` → leitura de temperatura e umidade.  

2. **Configuração do sensor**
   ```cpp
   #define DHTPIN 27
   #define DHTTYPE DHT11
   DHT dht(DHTPIN, DHTTYPE);
   ```
   - Define o **GPIO 27** como pino de dados.  
   - Define o tipo de sensor (DHT11, mas pode ser DHT22).  

3. **Conexão ao Wi-Fi**
   ```cpp
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
     Serial.print(".");
   }
   Serial.println(WiFi.localIP());
   ```
   - Conecta o ESP32 ao Wi-Fi.  
   - Mostra o **endereço IP** no **Monitor Serial** (use 115200 baud).  
   - Esse IP deve ser digitado no navegador.  

4. **Funções para leitura**
   ```cpp
   String readDHTTemperature() {
     float t = dht.readTemperature();
     return String(t);
   }

   String readDHTHumidity() {
     float h = dht.readHumidity();
     return String(h);
   }
   ```
   - Leem os valores do sensor.  
   - Retornam como `String` para exibição no HTML.  

5. **Interface Web**
   ```html
   <div class="card">
     <h2>Temperatura</h2>
     <div class="value" id="temperature">%TEMPERATURE%</div>
     <div class="units">&deg;C</div>
   </div>
   ```
   - Mostra temperatura e umidade em **cartões**.  
   - `%TEMPERATURE%` e `%HUMIDITY%` são substituídos no código pelo valor real.  

6. **Atualização automática (JavaScript)**
   ```javascript
   setInterval(function () {
     fetch("/temperature")
       .then(r => r.text())
       .then(data => document.getElementById("temperature").innerHTML = data);
   }, 5000);
   ```
   - Faz requisições a cada 5 segundos para atualizar os valores sem recarregar a página.  

---

### 2. Servidor Web ESP32 com Controle de LED (`ESP32_Botao_WebServer.ino`)

Este exemplo permite **ligar e desligar um LED** conectado ao **GPIO 2** via página web.  
É ideal para aprender como controlar **saídas digitais** pelo navegador.

#### Estrutura do código

1. **Importação de bibliotecas**
   ```cpp
   #include <WiFi.h>
   ```
   - Apenas a biblioteca de Wi-Fi é necessária.  

2. **Definições iniciais**
   ```cpp
   const int pinoLED = 2;
   String estadoLED = "off";
   ```
   - Define o **GPIO 2** como saída.  
   - Usa `estadoLED` para armazenar o estado atual (ligado/desligado).  

3. **Conexão ao Wi-Fi**
   ```cpp
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   Serial.println(WiFi.localIP());
   ```
   - Mesmo processo do exemplo anterior.  

4. **Controle via requisições**
   ```cpp
   if (header.indexOf("GET /2/on") >= 0) {
     estadoLED = "on";
     digitalWrite(pinoLED, HIGH);
   } else if (header.indexOf("GET /2/off") >= 0) {
     estadoLED = "off";
     digitalWrite(pinoLED, LOW);
   }
   ```
   - Se a URL acessada for `/2/on`, liga o LED.  
   - Se for `/2/off`, desliga.  

5. **Interface Web**
   ```html
   <div class="card">
     <h2>LED no GPIO 2</h2>
     <div class="state">off</div>
     <a href="/2/on"><button class="button">LIGAR</button></a>
   </div>
   ```
   - Mostra o estado atual do LED.  
   - Inclui botões para ligar/desligar.  

6. **Estilo da página**
   ```css
   body {
     background: linear-gradient(135deg,#74ebd5 0%,#ACB6E5 100%);
     text-align: center;
   }
   .button {
     background-color: #4CAF50;
     padding: 16px 40px;
     color: white;
     font-size: 20px;
     border-radius: 10px;
   }
   .button2 { background-color: #555555; }
   ```
   - Define layout simples e responsivo.  
   - Botões verdes para **ligar**, cinzas para **desligar**.  

---

## Como usar

1. Abra a **Arduino IDE**.  
2. Instale o **ESP32 Core** (via Board Manager).  
3. Instale as bibliotecas necessárias:  
   - [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library) (apenas para o exemplo do sensor).  
4. Carregue o código `.ino` do exemplo desejado.  
5. Abra o **Monitor Serial** em **115200 baud**.  
6. Copie o **endereço IP** exibido e cole no navegador conectado à mesma rede Wi-Fi.  

---

## Estrutura do Repositório

```
webserver-esp32/
│
├── ESP32_Sensor_WebServer/
│   └── ESP32_Sensor_WebServer.ino
│
├── ESP32_Botao_WebServer/
│   └── ESP32_Botao_WebServer.ino
│
└── README.md
```

---

## Referências

- [Random Nerd Tutorials – ESP32 Projects](https://randomnerdtutorials.com/projects-esp32/)  
- [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)  
- [Documentação oficial ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)  
- ChatGPT (OpenAI) – apoio na documentação e padronização.  

---

## Autor

Projetos desenvolvidos por **André Tritiack** para fins didáticos em **IoT e Web Servers com ESP32**.
