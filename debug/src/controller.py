# Controller P
def angle_from_center_P(center):
    # define controller params
    Kp = 0.2

    # calculate displacement from center
    displacement = center - 64

    # 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
    angle = 64 + Kp * displacement

    # divide by max to get a percentage
    angle = angle / 128.0

    return 90 - angle * 180

# Controller PD
def angle_from_center_PD(center, prev_center, sampling_time):
    # define controller params
    Kp = 1
    Kd = 0.9
    a = 0.01 # filter coefficient

    # apply low-pass filter to input signal
    center = a * center + (1 - a) * prev_center

    # calculate displacement from center
    displacement = center - 64

    # calculate derivative of displacement
    d_displacement = (center - prev_center)/sampling_time

    # 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
    angle = 64 + Kp * displacement + Kd * d_displacement

    # divide by max to get a percentage
    angle = angle / 128.0

    return 90 - angle * 180

def speed_controller(angle_setpoint, angle, angle_error_int, angle_error_prev, angle_output_prev, sampling_time):
    # experiment for the desired wheel-speed ration, right now it's 0.6:1 for max steer
    # define controller params
    Kp = 0.05
    Ki = 0.1
    Kd = 0.9

    # Calculate the error between the setpoint and the actual angle
    angle_error = angle_setpoint - angle
    
    # Calculate the proportional term
    angle_p = Kp * angle_error
    
    # Calculate the integral term
    angle_error_int += angle_error * sampling_time
    angle_i = Ki * angle_error_int
    
    # Calculate the derivative term
    angle_d = Kd * (angle_error - angle_error_prev) / sampling_time
    
    # Calculate the output
    angle_output = angle_p + angle_i + angle_d
    
    # Apply the output to the back wheels, saturated and 0 and 1
    left_wheel_speed = min(max(1 - angle_output,0),1)
    right_wheel_speed = max(min(1 + angle_output,1),0)
    
    # Store the previous values for the derivative and integral terms
    angle_error_prev = angle_error
    angle_output_prev = angle_output
    
    return left_wheel_speed, right_wheel_speed, angle_error_int, angle_error_prev, angle_output_prev
