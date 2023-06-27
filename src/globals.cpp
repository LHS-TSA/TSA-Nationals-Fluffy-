#include "main.h"

//motors
pros::Motor front_left_drive(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor front_right_drive(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_left_drive(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_right_drive(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_left_drive_top(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor back_right_drive_top(8, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor intake(10, pros::E_MOTOR_GEAR_BLUE, false, 
pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor Catapult(14, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

// controller
pros::Controller con(pros::E_CONTROLLER_MASTER);
pros::ADIDigitalIn limitSwitch('A');
pros::ADIMotor pisty('B');
pros::ADIMotor Piston('C');
pros::Vision cam(14);
pros::IMU gyro(3); 


