#include "main.h"

//Motor Definitions
pros::Motor left_front_mtr(18, pros::E_MOTOR_GEAR_BLUE, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor left_middle_mtr(19, pros::E_MOTOR_GEAR_BLUE, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor left_back_mtr(20, pros::E_MOTOR_GEAR_BLUE, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor right_front_mtr(12, pros::E_MOTOR_GEAR_BLUE, false, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor right_middle_mtr(13, pros::E_MOTOR_GEAR_BLUE, false, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor right_back_mtr(11, pros::E_MOTOR_GEAR_BLUE, false, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_mtr(14, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor delivery_mtr(1, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::ADIDigitalOut blocker('A');
pros::ADIDigitalOut climber('B');
pros::ADIDigitalOut wings('C');

// Chassis constructor
Drive chassis(
	//Left motor ports
  	{left_front_mtr, left_middle_mtr, left_back_mtr}
	//Right motor ports
  	,{right_front_mtr, right_middle_mtr, right_back_mtr}
  	// IMU Port
  	,10
  	// Wheel Diameter
  	,3.25
  	// External Gear Ratio
  	,0.6
	//Wheel Circumference
	,10.21
);

Intake intake(
	{intake_mtr}
);

Delivery slapper(
	{delivery_mtr}
);

Pneumatics pneumatics(
	{blocker, climber, wings}

);

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::register_btn1_cb(on_center_button);
	chassis.initialize();
	intake.initialize();
	slapper.initialize();
	pneumatics.blocker_initialize();
	pneumatics.climber_initialize();
	pneumatics.wings_initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	chassis.set_brake_mode('H');
	//far_qual();
	//far_elim();
	close_qual();
	//close_elim();
	//skills();
	chassis.set_brake_mode('C');
}
void opcontrol() {
	chassis.set_brake_mode('C');
	while(true){
		chassis.arcade_control();
		intake.intake_control();
		slapper.delivery_control();
		pneumatics.blocker_control();
		pneumatics.climber_control();
		pneumatics.wings_control();
		pros::delay(util::DELAY_TIME);
	}
}

//test updates
