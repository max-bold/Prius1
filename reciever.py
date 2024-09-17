import serial
import ctypes


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


device = serial.Serial("COM3", 115200)
while True:
    data = device.read_until(b"\r\n")
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
