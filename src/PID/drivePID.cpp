#include "main.h"

void drivePID(double distance, int maxVoltage){
  frontLeft.tare_position(); //set all motor positions to 0
  frontRight.tare_position();
  backLeft.tare_position();
  backRight.tare_position();

  double sp = distance * 1.5 * 360; //set point

  bool driving = true; //driving true until condition met
  float pConst = 0.2; //set constant values
  float iConst = 0.0;
  float dConst = 0.005;

  double targetPos{}; //initialize all with 0
  double currentPos{};
  double error{};
  double prev_error{};
  double integral{};
  double dError{};

  double kp{};
  double ki{};
  double kd{};

  double giveVoltage{};
  double realVelocity{};

  while(driving){
    targetPos = sp;
    currentPos = (backLeft.get_position() + backRight.get_position())/2;

    prev_error = error;
    error = targetPos - currentPos;
    dError = error - prev_error;

    kp = error * pConst;
    kd = (dError * dConst)/0.01;
    giveVoltage = kp + kd;

    printf("%f\n", kd);
    printf("%f\n", error);

    if(abs(giveVoltage) > maxVoltage){
      giveVoltage = maxVoltage * abs(giveVoltage)/giveVoltage; //keep the same sign
    }
    else if (abs(giveVoltage)<20){
      giveVoltage = 25 * abs(giveVoltage)/giveVoltage;
    }

    frontLeft.move(giveVoltage);
    frontRight.move(giveVoltage);
    backLeft.move(giveVoltage);
    backRight.move(giveVoltage);

    if(fabs(error) <= 10){
      break;
    }

    pros::delay(10);
  }

}

void turnPID(double degrees, int maxVoltage){
  frontLeft.tare_position(); //set all motor positions to 0
  frontRight.tare_position();
  backLeft.tare_position();
  backRight.tare_position();

  double sp = degrees * 1.5; //set point

  bool driving = true; //driving true until condition met
  float pConst = 0.35; //set constant values
  float iConst = 0.0;
  float dConst = 0.0010;

  double targetPos{}; //initialize all with 0
  double currentPos{};
  double error{};
  double prev_error{};
  double integral{};
  double dError{};

  double kp{};
  double ki{};
  double kd{};

  double giveVoltage{};
  double realVelocity{};

  while(driving){
    targetPos = sp;
    currentPos = (backLeft.get_position());

    prev_error = error;
    error = targetPos - currentPos;
    dError = error - prev_error;

    kp = error * pConst;
    kd = (dError * dConst)/0.01;
    giveVoltage = kp + kd;

    printf("%f\n", kd);
    printf("%f\n", error);

    if(abs(giveVoltage) > maxVoltage){
      giveVoltage = maxVoltage * abs(giveVoltage)/giveVoltage; //keep the same sign
    }
    else if (abs(giveVoltage)<35){
      giveVoltage = 35 * abs(giveVoltage)/giveVoltage;
    }

    frontLeft.move(-giveVoltage);
    frontRight.move(giveVoltage);
    backLeft.move(-giveVoltage);
    backRight.move(giveVoltage);

    if(fabs(error) <= 10){
      break;
    }

    pros::delay(10);
  }

}
