#include <Servo.h>
#include <SoftwareSerial.h>
Servo servoX;
Servo servoY;
int level = 1;
SoftwareSerial bluetooth(10,11);
unsigned long lastMoveTime = 0;
int randomX, randomY, currentX, currentY;
bool isMovingX = false, isMovingY = false;
int targetDuration = 5000;

void setup() {
  servoX.attach(5);
  servoY.attach(4);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  servoX.write(0);
  servoY.write(90);
}

void loop() {
  if (bluetooth.available()) {
    int newLevel = Serial.parseInt();
    if (newLevel >= 1 && newLevel <= 4) {
      level = newLevel;
      Serial.print("Level changed to: ");
      Serial.println(level);

      if (level == 1) targetDuration = 5000;
      else if (level == 2) targetDuration = 3000;
      else if (level == 3) targetDuration = 2000;
      else if (level == 4) targetDuration = 1000;
    }
  }

  gameScope(targetDuration);
}

void gameScope(int duration) {
  unsigned long currentTime = millis();

  // Move servos only if the specified time interval has passed
  if (currentTime - lastMoveTime >= duration) {
    lastMoveTime = currentTime; // Reset last move time

    // Generate random positions for servos
    randomX = random(0, 150);
    randomY = random(0, 75);
    currentX = servoX.read();
    currentY = servoY.read();

    isMovingX = true;
    isMovingY = true;

    digitalWrite(8, HIGH);  // Turn on LED to indicate movement
  }

  // Move servo X gradually
  if (isMovingX) {
    if (randomX > currentX) {
      currentX++;
      servoX.write(currentX);
    } else if (randomX < currentX) {
      currentX--;
      servoX.write(currentX);
    } else {
      isMovingX = false;  // Movement complete
    }
  }

  // Move servo Y gradually
  if (isMovingY) {
    if (randomY > currentY) {
      currentY++;
      servoY.write(currentY);
    } else if (randomY < currentY) {
      currentY--;
      servoY.write(currentY);
    } else {
      isMovingY = false;  // Movement complete
    }
  }

  // Turn off LED when movement is complete
  if (!isMovingX && !isMovingY) {
    digitalWrite(8, LOW);
  }
}
