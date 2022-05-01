#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
float tpu = 51.6;
float tpuTurn = 8.5;
void initialize() {
	setupSelector();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
	//setupSelector();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

unsigned int auton_num{};
void autonomous() {
	//skillsRun();
		switch(autonChosen){
	        case 0: leftWPAuton(); break;
	        case 1: rightWPAuton(); break;
	        case 2: leftAuton(); break;
					case 3: rightAuton(); break;

					case 4: skillsRun(); break;
					case 5: skillsRun2(); break;
					case 6: skillsRun3(); break;
					case 7: neutralDistAuton(); break;
					case 8: doNothing(); break;
	        default: leftAuton(); break;
	    }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::lcd::set_text(2, "In opcontrol");
	int counter=0;
	while (true) {
		driveControl();
		frontClawControl();
		backClawControl();
		liftControl();
		//update_position90();

		bool runAuton = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
		if(runAuton && !pros::competition::is_connected()){
			 autonomous();
		}

		/*counter++;
		if (counter%5==0){
		printf("%f\n",chassis::rightMotors->getPosition());
	}*/

		pros::delay(20);
	}

}
