from tvtk.tools import tvtk_doc
from tvtk.api import tvtk

if 0:
    # guilding document
    tvtk_doc.main()

if 0:
    s = tvtk.CubeSource(x_length = 1.0, y_length = 2.0, z_length = 3.0)
    print(s)
    print(s.x_length)
    print(s.y_length)
    print(s.center)
    print(s.output_points_precision)

if 0:
    s = tvtk.ConeSource(height = 3.0, radius = 1.0, resolution = 36)
    print(s)
    print(s.height)
    print(s.radius)

if 1:
    # ---- Visualization Pipeline ----
    # data source
    # s = tvtk.CubeSource(x_length = 1.0, y_length = 2.0, z_length = 3.0)
    s = tvtk.ConeSource(height = 3.0, radius = 1.0, resolution = 36)

    # mapper: data source -> graph data
    m = tvtk.PolyDataMapper(input_connection = s.output_port)
    # --------------------------------

    # ---- Graphic Pipeline ----
    # actor: 实体
    a = tvtk.Actor(mapper = m)
    # renderer: 渲染器
    r = tvtk.Renderer(background = (0, 0, 0))
    r.add_actor(a)

    # window
    w = tvtk.RenderWindow(size = (600, 600))
    w.add_renderer(r)

    # interactor
    i = tvtk.RenderWindowInteractor(render_window = w)
    i.initialize()
    i.start()
    # --------------------------

