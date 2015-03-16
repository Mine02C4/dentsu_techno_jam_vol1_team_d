#!/usr/bin/python

import random
import time
from fluent import sender
from fluent import event

sender.setup('td.eeg_datasets', host='localhost', port=24224)

lower = 40
upper = 70

while True:
    data = []
    for i in range(0, 5):
        data.append(int(random.uniform(lower, upper)))
    event.Event('kansei_sample', {
        'concentration': data[0],
        'interest': data[1],
        'drowsiness': data[2],
        'stress': data[3],
        'like': data[4]
    })
    time.sleep(1)
