#!/usr/bin/python

"""
This example is a try to know more about 
signal.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QPushButton, QApplication


class Example(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        btn1 = QPushButton("Boton 1", self) # Creacion boton 1
        btn1.move(30, 50)

        btn2 = QPushButton("Boton 2", self) # Creacion boton 1
        btn2.move(150, 50)

        btn1.clicked.connect(self.buttonClicked) # Conectar el boton 1 cuando se haga click
        btn2.clicked.connect(self.buttonClicked) # Conectar el boton 2 cuando se haga click

        self.statusBar()

        self.setGeometry(300, 300, 450, 350)
        self.setWindowTitle('Envío de Señales')
        self.show()

    def buttonClicked(self):
        sender = self.sender()
        self.statusBar().showMessage(sender.text() + ' está siendo presionado') # Mostra mensaje cuando se presiona un boton


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()