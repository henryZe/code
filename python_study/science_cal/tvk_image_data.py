from tvtk.api import tvtk
import numpy as np

if 0:
    img = tvtk.ImageData(origin = (1, 2, 3), spacing = (1, 1, 1), dimensions = (3, 4, 5))

    print(img)
    for n in range(6):
        print(img.get_point(n))

if 1:
    x = np.array([0, 3, 9, 15])
    y = np.array([0, 1, 5])
    z = np.array([0, 2, 3])
    r = tvtk.RectilinearGrid()
    r.x_coordinates = x
    r.y_coordinates = y
    r.z_coordinates = z
    r.dimensions = len(x), len(y), len(z)

    for n in range(6):
        print(r.get_point(n))








