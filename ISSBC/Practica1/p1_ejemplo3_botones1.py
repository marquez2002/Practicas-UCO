#!/usr/bin/python

"""
This example is a try to know more about 
windows and buttons.

Author: i02matog
"""

import sys 
from PyQt5.QtWidgets import (QWidget, QToolTip, QPushButton, QApplication)
from PyQt5.QtGui import QFont


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        QToolTip.setFont(QFont('Calibri', 12)) # Modifica el tipo de letra y tamaño
        
        self.setToolTip('This is a <b>QWidget</b> widget') # Crea información sobre la herramienta

        btn = QPushButton('Cerrar', self) # Creación del boton
        btn.clicked.connect(QApplication.instance().quit)
        btn.setToolTip('This is a <b>QPushButton</b> widget') # Crea información sobre la herramienta
        btn.resize(btn.sizeHint()) # Tamaño idoneo predefinido
        btn.move(50, 50) # Determinar el tamaño de la ventana

        self.setGeometry(300, 300, 300, 200) # Geometria de la ventana
        self.setWindowTitle('Ejemplo Botones') # Titulo de la ventana
        self.show() # Mostrar ventana
        


def main():

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()



    