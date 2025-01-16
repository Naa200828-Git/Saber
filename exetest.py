import pygame
import sys
import random

# Initialize pygame
pygame.init()

# Set the size of the window
width, height = 800, 600
screen = pygame.display.set_mode((width, height))

# Define colors
WHITE = (255, 255, 255)
DARK_GREEN = (0, 100, 0)
LIGHT_GREEN = (144, 238, 144)

# Set the frame rate
clock = pygame.time.Clock()

# Define the base and sprite sizes
base_size = 50
sprite_sizes = [40, 30, 20, 10, 5]  # Sizes of the sprites
offsets = [10, 20, 40, 80, 160]    # Offsets for each sprite layer (double the previous)

# Generate random position for the base within the window (this is the object position)
base_x = random.randint(100, width - 100)
base_y = random.randint(100, height - 100)

# Initialize the camera position, initially centered on the player (base)
camera_x, camera_y = base_x, base_y

# Create the object (base + 5 sprites)
sprites = []
for i in range(5):
    sprite = {
        'size': sprite_sizes[i],
        'offset': offsets[i]
    }
    sprites.append(sprite)

# Main game loop
while True:
    screen.fill(WHITE)  # Fill the screen with white color

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Get the state of all keys
    keys = pygame.key.get_pressed()

    # Move the camera with WASD keys (but keep the player centered)
    if keys[pygame.K_a]:  # Move left
        camera_x -= 5
    if keys[pygame.K_d]:  # Move right
        camera_x += 5
    if keys[pygame.K_w]:  # Move up
        camera_y -= 5
    if keys[pygame.K_s]:  # Move down
        camera_y += 5

    # Apply small adjustment to camera's Y position (camera follows player)
    camera_y_adjusted = camera_y - 15

    # Tilt the object slightly based on the camera movement (simulate a tilt)
    tilt_offset_x = (camera_x - base_x) / 10  # Tilt increases as you move away from the object on X axis
    tilt_offset_y = (camera_y_adjusted - base_y) / 10  # Tilt increases as you move away from the object on Y axis

    # Draw the base (dark green square), adjusted for camera position and tilt
    pygame.draw.rect(screen, DARK_GREEN, 
                     (base_x - base_size // 2 - camera_x + tilt_offset_x + width // 2, 
                      base_y - base_size // 2 - camera_y_adjusted + tilt_offset_y + height // 2, 
                      base_size, base_size))

    # Draw the layers of sprites (smaller squares with increasing offsets)
    for sprite in sprites:
        size = sprite['size']
        offset = sprite['offset']

        # Each sprite is centered on the base, but offset away
        pygame.draw.rect(
            screen,
            LIGHT_GREEN,  # Light green color for sprites
            (base_x - size // 2 - camera_x + tilt_offset_x + offset + width // 2, 
             base_y - size // 2 - camera_y_adjusted + tilt_offset_y + offset + height // 2, 
             size, size)
        )

    # Update the display
    pygame.display.flip()

    # Limit the frame rate to 60 FPS
    clock.tick(60)
