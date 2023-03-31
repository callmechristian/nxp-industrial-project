namespace Steer {
    extern double steeringAngle;
    extern double prev_err;
    extern double Kd;
    extern double Kp;
    
    void initializeServo();

    // void calibrateServo();

    void steerLoop();
}