#include "main.h"

class Intake{
    public:
    pros::Motor intake_mtr;
    Intake(pros::Motor intake_mtr_port);

    void intake_control();
    void initialize();
    void move(double voltage);
        
};