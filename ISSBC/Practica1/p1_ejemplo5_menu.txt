#!/usr/bin/python

"""
This example is a try to know more about 
menus.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QAction, qApp, QApplication, QMenu
from PyQt5.QtGui import QIcon

class Example(QMainWindow):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        exitAct = QAction(QIcon('salir.png'), '&Salir', self) # Personalizar tanto el icono, como el nombre
        exitAct.setShortcut('Ctrl+Q') # Comando indicado para realizar una determinada acción
        exitAct.setStatusTip('Salir de la aplicación') # Información acerca del elemento seleccionado
        exitAct.triggered.connect(qApp.quit) # Emite una señal para la salida del programa
        
        impMenu = QMenu('Importar', self) # Comando para la creación del submenu
        impAct = QAction('Importar email', self) # Acciones dentro del submenu
        impMenu.addAction(impAct) #Añadir la accion de importar email
        
        
        viewStatAct = QAction('Ver barra', self, checkable=True) # Crear accion de true/false
        exitAct.setShortcut('Ctrl+Q') # Comando indicado para realizar una determinada acción
        viewStatAct.setStatusTip('Ver barra') # 
        viewStatAct.setChecked(True) # Comienza en true
        viewStatAct.triggered.connect(self.toggleMenu) # Accede a toggleMenu para ver las diferentes acciones
        
        self.statusBar()

        menubar = self.menuBar() # Creación del menu
        fileMenu = menubar.addMenu('&Menu') # Nombre del menu
        fileMenu.addAction(exitAct) # Añadir acción de salida del menu
        fileMenu.addMenu(impMenu) # Añadir submenu al menu creado
        fileMenu.addAction(viewStatAct) # Añadir acción de checkable

        self.setGeometry(300, 300, 300, 300)
        self.setWindowTitle('Menu')
        self.show()

    def contextMenuEvent(self, event):
        cmenu = QMenu(self)

        newAct = cmenu.addAction("Nuevo")
        openAct = cmenu.addAction("Abrir")
        quitAct = cmenu.addAction("Cerrar")
        action = cmenu.exec_(self.mapToGlobal(event.pos()))

        if action == quitAct:
            qApp.quit()

    def toggleMenu(self, state):
        if state:
            self.statusbar.show()
        else:
            self.statusbar.hide()




def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()