from tvtk.tools import tvtk_doc
from tvtk.api import tvtk

if 0:
    # guilding document
    tvtk_doc.main()

if 1:
    s = tvtk.CubeSource(x_length = 1.0, y_length = 2.0, z_length = 3.0)
    print(s)
