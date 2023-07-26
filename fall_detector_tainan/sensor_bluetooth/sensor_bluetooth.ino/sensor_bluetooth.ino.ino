#include <SoftwareSerial.h>

SoftwareSerial bluetooth(3, 4); //RX, TX

void setup() 
{
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() 
{
  bluetooth.print("Mensagem enviada via Bluetooth");
  Serial.println("Mensagem no Monitor Serial");
  delay(200);
}