#include "main.h"

Drive::Drive(std::vector<pros::Motor> left_motors, std::vector<pros::Motor> right_motors, int imu_port, double wheel_diameter, double ratio, double wheel_circumference)
    : inertial(imu_port),
    left_mtr_grp(left_motors),
    right_mtr_grp(right_motors),
    in_to_deg(ratio/360.0 * wheel_circumference) {

    // Set constants for tick_per_inch calculation
    double WHEEL_DIAMETER = wheel_diameter;
    double RATIO = ratio;
    double WHEEL_CIRCUMFERENCE = wheel_circumference;
}

double Drive::get_TPI() {
  TPI = ratio * 360/wheel_circumference;;
  return TPI;
}

void Drive::initialize() {
  imu_calibrate();
  reset_drive_sensor();
  set_brake_mode('C');
}

bool Drive::imu_calibrate() {
    inertial.reset();
    int iter = 0;
    while (true) {
        iter += util::DELAY_TIME;
        if (iter >= 2000) {
            if (!(inertial.get_status() & pros::c::E_IMU_STATUS_CALIBRATING)) {
                break;
            } if (iter >= 3000) {
                printf("No IMU plugged in, (took %d ms to realize that)\n", iter);
                return false;
            }
        }
        pros::delay(util::DELAY_TIME);
    }
    printf("IMU is done calibrating (took %d ms)\n", iter);
    return true;
}

void Drive::reset_drive_sensor() {
    left_mtr_grp.tare_position();
    right_mtr_grp.tare_position();
}

void Drive::arcade_control() {
    //Grabs joystick position
    int horz = master.get_analog(ANALOG_LEFT_X);
    int vert = master.get_analog(ANALOG_LEFT_Y);
    //Checks to make sure joystick isn't it deadzone
    if (abs(horz) < deadzone){
        horz = 0;}
    if (abs(vert) < deadzone){
        vert = 0;}
    vert = vert * 100;
    horz = horz * 100;
    if (master.get_digital(DIGITAL_A)){
        vert = -vert;
    }
    left_mtr_grp.move_voltage(vert + horz);
    right_mtr_grp.move_voltage(vert - horz);
}

double Drive::left_sensor() {
    //Grabs average encoder value of left motor encoders
    std::vector<double> sum;
    int total;
    int count = 3;
    sum = left_mtr_grp.get_positions();
    total = fabs(sum[0]) + fabs(sum[1]) + fabs(sum[2]);
    return total / count * in_to_deg;
}

double Drive::right_sensor() {
    //Grabs average encoder value of left motor encoders
    std::vector<double> sum;
    int total;
    int count = 3;
    sum = right_mtr_grp.get_positions();
    total = fabs(sum[0]) + fabs(sum[1]) + fabs(sum[2]);
    return total / count * in_to_deg;
}

void Drive::set_brake_mode(char brake_type) {
    if (brake_type == 'H'){
        left_mtr_grp.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        right_mtr_grp.set_brake_modes(E_MOTOR_BRAKE_HOLD);
    }
    else if (brake_type == 'C'){
        left_mtr_grp.set_brake_modes(E_MOTOR_BRAKE_COAST);
        right_mtr_grp.set_brake_modes(E_MOTOR_BRAKE_COAST);
    }
}

double Drive::get_gyro() { 
    return inertial.get_heading(); 
}

void Drive::reset_gyro() { 
    inertial.set_heading(0); 
}

void Drive::set_drive(int left, int right) {
    left_mtr_grp.move_voltage(left * (12000.0 / 127.0));
    right_mtr_grp.move_voltage(right * (12000.0 / 127.0));
}

void Drive::drive_with_voltage(double leftVoltage, double rightVoltage){
    left_mtr_grp.move_voltage(leftVoltage * 1000);
    right_mtr_grp.move_voltage(rightVoltage * 1000);
}


// All PID constants are passed as kP, kI, kD, and startI. The kP, kI, and kD are pretty standard,
// but startI keeps the integral value at 0 until the absolute value of the error is below startI.
// This prevents integral windup on bigger turns.
//Set PID constants:
void Drive::set_turn_constants(double turn_max_voltage, double turn_kp, double turn_ki, double turn_kd, double turn_starti){
    this->turn_max_voltage = turn_max_voltage;
    this->turn_kp = turn_kp;
    this->turn_ki = turn_ki;
    this->turn_kd = turn_kd;
    this->turn_starti = turn_starti;
}

void Drive::set_drive_constants(double drive_max_voltage, double drive_kp, double drive_ki, double drive_kd, double drive_starti){
    this->drive_max_voltage = drive_max_voltage;
    this->drive_kp = drive_kp;
    this->drive_ki = drive_ki;
    this->drive_kd = drive_kd;
    this->drive_starti = drive_starti;
}

void Drive::set_heading_constants(double heading_max_voltage, double heading_kp, double heading_ki, double heading_kd, double heading_starti){
    this->heading_max_voltage = heading_max_voltage;
    this->heading_kp = heading_kp;
    this->heading_ki = heading_ki;
    this->heading_kd = heading_kd;
    this->heading_starti = heading_starti;
}

void Drive::set_swing_constants(double swing_max_voltage, double swing_kp, double swing_ki, double swing_kd, double swing_starti){
    this->swing_max_voltage = swing_max_voltage;
    this->swing_kp = swing_kp;
    this->swing_ki = swing_ki;
    this->swing_kd = swing_kd;
    this->swing_starti = swing_starti;
}

// Settle error and settle time work together to check whether the desired position was achieved, but
// timeout is separate. The robot must stay within the settle error for the duration of the settle time
// to be settled. If the duration of the movement reaches timeout without being settled, the robot
// gives up and goes to the next movement.
//Set PID exit conditions

void Drive::set_turn_exit_conditions(double turn_settle_error, double turn_settle_time, double turn_timeout){
    this->turn_settle_error = turn_settle_error;
    this->turn_settle_time = turn_settle_time;
    this->turn_timeout = turn_timeout;
}

void Drive::set_drive_exit_conditions(double drive_settle_error, double drive_settle_time, double drive_timeout){
    this->drive_settle_error = drive_settle_error;
    this->drive_settle_time = drive_settle_time;
    this->drive_timeout = drive_timeout;
}

void Drive::set_swing_exit_conditions(double swing_settle_error, double swing_settle_time, double swing_timeout){
    this->swing_settle_error = swing_settle_error;
    this->swing_settle_time = swing_settle_time;
    this->swing_timeout = swing_timeout;
}

double Drive::get_absolute_heading(){
    return(reduce_0_to_360( inertial.get_heading()*360.0/gyro_scale ) );
}

void Drive::turn_to_angle(double angle) {
    turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(double angle, double turn_max_voltage) {
    turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(double angle, double turn_max_voltage, double turn_settle_error, double turn_settle_time, double turn_timeout) {
    turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(double angle, double turn_max_voltage, double turn_settle_error, double turn_settle_time, double turn_timeout, double turn_kp, double turn_ki, double turn_kd, double turn_starti){
    desired_heading = angle;
    // Desired heading carries over the angle from one movement to another. That way, if the robot doesn't
    // finish a turn movement, it will still drive at the angle that was specified in the turn movement.
    PID turnPID(negative_180_to_180(angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
    while(turnPID.is_settled() == false){
        double error = negative_180_to_180(angle - get_absolute_heading());
        // Reducing the angle to a value between -180 and 180 degrees ensures that the robot always takes the
        // shorter path when making a turn.
        double output = turnPID.compute(error);
        output = clamp(output, -turn_max_voltage, turn_max_voltage);
        drive_with_voltage(output, -output);
        pros::Task::delay(10);
    }
    drive_with_voltage(0, 0);
    left_mtr_grp.brake();
    right_mtr_grp.brake();
}

void Drive::drive_distance(double distance){
    drive_distance(distance, desired_heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_distance(double distance, double heading){
    drive_distance(distance, desired_heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage){
    drive_distance(distance, desired_heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout){
    drive_distance(distance, desired_heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_distance(double distance, double drive_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti){
    PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
    double start_average_position = (left_sensor() + right_sensor())/2.0;
    // Rather than resetting the drive position , this function just notes what the drive position started at and determines error relative to that value.
    double average_position = start_average_position;
    while(drivePID.is_settled() == false){
        average_position = (left_sensor() + right_sensor())/2.0;
        double drive_error = distance+start_average_position-average_position;
        // Just like for turns, reducing from -180 to 180 degrees ensures that the robot takes the quickest path to the desired heading.
        double drive_output = drivePID.compute(drive_error);
        drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
        drive_with_voltage(drive_output, drive_output);
        pros::Task::delay(10);
    }
    left_mtr_grp.brake();
    right_mtr_grp.brake();
}

void Drive::drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti, double heading_kp, double heading_ki, double heading_kd, double heading_starti){
    desired_heading = heading;
    PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
    PID headingPID(negative_180_to_180(heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
    double start_average_position = (left_sensor() + right_sensor())/2.0;
    // Rather than resetting the drive position , this function just notes what the drive position started at and determines error relative to that value.
    double average_position = start_average_position;
    while(drivePID.is_settled() == false){
        average_position = (left_sensor() + right_sensor())/2.0;
        double drive_error = distance+start_average_position-average_position;
        double heading_error = negative_180_to_180(heading - get_absolute_heading());
        // Just like for turns, reducing from -180 to 180 degrees ensures that the robot takes the quickest path to the desired heading.
        double drive_output = drivePID.compute(drive_error);
        double heading_output = headingPID.compute(heading_error);
        drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
        heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);
        drive_with_voltage(drive_output+heading_output, drive_output-heading_output);
        pros::Task::delay(10);
    }
    left_mtr_grp.brake();
    right_mtr_grp.brake();
}

void Drive::left_swing_to_angle(double angle){
    left_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::left_swing_to_angle(double angle, double swing_max_voltage){
    right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::left_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout){
    left_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::left_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout, double swing_kp, double swing_ki, double swing_kd, double swing_starti){
    desired_heading = angle;
    PID swingPID(negative_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
    while(swingPID.is_settled() == false){
        double error = negative_180_to_180(angle - get_absolute_heading());
        double output = swingPID.compute(error);
        output = clamp(output, -turn_max_voltage, turn_max_voltage);
        left_mtr_grp.move_voltage(output);
        //Only the left side of the drive turns, making this a "left swing".
        right_mtr_grp.brake();
        pros::Task::delay(10);
    }
    left_mtr_grp.brake();
    right_mtr_grp.brake();
}

void Drive::right_swing_to_angle(double angle){
    right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::right_swing_to_angle(double angle, double swing_max_voltage){
    right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::right_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout){
    right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::right_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout, double swing_kp, double swing_ki, double swing_kd, double swing_starti){
    desired_heading = angle;
    PID swingPID(negative_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
    while(swingPID.is_settled() == false){
        double error = negative_180_to_180(angle - get_absolute_heading());
        double output = swingPID.compute(error);
        output = clamp(output, -turn_max_voltage, turn_max_voltage);
        right_mtr_grp.move_voltage(output);
        //Only the right side of the drive turns, so this is a "right swing".
        left_mtr_grp.set_brake_modes(MOTOR_BRAKE_HOLD);
        left_mtr_grp.brake();
        pros::Task::delay(10);
    }
    left_mtr_grp.brake();
    right_mtr_grp.brake();
}

void Drive::set_heading(double orientation_deg){
    inertial.set_heading(reduce_0_to_360(orientation_deg*gyro_scale/360.0));
}