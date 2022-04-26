#include "main.h"

int liftVelocity = -100;
int lowerVelocity = 100;

void liftControl(){
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  bool lowerLiftButton=master.get_digital(DIGITAL_L2);
  bool raiseLiftButton=master.get_digital(DIGITAL_L1);

  if(raiseLiftButton && lowerLiftButton){
    liftMotor.move_velocity(0);
  }
  else if (raiseLiftButton){
    liftMotor.move_velocity(liftVelocity);
  }
  else if (lowerLiftButton){
    liftMotor.move_velocity(lowerVelocity);
  }
  else{
    liftMotor.move_velocity(0);
  }

}
