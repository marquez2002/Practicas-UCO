#!/usr/bin/python

"""
This example is a try to know more about 
signal.

Author: i02matog
"""

import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QWidget, QLCDNumber, QSlider, QVBoxLayout, QApplication)


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):

        lcd = QLCDNumber(self) # lcd valor numerico
        sld = QSlider(Qt.Horizontal, self) 

        vbox = QVBoxLayout() # Creación de las cajas
        vbox.addWidget(lcd) # Adiccion al widget de lcd
        vbox.addWidget(sld) # Adiccion al widget de sld

        self.setLayout(vbox) # ...
        sld.valueChanged.connect(lcd.display) # Conexion 

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Señales')
        self.show()

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()