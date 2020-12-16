import scrapy


class StocksSpider(scrapy.Spider):
    name = 'stocks'
    allowed_domains = ['hq.gucheng.com']
    start_urls = ['https://hq.gucheng.com/']

    def parse(self, response):
        pass
