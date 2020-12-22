import pygame, sys

pygame.init()

screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption("大航海时代4")

fps = 1
fclock = pygame.time.Clock()

num = 0
while True:
    # create event
    uevent = pygame.event.Event(pygame.KEYDOWN,
                {'unicode': 123, 'key': pygame.K_SPACE, 'mod': pygame.KMOD_ALT})
    pygame.event.post(uevent)
    num = num + 1

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

        elif event.type == pygame.KEYDOWN:
            if event.unicode == '':
                print('[KEYDOWN {}]:'.format(num), '#', event.key, event.mod)
            else:
                print('[KEYDOWN {}]:'.format(num), event.unicode, event.key, event.mod)

    pygame.display.update()
    # call tick function once per updating frame
    fclock.tick(fps)
