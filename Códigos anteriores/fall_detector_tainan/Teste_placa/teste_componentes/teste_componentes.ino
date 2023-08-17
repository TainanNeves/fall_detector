#include <SoftwareSerial.h>

#define LED1 6
#define LED2 7
#define buzzer 8
#define dispensa 9
#define ajuda 10

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(dispensa, INPUT_PULLUP);
  pinMode(ajuda, INPUT_PULLUP);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

  digitalWrite(LED1, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED1, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  
  digitalWrite(LED2, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED2, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  
  digitalWrite(buzzer, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                      // wait for a second
  digitalWrite(buzzer, LOW);   // turn the LED off by making the voltage LOW

  Serial.print("Dispensa: "); Serial.print(digitalRead(dispensa));
  Serial.print(" | Ajuda: "); Serial.println(digitalRead(ajuda));
  delay(200);

  if(digitalRead(ajuda) != HIGH){
    digitalWrite(LED1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(LED1, LOW);
    digitalWrite(buzzer, LOW);
    delay(400);
    digitalWrite(LED1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(LED1, LOW);
    digitalWrite(buzzer, LOW);
  }

  if(digitalRead(dispensa) != HIGH){
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(LED2, LOW);
    digitalWrite(buzzer, LOW);
    delay(400);
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(LED2, LOW);
    digitalWrite(buzzer, LOW);
    delay(400);
    digitalWrite(LED2, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(LED2, LOW);
    digitalWrite(buzzer, LOW);
  }
}
