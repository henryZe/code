import pygame, sys
from math import pi

pygame.init()

screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption("大航海时代4")

gold = 255, 251, 0
red = pygame.Color('red')
white = 255, 255, 255
green = pygame.Color('green')

# surface, color, (point(left, top), left, top), edge_width
# r1rect = pygame.draw.rect(screen, gold, (100, 100, 200, 100), 5)
# r2rect = pygame.draw.rect(screen, red, (210, 210, 200, 100), 0)

e1rect = pygame.draw.ellipse(screen, green, (50, 50, 500, 300), 3)
c1rect = pygame.draw.circle(screen, gold, (200, 180), 30, 5)
c2rect = pygame.draw.circle(screen, gold, (400, 180), 30)
r1rect = pygame.draw.rect(screen, red, (170, 130, 60, 10), 3)
r2rect = pygame.draw.rect(screen, red, (370, 130, 60, 10))
plist = [(295, 170), (285, 250), (260, 280), (340, 280), (315, 250), (305, 170)]
l1rect = pygame.draw.lines(screen, gold, True, plist, 2)
a1rect = pygame.draw.arc(screen, red, (200, 220, 200, 100), 1.4 * pi, 1.9 * pi, 3)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    pygame.display.update()
