#!/usr/bin/python

"""
This example is a try to know more about 
toolbars, menus and status.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QTextEdit, QAction, QApplication, qApp, QMenu, QFileDialog
from PyQt5.QtGui import QIcon


class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):

        textEdit = QTextEdit()
        self.setCentralWidget(textEdit)

        exitAct = QAction(QIcon('salir.png'), 'Salir', self)
        exitAct.setShortcut('Ctrl+Q')
        exitAct.triggered.connect(qApp.quit)
        
        impAct = QAction(QIcon('importar.png'), 'Importar', self)
        impAct.setShortcut('Ctrl+I')


        self.statusBar()

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&Menu') # Nombre del menu
        fileMenu.addAction(exitAct) # Añadir acción de salida del menu
        fileMenu.addAction(impAct) # Añadir submenu al menu creado
        
        toolbar = self.addToolBar('Salir')
        toolbar.addAction(exitAct)
        toolbar.addAction(impAct)

        self.setGeometry(300, 300, 350, 250)
        self.setWindowTitle('App de Notas')        

        self.text_edit = QTextEdit()
        self.setCentralWidget(self.text_edit)

        self.toolbar = self.addToolBar("Archivo")

        self.action_new = QAction("Nuevo", self)
        self.action_new.triggered.connect(self.new_file)
        self.toolbar.addAction(self.action_new)

        self.action_open = QAction("Abrir", self)
        self.action_open.triggered.connect(self.open_file)
        self.toolbar.addAction(self.action_open)

        self.action_save = QAction("Guardar", self)
        self.action_save.triggered.connect(self.save_file)
        self.toolbar.addAction(self.action_save)

        self.action_exit = QAction("Salir", self)
        self.action_exit.triggered.connect(self.close)
        self.toolbar.addAction(self.action_exit)

        self.show()

    def new_file(self):
        self.text_edit.clear()

    def open_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Abrir archivo", "", "Archivos de texto (*.txt)")
        if file_path:
            with open(file_path, "r") as f:
                self.text_edit.setText(f.read())

    def save_file(self):
        file_path, _ = QFileDialog.getSaveFileName(self, "Guardar archivo", "", "Archivos de texto (*.txt)")
        if file_path:
            with open(file_path, "w") as f:
                f.write(self.text_edit.toPlainText())


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
