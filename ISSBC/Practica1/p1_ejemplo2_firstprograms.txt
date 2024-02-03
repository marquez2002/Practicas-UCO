#!/usr/bin/python

"""
ZetCode PyQt5 tutorial

In this example, we create a simplewindow in PyQt5.

Author: Jan Bodnar
Website: zetcode.com
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget

def main():

    app = QApplication(sys.argv) 

    w = QWidget() # Creacion de la ventana
    w.resize(250, 150) # Tamaño de la ventana
    w.move(300, 300) # Posicion de la ventana
    w.setWindowTitle('Simple') # Titulo de la ventana
    w.show() # Mostrar 

    sys.exit(app.exec_()) #Salida


if __name__ == '__main__':
    main()