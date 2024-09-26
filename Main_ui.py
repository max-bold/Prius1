# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'Main.ui'
##
## Created by: Qt User Interface Compiler version 6.7.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QDialog,
    QFrame, QGridLayout, QLCDNumber, QLabel,
    QPushButton, QSizePolicy, QWidget)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(386, 345)
        self.gridLayout_2 = QGridLayout(Dialog)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.pump_cb = QCheckBox(Dialog)
        self.pump_cb.setObjectName(u"pump_cb")
        self.pump_cb.setEnabled(False)
        self.pump_cb.setAutoFillBackground(False)
        self.pump_cb.setCheckable(True)

        self.gridLayout.addWidget(self.pump_cb, 2, 0, 1, 1)

        self.close_cb = QCheckBox(Dialog)
        self.close_cb.setObjectName(u"close_cb")
        self.close_cb.setEnabled(False)
        self.close_cb.setAutoFillBackground(False)
        self.close_cb.setCheckable(True)

        self.gridLayout.addWidget(self.close_cb, 1, 0, 1, 1)

        self.open_cb = QCheckBox(Dialog)
        self.open_cb.setObjectName(u"open_cb")
        self.open_cb.setEnabled(False)
        self.open_cb.setAutoFillBackground(False)
        self.open_cb.setCheckable(True)

        self.gridLayout.addWidget(self.open_cb, 0, 0, 1, 1)

        self.power_cb = QCheckBox(Dialog)
        self.power_cb.setObjectName(u"power_cb")
        self.power_cb.setEnabled(False)
        self.power_cb.setAutoFillBackground(False)
        self.power_cb.setCheckable(True)

        self.gridLayout.addWidget(self.power_cb, 3, 0, 1, 1)


        self.gridLayout_2.addLayout(self.gridLayout, 5, 0, 1, 3)

        self.StatusLabel = QLabel(Dialog)
        self.StatusLabel.setObjectName(u"StatusLabel")
        self.StatusLabel.setMaximumSize(QSize(16777215, 10))

        self.gridLayout_2.addWidget(self.StatusLabel, 6, 0, 1, 3)

        self.label = QLabel(Dialog)
        self.label.setObjectName(u"label")
        self.label.setMaximumSize(QSize(16777215, 20))
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label, 1, 0, 1, 1)

        self.label_2 = QLabel(Dialog)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label_2, 1, 1, 1, 1)

        self.etadc = QLCDNumber(Dialog)
        self.etadc.setObjectName(u"etadc")
        self.etadc.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.etadc, 3, 2, 1, 1)

        self.label_3 = QLabel(Dialog)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label_3, 1, 2, 1, 1)

        self.etvalue = QLCDNumber(Dialog)
        self.etvalue.setObjectName(u"etvalue")
        self.etvalue.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.etvalue, 2, 2, 1, 1)

        self.posvalue = QLCDNumber(Dialog)
        self.posvalue.setObjectName(u"posvalue")
        self.posvalue.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.posvalue, 2, 0, 1, 1)

        self.line = QFrame(Dialog)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.gridLayout_2.addWidget(self.line, 4, 0, 1, 3)

        self.gridLayout_3 = QGridLayout()
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.UpdButton = QPushButton(Dialog)
        self.UpdButton.setObjectName(u"UpdButton")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.UpdButton.sizePolicy().hasHeightForWidth())
        self.UpdButton.setSizePolicy(sizePolicy)
        self.UpdButton.setMinimumSize(QSize(0, 20))
        self.UpdButton.setMaximumSize(QSize(16777215, 20))

        self.gridLayout_3.addWidget(self.UpdButton, 0, 2, 1, 1)

        self.PortSelectCombo = QComboBox(Dialog)
        self.PortSelectCombo.setObjectName(u"PortSelectCombo")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.PortSelectCombo.sizePolicy().hasHeightForWidth())
        self.PortSelectCombo.setSizePolicy(sizePolicy1)
        self.PortSelectCombo.setMinimumSize(QSize(0, 20))
        self.PortSelectCombo.setMaximumSize(QSize(16777215, 20))

        self.gridLayout_3.addWidget(self.PortSelectCombo, 0, 1, 1, 1)


        self.gridLayout_2.addLayout(self.gridLayout_3, 0, 0, 1, 3)

        self.ttvalue = QLCDNumber(Dialog)
        self.ttvalue.setObjectName(u"ttvalue")
        self.ttvalue.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.ttvalue, 2, 1, 1, 1)

        self.lcdNumber_4 = QLCDNumber(Dialog)
        self.lcdNumber_4.setObjectName(u"lcdNumber_4")
        self.lcdNumber_4.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_4, 3, 0, 1, 1)

        self.lcdNumber_5 = QLCDNumber(Dialog)
        self.lcdNumber_5.setObjectName(u"lcdNumber_5")
        self.lcdNumber_5.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_5, 3, 1, 1, 1)

        self.gridLayout_2.setRowStretch(1, 1)
        self.gridLayout_2.setRowStretch(2, 1)
        self.gridLayout_2.setRowStretch(3, 1)
        self.gridLayout_2.setRowStretch(4, 1)
        self.gridLayout_2.setRowStretch(5, 1)
        self.gridLayout_2.setRowStretch(6, 1)

        self.retranslateUi(Dialog)

        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Prius monitor V0.1", None))
        self.pump_cb.setText(QCoreApplication.translate("Dialog", u"Pump on", None))
        self.close_cb.setText(QCoreApplication.translate("Dialog", u"Close signal", None))
        self.open_cb.setText(QCoreApplication.translate("Dialog", u"Open signal", None))
        self.power_cb.setText(QCoreApplication.translate("Dialog", u"Power ok", None))
        self.StatusLabel.setText(QCoreApplication.translate("Dialog", u"TextLabel", None))
        self.label.setText(QCoreApplication.translate("Dialog", u"Valve position", None))
        self.label_2.setText(QCoreApplication.translate("Dialog", u"Tank temp", None))
        self.label_3.setText(QCoreApplication.translate("Dialog", u"Engine temp", None))
        self.UpdButton.setText(QCoreApplication.translate("Dialog", u"Update", None))
    # retranslateUi

