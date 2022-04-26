#ifndef CONTROL_H
#define CONTROL_H

//inmatch controls
void driveControl();
void backFourBarControl();
void liftControl();
void frontClawControl();
void backClawControl();
void driveControlARMS();

//auton methods
void hookRotate(float degrees, float vel);
void backBarUp(float velocity);
void backBarDown(float velocity);
void moveRel(float distance, float velocity);
void armMove(float distance, float velocity);
void turnRel(float distance, float velocity);
void turnPID(double degrees, int maxVoltage);
void drivePID(double distance, int maxVoltage);

void openClawPistons();
void closeClawPistons();
void openBackPistons();
void closeBackPistons();

void moveTime(float distance, float velocity, float time);
void barWhileMoveRel(float distance1, float distance2, float velocity1, float velocity2);
void moveDrive(float leftSpeed, float rightSpeed);

void update_position90();
void update_position180();
void update_position270();
void update_position0();

#endif
