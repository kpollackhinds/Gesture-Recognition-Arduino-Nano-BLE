from machine import Pin, UART
import time
import network
import socket
from extras import secrets
import struct
 

led = Pin("LED", Pin.OUT)
wifi_led = Pin(15, Pin.OUT, value=0)

uart = UART(0, baudrate=115200, tx= Pin(16), rx=Pin(17))

ssid = secrets['ssid']
pw = secrets['pw']

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, pw)

page = open("index.html", "r")
html = page.read()
page.close()

timeout = 10

#
while timeout >0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    timeout -=1

    print('waiting for connection...')
    time.sleep(1)

# Handle connection error
# Error meanings
# 0  Link Down
# 1  Link Join
# 2  Link NoIp
# 3  Link Up
# -1 Link Fail
# -2 Link NoNet
# -3 Link BadAuth

if wlan.status() !=3:
    raise RuntimeError('network connection failed')
else:
    print('connected')
    status = wlan.ifconfig()
    print( 'ip = ' + status[0])

addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]

s = socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
s.bind(addr)
s.listen(1)

def bytes_to_float(byte_array):
    # Convert the byte array to a float
    float_value = struct.unpack('<f', byte_array)[0]
    return float_value

while True:

    cl, addr = s.accept()
    cl_file = cl.makefile('rwb', 0)

    while True:
        line = cl_file.readline()

        if not line or line == b'\r\n':
           break
        
        response = html

        
    if uart.any():
        data = uart.read(4)
        conv_data = bytes_to_float(data)
        print(conv_data)
        led.toggle
        
    time.sleep(2)
    print('next')