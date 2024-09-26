import sys
from typing import Iterable, Mapping
from PySide6.QtWidgets import QApplication, QDialog
from PySide6.QtCore import Qt
import serial.tools
import serial.tools.list_ports
from Main_ui import Ui_Dialog
import serial
from threading import Thread
import time
from reciever import Data


class MainWindow(QDialog):
    def __init__(self):
        super().__init__()
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)

        self.ui.UpdButton.pressed.connect(self.getportlist)
        self.getportlist()

    def getportlist(self):
        self.ui.PortSelectCombo.clear()
        for port in serial.tools.list_ports.comports():
            self.ui.PortSelectCombo.addItem(port.description)


class Worker(Thread):
    def __init__(self, ui: MainWindow) -> None:
        super().__init__()
        self.ui = ui.ui
        self.stopreq = False

    def run(self):
        while True:
            if self.stopreq:
                break
            try:
                text = self.ui.PortSelectCombo.currentText()
                a = text.find("(") + 1
                b = text.find(")")
                self.device = serial.Serial(text[a:b], 115200, timeout=1)
            except:
                self.ui.StatusLabel.setText("Lost connecton!")
                time.sleep(0.1)
            else:
                self.ui.StatusLabel.setText(f"Connected to {text[a:b]}")
                while True:
                    try:
                        data = self.device.read_until(b"\r\n")
                    except:

                        break
                    else:
                        if len(data) == 22:
                            self.ui.StatusLabel.setText(f"Connection OK")
                            struct = Data.from_buffer_copy(data)
                            self.ui.etvalue.display(f"{struct.et:.1f}")
                            self.ui.ttvalue.display(f"{struct.tt:.1f}")
                            self.ui.posvalue.display(f"{struct.vp:.2f}")
                            self.ui.open_cb.setChecked(struct.op == 0)
                            self.ui.close_cb.setChecked(struct.cp == 0)
                            self.ui.pump_cb.setChecked(struct.pp == 0)
                            self.ui.power_cb.setChecked(struct.pcp == 0)
                        else:
                            self.ui.StatusLabel.setText(f"No data received!")

    def stop(self):
        self.stopreq = True
        self.device.close()

    def restart(self):
        self.device.close()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()
    worker = Worker(window)

    window.ui.PortSelectCombo.currentTextChanged.connect(worker.restart)

    worker.start()
    app.exec()
    worker.stop()
