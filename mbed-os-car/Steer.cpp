#include "Steer.h"
#include <utility>
#include <vector>
#include "Camera.h"
#include <iostream>
#include <math.h>


#include "ThisThread.h"
#include "Car.h"
#include "Controller.h"
#include "RearMotors.h"

namespace Steer{
    // PARAMS
    int THRESHOLD_BLACK = 50; // arbitrary value
    int TRACK_WIDTH = 32; // arbitrary value

    // Variables used in control
    double steeringAngle = 0.5; // assume steering is in neutral
    double prevSteeringAngle = 0.5; // assume initial position is neutral
    double prev_center = 64.0; // assume car is placed in the center of the track
    double angle_error_int = 0; // assume 0 initial condition for integrator
    double angle_error_prev = 0; // assume no angle error in initial condition
    double angle_output_prev = 0; // assume car started with no initial speed

    // if the servo is not working properly and has a neutral steering bias
    double STEER_BIAS = 0.1;

    // pointers to where we assign the motor speeds
    double* wheel_l_speed_ptr = &RearMotors::wheel_l_speed;
    double* wheel_r_speed_ptr = &RearMotors::wheel_r_speed;
    
    // high level control
    bool foundFinishLine = false;
    int lapsAroundTheSun = 0; // how many laps we did

    // serpentine detection
    std::vector<double> centerHistory; // center history vector
    double maxDeviation; // max deviation across iterations to consider
    int MAX_CENTER_HISTORY = 30; // how many values of the center we keep

    void initializeServo(){
        ThisThread::sleep_for(3s);

        std::cout<<"Calibrating Servo..."<<std::endl;
        Car::servo.calibrate();

        std::cout<<"Done."<<std::endl;

        // std::cout<<"Steering to 0.3"<<std::endl;
        Car::servo = 0.3+STEER_BIAS;
        ThisThread::sleep_for(1s);
        Car::servo = 0.7+STEER_BIAS;
        ThisThread::sleep_for(1s);
        std::cout<<"Steering back to half..."<<std::endl;
        Car::servo = 0.5+STEER_BIAS;
    }

    void calculateSteer(){
        int leftLine=0;
        int rightLine=128;
        double center = 64;

        // Find center
        center = compute_center();

        // PD CONTROLLER for wheel angle
        steeringAngle = Controller::angle_from_center_PD(center, prev_center, 0.01) + STEER_BIAS;

        // P CONTROLLER for wheel angle
        // steeringAngle = Controller::angle_from_center_P(center);

        // PID CONTROLLER for individual wheel speed
        std::pair<double, double> p = Controller::wheel_speed_controller_PID(steeringAngle, 0.5+(64-center)/128.0, angle_error_int, angle_error_prev, angle_output_prev, Controller::sampling_time);
        *wheel_l_speed_ptr = p.first;
        *wheel_r_speed_ptr = p.second;

        // update previous center with current 
        prev_center = center;
        // update previous angle with current steering angle
        prevSteeringAngle = steeringAngle;
        // Store the previous values for the derivative and integral terms

        // add center to vector
        centerHistory.push_back(center);

        // erase any elements after MAX_CENTER_HISTROY
        if(centerHistory.size() > MAX_CENTER_HISTORY) {
            centerHistory.erase(centerHistory.begin());
        }

        if(isFinishFlag(Camera::cameraData, THRESHOLD_BLACK, THRESHOLD_BLACK, 5)) {
            foundFinishLine = true;
            lapsAroundTheSun++;
        }

        if(lapsAroundTheSun == 0) {
            // steer as normal
            // check for serpentines
            if(isSerpentineSection(centerHistory, maxDeviation)) {
                steeringAngle = 0.5 + STEER_BIAS;
            }
        } else if (lapsAroundTheSun == 1) {
            // reduce speed and check for obstacle
        } else if (lapsAroundTheSun > 1) {
            // dance
        }
        
        // // uncomment for debug
        // std::string s = std::to_string(center)+"\t"+ std::to_string(steeringAngle)+"\n";
        // std::cout<< s<< std::endl;
    }

    void steerLoop(){
        while(1) {
            calculateSteer();
            // Car::servo = steeringAngle;
            Car::servo = steeringAngle;
            ThisThread::sleep_for(1ms); // WARNING!!! update sampling time in Controller.h accordingly!!!
        }
    }

    double compute_center() {
        int leftLine = -1;
        int rightLine = -1;
        float center = 64;

        // Find the left line
        for (int i = 64; i > 0; i--) {
            if(Camera::cameraData[i] > THRESHOLD_BLACK) {
                leftLine = i;
            }
        }

        // Find the right line
        for (int i = 64; i < 128; i++) {
            if(Camera::cameraData[i] == 1) {
                rightLine = i;
            }
        }

        // Compute the center
        center = (leftLine+rightLine)/2.0f;

        // If there is only a left line
        if(leftLine != -1 && rightLine == -1) {
            center = (128+leftLine)/2.0f;
        }

        // If there is only a right line
        if(leftLine == -1 && rightLine != -1) {
            center = rightLine/2.0f;
        }

        // If there are no lines
        if(leftLine == -1 && rightLine == -1) {
            return center;
        }

        return center;
    }

    bool isSerpentineSection(const std::vector<double>& centerHistory, double maxDeviation) {
        if (centerHistory.size() < 2) {
            return false;
        }
        double prevCenter = centerHistory[0];
        double prevDiff = centerHistory[1] - prevCenter;
        for (size_t i = 1; i < centerHistory.size(); i++) {
            double center = centerHistory[i];
            double diff = center - prevCenter;
            if (std::abs(diff) > maxDeviation || diff * prevDiff >= 0) {
                return false;
            }
            prevCenter = center;
            prevDiff = diff;
        }
        return true;
    }

    bool isFinishFlag(const std::vector<int>& cameraOutput, int blackThreshold, int whiteThreshold, int minSegmentLength) {
        int segmentLength = 0;
        bool isBlack = false;
        for (int pixel : cameraOutput) {
            if (pixel > blackThreshold && !isBlack) {
                if (segmentLength >= minSegmentLength) {
                    return true;
                }
                segmentLength = 1;
                isBlack = true;
            } else if (pixel < whiteThreshold && isBlack) {
                if (segmentLength >= minSegmentLength) {
                    return true;
                }
                segmentLength = 1;
                isBlack = false;
            } else {
                segmentLength++;
            }
        }
        return false;
    }
}