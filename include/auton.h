#include "main.h"

class Drive;
class Intake;
class Delivery;
class Pneumatics;
extern Drive chassis;
extern Intake intake;
extern Delivery slapper;
extern Pneumatics pneumatics;

void default_constants();

// Autonomous Procedures
void far_qual();
void far_elim();
void close_qual();
void close_elim();
void skills();