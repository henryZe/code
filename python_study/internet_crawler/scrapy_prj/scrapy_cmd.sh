#!/bin/sh

scrapy startproject py123demo
cd py123demo
scrapy genspider demo1 python123.io
scrapy crawl demo1
