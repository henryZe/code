# -*- coding: utf-8 -*-
"""
Created on Fri Nov 27 22:13:17 2020

@author: user
"""

import requests
from bs4 import BeautifulSoup

if 1:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    r.encoding = r.apparent_encoding
    demo = r.text
    # print(demo)

    soup = BeautifulSoup(demo, "html.parser")
    print(soup.prettify())

