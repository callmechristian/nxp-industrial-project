import pygame
import math

# Initialize Pygame
pygame.init()

# Set screen size
screen = pygame.display.set_mode((600, 600))

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

# for derivation
prev_center = 64
sampling_time = 0.5


# Draw X function
def draw_x(x_pos, x_y_pos):
    pygame.draw.line(screen, x_color, (x_pos-x_size/2, x_y_pos-x_size/2), (x_pos+x_size/2, x_y_pos+x_size/2), 5)
    pygame.draw.line(screen, x_color, (x_pos-x_size/2, x_y_pos+x_size/2), (x_pos+x_size/2, x_y_pos-x_size/2), 5)

# Create rectangle surface
rect_surface = pygame.Surface((rect_width, rect_height), pygame.SRCALPHA)
pygame.draw.rect(rect_surface, rect_color, (0, 0, rect_width, rect_height))

# Get initial position of rotated rectangle and draw it onto screen
rotated_rect = rect_surface.get_rect(center=(300, 300))
screen.blit(rect_surface, rotated_rect)


# Initialize font
font = pygame.font.SysFont("Arial", 24)

# Function to display rotation angle
def display_angle(angle):
    angle_text = font.render(f"Angle: {angle:.1f}", True, (0, 0, 0))
    angle_rect = angle_text.get_rect(center=(300, 580))
    screen.blit(angle_text, angle_rect)

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
def angle_from_center_PD(center):
    # define controller params
    Kp = 0.2
    Kd = 0.1

    # calculate displacement from center
    displacement = center - 64

    # calculate derivative of displacement
    d_displacement = (center - prev_center)/sampling_time

    # 64 is neutral steering i.e. 50%, then we add Kp * displacement which is simple gain (P) control
    angle = 64 + Kp * displacement + Kd * d_displacement

    # divide by max to get a percentage
    angle = angle / 128.0

    return 90 - angle * 180

# Update display
pygame.display.update()

# Main game loop
while True:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                x_pos -= 10  # Move X left
                x_value -= 10
            elif event.key == pygame.K_RIGHT:
                x_pos += 10  # Move X right
                x_value += 10

    # P CONTROLLER
    # Compute angle based on the target x
    # rect_angle = angle_from_center_P(x_value)

    # TODO: implement async so you can actually compute the PD
    # PD CONTROLLER
    rect_angle = angle_from_center_PD(x_value)

    # Rotate surface by current angle
    rotated_surface = pygame.transform.rotate(rect_surface, rect_angle)

    # Get rotated rectangle position and draw it onto screen
    rotated_rect = rotated_surface.get_rect(center=(300, 300))
    screen.fill((255, 255, 255))  # Clear screen
    screen.blit(rotated_surface, rotated_rect)

    # Draw X
    draw_x(x_pos, x_y_pos)

    # Display rotation angle
    display_angle(rect_angle)

    # Update display
    pygame.display.update()
