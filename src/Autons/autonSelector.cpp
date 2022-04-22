#include "main.h"


//unsigned int auton_num{}; //global <--declared in main

void setupSelector(){

  //Auton Selector

  unsigned int count{};
  std::string autonNames[9]= {"Left","Right","LeftWinP","RightWinP","Skills1","Skills2","Skills3","NeutralDist","doNothing"};
  count=0; //defined in main.h
  bool runSelector = true;

  bool runAuton = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

  int counter = 0;
  while(runSelector){
  	if(tapA.get_new_press() == 1) { //change count number when adding more
  		 count++;
  	}
    if(tapB.get_new_press() == 1) {
      count--;
    }
    if(count>6){ //prefer to use array.length
  		count=0;
  	}

    pros::lcd::print(2,"%d: %s\n",count,autonNames[count]);

  	if(tapC.get_new_press()==1){
  		auton_num=count;
  	  pros::lcd::print(2,"%d: %s \t Auton Chosen \n",count,autonNames[count]);
  	  runSelector = false;
      break;
  	}
    else if(runAuton){
      auton_num=count;
      pros::lcd::print(2,"%d: %s \t Auton Chosen \n",count,autonNames[count]);
      runSelector = false;
      break;
    }
    counter++;
  	pros::delay(20);

    if(counter>200){ //250 for regular select time
      auton_num=count;
      runSelector = false;
      break;
    }
	}
  pros::lcd::set_text(1, "Selector ended");// End autonSelector while statement
} // End if
