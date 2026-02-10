//Modo de Acess Point

#include <WiFi.h>
#include <WebServer.h>

//Dados da rede AP criada
const char *nome_rede = "ESP32_PROJETO_2";
const char *senha = "12345678";
//Criar servidor
WebServer server(80);

//Estruturação do site
void handleRoot() { //MODIFICAR ESTRUTURA E APARÊNCIA DO SITE PARA O QUE PRECISAMOS
  String site = "!DOCTYPE html><html>";
  site += "<head><meta name=\"viewport\"content"width=device-widht, initial-scale=1"></head>";
  site += "body style=\"text-align:center; font-family:sans-serif;\">";
  site += "<h1>Controle Wi-Fi (AP)<\h1>";
  site += "<p><a href\"/BOTAO\"><button style=\font-size:20px; background-color: COR; color: COR2;\">TEXTO</button></a></p";
  site += "<p><a href\"/BOTAO\"><button style=\font-size:20px; background-color: COR; color: COR2;\">TEXTO</button></a></p";
  site += "</body></html>";
  server.send(200, "text/html", site);
}

/*
void handleArmaOn() {
  //StatusArma = HIGH;
  Serial.println("Status Arma: LIGADA");
  handleRoot(); //Atualiza a página para ver o status da arma
}
 
void handleArmaOff() {
  //StatusArma = LOW;
  Serial.println("Status Arma: DESLIGADA");
  handleRoot(); //Atualiza a página para ver o status da arma
}
*/

void setup() {
  //Iniciar Monitor Serial
  Serial.begin(115200);
  //Conexão WiFi
  WiFi.softAP(nome_rede, senha);
  Serial.println("ESP32 iniciado em modo Access Point");
  //Geração do IP
  IPAdress IP = WiFi.softAPIP();
  Serial.print("Endereço IP do AP: ");
  Serial.println(IP);

  //Definição das rotas a partir do site
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
    server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
  });
  server.on("/tras", []() {
    Serial.println("Comando recebido: TRAS");
    server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
  });
  server.on("/esquerda", []() {
    Serial.println("Comando recebido: ESQUERDA");
    server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
  });
  server.on("/direita", []() {
    Serial.println("Comando recebido: DIREITA");
    server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
  });
  int status = 0;
  server.on("/arma", []() {
    if (status == 0) {
      status = 1;
      Serial.println("Status Arma: LIGADA");
      server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
    } else {
      status = 0;
      Serial.println("Status Arma: DESLIGADA");
      server.send(200, "text/plain", "OK"); //ou handleRoot()   pesquisar diferença
    }
    
  });

  server.begin();
}


void loop() {
  //Manter servidor sempre atualizado/a postos
  server.handleClient();
}
