#include <Servo.h>
Servo servoYB;
Servo servoX;
Servo servoYT;

int posTest = 0;
float servoSensitivity = 2.0;

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
    int servoRotX = getX(data);
    int servoRotY = getY(data);
    servoYB.write(servoRotY);
    servoX.write(servoRotX);
  }
}

int getX(String d){
  d.remove(d.indexOf("Y"));
  d.remove(d.indexOf("X"), 1);
  return d.toInt();
}

int getY(String d) {
  d.remove(d.indexOf("X"), d.indexOf("Y") + 1);
  return d.toInt();
}
