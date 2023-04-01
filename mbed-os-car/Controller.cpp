#include <math.h>
#include <utility>

namespace Controller {
    double sampling_time = 0.01; // 10 milliseconds is 0.01 seconds

    // P controller -- returns (type double) angle between 0 and 1
    double angle_from_center_P(double center) {
        // controller params
        double Kp = 1;

        // return value i.e. angle
        double ret_;

        // calculate the displacement from the center
        double displacement = center - 64;

        // 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
        ret_ = 64 + Kp * displacement;

        // divide by max to get a percentage
        ret_ = ret_ / 128.0;

        return ret_;
    }

    // PD controller -- returns (type double) angle between 0 and 1
    double angle_from_center_PD(double center, double prev_center, double sampling_time) {
        // controller params
        double Kp = 1;
        double Kd = 1;

        // return value i.e. angle
        double ret_;

        // calculate the displacement from the center
        double displacement = center - 64;

        // error derivative i.e. displacement derivative
        double d_displacement = (center - prev_center) / sampling_time;

        // 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
        ret_ = 64 + Kp * displacement;

        // divide by max to get a percentage
        ret_ = ret_ / 128.0;

        return ret_;
    }

    // controller for speed of wheels based on wheel angle outputs std::pair<double,double> with first value being left wheel speed, second value right wheel speed
    std::pair<double,double> wheel_speed_controller_PID(double angle_setpoint, double current_angle, double& angle_error_int, double& angle_error_prev, double& angle_output_prev, double sampling_time) {
        // experiment for the desired wheel-speed ratio, right now it's 0.6:1 for max steer
        // define controller params
        double Kp = 0.05;
        double Ki = 0.1;
        double Kd = 0.9;
        // define desire min speed an max speed
        double max_speed = 0.4; // 40% of max speed
        double min_speed = 0; // don't allow spinning the wheel backwards

        // Calculate the error between the setpoint and the actual angle
        double angle_error = angle_setpoint - current_angle;

        // Calculate the proportional term
        double angle_p = Kp * angle_error;

        // Calculate the integral term
        angle_error_int += angle_error * sampling_time;
        double angle_i = Ki * angle_error_int;

        // Calculate the derivative term
        double angle_d = Kd * (angle_error - angle_error_prev) / sampling_time;

        // Calculate the output
        double angle_output = angle_p + angle_i + angle_d;

        // Apply the output to the back wheels, saturated between min_speed and max_speed
        double left_wheel_speed = std::fmin(std::fmax(max_speed - angle_output, min_speed), max_speed);
        double right_wheel_speed = std::fmax(std::fmin(max_speed + angle_output, max_speed), min_speed);

        // Store the previous values for the derivative and integral terms
        angle_error_prev = angle_error;
        angle_output_prev = angle_output;

        return std::pair<double,double>(left_wheel_speed,right_wheel_speed);
    }
}