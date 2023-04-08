#pragma once

#include <vector>

namespace Steer {
    extern double steeringAngle;
    extern double prev_err;

    void initializeServo();
    bool isSerpentineSection(const std::vector<double>& centerHistory, double maxDeviation);
    bool isFinishFlag(const std::vector<int>& cameraOutput, int blackThreshold, int whiteThreshold, int minSegmentLength);
    double compute_center();
    void checkForObstacle();
    void steerLoop();
}