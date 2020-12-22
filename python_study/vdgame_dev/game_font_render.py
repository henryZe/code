import pygame, sys
import pygame.freetype

pygame.init()

screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption("大航海时代4")

gold = 255, 251, 0

# font_file, size
font1 = pygame.freetype.Font("C://Windows//Fonts//msyh.ttc", 36)
f1surf, f1rect = font1.render("大航海时代IV",
                fgcolor = pygame.color.Color("green"),
                bgcolor = pygame.color.Color("blue"),
                size = 50)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    # locate surface at the point of screen
    # surface, location
    screen.blit(f1surf, (200, 160))
    pygame.display.update()
