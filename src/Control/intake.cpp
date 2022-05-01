#include "main.h"

double intakeVoltage = 127;
double outtakeVoltage = -127; //HEY WAASIF VOLTAGE GOES BETWEEN 0 AND 127 SO MAKE IT LOWER IF ITS NOT WORKING

void intakeControl(){
  bool intake = master.get_digital(DIGITAL_L1);
  bool outtake = master.get_digital(DIGITAL_L2);

  if (intake){
    conveyorMotor.move(intakeVoltage);
  }
  else if(outtake){
    conveyorMotor.move(outtakeVoltage);
  }
}
