/* 
 * Motor de Passo
 * 
 * 
 * References
 * 
 * 
 */

//***********Bibliotecas***********


//***********Configuração Pinos Drives Motores***********
int driver1PUL = 3 ; // Pino digital PUL driver 1
int driver1DIR = 6  ; // Pino digital DIR driver 1



//***********Variáveis de Controle***********

long giro1 = 0; // Controle giro 1
long giro2 = 0; // Controle giro 2


int pd1 = 500;//Controle velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750    
int pd2 = 500;//Controle velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750

int  incomingByte = 0; // Recebe Valor temperatura

//***********Setup***********
void setup() {
  Serial.begin(9600); // Inicia porta serial
  
  pinMode (driver1PUL, OUTPUT); //Define pino relé sáida
  pinMode (driver1DIR, OUTPUT); //Define pino relé sáida

}
//***********Função FGiro Motor 1***********
void giroMotor1(){
       
       Serial.println("Entrou");
       digitalWrite(driver1DIR,HIGH);
 
       for (giro1; giro1<=10; giro1++)
       {
          digitalWrite(driver1PUL,HIGH);
          delayMicroseconds(pd1);
          digitalWrite(driver1PUL,LOW);
          delayMicroseconds(pd1);
       }
       Serial.println(giro1);
       giro1 = 0;
       
}

//***********Função FGiro Motor 1***********
void giroMotor2(){
       
       Serial.println("Entrou");
       digitalWrite(driver1DIR,LOW);
 
       for (giro1; giro1<=10; giro1++)
       {
          digitalWrite(driver1PUL,HIGH);
          delayMicroseconds(pd1);
          digitalWrite(driver1PUL,LOW);
          delayMicroseconds(pd1);
       }
       Serial.println(giro1);
       giro1 = 0;
       
}

//***********Loop***********
void loop() {

  incomingByte = Serial.read();
  
  if (incomingByte == 'A') { giroMotor1();}
  else if(incomingByte == 'C'){ giroMotor2();}

}
