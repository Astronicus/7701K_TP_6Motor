#include "main.h"

# define WHEEL_CIRCUMFRENCE 17.01696021 //added gear ratio //10.2101761241668280 // 3.25 in
# define TURN_CONSTANT 1
# define pi 3.14159265359
int imuSign = -1;

extern double global_x;
extern double global_y;
extern double orientation_degrees;
extern int whichPos;
extern bool updateSlow;

extern double global_orientation0;
extern double global_orientation90;
extern double global_orientation180;
extern double global_orientation270;

extern double global_orientation; //in rad
extern double orientation_degrees;

int count = 0;

void reset_tracker_wheels(){
  //leftEncoder.reset();
  //rightEncoder.reset();
  backLeft.tare_position();
  backRight.tare_position();
}


void move_drive(double vel, double vol){
  frontLeft.move(vel);
  frontRight.move(vol);
  backLeft.move(vel);
  backRight.move(vol);
}


void stop_drive(){
  frontLeft.move(0);
  frontRight.move(0);
  backLeft.move(0);
  backRight.move(0);
  frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  backRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void turnRel_imuTime(double degrees, double kb, double msTarget) {
  updateSlow = true;

  double target;
  target = ((imuSign * Inertial.get_rotation()) + degrees) * TURN_CONSTANT;
  double init_error = target - (imuSign * Inertial.get_rotation());
  double P_Gain = 1.4;
  double I_Gain = 0.000;
  double D_Gain = 0;
  double prev_error = 0;
  double error = 0;
  double error_sum = 0;
  double derror = 0;
  double vel = 0;
  double vel_error = 0;
  double kp_vel = 0;
  double final_vol = 0;
  double I_Gain2 = 0;

  int arrived = 0;
  int i_counter = 0;

  double brake = 0;

  bool timeLimit = true;
  int iter=0;
  if(msTarget==0){
    timeLimit=false;
  }

  while (true) {
    error = target - (imuSign * Inertial.get_rotation());
    error_sum += error;

    derror = (error - prev_error) / .01;

    if (fabs(error) > (fabs(init_error) * .75)) {
      P_Gain = 0;
      I_Gain = 0.035;
      D_Gain = 0;

    }
    else{
      P_Gain = 2.00;
      I_Gain = 0.00;
      I_Gain2 = 0.025;
      D_Gain = 1.8;
    }

    if (fabs(error) < 0.75 * abs(init_error) && fabs(error) > 10 && derror > 10) {
      error_sum = 0;
    }

    //set absolute value of velocity
    vel = (P_Gain * error) + (D_Gain * (derror / 16)) + (I_Gain * error_sum);
    prev_error = error;
    if (fabs(vel) > 80) {
      vel = (fabs(error) / error) * 80;
    }
    if (fabs(vel) < 30) {
      vel = (fabs(error) / error) * 30;
      if (derror<10) vel+= (I_Gain2 * error_sum);
    }
    vel_error = vel - derror;
    final_vol = (kb * vel);

    if (iter%100 == 0){
    printf("angle error for turn: %f     voltage:   %f", error, final_vol);
    printf("\n");
  }


    move_drive(-final_vol, final_vol);
    //verify robot is at position for a certain period of time
    if (error > -.5 && error < .5) {
      error_sum = 0;
      arrived += 1;
    }
    if (arrived == 1) {
      //reset_tracker_wheels();
      brake = fabs(final_vol) / final_vol * -20;
      move_drive(-brake, brake);
      pros::delay(50);
      move_drive(0, 0);
      break;

    }
    if(timeLimit && iter >= msTarget){
      break;
    }
    iter+=10;

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    pros::delay(10);
  }
}

void turnRel_imu(double degrees, double kb) {
  updateSlow = true;

  double target;
  target = ((imuSign * Inertial.get_rotation()) + degrees) * TURN_CONSTANT;
  double init_error = target - (Inertial.get_rotation() * imuSign);
  double P_Gain = 1.2;
  double I_Gain = 0.000;
  double D_Gain = 0;
  double prev_error = 0;
  double error = 0;
  double error_sum = 0;
  double derror = 0;
  double vel = 0;
  double vel_error = 0;
  double kp_vel = 0;
  double final_vol = 0;
  double I_Gain2 = 0;

  int arrived = 0;
  int i_counter = 0;

  double brake = 0;

  while (true) {
    error = target - (imuSign * Inertial.get_rotation());
    error_sum += error;

    derror = (error - prev_error) / .01;

    if (fabs(error) > (fabs(init_error) * .75)) {
      P_Gain = 0;
      I_Gain = 0.035;
      D_Gain = 0;

    }
    else{
      P_Gain = 2.00;
      I_Gain = 0.00;
      I_Gain2 = 0.025;
      D_Gain = 1.8;
    }

    if (fabs(error) < 0.75 * abs(init_error) && fabs(error) > 15 && abs(derror)<10) {
      error_sum = 0;
    }


    //set absolute value of velocity
    vel = (P_Gain * error) + (D_Gain * (derror / 16)) + (I_Gain * error_sum);
    prev_error = error;
    if (fabs(vel) > 80) {
      vel = (fabs(error) / error) * 80;
    }
      if (fabs(vel) < 30) {
        vel = (fabs(error) / error) * 30;
        if (derror<10) vel+= (I_Gain2 * error_sum);
      }
    vel_error = vel - derror;
    final_vol = (kb * vel);

    if (count%6 == 0){
    printf(" angle error: %f", error);
    printf("   VOLTAGE: %f    ", final_vol);
  }


    move_drive(-final_vol, final_vol);
    //verify robot is at position for a certain period of time
    if (error > -.5 && error < .5) {
      error_sum = 0;
      arrived += 1;
    }
    if (arrived == 1) {
      //reset_tracker_wheels();
      brake = fabs(final_vol) / final_vol * -20;
      move_drive(-brake, brake);
      pros::delay(50);
      move_drive(0, 0);
      break;

    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    pros::delay(10);
    count++;
  }
}

void turnAbs_imu(double degrees, double kb){
  updateSlow = true;

  double target;
  target = degrees;
  double init_error = target - (orientation_degrees);
  double P_Gain = 1.2;
  double I_Gain = 0.000;
  double D_Gain = 0;
  double prev_error = 0;
  double error = 0;
  double error_sum = 0;
  double derror = 0;
  double vel = 0;
  double vel_error = 0;
  double kp_vel = 0;
  double final_vol = 0;
  double I_Gain2 = 0;

  int arrived = 0;
  int i_counter = 0;

  double brake = 0;

  if(init_error >= 180){
    while(init_error>=180){
      target-=360;
      init_error-=360;
    }

  }
  else if(init_error <= -180){
    while(init_error<=-180){
      target+=360;
      init_error+=360;
    }
  }

  while (true) {
    error = target - (orientation_degrees);
    error_sum += error;

    derror = (error - prev_error) / .01;

    if (fabs(error) > (fabs(init_error) * .75)) {
      P_Gain = 0;
      I_Gain = 0.035;
      D_Gain = 0;

    }
    else{
      P_Gain = 2.00;
      I_Gain = 0.00;
      I_Gain2 = 0.025;
      D_Gain = 1.8;
    }

    if (fabs(error) < 0.75 * abs(init_error) && fabs(error) > 15 && derror > 10) {
      error_sum = 0;
    }

    //set absolute value of velocity
    vel = (P_Gain * error) + (D_Gain * (derror / 16)) + (I_Gain * error_sum);
    prev_error = error;
    if (fabs(vel) > 80) {
      vel = (fabs(error) / error) * 80;
    }
    if (fabs(vel) < 30) {
      vel = (fabs(error) / error) * 30;
      if (derror<10) vel+= (I_Gain2 * error_sum);
    }
    vel_error = vel - derror;
    final_vol = (kb * vel);

    if (count%10 == 0){
    printf("angle error: %f", error);
    printf("\n");
  }


    move_drive(-final_vol, final_vol);
    //verify robot is at position for a certain period of time
    if (error > -.5 && error < .5) {
      error_sum = 0;
      arrived += 1;
    }
    if (arrived == 1) {
      //reset_tracker_wheels();
      brake = fabs(final_vol) / final_vol * -20;
      move_drive(-brake, brake);
      pros::delay(50);
      move_drive(0, 0);
      break;

    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    pros::delay(10);
    count++;
  }

}

void turn_to_pos(double x, double y, double kb){
  updateSlow = true;
  x = x * 503;
  y = y * 503;

  double target = atan2((y - global_y) , (x - global_x)) * (180/pi);
  updateSlow = true;

  double init_error = target - (orientation_degrees);
  double P_Gain = 1.2;
  double I_Gain = 0.000;
  double D_Gain = 0;
  double prev_error = 0;
  double error = 0;
  double error_sum = 0;
  double derror = 0;
  double vel = 0;
  double vel_error = 0;
  double kp_vel = 0;
  double final_vol = 0;
  double I_Gain2 = 0;

  int arrived = 0;
  int i_counter = 0;

  double brake = 0;

  printf("%f",init_error);

  if(init_error >= 180){
    while(init_error > 180){
      init_error-=360;
      target-=360;
    }
    printf("\nSUBTRACTED!");
  }
  else if(init_error <= -180){
    while(init_error <= -180){
      init_error+=360;
      target+=360;
    }
    printf("ADDED!\nADDED!\n");
  }

  while (true) {
    error = target - (orientation_degrees);
    error_sum += error;

    derror = (error - prev_error) / .01;

    if (fabs(error) > (fabs(init_error) * .75)) {
      P_Gain = 0;
      I_Gain = 0.035;
      D_Gain = 0;

    }
    else{
      P_Gain = 2.00;
      I_Gain = 0.00;
      I_Gain2 = 0.025;
      D_Gain = 1.8;
    }

    if (fabs(error) < 0.75 * abs(init_error) && fabs(error) > 15 && derror > 3) {
      error_sum = 0;
    }


    //set absolute value of velocity
    vel = (P_Gain * error) + (D_Gain * (derror / 16)) + (I_Gain * error_sum);
    prev_error = error;
    if (fabs(vel) > 80) {
      vel = (fabs(error) / error) * 80;
    }
    if (fabs(vel) < 30) {
      vel = (fabs(error) / error) * 30;
      if (derror<10) vel += (I_Gain2 * error_sum);
    }
    vel_error = vel - derror;
    final_vol = (kb * vel);

    if (count%6 == 0){
    printf(" angle error: %f", error);
    printf("   VOLTAGE: %f    ", final_vol);
    printf("");
  }


    move_drive(-final_vol, final_vol);
    //verify robot is at position for a certain period of time
    if (error > -.5 && error < .5) {
      error_sum = 0;
      arrived += 1;
    }
    if (arrived == 1) {
      //reset_tracker_wheels();
      brake = fabs(final_vol) / final_vol * -20;
      move_drive(-brake, brake);
      pros::delay(50);
      move_drive(0, 0);
      break;

    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    pros::delay(10);
    count++;
  }
}

void turn_to_pos_backward(double x, double y, double kb){
  updateSlow = true;
  x = x * 503;
  y = y * 503;

  double target = atan2((y - global_y) , (x - global_x)) * (180/pi) + 180;
  updateSlow = true;

  double init_error = target - (orientation_degrees);
  double P_Gain = 1.2;
  double I_Gain = 0.000;
  double D_Gain = 0;
  double prev_error = 0;
  double error = 0;
  double error_sum = 0;
  double derror = 0;
  double vel = 0;
  double vel_error = 0;
  double kp_vel = 0;
  double final_vol = 0;
  double I_Gain2 = 0;

  int arrived = 0;
  int i_counter = 0;

  double brake = 0;

  printf("%f",init_error);

  if(init_error >= 180){
    while(init_error > 180){
      init_error-=360;
      target-=360;
    }
    printf("\nSUBTRACTED!");
  }
  else if(init_error <= -180){
    while(init_error <= -180){
      init_error+=360;
      target+=360;
    }
    printf("ADDED!\nADDED!\n");
  }

  while (true) {
    error = target - (orientation_degrees);
    error_sum += error;

    derror = (error - prev_error) / .01;

    if (fabs(error) > (fabs(init_error) * .75)) {
      P_Gain = 0;
      I_Gain = 0.035;
      D_Gain = 0;

    }
    else{
      P_Gain = 2.00;
      I_Gain = 0.00;
      I_Gain2 = 0.025;
      D_Gain = 1.8;
    }

    if (fabs(error) < 0.75 * abs(init_error) && fabs(error) > 15 && derror > 3) {
      error_sum = 0;
    }


    //set absolute value of velocity
    vel = (P_Gain * error) + (D_Gain * (derror / 16)) + (I_Gain * error_sum);
    prev_error = error;
    if (fabs(vel) > 80) {
      vel = (fabs(error) / error) * 80;
    }
    if (fabs(vel) < 30) {
      vel = (fabs(error) / error) * 30;
      if (derror<10) vel += (I_Gain2 * error_sum);
    }
    vel_error = vel - derror;
    final_vol = (kb * vel);

    if (count%6 == 0){
    printf(" angle error: %f", error);
    printf("   VOLTAGE: %f    ", final_vol);
    printf("");
  }


    move_drive(-final_vol, final_vol);
    //verify robot is at position for a certain period of time
    if (error > -.5 && error < .5) {
      error_sum = 0;
      arrived += 1;
    }
    if (arrived == 1) {
      //reset_tracker_wheels();
      brake = fabs(final_vol) / final_vol * -20;
      move_drive(-brake, brake);
      pros::delay(50);
      move_drive(0, 0);
      break;

    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    pros::delay(10);
    count++;
  }
}

void curvy_odom(double max_vel, double xf, double yf, double zone, double zone_constant) {
  updateSlow = false;

  xf = xf * 503;
  yf = yf * 503;

  double error;
  double init_error = sqrt(pow((global_x - xf), 2) + pow((global_y - yf), 2));
  double total_error;
  double desired_angle = atan2((yf - global_y) , (xf - global_x));
  double init_angle_error = desired_angle - global_orientation;
  double angle_error;
  double correction;
  double vel_target;
  double vel_error;
  double final_vol;
  double arrived = 0;

  double kB = 1;
  double kp = .2;
  double kd = 0;
  double ki = .002;

  double kpa = .02;

  double kc = .2;

  double vel_kp;
  double i_counter;

  double flip = 1;

  double init_length = fabs(backLeft.get_position());
  double length = 0;

  printf("\n\n\n\nInitial Angle Error:%f\n", init_angle_error);
  printf("Desired Angle:%f\n", desired_angle);
  printf("Global Orientation %f\n", global_orientation);
  printf("Global Orientation90 %f\n", global_orientation90);
  printf("\n\n\n\n\n");

  while (true) {
    length = fabs(fabs(backLeft.get_position()) - init_length);
    error = sqrt(pow((global_x - xf), 2) + pow((global_y - yf), 2));
    total_error += error;
    desired_angle = atan2((yf - global_y) , (xf - global_x));


    if (fabs(error) > (fabs(init_error) * .75)) {
      kp = 0;
      ki = 0.00002;
      kd = 0;

    }
    else{
      kp = .3;
      ki = 0.00002;
      kd = .2;
      if (fabs(error) < 250) {
        ki = 0.00002;
        i_counter ++;
        if(i_counter == 1){
          total_error = 0;
        }
      }
    }
    angle_error = desired_angle - global_orientation;
    if(fabs(angle_error) > pi){
      if(angle_error>=0){
        while(angle_error > pi){
          angle_error -= 2*pi;
        }
        if(count%3000==0){
          printf("Subtracted angle");
        }
      }
      else{
        while(angle_error < -1 * pi){
          angle_error += 2*pi;
        }
      }
    }

    vel_target = flip * ((error * kp) + (total_error * ki));
    final_vol = kB * vel_target;
     if (fabs(final_vol) > max_vel) {
      final_vol = fabs(final_vol) / final_vol * max_vel;
    }


    if(fabs(length) < zone){
      correction = zone_constant;
      if(flip == 1){
        if(fabs(angle_error) / angle_error == 1){
          move_drive(final_vol * correction, final_vol);
        }
        if(fabs(angle_error) / angle_error == -1){
          move_drive(final_vol, final_vol * correction);
        }
      }
      else{
        if(fabs(angle_error) / angle_error == -1){
          move_drive(final_vol * correction, final_vol);
        }
        if(fabs(angle_error) / angle_error == 1){
          move_drive(final_vol, final_vol * correction);
        }
      }
    }
    else{

      correction = .85 - (kpa * fabs(angle_error * (180 / pi)));
      if (correction < .2){
        correction = .2;
      }

        if(flip == 1){
          if(fabs(angle_error) / angle_error == 1){
            move_drive(final_vol * correction, final_vol);
          }
          if(fabs(angle_error) / angle_error == -1){
            move_drive(final_vol, final_vol * correction);
          }
          if(fabs(angle_error) / angle_error == 0){
            move_drive(final_vol, final_vol);
          }
        }
        else{
          if(fabs(angle_error) / angle_error == -1){
            move_drive(final_vol * correction, final_vol);
          }
          if(fabs(angle_error) / angle_error == 1){
            move_drive(final_vol, final_vol * correction);
          }
          if(fabs(angle_error) / angle_error == 0){
            move_drive(final_vol, final_vol);
          }
        }
    }

    if (error < 50) {
      arrived++;
    }
    if (arrived == 1) {
      move_drive(0, 0);
      break;
    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    count++;
    if(count%6000==0){
      printf("%f", angle_error);
      printf("\n");
    }

  }
}

void curvy_odomBackward(double max_vel, double xf, double yf, double zone, double zone_constant) {
  updateSlow = false;

  xf = xf * 503;
  yf = yf * 503;

  double error;
  double init_error = sqrt(pow((global_x - xf), 2) + pow((global_y - yf), 2));
  double total_error;
  double desired_angle = atan2((yf - global_y) , (xf - global_x)) + pi;
  double init_angle_error = desired_angle - global_orientation;
  double angle_error;
  double correction;
  double vel_target;
  double vel_error;
  double final_vol;
  double arrived = 0;

  double kB = 1;
  double kp = .2;
  double kd = 0;
  double ki = .002;

  double kpa = .02;

  double kc = .2;

  double vel_kp;
  double i_counter;

  double flip = 1;

  double init_length = fabs(backLeft.get_position());
  double length = 0;

  printf("Initial Angle Error:%f\n", init_angle_error);
  printf("Desired Angle:%f\n", desired_angle);
  printf("Global Orientation %f\n", global_orientation);
  printf("Global Orientation90 %f\n", global_orientation90);
  printf("\n\n\n\n\n");

  while (true) {
    length = fabs(fabs(backLeft.get_position()) - init_length);
    error = sqrt(pow((global_x - xf), 2) + pow((global_y - yf), 2));
    total_error += error;
    desired_angle = atan2((yf - global_y) , (xf - global_x)) + pi;


    if (fabs(error) > (fabs(init_error) * .75)) {
      kp = 0;
      ki = 0.00002;
      kd = 0;
    }
    else{
      kp = .3;
      ki = 0;
      kd = .2;
      if (fabs(error) < 250) {
        ki = 0.00002;
        i_counter ++;
        if(i_counter == 1){
          total_error = 0;
        }
      }
    }
    angle_error = desired_angle - global_orientation;
    if(fabs(init_angle_error) > pi){
      if(fabs(desired_angle) / desired_angle == 1){
        while(desired_angle > pi){
          desired_angle-= 2*pi;
          angle_error = desired_angle - global_orientation;
        }
      }
      else{
        while(desired_angle < -pi){
          desired_angle+= 2*pi;
          angle_error = desired_angle - global_orientation;
      }
    }
  }
    vel_target = flip * ((error * kp) + (total_error * ki));
    final_vol = kB * vel_target;
     if (fabs(final_vol) > max_vel) {
      final_vol = fabs(final_vol) / final_vol * max_vel;
    }


    if(fabs(length) < zone){
      correction = zone_constant;
      if(flip == 1){
        if(fabs(angle_error) / angle_error == 1){
          move_drive(-final_vol * correction, -final_vol);
        }
        if(fabs(angle_error) / angle_error == -1){
          move_drive(-final_vol, -final_vol * correction);
        }
      }
      else{
        if(fabs(angle_error) / angle_error == -1){
          move_drive(-final_vol * correction, -final_vol);
        }
        if(fabs(angle_error) / angle_error == 1){
          move_drive(-final_vol, -final_vol * correction);
        }
      }
    }
    else{

      correction = .85 - (kpa * fabs(angle_error * (180 / pi)));
      if (correction < .2){
        correction = .2;
      }

        if(flip == 1){
          if(fabs(angle_error) / angle_error == 1){
            move_drive(-final_vol, -final_vol * correction);
          }
          if(fabs(angle_error) / angle_error == -1){
            move_drive(-final_vol * correction, -final_vol);
          }
          if(fabs(angle_error) / angle_error == 0){
            move_drive(-final_vol, -final_vol);
          }
        }
        else{
          if(fabs(angle_error) / angle_error == -1){
            move_drive(-final_vol, -final_vol * correction);
          }
          if(fabs(angle_error) / angle_error == 1){
            move_drive(-final_vol * correction, -final_vol);
          }
          if(fabs(angle_error) / angle_error == 0){
            move_drive(-final_vol, -final_vol);
          }
        }
    }

    if (error < 50) {
      arrived++;
    }
    if (arrived == 1) {
      move_drive(0, 0);
      break;
    }

    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
    count++;
    if(count%6000==0){
      printf("VOLTAGE: %f", -final_vol);
      printf("ERROR: %f", error);
      printf("\n");
  }
}
}

void delay_update(double ms){
  double time = 0;
  while(time<ms){
    switch(whichPos){
          case 0: update_position0(); break;
          case 90: update_position90(); break;
          case 180: update_position180(); break;
          case 270: update_position270(); break;
          default: update_position90(); break;
      }
  pros::delay(10);
  time+=10;
  }
}
