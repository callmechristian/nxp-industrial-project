import asyncio
import pygame
from src.car import Car
from src.controller import *
import matplotlib.pyplot as plt
from src.utils import sine_signal

# Initialize Pygame
pygame.init()

# Def screen params
SCREEN_WIDTH = 600
SCREEN_HEIGHT = 600

# Set screen size
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

# Define rectangle parameters
rect_width = 80
rect_height = 120
rect_color = (255, 0, 0)
rect_angle = 0  # Initial angle of the rectangle

# Define X parameters
x_size = 20
x_color = (255, 0, 0)
x_pos = 300  # Initial position of X in the center of the screen
x_y_pos = 50  # Y position of X in the top center of the screen
x_value = 64 # mimic camera data

# define async angle for sampling_time implementation
angle_async = 0

# for derivation
prev_center = 64
sampling_time = 0.1

# for speed controller
angle_error_int = 0.0
angle_error_prev = 0.0
angle_output_prev = 0.0
prev_angle = 0
wheel_l_speed = 1
wheel_r_speed = 1

# Draw X function
def draw_x(x_pos, x_y_pos):
    pygame.draw.line(screen, x_color, (x_pos-x_size/2, x_y_pos-x_size/2), (x_pos+x_size/2, x_y_pos+x_size/2), 5)
    pygame.draw.line(screen, x_color, (x_pos-x_size/2, x_y_pos+x_size/2), (x_pos+x_size/2, x_y_pos-x_size/2), 5)

# Function to display rotation angle
def display_angle(angle):
    angle_text = font.render(f"Angle: {angle:.1f}", True, (0, 0, 0))
    angle_rect = angle_text.get_rect(center=(300, 580))
    screen.blit(angle_text, angle_rect)

# Function to display wheel speeds
def display_speed(wheel_l_speed, wheel_r_speed):
    # L Wheel
    angle_text = font.render(f"Speed L: {wheel_l_speed:.1f}", True, (0, 0, 0))
    angle_rect = angle_text.get_rect(center=(240, 560))
    screen.blit(angle_text, angle_rect)

    # R Wheel
    angle_text = font.render(f"Speed R: {wheel_r_speed:.1f}", True, (0, 0, 0))
    angle_rect = angle_text.get_rect(center=(360, 560))
    screen.blit(angle_text, angle_rect)

# Create rectangle object
car = Car(rect_width, rect_height, rect_color, rect_angle)

# Initialize font
font = pygame.font.SysFont("Arial", 24)

# Update display
pygame.display.update()

# Define async function to handle game loop
async def game_loop():
    global x_pos, x_value, angle_async

    while True:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x_pos -= 10  # Move X left
                    x_value = (x_pos/SCREEN_WIDTH)*128
                elif event.key == pygame.K_RIGHT:
                    x_pos += 10  # Move X right
                    x_value = (x_pos/SCREEN_WIDTH)*128

        # Rotate rectangle and draw it onto screen
        car.rotate(angle_async)
        car.draw(screen)

        # Draw X
        draw_x(x_pos, x_y_pos)

        # Display rotation angle
        display_angle(angle_async)
        # Display wheel speed
        display_speed(wheel_l_speed, wheel_r_speed)

        # Update display
        pygame.display.update()

        # Sleep for a short period to avoid hogging the event loop
        await asyncio.sleep(0.01)

# Define async for camera loop
async def controller_loop():
    global x_value
    global x_pos
    global angle_async
    global prev_center
    global sampling_time
    global angle_error_int, angle_error_prev, angle_output_prev, wheel_l_speed, wheel_r_speed, prev_angle

    while True:
        print(str(x_value))

        # # P CONTROLLER
        # angle_async = angle_from_center_P(x_value)

        # PD CONTROLLER for angle of the wheels
        angle_async = angle_from_center_PD(x_value, prev_center, sampling_time)

        # PI CONTROLLER for speed of each wheel
        wheel_l_speed, wheel_r_speed, angle_error_int, angle_error_prev, angle_output_prev = speed_controller(angle_async, prev_angle, angle_error_int, angle_error_prev, angle_output_prev, sampling_time)

        prev_angle = angle_async

        # Update prev_center for derivative term
        prev_center = x_value

        # Sleep for sampling time duration then sample again
        await asyncio.sleep(sampling_time)

# Initialize the plot
fig, ax = plt.subplots()
line, = ax.plot([], [])

# Define a coroutine for the plot update loop
async def plot_loop():
    # Keep track of the x and y data points
    x_data = []
    y_data = []
    
    # Start the loop
    while True:
        # Update the y data with the current angle
        y_data.append(angle_async)
        
        # Add the current time as the x data
        x_data.append(asyncio.get_event_loop().time())
        
        # Update the plot
        line.set_data(x_data, y_data)
        ax.relim()
        ax.autoscale_view(True, True, True)
        plt.draw()
        plt.pause(0.001)
        
        # Sleep for a short duration to control the loop speed
        await asyncio.sleep(0.01)

# Start the event loop
async def main():
    await asyncio.gather(game_loop(), controller_loop(), plot_loop())

if __name__ == '__main__':
    asyncio.run(main())
