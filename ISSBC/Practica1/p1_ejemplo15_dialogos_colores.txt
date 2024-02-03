#!/usr/bin/python

"""
This example is a try to know more about 
color dialogs.

Author: i02matog
"""

from PyQt5.QtWidgets import (QWidget, QPushButton, QFrame, QColorDialog, QApplication)
from PyQt5.QtGui import QColor
import sys


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        col = QColor(0, 0, 0)

        self.btn = QPushButton('Cambiar Color', self) # Boton para modificar el color
        self.btn.move(20, 20)
        self.btn.clicked.connect(self.showDialog) # Conectar el boton para mostrar dialogo

        self.frm = QFrame(self)
        self.frm.setStyleSheet("QWidget { background-color: %s }" % col.name())
        self.frm.setGeometry(150, 20, 100, 100)

        self.setGeometry(300, 300, 450, 350)
        self.setWindowTitle('Dialogo Colores')
        self.show()

    def showDialog(self):
        col = QColorDialog.getColor()
        if col.isValid():
            self.frm.setStyleSheet('QWidget { background-color: %s }' % col.name())


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()