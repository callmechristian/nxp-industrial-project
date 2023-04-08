#include "Steer.h"
#include <utility>
#include <vector>
#include "Camera.h"
#include <iostream>
#include <math.h>

// Own headers
#include "ThisThread.h"
#include "Car.h"
#include "Controller.h"
#include "RearMotors.h"
#include "Ultrasonic.h"

// CONTROLLER SETUP -----------------------------------------------------------------------------------------------------------------------//
#define FLAG_STEERING_CONTROLLER "P"            // currently implemented P and PD
#define FLAG_SPEED_CONTROLLER "PID"             // currently implemented P and PID
#define FLAG_DIFF_DRIVE_RATIO 0.9
// PARAMS -------------------------------------------------------------------------------------------------------------------------------- //
#define THRESHOLD_BLACK 50                      // arbitrary value // int THRESHOLD_BLACK = 50;
#define TRACK_WIDTH 32                          // arbitrary value // int TRACK_WIDTH = 32;
#define THRESHOLD_CHECKER_COUNT 5               // depends on how the finish flag looks like // int THRESHOLD_CHECKER_COUNT = 5;
#define THRESHOLD_CHECKER_SIZE 3                // minimum width of each checker in the finish flag // int THRESHOLD_CHECKER_SIZE = 3;
// CONSTANTS ----------------------------------------------------------------------------------------------------------------------------- //
#define STEER_BIAS 0.1                          // if the servo is not working properly and has a neutral steering bias
//---------------------------------------------------------------------------------------------------------------------------------------- //

namespace Steer{
    // Variables used in control
    double steeringAngle = 0.5; // assume steering is in neutral
    double prevSteeringAngle = 0.5; // assume initial position is neutral
    double prev_center = 64.0; // assume car is placed in the center of the track
    double angle_error_int = 0; // assume 0 initial condition for integrator
    double angle_error_prev = 0; // assume no angle error in initial condition
    double angle_output_prev = 0; // assume car started with no initial speed

    // pointers to where we assign the motor speeds
    double* wheel_l_speed_ptr = &RearMotors::wheel_l_speed;
    double* wheel_r_speed_ptr = &RearMotors::wheel_r_speed;

    // maximum car speed
    double max_speed_car = 0.4;
    
    // high level control
    bool foundFinishLine = false;
    std::vector<bool> finishLine_history;
    int COOUNTER_LAPS_AROUND_THE_SUN = 0; // how many laps we did

    // serpentine detection
    std::vector<double> centerHistory; // center history vector
    double maxDeviation = 5; // max deviation across iterations to consider
    int MAX_CENTER_HISTORY = 30; // how many values of the center we keep

    // misc
    std::string _cmp_;

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

        _cmp_ = FLAG_STEERING_CONTROLLER;
        if(_cmp_.compare("P")) {
                // P CONTROLLER for wheel angle
                steeringAngle = Controller::angle_from_center_P(center) + STEER_BIAS;
        } else if(_cmp_.compare("PD")) {
                // PD CONTROLLER for wheel angle
                 steeringAngle = Controller::angle_from_center_PD(center, prev_center, 0.01) + STEER_BIAS;
        }

        // define pair
        std::pair<double,double> p;

        _cmp_ = FLAG_SPEED_CONTROLLER; // comparator TODO: change later to something more efficient
        if(_cmp_.compare("P")) {
            // P CONTROLLER for individual wheel speed
            p = Controller::wheel_speed_controller_P(center, max_speed_car, FLAG_DIFF_DRIVE_RATIO);
        } else if(_cmp_.compare("PID")) {
            // PID CONTROLLER for individual wheel speed
            p = Controller::wheel_speed_controller_PID(steeringAngle, 0.5+(64-center)/128.0, angle_error_int, angle_error_prev, angle_output_prev, Controller::sampling_time, max_speed_car);
        }

        // set speed values
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

        // update finish line history vector
        finishLine_history.push_back(isFinishFlag(Camera::cameraData, THRESHOLD_BLACK, THRESHOLD_BLACK, 5));

        // remove any values after 30
        if(finishLine_history.size() > 30) {
            finishLine_history.erase(finishLine_history.begin());
        }

        // go through the list and decide if we found the finish line flag
        int fline_ctr_ = 0;
        for(bool detection : finishLine_history) {
            if(detection) {
                fline_ctr_++;
            }
        }
        if(fline_ctr_ > THRESHOLD_CHECKER_COUNT) {
            foundFinishLine = true;
            COOUNTER_LAPS_AROUND_THE_SUN++;
            finishLine_history.clear();
        }

        // High level control depending on stage
        if(COOUNTER_LAPS_AROUND_THE_SUN == 0) {
            // steer as normal
            // check for serpentines
            // TODO: untested
            if(isSerpentineSection(centerHistory, maxDeviation)) {
                // only set steering straight
                    steeringAngle = 0.5 + STEER_BIAS;
            }
        } else if (COOUNTER_LAPS_AROUND_THE_SUN == 1) {
            // TODO: untested
            // reduce speed and check for obstacle
            max_speed_car = 0.3;
            checkForObstacle();
        } else if (COOUNTER_LAPS_AROUND_THE_SUN > 1) {
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
        int number_checkers = 0;
        bool isBlack = true;
        for (int pixel : cameraOutput) {
            // if pixel is above black threshold and we weren't black before
            if (pixel > blackThreshold && isBlack) {
                segmentLength++;
            } else {
                // count switch if we're above desired checker threshold
                if(segmentLength > THRESHOLD_CHECKER_SIZE) {
                    number_checkers++;
                }
                segmentLength = 0;
                isBlack = false;
            }

            // if pixel is below threshold, it's white
            if (pixel <= blackThreshold && !isBlack) {
                segmentLength++;
            } else {
                if(segmentLength > THRESHOLD_CHECKER_SIZE) {
                    number_checkers++;
                }
                segmentLength = 0;
                isBlack = true;
            }
        }

        if(number_checkers>THRESHOLD_CHECKER_COUNT) {
            return true;
        }

        return false;
    }

    void checkForObstacle() {
        // TODO: implement
        int dist_to_obstacle = Ultrasonic::distance();
        if(dist_to_obstacle < 30) {
            max_speed_car = 0;
        }
    }
}