#include "main.h"

void moveRel(float distance, float velocity){
  distance*=1.5*360;
  /*frontLeft.tare_position();
  frontRight.tare_position();
  backLeft.tare_position();
  backRight.tare_position();
  */

  update_position();

  float targetDistance = distance + frontLeft1.get_position();
  moveDrive(velocity,velocity);

  int counter = 0;
  while (!((frontLeft1.get_position() < (targetDistance+10)) && (frontLeft1.get_position() > targetDistance-10))) {
  pros::delay(2);
  update_position();
  counter++;
  if(counter>3000){
    break;
  }
}
}

void moveTime(float distance, float velocity, float time){
  distance*=1.5*360;
  frontLeft1.tare_position();
  frontRight1.tare_position();
  frontLeft2.tare_position();
  frontRight2.tare_position();
  backLeft.tare_position();
  backRight.tare_position();

  frontLeft1.move_absolute(distance, velocity );
  frontRight1.move_absolute(distance, velocity);
  frontLeft2.move_absolute(distance, velocity );
  frontRight2.move_absolute(distance, velocity);
  backLeft.move_absolute(distance, velocity);
  backRight.move_absolute(distance, velocity);

  pros::delay(time);
}

void turnRel(float distance, float velocity){
  distance*=(2.93);

  float target = frontLeft1.get_position() - distance;

  frontLeft1.move_relative(-distance, velocity );
  frontRight1.move_relative(distance, velocity);
  frontLeft2.move_relative(-distance, velocity );
  frontRight2.move_relative(distance, velocity);
  backLeft.move_relative(-distance, velocity);
  backRight.move_relative(distance, velocity);

  float error = abs(target - frontLeft1.get_position());

  int counter = 0;
  while ( error > 10 ){
    error = abs(target - frontLeft1.get_position());
    pros::delay(5);
    update_position();
    if(error<10){
      break;
    }
  } //.makeworlds
  //counter++;

  /*if(counter%50 == 0){
    printf("%f\n",frontLeft.get_position());
  }
  */
}

void armMove(float distance, float velocity){
  distance*=2.92;
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  liftMotor.move_relative(distance, velocity);
  pros::delay(10);
  update_position();
}
void conveyorIntake(float time, float velocity){
  time*=10;
  conveyorMotor.move_relative(time, velocity);
}
