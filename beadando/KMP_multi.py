import sys
from time import time
from timeit import default_timer as timer
import threading


def fill_LPS(pattern, lps):
    le = 0
    lps[0] = 0
    i = 1
    while (i < len(pattern)):
        if (pattern[i] == pattern[le]):
            le += 1
            lps[i] = le
            i += 1
        else:
            if (le != 0):
                le = lps[le - 1]
            else:
                lps[i] = 0
                i += 1
            

def KMPSearch_Count(pattern, line):
    count = 0
    m = len(pattern)
    n = len(line)
    lps = [0] * m
    
    fill_LPS(pattern, lps)
    
    i = 0
    j = 0
    while (i < n):
        if (pattern[j] == line[i]):
            i += 1
            j += 1
        
        if (j == m):
            count += 1
            j = lps[j - 1]
        elif (i < n and pattern[j] != line[i]):
            if (j != 0):
                j = lps[j - 1]
            else:
                i += 1
    return count

lines = []
count = 0

lock = threading.Lock()

def count_words(word, begin, end, num):
    global count
    i = begin
    while i < end and i < len(lines):
        lock.acquire()
        count += KMPSearch_Count(word, lines[i])
        i += 1
        lock.release()
    

def getLines(filename):
    text = []
    with open(filename) as file:
        text = file.readlines()
    return text


def main(): 
    filename = 'test.txt'

    global lines
    lines = getLines(filename)
    
    thread_count = 4
    
    if (len(lines) % thread_count == 0):
        step = len(lines) // thread_count
    else:
        step = len(lines) // thread_count + 1
        
    th = []    
        
    for i in range(thread_count):
        start = i * step
        end = start + step
        th.append(threading.Thread(target=count_words, args=('lorem', start, end, i)))
    
    for i in range(thread_count):
        th[i].start()
        
    for i in range(thread_count):
        th[i].join()
    
    print('count: {}'.format(count))
    
    
    
    start_time = timer()
    print('eltelt ido: {}'.format((timer() - start_time)))
    



if __name__ == '__main__':
    main()