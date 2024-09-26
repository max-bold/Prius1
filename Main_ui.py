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
    QFrame, QGridLayout, QHBoxLayout, QLCDNumber,
    QLabel, QPushButton, QSizePolicy, QWidget)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(401, 329)
        self.gridLayout_2 = QGridLayout(Dialog)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.checkBox_3 = QCheckBox(Dialog)
        self.checkBox_3.setObjectName(u"checkBox_3")
        self.checkBox_3.setAutoFillBackground(False)
        self.checkBox_3.setCheckable(False)

        self.gridLayout.addWidget(self.checkBox_3, 2, 0, 1, 1)

        self.checkBox_2 = QCheckBox(Dialog)
        self.checkBox_2.setObjectName(u"checkBox_2")
        self.checkBox_2.setAutoFillBackground(False)
        self.checkBox_2.setCheckable(False)

        self.gridLayout.addWidget(self.checkBox_2, 1, 0, 1, 1)

        self.checkBox = QCheckBox(Dialog)
        self.checkBox.setObjectName(u"checkBox")
        self.checkBox.setAutoFillBackground(False)
        self.checkBox.setCheckable(False)

        self.gridLayout.addWidget(self.checkBox, 0, 0, 1, 1)

        self.checkBox_4 = QCheckBox(Dialog)
        self.checkBox_4.setObjectName(u"checkBox_4")
        self.checkBox_4.setAutoFillBackground(False)
        self.checkBox_4.setCheckable(False)

        self.gridLayout.addWidget(self.checkBox_4, 3, 0, 1, 1)


        self.gridLayout_2.addLayout(self.gridLayout, 5, 0, 1, 3)

        self.label = QLabel(Dialog)
        self.label.setObjectName(u"label")
        self.label.setMaximumSize(QSize(16777215, 20))
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label, 1, 0, 1, 1)

        self.lcdNumber_5 = QLCDNumber(Dialog)
        self.lcdNumber_5.setObjectName(u"lcdNumber_5")
        self.lcdNumber_5.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_5, 3, 1, 1, 1)

        self.lcdNumber_6 = QLCDNumber(Dialog)
        self.lcdNumber_6.setObjectName(u"lcdNumber_6")
        self.lcdNumber_6.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_6, 3, 2, 1, 1)

        self.lcdNumber_2 = QLCDNumber(Dialog)
        self.lcdNumber_2.setObjectName(u"lcdNumber_2")
        self.lcdNumber_2.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_2, 2, 1, 1, 1)

        self.line = QFrame(Dialog)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.gridLayout_2.addWidget(self.line, 4, 0, 1, 3)

        self.lcdNumber_4 = QLCDNumber(Dialog)
        self.lcdNumber_4.setObjectName(u"lcdNumber_4")
        self.lcdNumber_4.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_4, 3, 0, 1, 1)

        self.label_3 = QLabel(Dialog)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label_3, 1, 2, 1, 1)

        self.lcdNumber = QLCDNumber(Dialog)
        self.lcdNumber.setObjectName(u"lcdNumber")
        self.lcdNumber.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber, 2, 0, 1, 1)

        self.label_2 = QLabel(Dialog)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout_2.addWidget(self.label_2, 1, 1, 1, 1)

        self.lcdNumber_3 = QLCDNumber(Dialog)
        self.lcdNumber_3.setObjectName(u"lcdNumber_3")
        self.lcdNumber_3.setMinimumSize(QSize(100, 70))

        self.gridLayout_2.addWidget(self.lcdNumber_3, 2, 2, 1, 1)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.PortSelectCombo = QComboBox(Dialog)
        self.PortSelectCombo.setObjectName(u"PortSelectCombo")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Minimum)
        sizePolicy.setHorizontalStretch(1)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.PortSelectCombo.sizePolicy().hasHeightForWidth())
        self.PortSelectCombo.setSizePolicy(sizePolicy)
        self.PortSelectCombo.setMaximumSize(QSize(16777215, 20))

        self.horizontalLayout.addWidget(self.PortSelectCombo)

        self.UpdButton = QPushButton(Dialog)
        self.UpdButton.setObjectName(u"UpdButton")

        self.horizontalLayout.addWidget(self.UpdButton)


        self.gridLayout_2.addLayout(self.horizontalLayout, 0, 0, 1, 3)

        self.StatusLabel = QLabel(Dialog)
        self.StatusLabel.setObjectName(u"StatusLabel")

        self.gridLayout_2.addWidget(self.StatusLabel, 6, 0, 1, 3)

        self.gridLayout_2.setRowStretch(1, 1)
        self.gridLayout_2.setRowStretch(2, 1)
        self.gridLayout_2.setRowStretch(3, 1)
        self.gridLayout_2.setRowStretch(4, 1)
        self.gridLayout_2.setRowStretch(5, 1)

        self.retranslateUi(Dialog)

        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"Prius monitor V0.1", None))
        self.checkBox_3.setText(QCoreApplication.translate("Dialog", u"Pump on", None))
        self.checkBox_2.setText(QCoreApplication.translate("Dialog", u"Close signal", None))
        self.checkBox.setText(QCoreApplication.translate("Dialog", u"Open signal", None))
        self.checkBox_4.setText(QCoreApplication.translate("Dialog", u"Power ok", None))
        self.label.setText(QCoreApplication.translate("Dialog", u"Valve position", None))
        self.label_3.setText(QCoreApplication.translate("Dialog", u"Engine temp", None))
        self.label_2.setText(QCoreApplication.translate("Dialog", u"Tank temp", None))
        self.UpdButton.setText(QCoreApplication.translate("Dialog", u"Update", None))
        self.StatusLabel.setText(QCoreApplication.translate("Dialog", u"TextLabel", None))
    # retranslateUi

