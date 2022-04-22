#ifndef ODOM_H
#define ODOM_H

void reset_tracker_wheels();
void move_drive(double vel, double vol);
void turnRel_imuTime(double degrees, double kb, double msTarget);
void turnRel_imu(double degrees, double kb);
void setWhichPos(int setPos);
void curvy_odom(double max_vel, double xf, double yf, double zone, double zone_constant);
void delay_update(double ms);
void turnAbs_imu(double degrees, double kb);
void turn_to_pos(double x, double y, double kb);
void curvy_odomBackward(double max_vel, double xf, double yf, double zone, double zone_constant);
void turn_to_pos_backward(double x, double y, double kb);

void setPos(double x, double y);
void update_position();

#endif
