#include <WebSocketsServer.h>
#include <WebServer.h>
#include <Arduino.h>
#include <Boards.h>
#include "pagina.h"
#include <Redes.h>
#include <WiFi.h>

int ENA1 = esp2_ENA1; // Motor direito
int MD1 = esp2_MD1;
int MD2 = esp2_MD2;

int ENA2 = esp2_ENA2; // Motor esquerdo
int ME1 = esp2_ME1;
int ME2 = esp2_ME2;

const char* ssid = ssi;
const char* password = passwor;

WebServer servidor(80);
WebSocketsServer websocket = WebSocketsServer(81);

void parar() {
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, LOW);
  digitalWrite(ME1, LOW);
  digitalWrite(ME2, LOW);
}

void comando(String dados) {
  if (dados == "frente") {
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(ME1, HIGH);
    digitalWrite(ME2, LOW);
  }
  else if (dados == "atras") {
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
    digitalWrite(ME1, LOW);
    digitalWrite(ME2, HIGH);
  }
  else if (dados == "esquerda") {
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(ME1, LOW);
    digitalWrite(ME2, HIGH);
  }
  else if (dados == "direita") {
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
    digitalWrite(ME1, HIGH);
    digitalWrite(ME2, LOW);
  }
  else if (dados == "parar") {
    parar();
  }
}

void evento(uint8_t numero, WStype_t tipo, uint8_t *payload, size_t tamanho) {
  if (tipo == WStype_TEXT) {
    String mensagem = String((char*)payload);
    comando(mensagem);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA1, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(ME1, OUTPUT);
  pinMode(ME2, OUTPUT);

  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);

  WiFi.mode(WIFI_MODE_STA);

  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  servidor.on("/", paginaPrincipal);
  servidor.begin();

  websocket.begin();
  websocket.onEvent(evento);

  Serial.println("WebSocket iniciado");
}

void loop() {
  servidor.handleClient();
  websocket.loop();
}