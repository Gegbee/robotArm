#include <Servo.h>

Servo servoYB;
Servo servoX;
Servo servoYT;

float servoSensitivity = 4.0;

int servoRotY = 90;
int servoRotX = 90;
int servoRotZ = 90;

void setup() {
  servoYT.attach(8);
  servoYB.attach(9);
  servoX.attach(10);
  servoX.write(90);
  servoYB.write(90);
  servoYT.write(90);
  Serial.begin(9600);
  Serial.setTimeout(15);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    int sb = (getLY(data) * servoSensitivity);
    int st = (getRY(data) * servoSensitivity);
    int sx = (getRX(data) * servoSensitivity);
    servoRotZ += st;
    servoRotY += sb;
    servoRotX += sx;
    servoRotX = constrain(servoRotX, 0 , 179);
    servoRotY = constrain(servoRotY, 0 , 179);
    servoRotZ = constrain(servoRotZ, 0 , 179);
    if (servoYB.read() != servoRotZ) {
      servoYB.write(servoRotZ);
    }
    if (servoYT.read() != servoRotY) {
      servoYT.write(servoRotY);
    }
    if (servoX.read() != servoRotX) {
      servoX.write(servoRotX);
    }
  }
}
int getRX(String d) {
  d = d.substring(2, 3);
  return parseNumbers(d.toInt());
}
int getLX(String d) {
  d = d.substring(5, 6);
  return parseNumbers(d.toInt());
}
int getLY(String d) {
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
