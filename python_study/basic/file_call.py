#!/usr/bin/python
# -*- coding: utf-8 -*-

import hello, sys
from PIL import Image

hello.test()

im = Image.open('test.png')
print(im.format, im.size, im.mode)
im.thumbnail((200, 100))
im.save('thumb.jpg', 'JPEG')

print(sys.path)