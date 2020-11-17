# -*- coding: utf-8 -*-

from PIL import Image
import numpy as np

if 0:
    im = np.array(Image.open("./beijing.jpg"))
    print(im.shape, im.dtype)
    
    a = [255, 255, 255] - im
    b = Image.fromarray(a.astype('uint8'))
    b.save("./beijing_transfer.jpg")

if 1:
    a = np.array(Image.open("./beijing.jpg").convert("L"))
    b = 255 - a
    im = Image.fromarray(b.astype('uint8'))
    im.save("./beijing_L.jpg")
