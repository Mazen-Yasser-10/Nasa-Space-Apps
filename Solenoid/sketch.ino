#include <Servo.h>
#include <SoftwareSerial.h>
Servo servoX;
Servo servoY;
int level = 1;
int targetDuration = 5000;
SoftwareSerial bluetooth(10,11);
unsigned long lastMoveTime = 0;
int randomX, randomY, currentX, currentY;
bool isMovingX = false, isMovingY = false;

void setup() 
{
  servoX.attach(5);
  servoY.attach(4);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  servoX.write(0);
  servoY.write(90);
}

void loop() 
{
  if (bluetooth.available()) 
  //if (Serial.available()) 
  {
    int newLevel = Serial.parseInt();
    if (newLevel >= 1 && newLevel <= 4) 
    {
      level = newLevel;
      Serial.print("Level changed to: ");
      Serial.println(level);

      if (level == 1) 
        targetDuration = 5000;
      else if (level == 2) 
        targetDuration = 3000;
      else if (level == 3) 
      targetDuration = 2000;
      else if (level == 4) 
      targetDuration = 1000;
    }
  }

  gameScope(targetDuration);
}

void gameScope(int duration) 
{
  unsigned long currentTime = millis();

  if (currentTime - lastMoveTime >= duration) 
  {
    lastMoveTime = currentTime;

    randomX = random(0, 150);
    randomY = random(0, 75);
    currentX = servoX.read();
    currentY = servoY.read();

    isMovingX = true;
    isMovingY = true;

    digitalWrite(8, HIGH);
  }

  if (isMovingX) 
  {
    if (randomX > currentX) 
    {
      currentX++;
      servoX.write(currentX);
    } 
    else if (randomX < currentX) 
    {
      currentX--;
      servoX.write(currentX);
    } 
    else 
    {
      isMovingX = false;
    }
  }

  if (isMovingY) 
  {
    if (randomY > currentY) 
    {
      currentY++;
      servoY.write(currentY);
    } 
    else if (randomY < currentY) 
    {
      currentY--;
      servoY.write(currentY);
    }
    else 
    {
      isMovingY = false;
    }
  }

  if (!isMovingX && !isMovingY)
    digitalWrite(8, LOW);
}