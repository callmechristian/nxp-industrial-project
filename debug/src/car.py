import pygame

class Car:
    def __init__(self, width, height, color, angle):
        self.width = width
        self.height = height
        self.color = color
        self.angle = angle

        # Create original rectangle surface
        self.original_surface = pygame.Surface((width, height), pygame.SRCALPHA)
        pygame.draw.rect(self.original_surface, color, (0, 0, width, height))

        # Get initial position of rotated rectangle
        self.rect = self.original_surface.get_rect(center=(300, 300))

    def rotate(self, angle):
        # Create new surface with rotated rectangle
        self.surface = pygame.transform.rotate(self.original_surface, angle)

        # Get rotated rectangle position
        self.rect = self.surface.get_rect(center=self.rect.center)

        # Update angle
        self.angle = angle

    def draw(self, screen):
        # Draw rotated rectangle onto screen
        screen.fill((255, 255, 255))  # Clear screen
        screen.blit(self.surface, self.rect)
