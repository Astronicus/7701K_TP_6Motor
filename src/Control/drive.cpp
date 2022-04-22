#include "main.h"

void brakeMode(){
  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
void coastMode(){
  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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

  double turnConst = 1.5;       // lower = linear, higher = cubic; cannot be 0
  double turnInput = master.get_analog(ANALOG_RIGHT_X) * (double)100 / 127.0;
  double turnSpeed = turnConst * (pow(turnInput, 3) / 10000 + turnInput / turnConst) / (turnConst + 1);

  float frontLeftMod = (LEFTY + turnSpeed); //front left
  float frontRightMod = (LEFTY - turnSpeed); //front right
  float backLeftMod = (LEFTY + turnSpeed); //back left
  float backRightMod = (LEFTY - turnSpeed); //back right

  frontLeft.move (frontLeftMod ); // * driveMultiplier
  frontRight.move(frontRightMod );
  backLeft.move  (backLeftMod  );
  backRight.move (backRightMod  );

} // Op Drive Ends//
