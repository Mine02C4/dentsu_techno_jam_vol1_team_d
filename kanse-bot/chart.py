#!/usr/bin/python

import shutil
import requests

cht = "r"
chxt = "y,x"
chls = "2|2"
chco = "0088ff"
chxp = "0,0,20,40,60,80,100"
chxl = "1:|interest|concentration|drowsiness|stress|like"
chts = "000000,20"
chtt = "KANSEI"
chs = "320x320"

def spider_chart(interest, concentration, drowsiness, stress, like, file):
    chd = "t:%d, %d, %d, %d, %d, %d" % (interest, concentration, drowsiness, stress, like, interest)
    url = "http://chart.apis.google.com/chart" + "?cht=" + cht + "&chxt=" + chxt+ "&chls=" + chls + "&chco=" + chco + "&chxp=" + chxp + "&chxl=" + chxl + "&chts=" + chts + "&chtt=" + chtt + "&chs=" + chs + "&chd=" + chd
    res = requests.get(url, stream=True)
    with open(file, "wb") as fp:
        shutil.copyfileobj(res.raw, fp)

if __name__ == '__main__':
    spider_chart(10, 30, 50, 70, 90, "chart.png")
