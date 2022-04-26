#include "main.h"

void frontClawControl(){
  bool closeHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  bool openHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

  if (closeHook){
    closeClawPistons();
  }
  else if(openHook){
    openClawPistons();
  }
}
void backClawControl(){
  bool closeHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  bool openHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);

  if (closeHook){
    closeBackPistons();
  }
  else if(openHook){
    openBackPistons();
  }
}

void openClawPistons(){
  clawPiston1.set_value(true);
  clawPiston2.set_value(true);
}
void closeClawPistons(){
  clawPiston1.set_value(false);
  clawPiston2.set_value(false);
}
void openBackPistons(){
  backPiston1.set_value(true);
  backPiston2.set_value(true);
}
void closeBackPistons(){
  backPiston1.set_value(false);
  backPiston2.set_value(false);
}

/*int hookVelocity = 150;

void hookControl(){
  hookMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  bool closeHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  bool openHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

  if(closeHook && openHook){
    hookMotor.move_velocity(0);
  }
  else if (closeHook){
    hookMotor.move_velocity(hookVelocity);
  }
  else if (openHook){
    hookMotor.move_velocity(-hookVelocity);
  }
  else{
    hookMotor.move_velocity(0);
  }
}
*/
