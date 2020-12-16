# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter


class StocksinfoPipeline:
    def process_item(self, item, spider):
        return item

class PerStockInfo_Pipeline:
    def open_spider(self, spider):
        self.f = open('Scrapy_StockInfo.txt', 'w', encoding = 'utf-8')

    def close_spider(self, spider):
        self.f.close()

    def process_item(self, item, spider):
        try:
            line = str(dict(item)) + '\n'
            self.f.write(line)
        except:
            pass

        return item
