#!/usr/bin/python

"""
This example is a try to know more about 
windows and buttons.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QWidget, QMessageBox, QApplication


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
    
        self.setGeometry(300, 300, 250, 150) # Geometria de la ventana
        self.setWindowTitle('Ejemplo Botones') # Titulo de la ventana
        self.show() # Mostrar ventana
        
    # Este evento solo se activará si se clica en la X
    def closeEvent(self, event):
        # Dentro de la nueva ventana se podrá colocar nombre, descripción y cuadros
        reply = QMessageBox.question(self, 'Aviso',
                                     "¿Estás seguro de salir?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)

        # Bucle if/else
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()