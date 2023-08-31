from machine import UART,Pin
import struct

led = Pin("LED", Pin.OUT)
uart = UART(0, baudrate=115200, tx= Pin(16), rx=Pin(17))

def bytes_to_float(byte_array):
    # Convert the byte array to a float
    float_value = struct.unpack('<f', byte_array)[0]
    return float_value

while True:
    if uart.any():
        data = uart.read(4)
        conv_data = bytes_to_float(data)
        print(conv_data)
        led.toggle