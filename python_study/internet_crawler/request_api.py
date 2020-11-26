# -*- coding: utf-8 -*-
"""
Created on Thu Nov 26 11:56:28 2020

@author: user
"""

import requests
import datetime

def getHTMLText(url):
    try:
        r = requests.get(url, timeout = 30)
        # if status_code != 200, raise HTTPError exception
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text
    except:
        return "cause exception"


if 0:
    r = requests.get("http://www.baidu.com")
    print(r.status_code)
    print(r.encoding)
    print(r.text)

    print(r.apparent_encoding)
    r.encoding = 'utf-8'
    print(r.text)

    print(type(r))
    print(r.headers)

if 0:
    url = "http://www.baidu.com"
    print(getHTMLText(url))

if 0:
    # 1 params
    kv = {'key1': 'value1', 'key2': 'value2'}
    r = requests.request('GET', 'http://python123.io/ws', params = kv)
    print(r.url)

    # 2 data
    r = requests.request('POST', 'http://python123.io/ws', data = kv)
    body = '主题内容'
    r = requests.request('POST', 'http://python123.io/ws', data = body)

    # 3 json
    r = requests.request('POST', 'http://python123.io/ws', json = kv)

    # 4 headers
    hd = {'user-agent': 'Chrome/10'}
    r = requests.request('POST', 'http://python123.io/ws', headers = hd)

    # files
    fs = {'file': open('data.xls', 'rb')}
    r = requests.request('POST', 'http://python123.io/ws', files = fs)

    # timeout
    r = requests.request('GET', 'http://www.google.com', timeout = 5)

if 0:
    starttime = datetime.datetime.now()

    for i in range(100):
        url = "http://www.baidu.com"
        print(getHTMLText(url))

    endtime = datetime.datetime.now()
    print("second: {}s".format((endtime - starttime).seconds))

if 0:
    url = "http://www.jd.com/robots.txt"
    print(url)
    print(getHTMLText(url))

    url = "http://www.qq.com/robots.txt"
    print(url)
    print(getHTMLText(url))

    url = "http://www.baidu.com/robots.txt"
    print(url)
    print(getHTMLText(url))

    url = "http://www.moe.edu.cn/robots.txt"
    print(url)
    print(getHTMLText(url))


if 1:


