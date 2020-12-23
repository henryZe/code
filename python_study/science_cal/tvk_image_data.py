from tvtk.api import tvtk
import numpy as np
from tvtkfunc import ivtk_scene, event_loop

def read_data():
    plot3d = tvtk.MultiBlockPLOT3DReader(
                xyz_file_name = "combxyz.bin",
                q_file_name = "combq.bin",
                scalar_function_number = 100,
                vector_function_number = 200)

    plot3d.update()
    return plot3d

if 0:
    img = tvtk.ImageData(origin = (1, 2, 3), spacing = (1, 1, 1), dimensions = (3, 4, 5))

    print(img)
    for n in range(6):
        print(img.get_point(n))

if 0:
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

if 0:
    s = tvtk.STLReader(file_name = "python.stl")
    m = tvtk.PolyDataMapper(input_connection = s.output_port)
    a = tvtk.Actor(mapper = m)

    win = ivtk_scene(a)
    win.scene.isometric_view()
    event_loop()

if 0:
    plot3d = read_data()
    grid = plot3d.output.get_block(0)
    print(grid)
    print(grid.dimensions)
    print(grid.points.to_array())
    print(grid.cell_data.number_of_arrays)
    print(grid.point_data.number_of_arrays)
    print(grid.point_data.scalars.name)
    print(grid.point_data.vectors.name)

