#include "main.h"

void hookControl(){
  bool closeHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  bool openHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

  if (closeHook){
    piston1.set_value(false);
    piston2.set_value(false);
    pros::lcd::print(1,"true pressed");
  }
  else if(openHook){
    piston1.set_value(true);
    piston2.set_value(true);
    pros::lcd::print(1,"false ressed");
  }
}
void frontClawControl(){
  frontClawMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  bool closeHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  bool openHook = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  if (closeHook){
    frontClawMotor.move_velocity(-100);
  }
  else if(openHook){
    frontClawMotor.move_velocity(100);
  }
  else{
    frontClawMotor.move_velocity(0);
  }
}
void openPistons(){
  piston1.set_value(true);
  piston2.set_value(true);
}
void closePistons(){
  piston1.set_value(false);
  piston2.set_value(false);
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
