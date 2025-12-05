#include "main.h"

Delivery::Delivery(pros::Motor delivery_mtr_port) 
    : delivery_mtr(delivery_mtr_port) {}

void Delivery::delivery_control() {
    if (master.get_digital(DIGITAL_X)){
        cata_running = !cata_running;
        if (cata_running) {
            move(120); 
        } else {
            move(0);
        }
        while (master.get_digital(DIGITAL_X)) {
            pros::delay(util::DELAY_TIME);
        }
    }
}

void Delivery::initialize() {
    delivery_mtr.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
}

void Delivery::move(double voltage) {
    delivery_mtr.move_voltage(voltage * 100);
}