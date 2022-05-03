#include "main.h"

double intakeVoltage = 110;
double outtakeVoltage = -110; //HEY WAASIF VOLTAGE GOES BETWEEN 0 AND 127 SO MAKE IT LOWER IF ITS NOT WORKING

void intakeControl(){
  bool intake = master.get_digital(DIGITAL_R1);
  bool outtake = master.get_digital(DIGITAL_R2);

  if (intake){
    conveyorMotor.move(intakeVoltage);
  }
  else if(outtake){
    conveyorMotor.move(outtakeVoltage);
  }
  else{
    conveyorMotor.move(0);
  }
}
