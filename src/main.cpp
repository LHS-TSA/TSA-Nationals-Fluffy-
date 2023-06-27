#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::shutdown();
	pros::lcd::initialize();
	back_left_drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	front_left_drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	back_left_drive_top.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	back_right_drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	front_right_drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	back_right_drive_top.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	gyro.reset();
	con.clear();
	pros::Task controller(controllerScreen, "print");
	pros::delay(2000);
}

void controllerScreen(){
	con.print(0,0, "%f", gyro.get_heading());
	pros::delay(50);
}																																																																																						   /**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
}

																																																																																							   /**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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

// Function to drive straight for a specified distance



void autonomous() {
	// shoot
	pros::delay(2000);
	intake.move_velocity(-400);
	setDrive(50, 50);
	pros::delay(250);
	setDrive(-150, -150);
	pros::delay(850);
	rotateToAngle(352, false);
	stop();
	pros::delay(250);
	auton_shoot();
	pros::delay(200);
	intake.move_velocity(600);
	rotateToAngle(233, false);
	driveStraight(100,true);
	pros::delay(100);
	rotateToAngle(310, true);
	setDrive(-300,-300);
	pros::delay(400);
	stop();
	pros::delay(100);
	
	//shoot
	pros::delay(300);
	stop();
	pisty.set_value(127);
	setDrive(300, 300);
	pros::delay(400);
	stop();
	pros::delay(200);
	rotateToAngle(224, false);
	pros::delay(200);
	driveStraight(80, false);
	intake.move_velocity(-600);
	pros::delay(200);

	setDrive(300,25);
	pros::delay(600);
	stop();
	// pros::delay(200);
	// rotateToAngle(3, true);
	// pros::delay(50);
	// driveStraight(70, false);
	// pros::delay(100);
	// rotateToAngle(235, true);
	// pros::delay(25);
	// setDrive(150,150);
	// pros::delay(200);
	stop();
	intake.move_velocity(0);

	// setDrive(-300,-300);
	// pros::delay(380);
	// stop();
	// pros::delay(100);
	// rotateToAngle(20);
	// pros::delay(200);
	// auton_shoot();
	// stop();
	// pros::delay(100);
	// // //roller
	
	// rotateToAngle(301);
	// intake.move(-600);
	// stop();
	// driveStraight(25, true);
	// pros::delay(100);
	// rotateToAngle(359);
	// pros::delay(100);
	// setDrive(300, 300);
	// pros::delay(100);
	// setDrive(-300,-300);
	// pros::delay(150);
	// stop();
	// rotateToAngle(1);
	/*
	intake.move(-600);
	pros::delay(940);
	setDrive(200,200);
	pros::delay(150);
	setDrive(-200,-200);
	//disc and shoot
	pros::delay(300);
	stop();
	
	intake.move(600);
	rotateToAngle(120);
	pros::delay(300);
	driveStraight(100);
	rotateToAngle(33);
	stop();
	setDrive(-200,-200);
	pros::delay(300);
	stop();
	auton_shoot();
	stop();*/
}

void driveStraight(double distance, bool direction)
{
	// Convert distance to encoder ticks
	int targetTicks = (int)((distance / (3.25 * 3.14159)) * 360);

	// Reset encoders
	front_right_drive.tare_position();
	front_left_drive.tare_position();

	// Calculate initial heading
	int initialHeading = gyro.get_heading();

	// PID constants
	double Kp = 1.0; // Proportional gain (increased)
	double Ki = 0.0; // Integral gain
	double Kd = 0.1; // Derivative gain (introduced)

	// PID variables
	double error = 0.0;
	double integral = 0.0;
	double derivative = 0.0;
	double lastError = 0.0;

	// Drive loop
	if(direction){
		while (front_left_drive.get_position() < targetTicks && front_right_drive.get_position() < targetTicks)
		{
			// Calculate error
			error = targetTicks - (front_left_drive.get_position() + front_right_drive.get_position()) / 2;

			// Update integral
			integral += error;

			// Calculate derivative
			derivative = error - lastError;

			// Calculate PID output
			double output = Kp * error + Ki * integral + Kd * derivative;

			// Set motor speeds

			// Update last error
			lastError = error;

			// Update heading correction
			int currentHeading = gyro.get_heading();
			int headingError = currentHeading - initialHeading;
			double headingCorrection = headingError * 0.1; // Increased heading correction sensitivity

			// Apply heading correction to motor speeds
			setDrive(300 + headingCorrection, 300 - headingCorrection); // Increased motor power

			// Delay to allow motors to update
			pros::delay(20);
		}
	}else{
		while (front_left_drive.get_position() < targetTicks && front_right_drive.get_position() < targetTicks)
		{
			// Calculate error
			error = targetTicks - (front_left_drive.get_position() + front_right_drive.get_position()) / 2;

			// Update integral
			integral += error;

			// Calculate derivative
			derivative = error - lastError;

			// Calculate PID output
			double output = Kp * error + Ki * integral + Kd * derivative;

			// Set motor speeds

			// Update last error
			lastError = error;

			// Update heading correction
			int currentHeading = gyro.get_heading();
			int headingError = currentHeading - initialHeading;
			double headingCorrection = headingError * 0.1; // Increased heading correction sensitivity

			// Apply heading correction to motor speeds
			setDrive(600 + headingCorrection, 600 - headingCorrection); // Increased motor power

			// Delay to allow motors to update
			pros::delay(20);
		}
	}
	

	// Stop motors
	stop();
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

while (true) {
	setDriveMotors();
	setCataMotor();
	setIntakeMotors();
	fire_pist();
	pros::delay(10);
}

}
