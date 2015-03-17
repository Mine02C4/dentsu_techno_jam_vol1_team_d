#!/usr/bin/python

import chart
import td
import time

while True:
    (interest, concentration, drowsiness, stress, like) = td.get_kansei()

    chart.spider_chart(interest, concentration, drowsiness, stress, like, "/var/www/html/chart.png")

    time.sleep(30)

