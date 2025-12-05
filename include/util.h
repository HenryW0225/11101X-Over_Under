#include "main.h"

//Controller
extern pros::Controller master;

extern int cata_running;
extern int blocker_open;
extern int climber_open;
extern int wings_open;

double reduce_0_to_360(double angle);

double negative_180_to_180(double angle);

double negative_90_to_90(double angle);

double to_rad(double angle_deg);

double to_deg(double angle_rad);

double clamp(double input, double min, double max);

double to_volt(double percent);

double to_mili_volt(double percent);

double deadband(double input, double width);
//Returns true if the input is < 0
bool is_reversed(double input);

namespace util { 
//Util variables
const int DELAY_TIME = 20;
}