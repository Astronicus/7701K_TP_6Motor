#include "main.h"

void brakeMode(){
  frontLeft1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontLeft2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontRight1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontRight2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coastMode(){
  frontLeft1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontLeft2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void moveDrive(float leftSpeed, float rightSpeed){
  frontLeft1.move(leftSpeed);
  frontRight1.move(rightSpeed);
  frontLeft2.move(leftSpeed);
  frontRight2.move(rightSpeed);
  backLeft.move(leftSpeed);
  backRight.move(rightSpeed);
}
void printDriveSpeeds(float fl, float fr, float bl, float br){
  pros::lcd::print(0,"FL: %f",fl);
  pros::lcd::print(1,"FR: %f",fr);
  pros::lcd::print(2,"BL: %f",bl);
  pros::lcd::print(3,"BR: %f",br);
}
////////////////////////////////////////////////////////////////////////////////

void driveControl() { //split arcade drive
  float LEFTY= master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  float RIGHTX= master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  //Linear multiply so forward/backward maxes at 100
  LEFTY = LEFTY * 1.10;
  if(LEFTY>127){
    LEFTY = 127;
  }

  //Linear multiply for turns (no longer used)
  //RIGHTX = RIGHTX * 5/6;

  //Deadzones
  if( (LEFTY < 5) && (LEFTY > -5) ){
    LEFTY=0;
  }
  if( (RIGHTX < 5) && (RIGHTX > -5) ){
    RIGHTX=0;
  }

  double turnConst = 1.67;       // lower = linear, higher = cubic; cannot be 0
  double turnInput = master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127.0;
  double turnSpeed = turnConst * (pow(turnInput, 3) / 10000 + turnInput / turnConst) / (turnConst + 1);
  turnSpeed = turnSpeed * 0.85;

  float leftMod = (LEFTY + turnSpeed); //front left
  float rightMod = (LEFTY - turnSpeed); //front right

  coastMode();
  moveDrive(leftMod,rightMod);
} // Op Drive Ends//
