#include "main.h"

class Pneumatics{
    public:
    pros::ADIDigitalOut blocker;
    pros::ADIDigitalOut climber;
    pros::ADIDigitalOut wings;
    Pneumatics(pros::ADIDigitalOut blocker_port, pros::ADIDigitalOut climber_port, pros::ADIDigitalOut wings);

    void blocker_control();
    void climber_control();
    void wings_control();
    void blocker_initialize();
    void climber_initialize();
    void wings_initialize();
    void wings_v(int value);
};