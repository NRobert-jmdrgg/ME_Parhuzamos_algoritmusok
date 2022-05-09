
import time
import sys
import collections
import concurrent.futures
import requests
# pip install pillow
from PIL import Image

import asyncio
# pip install aiohttp, aiofiles
import aiohttp        
import aiofiles


lines = []
with open('test.txt') as file:
    lines = file.readlines()
words = []
for line in lines:
    words.extend(line.split())

def get_longest():
    longest = ''
    for word in words:
        if len(word) > len(longest):
            longest = word
    # print('get_longest vege')
    return longest
    
def get_shortest():
    shortest = lines[0]
    for word in words:
        if len(word) < len(shortest):
            shortest = word
    # print('get_shortest vege')
    return shortest
    
def is_in_file(word):
    r = word in words
    # print('is_in_file vege')
    return r

def average_word_length():
    s = sum(len(word) for word in words)
    a = s / len(words)
    # print('average_word_length vege')
    return a
    
def most_common_word():
    wf = collections.Counter(words)
    mcw = list(wf)[0]
    # print('most common word vege')
    return mcw


word = sys.argv[1]
print('Eredmenyek:')

t1_start = time.process_time() 

l = get_longest()
s = get_shortest()
k = is_in_file(word)
a = average_word_length()
m = most_common_word()

r = [l, s, k, a, m]
# print(r)

t1_stop = time.process_time()

print(f'szekvencialis ido: {t1_stop - t1_start}')


t1_start = time.process_time() 

# cpythonban a GIL miatt nincs multithreading, az osszes egy szalon fog futni konkurensen
results = []
with concurrent.futures.ThreadPoolExecutor() as executor:
    # results egy future tipusu tomb
    results.append(executor.submit(get_longest))
    results.append(executor.submit(get_shortest))
    results.append(executor.submit(is_in_file, word))
    results.append(executor.submit(average_word_length))
    results.append(executor.submit(most_common_word))
    for r in concurrent.futures.as_completed(results):
        # print(r.result())
        pass
        
t1_stop = time.process_time()
        
print(f'threading ido: {t1_stop - t1_start}')
        
        
t1_start = time.process_time() 

results = []
with concurrent.futures.ProcessPoolExecutor(max_workers=5) as proc_executor:
    results.append(proc_executor.submit(get_longest))
    results.append(proc_executor.submit(get_shortest))
    results.append(proc_executor.submit(is_in_file, word))
    results.append(proc_executor.submit(average_word_length))
    results.append(proc_executor.submit(most_common_word))
    for r in concurrent.futures.as_completed(results):
        # print(r.result())
        pass
        
t1_stop = time.process_time()

print(f'mutliprocessing ido: {t1_stop - t1_start}')
        
urls = [
    'https://image.shutterstock.com/image-photo/grey-white-domestic-cat-600w-439615177.jpg',
    'https://image.shutterstock.com/image-photo/gray-kitten-white-background-600w-165838661.jpg',
    'https://image.shutterstock.com/image-photo/lazy-cat-sitting-on-cement-600w-1414420445.jpg',
    'https://image.shutterstock.com/image-photo/siberian-husky-puppy-winter-dog-600w-1871332402.jpg',
    'https://image.shutterstock.com/image-photo/walking-egyptian-mau-on-sunny-600w-1908418108.jpg',
    'https://image.shutterstock.com/image-photo/cute-cat-sitting-on-road-600w-773877655.jpg',
    'https://image.shutterstock.com/image-photo/british-blue-kitten-very-beautiful-600w-796071583.jpg',
    'https://image.shutterstock.com/image-photo/cute-kitten-sits-by-boards-600w-1631858755.jpg'
]
        
def download_image_seq(url, name):
    img_data = requests.get(url).content
    with open(f'img/{name}', 'wb') as handler:
        handler.write(img_data)

start = time.process_time()

names = []
for i, url in enumerate(urls):
    names.append(url.split('/')[4])
    download_image_seq(url, names[i])

for name in names:
    img = Image.open(f'img/{name}').convert('L')
    img.save(f'img/gray_{name}')
    
end = time.process_time()

print(f'grayscale szekvencialis ido: {end - start}')

async def download_image_async(urls, queue):
    for url in urls:
        name = url.split('/')[4]
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as resp:
                if resp.status == 200: #ok
                    f = await aiofiles.open(f'img/async_{name}', mode='wb')
                    await f.write(await resp.read())
                    await f.close()
                    await queue.put(f'img/async_{name}')


async def grayscale_image(queue):
    while True:
        name = await queue.get()
        img = Image.open(name).convert('L')
        img.save(name)
        queue.task_done()   
        

async def main():
    queue = asyncio.Queue()
    producers = []
    for i in range(0, len(urls), 2):
        producers.append(download_image_async(urls[i:i+2], queue))
    consumers = []
    for _ in range(4):
        consumers.append(asyncio.ensure_future(grayscale_image(queue)))
    await asyncio.gather(*producers,  return_exceptions=True)
    await queue.join()
    for consumer in consumers:
        consumer.cancel()
        
start = time.process_time()
        
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
loop.close() 

end = time.process_time()

print(f'grayscale async ido: {end - start}')