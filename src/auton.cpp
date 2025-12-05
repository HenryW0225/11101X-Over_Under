#include "main.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 4000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

// Autonomous Procedures
void far_qual(){}

void far_elim(){}

void close_qual(){
	chassis.drive_distance(6, -5, 0.5, 10, 4000, 1, 1, 1, 0);
	pneumatics.wings_v(1);
	pros::delay(200);
  chassis.turn_to_angle(280, 4, 10, 20, 4000, 1, 1, 1, 0);
  pneumatics.wings_v(0);
  pros::delay(250);
  chassis.drive_distance(26, 10, 1, 80, 4000, 1, 1, 1, 0);
	pros::delay(100);
	chassis.turn_to_angle(157, 4, 10, 20, 4000, 1, 1, 1, 0);
	pros::delay(100);
	intake.move(-120);
	pros::delay(250);
	chassis.drive_distance(22, 8, 2, 20, 3500, 1, 1, 1, 0);
	intake.move(0);
	pneumatics.wings_v(1);
	pros::delay(250);
	chassis.drive_distance(13, -5, 1, 10, 2000, 1, 1, 1, 0);
	pros::delay(100);
	chassis.drive_distance(5, 8, 1, 10, 3000, 1, 1, 1, 0);
	pros::delay(150);
	pneumatics.wings_v(0);
	pros::delay(250);
	chassis.turn_to_angle(200, 4, 10, 20, 4000, 1, 1, 1, 0);
	pros::delay(100);
	chassis.drive_distance(12, -8, 1, 10, 3000, 1, 1, 1, 0);
	pneumatics.wings_v(1);
	pros::delay(250);
	chassis.turn_to_angle(250, 4, 10, 20, 4000, 1, 1, 1, 0);
}

void close_elim(){
	chassis.drive_distance(40, 5, 2, 20, 4000, 1, 1, 1, 0);
	pros::delay(100);
	chassis.turn_to_angle(270, 5, 10, 20, 4000);
	pros::delay(100);
	intake.move(-120);
	pros::delay(200);
	chassis.drive_distance(3, 8, 0.5, 10, 2500, 1, 1, 1, 0);
	intake.move(0);
	pneumatics.wings_v(1);
	pros::delay(250);
	chassis.drive_distance(13, -5, 2, 20, 2000, 1, 1, 1, 0);
	pros::delay(100);
	chassis.drive_distance(5, 8, 1, 10, 3000, 1, 1, 1, 0);
}

void skills(){
    pneumatics.wings_v(1);
    pros::delay(500);
    pneumatics.wings_v(0);
    pros::delay(200);
    chassis.turn_to_angle(55, 4, 10, 20, 4000);
    pros::delay(80);
    chassis.drive_distance(29, -8, 1, 10, 4000, 1, 1, 1, 0);
    pros::delay(80);
    chassis.drive_distance(5, 8, 0.5, 10, 4000, 1, 1, 1, 0);
    pros::delay(80);
    chassis.turn_to_angle(139, -6, 10, 20, 4000, 1, 1, 1, 0);
    pros::delay(80);
    chassis.drive_distance(4, 6, 0.5, 10, 4000, 1, 1, 1, 0);
    slapper.move(120);
    pros::delay(30000);
    slapper.move(0);
    /*autonTurn(65, -55);
    pros::delay(80);
    autonDrive(29, -80);
    pros::delay(80);
    autonTurn(345, -55);
    pros::delay(80);
    autonDrive(67, -80);
    pros::delay(80);
    autonTurn(330, -55);
    pros::delay(80);
    autonDrive(30, -80);
    pros::delay(80);
    autonTurn(350, -55);
    pros::delay(80);
    autonDrive(10, 80);
    pros::delay(80);
    autonDrive(11, -80);
    pros::delay(80);
    autonDrive(13, 80);
    pros::delay(80);
    autonTurn(105, -55);
    pros::delay(80);
    chassis.drive_distance(48, 8, 2, 20, 4000);
    pros::delay(80);
    autonTurn(340, -55);
    pros::delay(80);
    wings.set_value(1);
    pros::delay(200);
    chassis.drive_distance(30, -8, 2, 20, 4000);
    pros::delay(80);
    chassis.drive_distance(15, 8, 2, 20, 4000);
    pros::delay(80);
    autonTurn(350, -55);
    pros::delay(80);
    chassis.drive_distance(16, -8, 2, 20, 4000);*/
}