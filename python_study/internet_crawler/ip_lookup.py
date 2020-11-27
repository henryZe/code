# -*- coding: utf-8 -*-
"""
Created on Fri Nov 27 21:05:16 2020

@author: user
"""

import requests

url = "https://api.ip138.com/ipv4/"
params = {'ip':'202.204.80.112'}
headers = {"token": "0fb19c5b74651f0ea4416d91a1e2cab1"}

r = requests.get(url, params = params, headers = headers)
print(r.request.url)

print(r.status_code)
print(r.text)
