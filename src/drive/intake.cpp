#include "main.h"

Intake::Intake(pros::Motor intake_mtr_port) 
    : intake_mtr(intake_mtr_port) {}

void Intake::intake_control() {
    move(0);
    if (master.get_digital(DIGITAL_L1)){
        move(120); }
    if (master.get_digital(DIGITAL_L2)){
        move(-120); }
}

void Intake::initialize() {
    intake_mtr.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
}

void Intake::move(double voltage) {
    intake_mtr.move_voltage(voltage * 100);
}