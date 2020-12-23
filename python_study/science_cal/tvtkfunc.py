from tvtk.tools import ivtk
from pyface.api import GUI

def ivtk_scene(actors):
    # create python shell
    win = ivtk.IVTKWithCrustAndBrowser()
    win.open()
    win.scene.add_actor(actors)
    return win

def event_loop():
    gui = GUI()
    gui.start_event_loop()
