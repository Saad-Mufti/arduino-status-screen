from pynput.keyboard import Key, Listener
import serial
from serial.tools import list_ports
import time, threading, sys
import ctypes

# Average word length (in characters)
AWL = 5
wpm = 0
ch_cnt = 0
words = 0
t0 = time.time()

ports = list_ports.comports()
matches = list(filter(lambda i: i.vid == 0x1A86 and i.pid == 0x55D4, ports))
matches = list(map(lambda a: a.name, matches))
name = ""
if len(matches) > 0:
    name = matches[0]
else:
    ctypes.windll.user32.MessageBoxW(None, "Device not found. Please plug it in and try again.", "Error", 0)
    sys.exit()
connection = serial.Serial(name, 250_000)


prev_key = None
def on_press(key):
    global prev_key, words
    if key == Key.space and key != prev_key or prev_key == None:
        words += 1
    prev_key = key
    

def on_release(key):
    return
    # if key == Key.esc:
    #     return False


words_tmp = 0
fails = 0
def calc():
    global wpm, words_tmp, words
    t = 5
    wpm = 60 * (words - words_tmp) // t
    print("WPM: " + str(wpm))
    if not connection.isOpen():
        try:
            connection.open()
        except: 
            print("Cannot open connection with port")
    
    try:
        connection.write(str(wpm).encode())
    except:
        global fails
        print("Device not available")
        if connection.isOpen():
            connection.close()
        fails += 1
        if fails == 100:
            sys.exit()
    words_tmp = words
    threading.Timer(t, calc).start()

calc()

with Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()

