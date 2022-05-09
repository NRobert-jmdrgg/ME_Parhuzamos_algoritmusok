from concurrent.futures import process
from queue import Queue
import sys
from time import time
from timeit import default_timer as timer
import multiprocessing as mp

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



def count_words(lines, word, begin, end, count):
    i = begin
    while i < end and i < len(lines):
        count += KMPSearch_Count(word, lines[i])
        i += 1

def getLines(filename):
    text = []
    with open(filename) as file:
        text = file.readlines()
    return text


def main(): 
    filename = 'test.txt'

    lines = getLines(filename)
    
    process_count = 4
    
    if (len(lines) % process_count == 0):
        step = len(lines) // process_count
    else:
        step = len(lines) // process_count + 1
        
    processes = []
    
    # osztott valtozo
    count = mp.Value('d', 0.0)
    
    for i in range(process_count):
        start = i * step
        end = start + step
        processes.append(mp.Process(target=count_words, args=(lines, 'lorem', start, end, count)))
    
    for p in processes:
        p.start()
    
    for p in processes:
        p.join()
        
        
    print('count: {}'.format(count))
    

    
    start_time = timer()
    print('eltelt ido: {}'.format((timer() - start_time)))
    


if __name__ == '__main__':
    main()