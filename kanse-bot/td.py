#!/usr/bin/python

import datetime
import os
import pytz
import tdclient
import time

apikey = os.getenv("TD_API_KEY")

def get_kansei():
    n = datetime.datetime.now(pytz.timezone('Asia/Tokyo'))
    n = n - datetime.timedelta(minutes=1)
    t = n.strftime("%Y-%m-%d %H:%M:%S %Z")

    with tdclient.Client(apikey) as client:
        job = client.query("eeg_datasets",
              "SELECT AVG(interest) AS interest" +
              "      ,AVG(concentration) AS concentration" +
              "      ,AVG(drowsiness) AS drowsiness" +
              "      ,AVG(stress) AS stress" +
              "      ,AVG(like) AS like" +
              "  FROM kansei_sample" +
              " WHERE TD_TIME_RANGE(time, '" + t + "'," +
              "                     TD_TIME_ADD('" + t + "', '1m'))"
              )
        while not job.finished():
            time.sleep(1)
        for row in job.result():
            return row

if __name__ == '__main__':
    (interest, concentration, drowsiness, stress, like) = get_kansei()
    print(interest, concentration, drowsiness, stress, like)
