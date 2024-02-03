#!/usr/bin/python

"""
This example is a try to know more about 
toolbars, menus and status.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QTextEdit, QAction, QApplication, qApp, QMenu
from PyQt5.QtGui import QIcon


class Example(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()


    def initUI(self):

        textEdit = QTextEdit()
        self.setCentralWidget(textEdit)

        exitAct = QAction(QIcon('salir.png'), 'Exit', self)
        exitAct.setShortcut('Ctrl+Q')
        exitAct.triggered.connect(qApp.quit)
        
        impAct = QAction(QIcon('importar.png'), 'Import', self)
        impAct.setShortcut('Ctrl+I')


        self.statusBar()

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&Menu') # Nombre del menu
        fileMenu.addAction(exitAct) # Añadir acción de salida del menu
        fileMenu.addAction(impAct) # Añadir submenu al menu creado
        
        toolbar = self.addToolBar('Exit')
        toolbar.addAction(exitAct)
        toolbar.addAction(impAct)

        self.setGeometry(300, 300, 350, 250)
        self.setWindowTitle('Main window')
        self.show()


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
