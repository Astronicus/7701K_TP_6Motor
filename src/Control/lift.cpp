#include "main.h"

int liftVelocity = -100;
int lowerVelocity = 100;

void liftControl(){
  leftLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  bool lowerLiftButton=master.get_digital(DIGITAL_L2);
  bool raiseLiftButton=master.get_digital(DIGITAL_L1);

  if(raiseLiftButton && lowerLiftButton){
    leftLift.move_velocity(0);
    rightLift.move_velocity(0);
  }
  else if (raiseLiftButton){
    leftLift.move_velocity(liftVelocity);
    rightLift.move_velocity(liftVelocity);
  }
  else if (lowerLiftButton){
    leftLift.move_velocity(lowerVelocity);
    rightLift.move_velocity(lowerVelocity);
  }
  else{
    leftLift.move_velocity(0);
    rightLift.move_velocity(0);
  }

}
