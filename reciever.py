import serial
import ctypes
import time


class Data(ctypes.Structure):
    _fields_ = [
        ("op", ctypes.c_int16),
        ("cp", ctypes.c_int16),
        ("pp", ctypes.c_int16),
        ("pcp", ctypes.c_int16),
        ("vp", ctypes.c_float),
        ("tt", ctypes.c_float),
        ("et", ctypes.c_float),
    ]


if __name__ == "__main__":
    while True:
        try:
            device = serial.Serial("COM8", 115200)
        except:
            print("Lost connecton!               ", end="\r")
            time.sleep(0.1)
        else:
            while True:
                try:
                    data = device.read_until(b"\r\n")
                except:
                    break
                else:
                    if len(data) == 22:
                        struct = Data.from_buffer_copy(data)
                        print(
                            struct.op,
                            struct.cp,
                            struct.pp,
                            struct.pcp,
                            f"{struct.vp:.2f}",
                            f"{struct.tt:.1f}",
                            f"{struct.et:.1f}",
                            sep=" ",
                            end="\r",
                        )
