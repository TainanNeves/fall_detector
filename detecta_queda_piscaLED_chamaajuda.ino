// Codigo adaptado de: Usuário do Arduino JohnChi

#include<Wire.h>//Biblioteca para comunicação I2C
#define pinoLED2 7
#define buzzer 8
#define pinoLED1 10
#define ajuda 11
#define dispensa 12

const unsigned long tempoLimite = 10000;
const int MPU_addr=0x68; //Endereço do sensor

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //Variaveis para pegar os valores medidos

void piscarLEDsBuzzer() {
  unsigned long tempoAtual = millis();
  while(tempoAtual <= tempoLimite){

    // Acende o LED 1 e ativa o buzzer
  digitalWrite(pinoLED1, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);

  // Apaga o LED 1 e desativa o buzzer
  digitalWrite(pinoLED1, LOW);
  digitalWrite(buzzer, LOW);
  delay(500);

  // Acende o LED 2
  digitalWrite(pinoLED2, HIGH);
  delay(500);

  // Apaga o LED 2
  digitalWrite(pinoLED2, LOW);
  delay(500);

  if(ajuda == 1){
    Serial.print("preciso de ajuda");
    break;
  }
  if(dispensa ==1){
    Serial.print("NÃO preciso de ajuda");
    break;
  }
  Serial.print("preciso de ajuda");
  break;
  }
  
}



void setup(){
  Wire.begin(); //Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr); //Começa a transmissao de dados para o sensor
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o MPU 6050
  Wire.endTransmission(true);
  pinMode(pinoLED1, OUTPUT);
  pinMode(pinoLED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ajuda, INPUT);
  pinMode(dispensa, INPUT);

  Serial.begin(9600); //Inicia a comunicaçao serial (para exibir os valores lidos)
}
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

  //Agora escreve os valores no monitor serial
  //Serial.print("AcX = "); Serial.print(AcX);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //Equação da temperatura em Cº de acordo com o datasheet
  //Serial.print(" | GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ);

  if (AcZ > 20000 || AcY > 15000 || AcX > 10000 || AcZ < -15000 || AcY  < -15000 || AcZ < -25000) {
   for (int i = 0; i <= 5; i++) {
    Serial.println("Houve uma possível queda, talvez precise chamar ajuda");
    piscarLEDsBuzzer();
  }



  }
  digitalWrite(pinoLED1, LOW);
  digitalWrite(pinoLED2, LOW);
  digitalWrite(buzzer,LOW);
}
