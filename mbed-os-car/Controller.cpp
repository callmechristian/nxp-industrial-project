namespace Controller {

    // P controller -- returns (type double) angle between 0 and 1
    double angle_from_center_P(double center, double Kp) {
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
    double angle_from_center_PD(double center, double prev_center, double Kp, double Kd, double sampling_time) {
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
}