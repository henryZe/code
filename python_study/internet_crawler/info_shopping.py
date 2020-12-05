# -*- coding: utf-8 -*-
"""
Created on Wed Dec  2 19:34:24 2020

@author: user
"""

import requests
import re
import os
from bs4 import BeautifulSoup

def getHTMLText(url):
    head = {'User-Agent': 'Chrome/10'}
    r = requests.get(url, headers = head, timeout = 30)
    r.raise_for_status()
    r.encoding = r.apparent_encoding
    return r.text

def parsePage(info_list, html):
    soup = BeautifulSoup(html, "html.parser")
    divs = soup.find_all('div', attrs = {'class': 'good-detail-text'})

    for div in divs:
        a = div.find('a')
        title = a.attrs['title']

        span = div.find('span', attrs = {'class': 'sale-price prime-cost'})
        price = span.text.split()[0]

        info_list.append([title, price])

def printGoodsList(info_list, goods):
    template = "{:4}\t{:64}\t{:8}\n"

    print(template.format('序号', '商品名称', '价格'))

    for i, item in enumerate(info_list):
        print(template.format(str(i + 1), item[0], item[1]))

    # ctx = "序号,商品名称,价格"
    # for i, item in enumerate(info_list):
    #     ctx += "{},{},{}\n".format(str(i + 1), item[0], item[1])

    # with open(os.path.join('./', goods + '.csv'), 'w') as f:
    #     f.write(ctx)
   
def main():
    goods = "书包"
    depth = 2
    start_url = "https://www.yohobuy.com/search?query=" + goods
    info_list = []

    for i in range(depth):
        url = start_url + '&page=' + str(i + 1)
        html = getHTMLText(url)
        parsePage(info_list, html)

    printGoodsList(info_list, goods)

main()
