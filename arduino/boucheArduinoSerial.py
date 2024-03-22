import serial.tools
import time

with serial.Serial('/dev/ttyACM0', 9600, timeout=1) as port:
    #port.write(b"tapointe\n")
    while True:
        top = port.readline()
        tap = top.decode()
        if tap!="\n" and tap!="" and tap!="\r":
            print("tap is: ", tap)
            print("top is: ", top)    
            if tap=="b\'BOOTING\r\n\'":
                print("HW says BOOTING")
            elif tap=="BOOTED":
                print("HW says BOOTED")
            elif tap=="READY":
                print("HW says READY")
            elif tap=="RECORDING":
                print("READ says RECORDING")
            elif tap=="ENDEDR":
                print("READ says BOOTED")
            elif tap=="QUIT":
                print("HW says it QUIT")