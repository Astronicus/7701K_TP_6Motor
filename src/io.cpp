#include "main.h"
//Motor Setup

#define frntLftMtr_PORT 20
#define frntRghtMtr_PORT 11
#define bckLftMtr_PORT 9
#define bckRghtMtr_PORT 4
#define frontClaw_PORT 14
#define backFourBar_PORT 2
#define leftLift_PORT 19
#define rightLift_PORT 5
#define inertial_PORT 1

#define piston_PORT 'A'
#define piston_PORT2 'B'
#define tapC_PORT 'E'
#define tapA_PORT 'C'
#define tapB_PORT 'D'

pros::Controller master (CONTROLLER_MASTER);

pros::Motor frontLeft(frntLftMtr_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontRight(frntRghtMtr_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeft(bckLftMtr_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRight(bckRghtMtr_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontClawMotor(frontClaw_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor backFourBarMotor(backFourBar_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor leftLift(leftLift_PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor rightLift(rightLift_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Imu Inertial(inertial_PORT);

pros::ADIDigitalOut piston1 (piston_PORT);
pros::ADIDigitalOut piston2 (piston_PORT2);
pros::ADIDigitalIn tapA (tapA_PORT);
pros::ADIDigitalIn tapB (tapB_PORT);
pros::ADIDigitalIn tapC (tapC_PORT);

//Sensor Setup
