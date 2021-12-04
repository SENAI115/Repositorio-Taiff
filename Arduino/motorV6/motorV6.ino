// ******** MOTOR DE PASSO *********

// ********** BIBLIOTECAS **********
#include <ArduinoJson.h>
#include <max6675.h>

// *********** CONFIGURAÇÃO PINOS TERMOPARES **************
#define GPIO_SO       8
#define GPIO_CS       9
#define GPIO_CLK      10

MAX6675 termopar01(GPIO_CLK, GPIO_CS, GPIO_SO);
MAX6675 termopar02(GPIO_CLK, GPIO_CS, GPIO_SO);
MAX6675 termopar03(GPIO_CLK, GPIO_CS, GPIO_SO);
MAX6675 termopar04(GPIO_CLK, GPIO_CS, GPIO_SO);


// ********* CONFIGURAÇÕES PINOS DRIVERS MOTORES ***********
int driver1PUL = 2;  // PINO DIGITAL PUL DRIVER 1
int driver1DIR = 5;  // PINO DIGITAL DIR DRIVER 1
int driver2PUL = 3;  // PINO DIGITAL PUL DRIVER 2
int driver2DIR = 6;  // PINO DIGITAL DIR DRIVER 2
int driver3PUL = 4;  // PINO DIGITAL PUL DRIVER 3
int driver3DIR = 7;  // PINO DIGITAL DIR DRIVER 3
int driverPUL;
int driverDIR;

// ********* VARIÁVEIS DE CONTROLE **********
long giro = 0;    // CONTROLE GIRO 1
int pd = 200;  // CONTROLE VELOCIDADE DOS MOTORES
int incomingByte = 0; // RECEBE VALOR TEMPERATURA

DynamicJsonDocument recebeJson(1024);
char* operacao;
char* sinal;
char* eixo;
char* pulso;
char* flagTermopar;
String dado;
boolean sentido;
int pos;
String pul;
String strOperacao;
String strSinal;
String strEixo;
String strPulso;
String strFlagTermopar;

int pino1 = 8;
int pino2 = 9;
int pino3 = 10;
int pinMode1 = 13;

int pinZeraX;
int pinZeraY;
int pinZeraZ;


// Variaveis das posições


char* posX;
char* posY;
char* posZ;
char* posR;
char* tempo;

String strPosX;
String strPosY;
String strPosZ;
String strPosR;
int intTempo;


int sensorPin = 0;
int lightlevel;

// ******** SETUP ********
void setup() {
  Serial.begin(9600); // INICIAL PORTA SERIAL
  pinMode(driver1PUL, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(driver1DIR, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(driver2PUL, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(driver2DIR, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(driver3PUL, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(driver3DIR, OUTPUT);  // DEFINE PINO RELÉ SAÍDA
  pinMode(pino1, INPUT_PULLUP);  //
  pinMode(pino2, INPUT_PULLUP);
  pinMode(pino3, INPUT_PULLUP);
  pinMode(pinMode1, OUTPUT);
}

// ********* LOOP **********
void loop() {

  //    digitalWrite(pinMode1, HIGH);
  //    delay(3000);
  //    digitalWrite(pinMode1, LOW);
//  if (Serial.available() > 0) {
//    deserializeJson(recebeJson, Serial);       // RECEBE JSON DA PORTA USB

    Serial.println("Temperatura");
    delay(1000);
    funcaoTermopares();
    //    posX = recebeJson["xpos"];
    //    posY = recebeJson["ypos"];
    //    posZ = recebeJson["zpos"];
    //    posR = recebeJson["rpos"];
    //    tempo = recebeJson["tempo"];
    //
    //    strPosY = String(posY);
    //    strPosZ = String(posZ);
    //    strPosR = String(posR);
    //    intTempo = (int)tempo;
    //
    //    giroMotor2("x", strPosX);
    //    giroMotor2("y", strPosY);
    //    giroMotor2("z", strPosZ);
    //    giroMotor2("r", strPosR);
    //
//  }

}

// ********* FUNÇÃO GIRO MOTOR MANUAL **********
void giroMotor(String strEixo, String strSinal, String strPulso) {

  if (strSinal.equals("+")) { // DEFINIÇÃO DO SENTIDO DO DESLOCAMENTO
    sentido = HIGH;
  } else {
    sentido = LOW;
  }

  definiDrivers(eixo); // DEFININDO DRIVERS
  definiPulsos(strPulso); // DEFININDO PULSOS
  digitalWrite(driverDIR, sentido);  // SET DOS PINOS DE COMUNICAÇÃO COM O DRIVER
  for (giro; giro <= pos; giro++) {  // LAÇO QUE MOVIMENTA OS MOTORES
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(pd);
    digitalWrite(driverPUL, LOW);
    delayMicroseconds(pd);
  }
  giro = 0;
  pos = 0;
}


// -------------------------------
boolean isPositivo(int pulso1) {

  if (pulso1 > 0) {
    return true;
  } else {
    return false;
  }

}
void giroMotor2(String strEixo, String strPulso) {

  if (isPositivo(strPulso.toInt())) { // DEFINIÇÃO DO SENTIDO DO DESLOCAMENTO
    sentido = HIGH;
  } else {
    sentido = LOW;
  }

  definiDrivers(eixo); // DEFININDO DRIVERS
  definiPulsos(strPulso); // DEFININDO PULSOS
  digitalWrite(driverDIR, sentido);  // SET DOS PINOS DE COMUNICAÇÃO COM O DRIVER
  for (giro; giro <= pos; giro++) {  // LAÇO QUE MOVIMENTA OS MOTORES
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(pd);
    digitalWrite(driverPUL, LOW);
    delayMicroseconds(pd);
  }
  giro = 0;
  pos = 0;
}

//-----------------------
// ***** FUNÇÃO ZERA MÁQUINA(MESA) *****
void zeroMaquina() {
  pinZeraX = digitalRead(pino1);
  pinZeraY = digitalRead(pino2);
  pinZeraZ = digitalRead(pino3);
  digitalWrite(driver1DIR, LOW);
  digitalWrite(driver2DIR, HIGH);
  digitalWrite(driver3DIR, LOW);

  if (pinZeraX == HIGH) {
    while (pinZeraX == HIGH) {
      pinZeraX = digitalRead(pino1);
      digitalWrite(driver1PUL, HIGH);
      delayMicroseconds(pd);
      digitalWrite(driver1PUL, LOW);
      delayMicroseconds(pd);
      if (pinZeraX == LOW) {
        Serial.println("Apertei o Botão");
      }
    }
  }
  if (pinZeraY == HIGH) {
    while (pinZeraY == HIGH) {
      pinZeraY = digitalRead(pino2);
      digitalWrite(driver2PUL, HIGH);
      delayMicroseconds(pd);
      digitalWrite(driver2PUL, LOW);
      delayMicroseconds(pd);
      if (pinZeraY == LOW) {
        Serial.println("Apertei o Botão");
      }
    }
  }
  if (pinZeraZ == HIGH) {
    while (pinZeraZ == HIGH) {
      pinZeraZ = digitalRead(pino3);
      digitalWrite(driver3PUL, HIGH);
      delayMicroseconds(pd);
      digitalWrite(driver3PUL, LOW);
      delayMicroseconds(pd);
      if (pinZeraZ == LOW) {
        Serial.println("Apertei o Botão");
      }
    }
  }
}

// ******** FUNÇÃO DEFINIÇÃO DOS DRIVERS *******
void definiDrivers(String eixo) {
  if (eixo.equals("x")) {
    driverDIR = driver1DIR;
    driverPUL = driver1PUL;
  } else if (eixo.equals("y")) {
    driverDIR = driver2DIR;
    driverPUL = driver2PUL;
  } else if (eixo.equals("z")) {
    driverDIR = driver3DIR;
    driverPUL = driver3PUL;
  }
}

// ******** FUNÇÃO DEFINIÇÃO DOS PULSOS ********
void definiPulsos(String strPulso) {
  pos = 440 * abs(strPulso.toInt());
}

// *********** FUNÇÃO TERMOPARES *************
void funcaoTermopares() {

  lightlevel = analogRead(sensorPin);

  //String jsonTemperatura = "{​​​​ \"T1:" + termopar01.readCelsius() + ", T2:" + termopar02.readCelsius() + ", T3:" + termopar03.readCelsius() + ", TA:" + termopar04.readCelsius() + "}​​​​";

  Serial.println(lightlevel);
  delay(500);
}
