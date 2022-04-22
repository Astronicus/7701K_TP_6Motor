#ifndef IO_H
#define IO_H

extern pros::Motor frontLeft;
extern pros::Motor frontRight;
extern pros::Motor backLeft;
extern pros::Motor backRight;
extern pros::Motor frontClawMotor;
extern pros::Motor backFourBarMotor;
extern pros::Motor leftLift;
extern pros::Motor rightLift;

extern pros::Controller master;
extern pros::ADIDigitalIn tapA;
extern pros::ADIDigitalIn tapB;
extern pros::ADIDigitalIn tapC;

extern pros::ADIDigitalOut piston1;
extern pros::ADIDigitalOut piston2;

extern pros::Imu Inertial;

#endif
