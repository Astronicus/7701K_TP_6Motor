#ifndef IO_H
#define IO_H

extern pros::Motor frontLeft1;
extern pros::Motor frontLeft2;
extern pros::Motor frontRight1;
extern pros::Motor frontRight2;
extern pros::Motor backLeft;
extern pros::Motor backRight;
extern pros::Motor liftMotor;
extern pros::Motor conveyorMotor;

extern pros::Controller master;
extern pros::ADIDigitalIn tapA;
extern pros::ADIDigitalIn tapB;
extern pros::ADIDigitalIn tapC;

extern pros::ADIDigitalOut backPiston1;
extern pros::ADIDigitalOut backPiston2;

extern pros::ADIDigitalOut clawPiston1;
extern pros::ADIDigitalOut clawPiston2;

extern pros::Imu Inertial;

#endif
