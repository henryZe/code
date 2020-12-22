import pygame, sys

pygame.init()

icon = pygame.image.load("PYG03-withered-flower.png")
pygame.display.set_icon(icon)

speed = [1, 1]
BLACK = 0, 0, 0
vInfo = pygame.display.Info()
size = width, height = 600, 400
# screen = pygame.display.set_mode(size)
screen = pygame.display.set_mode(size, pygame.RESIZABLE)
# screen = pygame.display.set_mode(size, pygame.NOFRAME)
# screen = pygame.display.set_mode(size, pygame.FULLSCREEN)

pygame.display.set_caption("Amazing Ball 1.0")
ball = pygame.image.load("PYG02-ball.gif")
ballrect = ball.get_rect()

# frames per second
fps = 100
fclock = pygame.time.Clock()

still = False

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
            elif event.key == pygame.K_RIGHT:
                speed_tone(0, 1)
            elif event.key == pygame.K_UP:
                speed_tone(1, -1)
            elif event.key == pygame.K_DOWN:
                speed_tone(1, 1)
            elif event.key == pygame.K_ESCAPE:
                sys.exit()

        elif event.type == pygame.VIDEORESIZE:
            size = width, height = event.size[0], event.size[1]
            screen = pygame.display.set_mode(size, pygame.RESIZABLE)

        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                still = True
        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:
                still = False
                ballrect = ballrect.move(event.pos[0] - ballrect.left, event.pos[1] - ballrect.top)
        elif event.type == pygame.MOUSEMOTION:
            if event.buttons[0] == 1:
                ballrect = ballrect.move(event.pos[0] - ballrect.left, event.pos[1] - ballrect.top)

    # whether the window set in minisize
    if pygame.display.get_active() and not still:
        ballrect = ballrect.move(speed[0], speed[1])

    if ballrect.left < 0 or ballrect.right > width:
        speed[0] = -speed[0]
        if ballrect.right > width and ballrect.right + speed[0] > ballrect.right:
            speed[0] = -speed[0]

    if ballrect.top < 0 or ballrect.bottom > height:
        speed[1] = -speed[1]
        if ballrect.bottom > height and ballrect.bottom + speed[1] > ballrect.bottom:
            speed[1] = -speed[1]

    screen.fill(BLACK)
    screen.blit(ball, ballrect)
    pygame.display.update()
    fclock.tick(fps)
