import pygame
import math

# Initialize Pygame
pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('3D Tree Layers')

# Colors
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
BROWN = (139, 69, 19)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)

# Camera parameters
camera_distance = 2
camera_speed = 0.1
camera_position = [SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2]

# Tree layers
tree_height = 100  # Total height of the tree
num_layers = 10  # Number of tree layers

# Function to draw the tree
def draw_tree(camera_distance):
    # Calculate the distance for each layer and render the layer
    layer_height = tree_height / num_layers
    for i in range(num_layers):
        # Calculate the "depth" of each layer based on the camera distance
        depth_factor = (camera_distance + i * 0.5)  # Increase depth factor to simulate distance
        layer_size = (camera_distance + i * 0.5) * 5  # Increase size with distance
        
        # Calculate the position to draw each layer (move away from camera on X, Y)
        x_offset = int(camera_position[0] + math.sin(i) * 40 * (camera_distance / 10))
        y_offset = int(camera_position[1] + math.cos(i) * 40 * (camera_distance / 10))

        # Draw the layer (simulate with circles for simplicity)
        pygame.draw.circle(screen, GREEN, (x_offset, y_offset), int(layer_size))

# Function to draw camera position indicator
def draw_camera_indicator():
    pygame.draw.circle(screen, BLUE, (camera_position[0], camera_position[1]), 10)
    pygame.draw.line(screen, BLUE, (camera_position[0], 0), (camera_position[0], SCREEN_HEIGHT), 1)
    pygame.draw.line(screen, BLUE, (0, camera_position[1]), (SCREEN_WIDTH, camera_position[1]), 1)

# Main loop
running = True
while running:
    screen.fill(BLACK)

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                camera_distance += camera_speed  # Move camera away
            elif event.key == pygame.K_DOWN:
                camera_distance = max(0.1, camera_distance - camera_speed)  # Move camera closer

    # Draw tree with current camera distance
    draw_tree(camera_distance)

    # Draw camera position indicator
    draw_camera_indicator()

    # Update the display
    pygame.display.flip()

    # Limit the framerate
    pygame.time.Clock().tick(60)

# Quit Pygame
pygame.quit()
