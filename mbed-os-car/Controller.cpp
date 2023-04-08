#include <cstdio>
#include <math.h>
#include <utility>


namespace Controller {
    double sampling_time = 0.001; // 10 milliseconds is 0.01 seconds

    // P controller -- returns (type double) angle between 0 and 1
    double angle_from_center_P(double center) {
        // controller params
        double Kp = -5; // Kp should be calculated according to track width i.e. width between the two lines

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
        double Kp = -5;
        double Kd = 2;

        // return value i.e. angle
        double ret_;

        // calculate the displacement from the center
        double displacement = 64 - center;

        // error derivative i.e. displacement derivative
        double d_displacement = (center - prev_center) / sampling_time;

        // 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
        ret_ = 64 + Kp * displacement + Kd * d_displacement;

        // divide by max to get a percentage
        ret_ = ret_ / 128.0;

        return ret_;
    }

    // controller for speed of wheels based on wheel angle outputs std::pair<double,double> with first value being left wheel speed, second value right wheel speed
    std::pair<double,double> wheel_speed_controller_PID(double angle_setpoint, double current_angle, double& angle_error_int, double& angle_error_prev, double& angle_output_prev, double sampling_time, double maxSpeed) {
        // experiment for the desired wheel-speed ratio, right now it's 0.6:1 for max steer
        // define controller params
        double Kp = -3;
        double Ki = 1;
        double Kd = 2;
        // define desire min speed an max speed
        double max_speed = maxSpeed; // 40% of max speed
        double min_speed = 0; // don't allow spinning the wheel backwards

        // Calculate the error between the setpoint and the actual angle
        double angle_error = angle_setpoint - current_angle;

        // Calculate the proportional term
        double angle_p = Kp * angle_error;

        // Calculate the integral term
        angle_error_int += angle_error * sampling_time;
        double angle_i = Ki * angle_error_int;

        // Calculate the derivative term
        double angle_d = Kd * (angle_error_prev - angle_error) / sampling_time;

        // Calculate the output
        double angle_output = angle_p + angle_i + angle_d;

        // Apply the output to the back wheels, saturated between min_speed and max_speed
        double left_wheel_speed = std::fmax(std::fmin(max_speed - angle_output, max_speed), min_speed);
        double right_wheel_speed = std::fmax(std::fmin(max_speed + angle_output, max_speed), min_speed);

        // Save variables for next iteration
        angle_error_prev = angle_error;
        angle_output_prev = angle_output;

        return std::pair<double,double>(left_wheel_speed,right_wheel_speed);
    }

    std::pair<double,double> wheel_speed_controller_P(double center, double max_speed, double diff_drive_ratio) {
        double Kp = 2;

        float left_wheel_speed = 0.0f;
        float right_wheel_speed = 0.0f;
        
        // Control the speed of the wheels with P
        if(center > 64.0f) {
            left_wheel_speed = -pow(max_speed,2)/(Kp*(center - 64.0f) + max_speed);
            right_wheel_speed = -pow(max_speed,2)*diff_drive_ratio/(Kp*(center - 64.0f) + max_speed);
        } else if(center < 64.0f) {
            left_wheel_speed = -pow(max_speed,2)*diff_drive_ratio/(Kp*(64.0f - center) + max_speed);
            right_wheel_speed = -pow(max_speed,2)/(Kp*(64.0f - center) + max_speed);
        } else if (center == 64.0f) {
            left_wheel_speed = max_speed;
            right_wheel_speed = max_speed;
        }

        return std::pair<double,double>(left_wheel_speed,right_wheel_speed);
    }
}