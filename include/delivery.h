#include "main.h"

class Delivery{
    public:
    pros::Motor delivery_mtr;
    Delivery(pros::Motor delivery_mtr_port);

    void delivery_control();
    void initialize();
    void move(double voltage);

};