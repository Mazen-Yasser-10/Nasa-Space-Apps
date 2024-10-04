#include <Servo.h>
Servo servoX;
Servo servoY;
int randomNum = 2500;
int level;

void setup() {
  servoX.attach(5);
  servoY.attach(4);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  servoX.write(0);
  servoY.write(90);
}

void loop() {
  if(Serial.available())
  {
    level = Serial.parseInt();
  }
  while(level == 1)
  {
    gameScope(5000);
  }
  while(level == 2)
  {
    gameScope(3000);
  }
  while(level == 3)
  {
    gameScope(2000);
  }
  while(level == 4)
  {
    gameScope(1000);
  }
}
void gameScope(int duration)
{
  if(millis() % duration <= 30)
  {
    int randomX = random(0,181);
    int randomY = random(0,181);
    int currentX = servoX.read();
    int currentY = servoY.read();
    if(randomX >= currentX)
    {
      for(int i = currentX ; i <= randomX ; i++)
      {
        servoX.write(i);
        delay(3);
      }
    }
    else
    {
      for(int i = currentX ; i >= randomX ; i--)
      {
        servoX.write(i);
        delay(3);
      }
    }
    if(randomY >= currentY)
    {
      for(int i = currentY ; i <= randomY ; i++)
      {
        servoY.write(i);
        delay(3);
      }
    }
    else
    {
      for(int i = currentY ; i >= randomY ; i--)
      {
        servoY.write(i);
        delay(3);
      }
    }
    digitalWrite(8,HIGH);
    delay(500);
  }
  digitalWrite(8,LOW);
}
