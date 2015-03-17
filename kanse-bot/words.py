#!/usr/bin/python
# coding: utf-8

import random

i_up   = [ 'おおっ', 'いくぞっ', 'ワー' ]
i_down = [ 'ふーん' ]

c_up   = [ 'ググっ', 'ギュッ' ]
c_down = [ 'フー' ]

d_up   = [ '' ]
d_down = [ 'ボー', 'スースー' ]

s_up   = [ 'ギリギリ', 'グー' ]
s_down = [ 'は～', 'ほー' ]

l_up   = [ 'ヤッタ' ]
l_down = [ 'エー' ]

def word(interest, concentration, drowsiness, stress, like):
    i =  1 if interest > 60 else -1 if interest < 40 else 0
    c =  1 if concentration > 60 else -1 if concentration < 40 else 0
    d =  1 if drowsiness > 60 else -1 if drowsiness < 40 else 0
    s =  1 if stress > 60 else -1 if stress < 40 else 0
    l =  1 if like > 60 else -1 if like < 40 else 0

    w = ""

    if i == 1:
      w = w + i_up[int(round(random.uniform(0, len(i_up) - 1)))] + " "
    if i == -1:
      w = w + i_down[int(round(random.uniform(0, len(i_down) - 1)))] + " "

    if c == 1:
      w = w + c_up[int(round(random.uniform(0, len(c_up) - 1)))] + " "
    if c == -1:
      w = w + c_down[int(round(random.uniform(0, len(c_down) - 1)))] + " "

    if d == 1:
      w = w + d_up[int(round(random.uniform(0, len(d_up) - 1)))] + " "
    if d == -1:
      w = w + d_down[int(round(random.uniform(0, len(d_down) - 1)))] + " "

    if s == 1:
      w = w + s_up[int(round(random.uniform(0, len(s_up) - 1)))] + " "
    if s == -1:
      w = w + s_down[int(round(random.uniform(0, len(s_down) - 1)))] + " "

    if l == 1:
      w = w + l_up[int(round(random.uniform(0, len(l_up) - 1)))] + " "
    if l == -1:
      w = w + l_down[int(round(random.uniform(0, len(l_down) - 1)))] + " "

    return w

if __name__ == '__main__':
    print word(61,43,44,44,44)
