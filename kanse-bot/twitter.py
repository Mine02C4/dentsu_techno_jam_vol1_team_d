#!/usr/bin/python
# coding: utf-8

import os
import twython
import urllib3.contrib.pyopenssl

urllib3.contrib.pyopenssl.inject_into_urllib3()
api = twython.Twython(os.getenv("CONSUMER_KEY"),
                      os.getenv("CONSUMER_SECRET"),
                      os.getenv("ACCESS_KEY"),
                      os.getenv("ACCESS_SECRET"))

def tweet(s):
    try:
        api.update_status(status = s)
    except twython.TwythonError as e:
        print e

if __name__ == '__main__':
    tweet("test message")

