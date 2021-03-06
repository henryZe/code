# -*- coding: utf-8 -*-
"""
Created on Fri Nov 27 22:13:17 2020

@author: user
"""

import requests
from bs4 import BeautifulSoup
import re

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    r.encoding = r.apparent_encoding
    demo = r.text
    # print(demo)

    soup = BeautifulSoup(demo, "html.parser")
    print(soup.prettify())

    print(soup.title)
    print(soup.a)
    print(soup.a.name)
    print(soup.a.parent.name)
    print(soup.a.parent.parent.name)

    tag = soup.a
    print(tag.attrs)
    print(tag.attrs['class'])
    print(tag.attrs['href'])
    print(type(tag.attrs))
    print(type(tag))
    print(tag.string)

    print(soup.p)
    print(soup.p.string)
    print(type(soup.p.string))

if 0:
    newsoup = BeautifulSoup("<b><!--This is a comment.--></b><p>This is not a comment.</p>",
                            "html.parser")
    print(newsoup.b.string)
    print(type(newsoup.b.string))

    print(newsoup.p.string)
    print(type(newsoup.p.string))

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    soup = BeautifulSoup(r.text, "html.parser")
    print(soup.prettify())

    print(soup.head)
    print(soup.head.contents)
    print(soup.body.contents)
    print(len(soup.body.contents))

    # 下行遍历
    print("children:")
    for child in soup.body.children:
        print(child)

    print("descendants:")
    for child in soup.body.descendants:
        print(child)

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    soup = BeautifulSoup(r.text, "html.parser")
    print(soup.prettify())

    # print(soup.title.parent)
    # print(soup.html.parent)
    # print(soup.parent)

    # 上行遍历
    for parent in soup.a.parents:
        if parent is None:
            print(parent)
        else:
            print(parent.name)

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    soup = BeautifulSoup(r.text, "html.parser")
    print(soup.a.next_sibling)
    print(soup.a.next_sibling.next_sibling)

    print(soup.a.previous_sibling)
    print(soup.a.previous_sibling.previous_sibling)

    for sibling in soup.a.previous_siblings:
        print(sibling)

    for sibling in soup.a.next_siblings:
        print(sibling)

if 0:
    # xml, extensible markup language
    '''
    <img src="china.jpg" size="10"> </img>
    name: img
    attr: src, size

    <img src="china.jpg" size="10" />
    Null Tag

    <!-- This is a comment, very useful -->
    Comment
    '''

    # json, JavaScript Object Notation
    '''
    "name": "Peking University"
    "name": ["henry", "eilene"]
    "name": {
        "male"  : "henry",
        "female": "eilene"
    }
    '''

    # yaml, YAML ain't markup language 
    '''
    name: henry
    name: #Comment
    -henry
    -eilene
    name:
        male: henry
        female: eilene
    '''

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    soup = BeautifulSoup(r.text, "html.parser")

    # find_all(name, attribute, recursive, string, ...)
    for link in soup.find_all("a"):
        print(link.get('href'))

    for link in soup.find_all(['a', 'b']):
        print(link.get('href'))

    for tag in soup.find_all(True):
        print(tag.name)

    for tag in soup.find_all(re.compile('b')):
        print(tag.name)

    for tag in soup.find_all(re.compile('b')):
        print(tag.name)

if 0:
    url = "https://python123.io/ws/demo.html"
    r = requests.get(url, timeout = 30)

    soup = BeautifulSoup(r.text, "html.parser")

    for tag in soup.find_all('p', 'course'):
        print(tag.name)
        print(tag.attrs)

    for tag in soup.find_all(id = 'link1'):
        print(tag)
        print(tag.string)

    for tag in soup.find_all(id = re.compile('link')):
        print(tag)

    for tag in soup.find_all('a', recursive=False):
        print(tag)

    for tag in soup.find_all('a', recursive=False):
        print(tag)

    for tag in soup.find_all(string = 'Basic Python'):
        print(tag)

    for tag in soup.find_all(string = re.compile('python')):
        print(tag)

    # find(): return first result
    # find_all(): return all results

    # find_parents(): return all results in parent
    # find_parent(): return first result in parent

    # find_next_siblings()
    # find_next_sibling()

    # find_previous_siblings()
    # find_previous_sibling()
