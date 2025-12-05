#include "main.h"

Pneumatics::Pneumatics(pros::ADIDigitalOut blocker_port, pros::ADIDigitalOut climber_port, pros::ADIDigitalOut wings_port) 
    : blocker(blocker_port),
    climber(climber_port),
    wings(wings_port) {}

void Pneumatics::blocker_control() {
    if (master.get_digital(DIGITAL_R2)){
        blocker_open = !blocker_open;
        blocker.set_value(blocker_open);
        while (master.get_digital(DIGITAL_R2)) {
            pros::delay(util::DELAY_TIME);
        }
    }
}

void Pneumatics::climber_control() {
   if (master.get_digital(DIGITAL_Y)){
        climber_open = !climber_open;
        climber.set_value(climber_open);
        while (master.get_digital(DIGITAL_Y)) {
            pros::delay(util::DELAY_TIME);
        }
    }
}

void Pneumatics::wings_control() {
 if (master.get_digital(DIGITAL_R1)){
        wings_open = !wings_open;
        wings.set_value(wings_open);
        while (master.get_digital(DIGITAL_R1)) {
            pros::delay(util::DELAY_TIME);
        }
    }
}


void Pneumatics::blocker_initialize() {
    blocker.set_value(0);
}

void Pneumatics::climber_initialize() {
    climber.set_value(0);
}

void Pneumatics::wings_initialize() {
    wings.set_value(0);
}

void Pneumatics::wings_v(int value) {
    wings.set_value(value);
}
