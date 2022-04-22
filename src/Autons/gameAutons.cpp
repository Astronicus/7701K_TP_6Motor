#include "main.h"

extern double global_x;
extern double global_y;

void leftAuton(){
  setWhichPos(90);
  backBarDown(200);
  pros::delay(175);
	barWhileMoveRel(-2.05,-0.45,200,200);
  pros::delay(250);
	backBarUp(150);
	pros::delay(150);
	moveRel(2.1,200);
  turnRel(180,100);
}

void rightAuton(){
  setWhichPos(90);
  backBarDown(200);
  pros::delay(100);
	barWhileMoveRel(-2.05,-0.45,200,200);
  pros::delay(250);
	backBarUp(150);
	pros::delay(150);
	moveRel(2.1,200);
  turnRel(180,100);
}

void leftWPAuton(){
  setWhichPos(180);
  setPos(1.2,0.5);
  piston1.set_value(true);
  piston2.set_value(true);
  pros::delay(1000);
  moveRel(0.3,100);
  turn_to_pos_backward(3,3,1);
  backBarDown(200);
  pros::delay(300);
  barWhileMoveRel(-2.0,-0.6,150,150);
  pros::delay(450);
  moveRel(2.0,100);


}

void rightWPAuton(){
  setWhichPos(270);
  setPos(5.5,0.5);
  moveRel(-0.8,75);
  pros::delay(500);
  piston1.set_value(true);
  piston2.set_value(true);
  pros::delay(500);
  moveRel(0.7,75);
  delay_update(500);
  backBarDown(200);
  delay_update(1000);
  moveRel(-1.2,75);
  delay_update(500);
  backBarUp(150);
  delay_update(750);
  turnRel(145,100);
  delay_update(500);
  moveRel(-0.8,100);
  delay_update(250);
  backBarDown(200);
  delay_update(750);
  moveRel(0.3,100);
  delay_update(200);
  turn_to_pos_backward(3,3,0.95);
  curvy_odomBackward(127,3,3,0,0);
  delay_update(500);
  backBarUp(200);
  delay_update(500);
  moveRel(2.5,150);


}

void skillsRun(){
  setWhichPos(90);
  setPos(5.5,0.4);
  armMove(1,100);
  openPistons();
  delay_update(2000);
  curvy_odom(100,5.5,0.735,0,0);
  delay_update(100);
  closePistons();
  armMove(-0.63,100);
  delay_update(1250); //first goal up in arm

  backBarDown(150);
  curvy_odom(100,5.5,5.17,0,0);
  turnAbs_imu(3,1);
  curvy_odomBackward(60,4.84,5.07,0,0);
  backBarUp(150);
  delay_update(1000);
  moveRel(0.175,80); //back goal picked up

  turn_to_pos(3.8,4,1);
  curvy_odom(100,2.95,4,0,0);
  turn_to_pos(2.95,6,1);
  moveRel(0.7,125);
  openPistons();
  delay_update(200);
  moveRel(-0.5,100); //first goal stacked

  delay_update(250);
  armMove(0.63,100);
  turn_to_pos(4.35,2.9,1);
  curvy_odom(100,4.35,2.9,0,0);
  closePistons(); //pick up yellow

  delay_update(250);
  armMove(-0.66,100);
  turn_to_pos(2.88,4.08,0.875);
  delay_update(500);
  curvy_odom(100,2.88,4.08,0,0);
  turnAbs_imu(90,1);
  moveRel(0.58,160);
  openPistons();
  delay_update(200);
  moveRel(-0.28,100); //2nd goal stacked

  armMove(-0.2,100);
  turnAbs_imu(270,0.86);
  moveRel(2.07,125);
  delay_update(500);
  moveRel(-0.25,125); //yellow has been pushed to 1.5,4.5


  delay_update(500);
  turnAbs_imu(180,1.01);
  pros::delay(500);
  moveRel(1.5,100);
  delay_update(300);
  turnAbs_imu(90,1.01);
  delay_update(300);
  moveRel(2.3,125);
  delay_update(300);
  delay_update(300); //yellow pushed

  turnAbs_imu(180,1.01);
  delay_update(250);
  armMove(0.88,100);
  delay_update(1500);
  moveRel(0.50,80);
  delay_update(750);
  closePistons(); //upper lefct picked up
  moveRel(-0.15,100);

  armMove(-0.80,100);
  delay_update(1500);
  turnRel_imu(94,1.01);
  moveRel(4.5,125);







  printf("Done");
}

void skillsRun2(){
  openPistons();
  armMove(1,100);
  pros::delay(2750);
  moveRel(0.6,75);
  pros::delay(500);
  closePistons();
  armMove(-0.90,100);
  pros::delay(2750);
  moveTime(-1.0,75,3000);
  //back to orig position

  moveRel(0.16,50);
  pros::delay(500);
  turnRel(90,100);
  pros::delay(400);
  backBarDown(200);
  pros::delay(300);
  moveRel(-3.5,150);
  pros::delay(300);
  backBarUp(100);
  turnRel(-90,100);
  pros::delay(500);
  moveRel(1,100);
  armMove(0.9,100);
  pros::delay(2500);
  openPistons();
  moveRel(-0.5,100);
  armMove(-0.9,100);
  pros::delay(1500);
  turnRel(180,100);
  pros::delay(1500);
  moveRel(0.6,50);
//against the wall facing perpendicular
  turnRel(90,100);
  moveRel(-3,100);
  pros::delay(500);
  backBarDown(200);
  pros::delay(1000);
  moveRel(0.5,100);
  backBarUp(200);
  pros::delay(1000);

  //two goals, now rest of regular skills run

  turnRel(50,100);
  moveRel(3.1,100);
  moveRel(-0.2,100);
  turnRel(-58,80);
  moveRel(-2.83,100);
  pros::delay(500);
  moveRel(0.2,100);
  pros::delay(500);
  turnRel(-65,80);
  pros::delay(500);
  backBarDown(200);
  pros::delay(1000);
  moveTime(-1.80,50,3000);
  pros::delay(1000);
  backBarUp(125);
  pros::delay(2000);
  moveRel(0.5,100);
  pros::delay(400);
  turnRel(78,80);
  pros::delay(500);
  moveRel(6,125);



}

void skillsRun3(){

}

void doNothing(){

}

void neutralDistAuton(){
  backBarDown(200);
	moveRel(-2.05,125);
	pros::delay(500);
	backBarUp(100);
	pros::delay(1000);
	moveRel(1.8,150);
}
