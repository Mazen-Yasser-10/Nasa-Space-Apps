#include <Servo.h>
Servo servoX;
Servo servoY;
int randomNum = 2500;

void setup() {
  servoX.attach(5);
  servoY.attach(4);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  servoX.write(0);
  servoY.write(90);
}

void loop() {
  if(millis() % randomNum <= 30)
  {
    servoX.write(random(0,181));
    servoY.write(random(0,181));
    delay(30);
    randomNum = random(1,5001);
    digitalWrite(8,HIGH);
    delay(500);
  }
  digitalWrite(8,LOW);
}
