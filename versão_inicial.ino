#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.softAP("ESP32_ROBO", "12345678");
  Serial.println("ESP32 iniciado em modo Access Point");

  server.on("/", []() {
    server.send(200, "text/html",
      "<h1>Controle do Robo</h1>"
      "<a href='/frente'>Frente</a><br>"
      "<a href='/tras'>Tras</a><br>"
      "<a href='/esquerda'>Esquerda</a><br>"
      "<a href='/direita'>Direita</a><br>"
      "<a href='/arma'>Arma</a><br>"
    );
  });

  server.on("/frente", []() {
    Serial.println("Comando recebido: FRENTE");
    server.send(200, "text/plain", "OK");
  });

  server.on("/tras", []() {
    Serial.println("Comando recebido: TRAS");
    server.send(200, "text/plain", "OK");
  });

  server.on("/esquerda", []() {
    Serial.println("Comando recebido: ESQUERDA");
    server.send(200, "text/plain", "OK");
  });

  server.on("/direita", []() {
    Serial.println("Comando recebido: DIREITA");
    server.send(200, "text/plain", "OK");
  });

  server.on("/arma", []() {
    Serial.println("Status Arma: LIGADA");
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
