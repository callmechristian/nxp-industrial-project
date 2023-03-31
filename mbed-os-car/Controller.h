namespace Controller {
    double angle_from_center_P(double center, double Kp);
    double angle_from_center_PD(double center, double prev_center, double Kp, double Kd, double sampling_time);
}