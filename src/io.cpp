#include "main.h"
//Motor Setup

#define frntLftMtr1_PORT 4
#define frntLftMtr2_PORT 3
#define bckLftMtr_PORT 5
#define frntRghtMtr1_PORT 1
#define frntRghtMtr2_PORT 2
#define bckRghtMtr_PORT 6

#define lift_PORT 7
#define conveyor_PORT 20

#define clawPiston1_PORT 'H'
#define clawPiston2_PORT 'G'
#define backPiston1_PORT 'B'
#define backPiston2_PORT 'B'

#define tapC_PORT 'E'
#define tapA_PORT 'C'
#define tapB_PORT 'D'
#define inertial_PORT 1

pros::Controller master (CONTROLLER_MASTER);

pros::Motor frontLeft1(frntLftMtr1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontLeft2(frntLftMtr2_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeft(bckLftMtr_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontRight1(frntRghtMtr1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontRight2(frntRghtMtr2_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRight(bckRghtMtr_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor liftMotor(lift_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor conveyorMotor(conveyor_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Imu Inertial(inertial_PORT);

pros::ADIDigitalOut clawPiston1 (clawPiston1_PORT);
pros::ADIDigitalOut clawPiston2 (clawPiston2_PORT);

pros::ADIDigitalOut backPiston1 (backPiston1_PORT);
pros::ADIDigitalOut backPiston2 (backPiston2_PORT);

pros::ADIDigitalIn tapA (tapA_PORT);
pros::ADIDigitalIn tapB (tapB_PORT);
pros::ADIDigitalIn tapC (tapC_PORT);

//Sensor Setup
