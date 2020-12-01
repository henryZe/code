# -*- coding: utf-8 -*-
"""
Created on Mon Nov 30 22:13:00 2020

@author: user
"""

import requests
from bs4 import BeautifulSoup
import bs4
import re

def getHTMLText(url):
    try:
        r = requests.get(url, timeout = 10)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
        return r.text

    except:
        print("cause exception")
        return ""

def fillUnivList(ulist, html):
    soup = BeautifulSoup(html, "html.parser")

    for tr in soup.find("tbody").children:
        if isinstance(tr, bs4.element.Tag):
            tds = tr('td')
            # rating, university, city, sort, score
            ulist.append([tds[0].text.strip(),
                          tds[1].text.strip(),
                          tds[2].text.strip(),
                          tds[3].text.strip(),
                          tds[4].text.strip()])

def printUnivList(ulist, num):
    f = "{0:^10}\t{1:{3}^10}\t{2:^10}"
    print(f.format("排名", "大学名称", "得分", chr(12288)))
    for i in range(num):
        u = ulist[i]
        print(f.format(u[0], u[1], u[4], chr(12288)))

def main():
    uinfo = []
    url = "https://www.shanghairanking.cn/rankings/bcur/2020"

    html = getHTMLText(url)
    fillUnivList(uinfo, html)
    printUnivList(uinfo, 30)

main()
