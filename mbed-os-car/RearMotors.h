namespace RearMotors {
    // extern double wheel_l_speed;
    // extern double wheel_r_speed;

    void initializeRearMotors();

    void move(double speed);
    void setRightWheelSpeed(double speed);
    void setLeftWheelSpeed(double speed);

    void motorLoop();
}