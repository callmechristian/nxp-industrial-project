clear

% Define parameters
m = 1;         % mass of the car (kg)
I = 0.1;       % moment of inertia of the car (kg*m^2)
l = 0.1;       % distance between front and rear wheels (m)
w = 0.05;       % distance between wheels (m)
K = 100;        % lateral stiffness of the tires (N/rad)
C = 100;        % longitudinal stiffness of the tires (N/m)
mu = 0.8;      % coefficient of friction between tire and ground
g = 9.81;      % acceleration due to gravity (m/s^2)

% controller
Kp = 10;       % proportional gain of the controller
Kd = 1;        % derivative gain of the controller

% Define initial conditions
x0 = 0;        % initial x position (m)
phi0 = 0;      % initial orientation (rad)
x_dot0 = 0;   % initial x velocity (m/s)
phi_dot0 = 0;  % initial angular velocity (rad/s)