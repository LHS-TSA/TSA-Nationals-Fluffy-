#include "main.h"

// motors
extern pros::Motor front_right_drive;
extern pros::Motor front_left_drive;
extern pros::Motor back_right_drive;
extern pros::Motor back_left_drive;
extern pros::Motor back_right_drive_top;
extern pros::Motor back_left_drive_top;
extern pros::Motor intake;
extern pros::Motor Catapult;

//controller and misc
extern pros::Controller con;
extern pros::ADIDigitalIn limitSwitch;
extern pros::IMU gyro;
// pisty = front 
// piston = expansion
extern pros::ADIMotor pisty;
extern pros::ADIMotor Piston;
extern pros::Vision cam;

