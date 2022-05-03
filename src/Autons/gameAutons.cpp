#include "main.h"

extern double global_x;
extern double global_y;


void leftWPAuton(){
  closeBackPistons();
  pros::delay(350);
  conveyorIntake(10,113);
  turnRel(90,75);
  openBackPistons();
  moveRel(2.3,200);
  closeClawPistons();
  moveRel(-2.0,100);
  
}

void rightWPAuton(){
  openBackPistons();
  moveRel(-0.8,100);
  closeBackPistons();
  conveyorIntake(10,113);
  turnRel(180,100);
  openBackPistons();
  turnRel(-60,100);
  moveRel(2.8,100);
  closeClawPistons();
  moveRel(-2.0,100);


}

void leftAuton(){
}

void rightAuton(){
}

void leftCentAuton(){
}

void rightCentAuton(){
}

void doNothing(){
}
