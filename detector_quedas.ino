//Programa desenvolvido por Grupo 03 - Disciplina de Engenharia Unificada UFABC
//Profa. Ana Simões


//Bibliotecas
#include<Wire.h>//Biblioteca para comunicação I2C

//Definições
#define pinoLEDyellow 12
#define pinoLEDred 13
#define buzzer 8
#define dismissButom 2
#define helpButom 3
const int MPU_addr=0x68; //Endereço do sensor
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //Variaveis para pegar os valores medidos

int queda = 0;    //Define queda como não no inicio do programa
int help = 0;     //Define help como não no inicio do programa

//Programa Setup (DEFINIÇÕES)
void setup(){
  Wire.begin(); //Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);

  pinMode (pinoLEDyellow, OUTPUT);
  pinMode (pinoLEDred, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(dismissButom, INPUT);
  pinMode(helpButom, INPUT);

  Serial.begin(9600); //Inicia a comunicaçao serial (para exibir os valores lidos)
}

//Funções
void Aguardadispensa(){
  while dismissButom == LOW{

  }
}

void detectaQueda(int magnitudeBase, magnitudeMedida){
  if (magnitudeMedida >= MagnitudeBase){
    digitalWrite(pinoLEDred,HIGH); //Acende luz vermelha
    digitalWrite(buzzer,LOW); //Toca o buzzer
    delay(5000); //Mantem deste estado por 5s
  }
  digitalWrite(pinoLEDred, LOW); //Desliga o LED vermelho
  digitalWrite(buzzer, HIGH); //Desliga o buzzer
  delay(333); //Aguarda para seguir com o programa
}

void aguardaHelp(){

}

void chamaajuda(){

}

void avisoQueda(){

}





//Programa Loop (PRINCIPAL)
void loop(){
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

  magnitude=sqrt(pow(AcX, 2)+pow(AcY, 2)+pow(AcZ, 2))     //Define a magnitude da queda não importando a direção

  //Agora escreve os valores no monitor serial
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //Equação da temperatura em Cº de acordo com o datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  Serial.print(" | Magnitude = "); Serial.println(magnitude);

  detectaQueda(10000, magnitude); //Faz a detecção de queda e primeiro aviso
}








