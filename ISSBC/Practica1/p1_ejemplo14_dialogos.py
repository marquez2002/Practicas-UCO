#!/usr/bin/python

"""
This example is a try to know more about 
dialogs.

Author: i02matog
"""

from PyQt5.QtWidgets import (QWidget, QPushButton, QLineEdit, QInputDialog, QApplication)
import sys


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.btn = QPushButton('Diálogo', self) #Boton
        self.btn.move(20, 20)
        self.btn.clicked.connect(self.showDialog) # El boton al pulsarse muestra el dialogo

        self.le = QLineEdit(self)
        self.le.move(130, 22)

        self.setGeometry(300, 300, 450, 350)
        self.setWindowTitle('Introduccion a los dialogos')
        self.show()

    def showDialog(self):
        text, ok = QInputDialog.getText(self, 'Introducir Dialogo',
                                        'Inserta tu nombre:')

        if ok:
            self.le.setText(str(text)) # Si es texto, se muestra en la pantalla


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()