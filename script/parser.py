#!/usr/bin/env python
# -*- coding: utf-8 -*-
import urllib2 
from HTMLParser import HTMLParser  

class MyHTMLParser(HTMLParser):
  def __init__(self):
    HTMLParser.__init__(self)
    self.data = []
  def handle_data(self, data):
    self.data.append(data)
p = MyHTMLParser()
f = urllib2.Request('http://wap.ratp.fr/siv/schedule?service=next&reseau=bus&referer=station&lineid=B187&stationname=mairie+de+cachan&submitAction=Valider')
f.add_header('User-agent', 'Mozilla 5.10')
res = urllib2.urlopen(f)
html = res.read()
p.feed(html)
print p.data
p.close()
