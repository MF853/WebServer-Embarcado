//Modo de Acess Point

#include <WiFi.h>
#include <WebServer.h>

//Dados da rede AP criada
const char *nome_rede = "ESP32_PROJETO_2";
const char *senha = "12345678";
//Criar servidor
WebServer server(80);

int status = 0;

//Funções para modularização (boas-práticas)
//---Página do controle
void handleControle() {
    String site = "<!DOCTYPE html><html>";
    site += "<head>";
    site += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    site += "<title>Controle do Robô *nome*</title>";
    //=====CSS=====
    site += "<style>";
    site += "body { font-family: Arial; background-color: #f2f2f2; text-align: center; margin: 0; }";
    //Menu superior (igual para as duas páginas)
    site += ".menu { background-color: #333; padding: 15px; }";
    site += ".menu a { color: white; margin: 0 20px; text-decoration: none; font-size: 18px; }";
    site += ".menu a.active { text-decoration: underline; font-weight: bold; }";
    //Classes para o controle
    site += ".controle { margin-top: 40px; display: grid; grid-template-columns: 90px 90px 90px; gap: 15px; justify-content: center; }";
    site += "button { font-size: 18px; padding: 20px; border-radius: 15px; border: none; }";
    site += ".move { background-color: #1e3a96; color: white; }";
    site += ".arma-off { background-color: #E53935; color: white; }";
    site += ".arma-on  { background-color: #43A047; color: white; }";
    site += "</style>";
    site += "</head><body>";
    //=====MENU SUPERIOR=====
    site += "<div class='menu'>";
    site += "<a href='/tutorial'>Tutorial</a>";
    site += "<a href='/controle' class='active'>Controle</a>";
    site += "</div>";
    //=====CONTROLE=====
    site += "<div class='controle'>";
    site += "<div></div>";
    site += "<a href='/frente'><button class='move'>↑</button></a>";
    site += "<div></div>";
    site += "<a href='/esquerda'><button class='move'>←</button></a>";
    if (status == 1) {
      site += "<a href='/arma'><button class='arma-on'>ARMA</button></a>";
    } else {
      site += "<a href='/arma'><button class='arma-off'>ARMA</button></a>";
    }
    site += "<a href='/direita'><button class='move'>→</button></a>";
    site += "<div></div>";
    site += "<a href='/tras'><button class='move'>↓</button></a>";
    site += "<div></div>";
    site += "</div>";
    site += "</body></html>";

    server.send(200, "text/html", site);
}

//---Página de tutorial
void handleTutorial() {
    String site = "<!DOCTYPE html><html>";
    site += "<head>";
    site += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    site += "<title>Tutorial</title>";
    //===== CSS =====
    site += "<style>";
    site += "body { font-family: Arial; background-color: #f2f2f2; margin: 0; }";
    //Menu superior (igual para as duas páginas)
    site += ".menu { background-color: #333; padding: 15px; text-align: center; }";
    site += ".menu a { color: white; margin: 0 20px; text-decoration: none; font-size: 18px; }";
    site += ".menu a.active { text-decoration: underline; font-weight: bold; }";
    //Conteúdo
    site += ".content { padding: 30px; max-width: 600px; margin: auto; }";
    site += "h1 { text-align: center; }";
    site += "ul { font-size: 18px; }";
    site += "li { margin-bottom: 10px; }";
    site += "</style>";
    site += "</head><body>";
    //===== MENU =====
    site += "<div class='menu'>";
    site += "<a href='/tutorial' class='active'>Tutorial</a>";
    site += "<a href='/controle'>Controle</a>";
    site += "</div>";
    //===== CONTEÚDO =====
    site += "<div class='content'>";
    site += "<h1>Como controlar o robô *nome*</h1>";
    site += "<ul>";
    site += "<li><b>Botão Frente (↑):</b> responsável por mover o robô para frente.</li>";
    site += "<li><b>Botão Trás(↓):</b> responsável por mover o robô para trás.</li>";
    site += "<li><b>Botão Esquerda(←):</b> responsável por girar o robô para a esquerda.</li>";
    site += "<li><b>Botão Direita(→):</b> responsável por girar o robô para a direita.</li>";
    site += "<li><b>Botão da arma (ARMA):</b> responsável por ligar ou desligar a arma do robô.</li>";
    site += "</ul>";
    site += "<p>O status da arma é indicado visualmente no controle através da cor do botão: se ele estiver vermelho = arma desligada e se ele estiver verde = arma ligada.</p>";
    site += "</div>";
    site += "</body></html>";

    server.send(200, "text/html", site);
}

void setup() {
  //Iniciar Monitor Serial
  Serial.begin(115200);
  //Conexão WiFi
  WiFi.softAP(nome_rede, senha);
  Serial.println("ESP32 iniciado em modo Access Point");
  //Geração do IP
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Endereço IP do AP: ");
  Serial.println(IP);

  //Definição das rotas a partir do site
  //---Definição das páginas
  server.on("/", []() {
    server.sendHeader("Location", "/controle");
    server.send(302, "text/plain", "");
  });

  server.on("/controle", handleControle);

  server.on("/tutorial", handleTutorial);

  //---Definição dos botões
  server.on("/frente", []() {
    Serial.println("Comando recebido: FRENTE");
    handleControle();
  });
  server.on("/tras", []() {
    Serial.println("Comando recebido: TRAS");
    handleControle();
  });
  server.on("/esquerda", []() {
    Serial.println("Comando recebido: ESQUERDA");
    handleControle();
  });
  server.on("/direita", []() {
    Serial.println("Comando recebido: DIREITA");
    handleControle();
  });
  server.on("/arma", []() {
    if (status == 0) {
      status = 1;
      Serial.println("Status Arma: LIGADA");
      handleControle();
    } else {
      status = 0;
      Serial.println("Status Arma: DESLIGADA");
      handleControle();
    }
    
  });

  server.begin();
}


void loop() {
  //Manter servidor sempre a postos para receber e entender requisição para executar o server.on()
  server.handleClient();
} e entender requisição para executar o server.on()
  server.handleClient();
}
