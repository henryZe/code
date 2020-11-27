# -*- coding: utf-8 -*-
"""
Created on Fri Nov 27 20:18:16 2020

@author: user
"""

import requests
import os

# url = "http://img0.dili360.com//ga/M02/49/A2/wKgBy1nPEYaAVlPHAABPhIqUzPA708.jpg"
url = "http://highlight-video.cdn.bcebos.com/video/6s/bec7fc30-309d-11eb-9c4b-7cd30a602318.mp4"
direct = "./img/"
path = direct + url.split('/')[-1]

try:
    if not os.path.exists(direct):
        os.mkdir(direct)

    if not os.path.exists(path):
        r = requests.get(url)
        
        with open(path, 'wb') as f:
            f.write(r.content)
            f.close()
            print("file saved")

    else:
        print("file already exist")

except:
    print("failed")
