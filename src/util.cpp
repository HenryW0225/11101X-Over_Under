#include "main.h"

//Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

//Variables
int cata_running = 0;
int blocker_open = 0;
int climber_open = 0;
int wings_open = 0; 
double PI = 3.14159265359;

//Functions
double reduce_0_to_360(double angle) {
  while(!(angle >= 0 && angle < 360)) {
    if( angle < 0 ) { angle += 360; }
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

double negative_180_to_180(double angle) {
  while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}

double negative_90_to_90(double angle) {
  while(!(angle >= -90 && angle < 90)) {
    if( angle < -90 ) { angle += 180; }
    if(angle >= 90) { angle -= 180; }
  }
  return(angle);
}

double to_rad(double angle_deg){
  return(angle_deg/(180.0/PI));
}

double to_deg(double angle_rad){
  return(angle_rad*(180.0/PI));
}

double clamp(double input, double min, double max){
  if( input > max ){ return(max); }
  if(input < min){ return(min); }
  return(input);
}

double to_volt(double percent){
  return(percent*12.0/100.0);
}

double to_mili_volt(double percent){
  return(percent*120.0);
}

double deadband(double input, double width){
  if (fabs(input)<width){
    return(0);
  }
  return (input);
}

bool is_reversed(double input) {
  if (input < 0) return true;
  return false;
}