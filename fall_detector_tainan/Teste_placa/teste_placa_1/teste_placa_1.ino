//Programa para teste de componentes

#include<Wire.h>//Biblioteca para comunicação I2C
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

#define pinoLED1 6
#define pinoLED2 7
#define buzzer  8
#define dispensa 11
#define ajuda 12

Adafruit_MPU6050 mpu;

void setup() {
  //Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));
  if (!mpu.begin(0x69)) { // Change address if needed
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  pinMode(pinoLED1, OUTPUT);
  pinMode(pinoLED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ajuda, INPUT_PULLUP);       //Se High = Desapertado, Else = apertado
  pinMode(dispensa, INPUT_PULLUP);    //Se High = Desapertado, Else = apertado
}

void readMPU( ) { /* function readMPU */
  ////Read acceleromter data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println("°C");

  Serial.print("Modulo: ");
  float modulo = sqrt(pow(a.acceleration.x,2)+pow(a.acceleration.y,2)+pow(a.acceleration.z,2));
  Serial.print(modulo);
  Serial.println("m/s^2");
}

void loop(){
  readMPU();
  delay(200);

  if(ajuda != HIGH){
    digitalWrite(pinoLED1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(pinoLED1, LOW);
    digitalWrite(buzzer, LOW);
  }

  if(dispensa != HIGH){
    digitalWrite(pinoLED2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(pinoLED2, LOW);
    digitalWrite(buzzer, LOW);
  }

}

