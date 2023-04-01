namespace Steer {
    extern double steeringAngle;
    extern double prev_err;

    void initializeServo();

    // void calibrateServo();

    void steerLoop();
}