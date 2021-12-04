// ******** MOTOR DE PASSO *********

// ********** BIBLIOTECAS **********
//#include <ArduinoJson.h>
//#include <max6675.h>

// *********** CONFIGURAÇÃO PINOS TERMOPARES **************
#define GPIO_SO       8
#define GPIO_CS       9
#define GPIO_CLK      10
 
//  MAX6675 termopar01(GPIO_CLK, GPIO_CS, GPIO_SO);
//  MAX6675 termopar02(GPIO_CLK, GPIO_CS, GPIO_SO);
//  MAX6675 termopar03(GPIO_CLK, GPIO_CS, GPIO_SO);
//  MAX6675 termopar04(GPIO_CLK, GPIO_CS, GPIO_SO);
  

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

//DynamicJsonDocument recebeJson(1024);
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
int tempo = 100;

int pino1 = 8;
int pino2 = 9;
int pino3 = 10;

int pinZeraX;
int pinZeraY;
int pinZeraZ;

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
}

// ********* LOOP **********
void loop() {

  if (Serial.available() > 0) {
    //deserializeJson(recebeJson, Serial);       // RECEBE JSON DA PORTA USB
    //operacao = recebeJson["operacao"];         // PARÂMETRO QUE DEFINE OPERAÇÃO/FUNÇÃO
    //sinal = recebeJson["sinal"];               // PARÂMETRO QUE DEFINE SINAL/SENTIDO
    //eixo = recebeJson["eixo"];                 // PARÂMETRO QUE DEFINE EIXO
    //pulso = recebeJson["pulso"];               // PARÂMETRO QUE DEFINE PULSOS
    //flagTermopar = recebeJson["flagTermopar"]; // PARÂMETRO QUE ACIONA OS TERMOPARES
    strOperacao = String(operacao);
    strSinal = String(sinal);
    strEixo = String(eixo);
    strPulso = String(pulso);
    strFlagTermopar = String(flagTermopar);

    giroMotor("x", strSinal, strPulso);
    giroMotor("y", strSinal, strPulso);
    giroMotor("z", strSinal, strPulso);
    giroMotor("r", strSinal, strPulso);
    

    //sleep(tempo);

    // ------------------------------- //






    if (strOperacao.equals("mov")) {
      giroMotor(strEixo, strSinal, strPulso);
    } else if (strOperacao.equals("zera")) {
      zeroMaquina();
    } else if (strOperacao.equals("termopar")) {
      //funcaoTermopares(strFlagTermopar);
    }
  }
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
  pos = 440 * strPulso.toInt();
}

// *********** FUNÇÃO TERMOPARES *************

/*
void funcaoTermopares(String strFlagTermopar) {
  int temp01 = termopar01.readCelsius();
  int temp02 = termopar02.readCelsius();
  int temp03 = termopar03.readCelsius();
  int temp04 = termopar04.readCelsius();  
}
*/
