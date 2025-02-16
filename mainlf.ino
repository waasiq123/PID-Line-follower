#include <L298N.h>
#include <QTRSensors.h>

#define AIN1 18
#define BIN1 26
#define AIN2 19
#define BIN2 27
#define PWMA 23
#define PWMB 25

L298N leftMotor(PWMA, AIN1, AIN2);
L298N rightMotor(PWMB, BIN1, BIN2);

const uint8_t SensorCount = 8;
QTRSensors qtr;
uint16_t sensorValues[SensorCount];

int baseSpeed = 150;
int maxSpeed = 200;
int error, lastError = 0;
int integral = 0;
float Kp = 0.045, Ki = 0.005, Kd = 0.8;

void setup() {
  Serial.begin(115200);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){32, 33, 34, 35, 36, 39, 12, 4}, SensorCount);

  for (uint16_t i = 0; i < 600; i++) {
    qtr.calibrate();
  }
}

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  bool allBlack = true;

  for (uint8_t i = 0; i < SensorCount; i++) {
    if (sensorValues[i] < 900) {
      allBlack = false;
      break;
    }
  }

  if (allBlack) {
    leftMotor.stop();
    rightMotor.stop();
    integral = 0;
    return;
  }

  error = position - 3500;
  integral += error;
  integral = constrain(integral, -2000, 2000);

  int correction = (Kp * error) + (Ki * integral) + (Kd * (error - lastError));
  lastError = error;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
  rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

  motorControl(leftSpeed, rightSpeed);
}

void motorControl(int left, int right) {
  if (left > 0) {
    leftMotor.setSpeed(left);
    leftMotor.backward();
  } else {
    leftMotor.setSpeed(-left);
    leftMotor.forward();
  }

  if (right > 0) {
    rightMotor.setSpeed(right);
    rightMotor.forward();
  } else {
    rightMotor.setSpeed(-right);
    rightMotor.backward();
  }
}
