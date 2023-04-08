#pragma once

#include <utility>

namespace Controller {
    extern double sampling_time;
    double angle_from_center_P(double center);
    double angle_from_center_PD(double center, double prev_center, double sampling_time);
    std::pair<double,double> wheel_speed_controller_PID(double angle_setpoint, double current_angle, double& angle_error_int, double& angle_error_prev, double& angle_output_prev, double sampling_time, double maxSpeed);
    std::pair<double,double> wheel_speed_controller_P(double center, double max_speed, double diff_drive_ratio);
}