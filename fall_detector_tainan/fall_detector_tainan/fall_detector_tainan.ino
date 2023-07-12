// Detector de queda em arduino
// Projeto desenvolvido durante a disciplina de Engenharia Unificada I na Universidade Federal do ABC

//Integrantes:
//  Tainan Cerqueira Neves
//  Thiago 
//  
//  
//  


//Definições
#include<Wire.h>//Biblioteca para comunicação I2C
#define pinoLED2 7
#define buzzer 8
#define pinoLED1 10
#define ajuda 11
#define dispensa 12
const unsigned long tempoLimite = 10000;
const int MPU_addr=0x68; //Endereço do sensor
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //Variaveis medidas no MPU6050

//Setup e enderecamento
void setup(){
  Wire.begin(); //Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);
  pinMode(pinoLED1, OUTPUT);
  pinMode(pinoLED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ajuda, INPUT_PULLUP);       //Se High = Desapertado, Else = apertado
  pinMode(dispensa, INPUT_PULLUP);    //Se High = Desapertado, Else = apertado

  Serial.begin(9600); //Inicia a comunicaçao serial (para exibir os valores lidos)
}



//Funcoes auxiliares

float medir(){
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x3B); // registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); // faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Agora escreve os valores no monitor serial
  //Serial.print("AcX = "); Serial.print(AcX);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //Equação da temperatura em Cº de acordo com o datasheet
  //Serial.print(" | GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ);

  float modulo_aceleracao = sqrt(pow(AcX,2)+pow(AcY,2)+pow(AcZ,2));
  return modulo_aceleracao;
}

int detecta_queda(modulo_aceleracao){
  if(modulo_acelercao >= 10000){
    int queda = 1;                      //queda
  }else{
    int queda = 0;                      //nao queda
  }

  return queda;
}

int queda_detectada(){
  int quer_ajuda = 1;
  //Acende tudo e apita por 5s
  digitalWrite(pinoLED1, HIGH);
  digitalWrite(pinoLED2, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(5000);

  //avalia por 15s se havera dispensa
  digitalWrite(pinoLED1, LOW);
  digitalWrite(pinoLED2, LOW);
  digitalWrite(buzzer, LOW);
  unsigned long tempoAtual = millis();
  while(int t=tempoAtual <= tempoAtual + 15000){
    digitalWrite(pinoLED1, HIGH);
    digitalWrite(pinoLED2, LOW);
    int dispensa = digitalRead(dispensa);
    if(dispensa != HIGH){
      quer_ajuda = 0;
      digitalWrite(pinoLED1, LOW);
      digitalWrite(pinoLED2, LOW);
      digitalWrite(buzzer, LOW);
      break
    }
    sleep(50);
    digitalWrite(pinoLED1, LOW);
    digitalWrite(pinoLED2, HIGH);
    dispensa = digitalRead(dispensa);
    if(dispensa != HIGH){
      quer_ajuda = 0;
      digitalWrite(pinoLED1, LOW);
      digitalWrite(pinoLED2, LOW);
      digitalWrite(buzzer, LOW);
      break
    }
    sleep(50);
    digitalWrite(buzzer, HIGH);
    sleep(200);
    dispensa = digitalRead(dispensa);
    if(dispensa != HIGH){
      quer_ajuda = 0;
      digitalWrite(pinoLED1, LOW);
      digitalWrite(pinoLED2, LOW);
      digitalWrite(buzzer, LOW);
      break
    }
    digitalWrite(buzzer, LOW);
    sleep(200);
  }

  //Retornando se ha queda ou nao
  return quer_ajuda;
}

int avalia_buscar_ajuda(){
  int ajuda = 0;
  int help = digitalRead(ajuda);
  if(help != HIGH){
    ajuda = 1;
  }

  return ajuda;
}

void envia_aviso_queda(){
  serial.Print("Enviando aviso que queda para tutor/responsável"); //Provisório
  sleep(5000);
}

void envia_aviso_ajuda(){
  serial.Print("Enviando aviso de pedido de ajuda para tutor/responsável");  //Provisório
  sleep(5000);
}


//Programa Principal
void loop(){
  float modulo_aceleracao = medir();  //Realiza a medida e grava em uma variavel
  sleep(150);                         //espera 150ms

  queda = detecta_queda(modulo_aceleracao);
  if(queda == 1){                     //Se queda
    int confirma_queda = queda_detectada();
    if(confirma_queda == 1){
      envia_aviso_queda()
    }
  }else{                              //Se não queda
    int quer_ajuda = avalia_buscar_ajuda();
    if(quer_ajuda == 1){
      envia_aviso_ajuda()
    }
  }
  
}
