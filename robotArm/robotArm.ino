#include <Servo.h>
Servo servoYB;
Servo servoX;
Servo servoYT;

float servoSensitivity = 4.0;

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
//    servoRotLX += getLX(data) * servoSensitivity;
//    servoRotLY += getLY(data) * servoSensitivity;
    servoRotRX += getRX(data) * servoSensitivity;
    servoRotRX = constrain(servoRotRX, 0 , 179);
//    int forcedYT = (180 - servoRotLX);
//    int forcedYB = servoRotLX;
//    servoYB.write(forcedYB);
//    servoYT.write(forcedYT);
    if (servoX.read() != servoRotRX) {
      servoX.write(servoRotRX);
    }
  }
}
int getRX(String d) {
  d = d.substring(2, d.indexOf("L"));
  int returnInt = d.toInt();
  if (returnInt == 2) {
    returnInt =  -1;
  } else if (returnInt == 0) {
    returnInt = 1;
  } else {
    returnInt = 0;
  }
  return returnInt;
}
int getLY(String d) {
  d.remove(0, d.indexOf("LY") + 1);
  d.remove(d.indexOf("R"), 2);
  return d.toInt();
}
int getLX(String d) {
  d.remove(0, d.indexOf("R") + 2);
  return d.toInt();
}
