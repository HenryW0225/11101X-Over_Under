#include "main.h"

class Drive{
public:
    int deadzone = 15;
    pros::Motor_Group left_mtr_grp;
    pros::Motor_Group right_mtr_grp;
    pros::IMU inertial;
    double wheel_diameter;
    double ratio;
    double TPI;
    double wheel_circumference;
    double gyro_scale = 360;
    double in_to_deg;
    //Turning variables
    double turn_max_voltage;
    double turn_kp;
    double turn_ki;
    double turn_kd;
    double turn_starti;
    double turn_settle_error;
    double turn_settle_time;
    double turn_timeout;
    //Driving variables
    double drive_max_voltage;
    double drive_kp;
    double drive_ki;
    double drive_kd;
    double drive_starti;
    double drive_settle_error;
    double drive_settle_time;
    double drive_timeout;
    //Heading variables
    double heading_max_voltage;
    double heading_kp;
    double heading_ki;
    double heading_kd;
    double heading_starti;
    //Swinging variables
    double swing_max_voltage;
    double swing_kp;
    double swing_ki;
    double swing_kd;
    double swing_starti;
    double swing_settle_error;
    double swing_settle_time;
    double swing_timeout;
    double desired_heading;
    Drive(std::vector<pros::Motor> left_motors, std::vector<pros::Motor> right_motors, int imu_port, double wheel_diameter, double ratio, double wheel_circumference);
    double left_sensor();
    double right_sensor();
    bool imu_calibrate();
    void reset_drive_sensor();
    void initialize();
    void arcade_control();
    double get_TPI();
    void set_brake_mode(char brake_type);
    double get_gyro();
    void set_drive(int left, int right);
    void reset_gyro();
    //Set autonomous function constants
    void set_turn_constants(double turn_max_voltage, double turn_kp, double turn_ki, double turn_kd, double turn_starti);
    void set_drive_constants(double drive_max_voltage, double drive_kp, double drive_ki, double drive_kd, double drive_starti);
    void set_heading_constants(double heading_max_voltage, double heading_kp, double heading_ki, double heading_kd, double heading_starti);
    void set_swing_constants(double swing_max_voltage, double swing_kp, double swing_ki, double swing_kd, double swing_starti);
    //Set autonomous function exit conditions
    void set_turn_exit_conditions(double turn_settle_error, double turn_settle_time, double turn_timeout);
    void set_drive_exit_conditions(double drive_settle_error, double drive_settle_time, double drive_timeout);
    void set_swing_exit_conditions(double swing_settle_error, double swing_settle_time, double swing_timeout);
    void drive_with_voltage(double leftVoltage, double rightVoltage);
    double get_absolute_heading();
    //Turning functions
    void turn_to_angle(double angle);
    void turn_to_angle(double angle, double turn_max_voltage);
    void turn_to_angle(double angle, double turn_max_voltage, double turn_settle_error, double turn_settle_time);
    void turn_to_angle(double angle, double turn_max_voltage, double turn_settle_error, double turn_settle_time, double turn_timeout);
    void turn_to_angle(double angle, double turn_max_voltage, double turn_settle_error, double turn_settle_time, double turn_timeout, double turn_kp, double turn_ki, double turn_kd, double turn_starti);
    //Driving functions
    void drive_distance(double distance);
    void drive_distance(double distance, double heading);
    void drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage);
    void drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout);
    void drive_distance(double distance, double drive_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti);
    void drive_distance(double distance, double heading, double drive_max_voltage, double heading_max_voltage, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti, double heading_kp, double heading_ki, double heading_kd, double heading_starti);
    //Swinging functions
    void left_swing_to_angle(double angle);
    void left_swing_to_angle(double angle, double swing_max_voltage);
    void left_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout);
    void left_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout, double swing_kp, double swing_ki, double swing_kd, double swing_starti);
    void right_swing_to_angle(double angle);
    void right_swing_to_angle(double angle, double swing_max_voltage);
    void right_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout);
    void right_swing_to_angle(double angle, double swing_max_voltage, double swing_settle_error, double swing_settle_time, double swing_timeout, double swing_kp, double swing_ki, double swing_kd, double swing_starti);
    void set_heading(double orientation_deg);
};