#include <Servo.h>

Servo servoYB;
Servo servoX;
Servo servoYT;

float servoSensitivity = 2.0;

int servoRotLX = 90;
int servoRotLY = 90;
int servoRotRX = 90;

void setup() {
  servoYT.attach(8);
  servoYB.attach(9);
  servoX.attach(10);
  servoX.write(90);
  servoYB.write(90);
  servoYT.write(90);
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    servoRotLX += getLX(data) * servoSensitivity;
    servoRotLY += getLY(data) * servoSensitivity;
    servoRotRX += getRX(data) * servoSensitivity;
    servoRotRX = constrain(servoRotRX, 0 , 179);
    int forcedYB = servoRotLX + servoRotLY;
    int forcedYT = 180 - servoRotLX + servoRotLY;
    if (servoYB.read() != forcedYT) {
      servoYB.write(forcedYB);
    }
    if (servoYT.read() != forcedYT) {
      servoYT.write(forcedYT);
    }
    if (servoX.read() != servoRotRX) {
      servoX.write(servoRotRX);
    }
  }
}
int getRX(String d) {
  d = d.substring(2, 3);
  return parseNumbers(d.toInt());
}
int getLY(String d) {
  d = d.substring(5, 6);
  return parseNumbers(d.toInt());
}
int getLX(String d) {
  d = d.substring(8, 9);
  return parseNumbers(d.toInt());
}
int getRY(String d) {
  d = d.substring(11, 12);
  return parseNumbers(d.toInt());
}

int parseNumbers(int number) {
  int returnInt;
    if (number == 2) {
    returnInt =  -1;
  } else if (number == 0) {
    returnInt = 1;
  } else {
    returnInt = 0;
  }
  return returnInt;
}
