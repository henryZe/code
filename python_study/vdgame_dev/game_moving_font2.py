import pygame, sys
import pygame.freetype

pygame.init()

size = width, height = 1600, 900
speed = [1, 1]
BLACK = 0, 0, 0
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Ball 1.0")

pos = [230, 160]
green = pygame.color.Color("green")
blue = pygame.color.Color("blue")

f1 = pygame.freetype.Font("C://Windows//Fonts//msyh.ttc", 36)
f1surf, f1rect = f1.render("大航海时代IV", fgcolor = green, bgcolor = blue, size = 50)

# frames per second
fps = 100
fclock = pygame.time.Clock()

def sign(num):
    if num < 0:
        return -1
    if num > 0:
        return 1
    if num == 0:
        return 0

def speed_tone(axis, direct):
    if (abs(speed[axis]) + direct) == 0:
        return
    speed[axis] = (abs(speed[axis]) + direct) * sign(speed[axis])

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                speed_tone(0, -1)
            if event.key == pygame.K_RIGHT:
                speed_tone(0, 1)
            if event.key == pygame.K_UP:
                speed_tone(1, -1)
            if event.key == pygame.K_DOWN:
                speed_tone(1, 1)

    if pos[0] <= 0 or pos[0] + f1rect.width > width:
        speed[0] = -speed[0]
    if pos[1] <= 0 or pos[1] + f1rect.height > height:
        speed[1] = -speed[1]

    pos[0] += speed[0]
    pos[1] += speed[1]

    screen.fill(BLACK)
    screen.blit(f1surf, (pos[0], pos[1]))
    pygame.display.update()
    fclock.tick(fps)
