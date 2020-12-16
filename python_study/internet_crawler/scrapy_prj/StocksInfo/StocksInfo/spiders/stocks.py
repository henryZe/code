import scrapy
import re

class StocksSpider(scrapy.Spider):
    name = 'stocks'
    start_urls = [
        'https://guba.eastmoney.com/remenba.aspx?type=1&tab=1',
        'https://guba.eastmoney.com/remenba.aspx?type=1&tab=2',
    ]

    def parse(self, response):
        stock_m = ['SH', 'SZ']
        prefix = stock_m[int(response.url[-1]) - 1]

        for href in response.css('a::attr(href)').extract():
            try:
                r_stock = re.findall(r'list,\d{6}', href)
                if len(r_stock) == 0:
                    continue

                stock = r_stock[0].split(',')[1]
                url = "https://hq.gucheng.com/" + prefix + stock + '/'

                yield scrapy.Request(url, callback=self.parse_perstock)
            except:
                continue

    def parse_perstock(self, response):
        infoDict = {}
        infoDict.update({ 'ID' : response.url[-9:-1] })

        hd = response.css('header.stock_title')
        h1 = hd.css('h1').extract()[0]
        print(h1)
        infoDict['Stock Name'] = re.findall(r'>.*</h1>', h1)[0][1:-5]

        div = response.css('div.s_date')
        keyList = div.css('dt').extract()
        valList = div.css('dd').extract()

        for i in range(len(keyList)):
            key = re.findall(r'>.*</dt>', keyList[i])[0][1:-5]
            try:
                val = re.findall(r'>.*</dd>', valList[i])[0][1:-5]
            except:
                val = '--'

            infoDict[key] = val

        yield infoDict
