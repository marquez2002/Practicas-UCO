#!/usr/bin/python

"""
This example is a try to know more about 
the layout of calculator.

Author: i02matog
"""


import sys
from PyQt5.QtWidgets import (QWidget, QGridLayout,
                             QPushButton, QApplication)


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        grid = QGridLayout()
        self.setLayout(grid)

        names = ['Cls', 'Bck', '', 'Close', # Diseño del cuadrado
                 '7', '8', '9', '/',
                 '4', '5', '6', '*',
                 '1', '2', '3', '-',
                 '0', '.', '=', '+']

        positions = [(i, j) for i in range(5) for j in range(4)] # Cantidad de posiciones

        for position, name in zip(positions, names):
            if name == '': 
                continue
            button = QPushButton(name) 
            grid.addWidget(button, *position)

        self.move(300, 150)
        self.setWindowTitle('Calculator')
        self.show()


def main():
    app = QApplication(sys.argcalculatorv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()