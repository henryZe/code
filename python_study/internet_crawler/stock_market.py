# -*- coding: utf-8 -*-
"""
Created on Thu Dec 10 19:06:20 2020

@author: user
"""

import time
import requests
import re
import os
from bs4 import BeautifulSoup
import traceback

def getHTMLText(url, code = 'utf-8'):
    try:
        r = requests.get(url, timeout = 10)
        r.raise_for_status()
        r.encoding = code
        return r.text
    except:
        return ""

def getStockList(lst, stockURL):
    tabs = 2
    stock_m = ['SH', 'SZ']

    for tab in range(tabs):
        html = getHTMLText(stockURL + "tab=" + str(tab + 1))
        if html == "":
            continue
        soup = BeautifulSoup(html, 'html.parser')

        div = soup.find('div', attrs = {'class' : 'ngbglistdiv'})
        a_tags = div.find_all('a')
        for a in a_tags:
            try:
                num = re.findall(r'\(\d{6}\)', a.string)[0]
                lst.append(stock_m[tab] + num[1:-1])
            except:
                continue

def getStockInfo(lst, stockURL, fpath):
    infoDict = {}
    count = 0

    with open(fpath, 'w', encoding = 'utf-8') as f:
        f.write(time.strftime('%Y-%m-%d', time.localtime(time.time())) + '\n')

    for stock in lst:
        count += 1

        try:
            html = getHTMLText(stockURL + stock + '/')
            if html == "":
                continue
            soup = BeautifulSoup(html, 'lxml')

            hd = soup.find('header', attrs = {'class' : 'stock_title'})
            h1 = hd.find('h1')

            div = soup.find('div', attrs = {'class' : 's_date'})
            keyList = div.find_all('dt')
            valueList = div.find_all('dd')

            infoDict.update({ 'ID' : stock })
            infoDict['Stock Name'] = h1.text

            for i in range(len(keyList)):
                key = keyList[i].text
                value = valueList[i].text
                infoDict[key] = value

            with open(fpath, 'a', encoding = 'utf-8') as f:
                f.write(str(infoDict) + '\n')
                print("\rProcessing: {:.2f}%".format(count * 100 / len(lst)), end = "")

        except:
            traceback.print_exc()
            continue

def main():
    stock_list_url = "https://guba.eastmoney.com/remenba.aspx?type=1&"
    stock_info_url = "https://hq.gucheng.com/"
    output_file = "./stock_info.txt"
    slist = []

    getStockList(slist, stock_list_url)
    getStockInfo(slist, stock_info_url, output_file)

main()
