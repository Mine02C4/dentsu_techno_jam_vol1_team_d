#!/usr/bin/python

import td
import time
import twitter
import words

while True:
    (interest, concentration, drowsiness, stress, like) = td.get_kansei()
    word = words.word(interest, concentration, drowsiness, stress, like)

    twitter.tweet("%s\ninterest:%d concentration:%d drowsiness:%d stress:%d like:%d  #kansei" % (word, interest, concentration, drowsiness, stress, like))
    time.sleep(30)

