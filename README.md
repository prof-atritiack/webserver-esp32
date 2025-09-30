# WebServer ESP32

Este repositório reúne exemplos práticos de uso do **ESP32** como servidor web em diferentes aplicações.  
Cada exemplo possui código `.ino` comentado e documentação de apoio.

---

## Exemplos disponíveis

### 1. Servidor Web ESP32 com Monitoramento de Temperatura e Umidade
- Leitura de temperatura e umidade usando **DHT11**.  
- Exibição em uma página web hospedada no ESP32.  
- Interface em HTML/CSS com cartões e atualização automática via JavaScript.   

### 2. Servidor Web ESP32 com Controle de LED (GPIO 2)
- Controle de um LED conectado ao **GPIO 2** do ESP32 via navegador.  
- Interface em HTML com botões ON/OFF.  
- Exibição do estado atual do LED na página.  

---

## Como usar

1. Abra a **Arduino IDE**.  
2. Instale o **ESP32 Core** (via Board Manager).  
3. Instale as bibliotecas necessárias (quando aplicável).  
4. Carregue o código `.ino` do exemplo desejado.  
5. Abra o **Monitor Serial** em **115200 baud**.  
6. Copie o endereço IP exibido e acesse no navegador conectado à mesma rede Wi-Fi.  

---

## Estrutura do Repositório

```
webserver-esp32/
│
├── ESP32_DHT_WebServer/
│   ├── ESP32_DHT_WebServer.ino
│   └── README.md
│
├── ESP32_WebServer_GPIO/
│   ├── ESP32_WebServer_GPIO.ino
│   └── README.md
│
└── README.md   <-- este arquivo
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
