from serial import Serial

port = Serial("COM3", 115200)
print(port)
port.close()
print(port.is_open)
