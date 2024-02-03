#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 18 11:29:53 2014

@author: acalvo
"""


from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QWidget, QCheckBox, QApplication



import sys
import ckCtrlDiagnostico



class DiagnosticDlg(QWidget):
    '''
    Cuadro de dialógo para la tarea de diangóstico
    '''
    def __init__(self, name, observables=None, parent=None):
        '''
        Inicio del cuadro de diálogo   
        @param name: Nombre del cuadro
        @type name: string
        @param observables: Posibles observables
        @type obsevables: tupla de dos valores 
        '''
        super(DiagnosticDlg, self).__init__(parent)

        self.name = name #Coloca el nombre al cuadro de diálogo
        #Label
        labelListA=QtWidgets.QLabel("Selecione los Fallos Presentados",self)
        labelListB=QtWidgets.QLabel("",self)#quitar
        observables_list = [(f.nombre , f.valor)  for f in observables] #Se cosntruye una lista de tuplas con nombre y valor de
                                                                        #las observables.
        header = ['NOMBRE', 'VALOR']
        #posiblesFallos = Fallos(self,   observables_list, header)
        self.tableWidgetPosiblesFallos = QtWidgets.QTableWidget(len(observables_list),2) #Crea la tabla de elementos observables de dps columnas
        self.tableWidgetPosiblesFallos.setColumnWidth(0, 400) #Asignan ancho a las columnas
        self.tableWidgetPosiblesFallos.setColumnWidth(1, 400) #Asignan ancho a las columnas
        self.tableWidgetPosiblesFallos.setHorizontalHeaderLabels(header) #Asigna etiquetas a las columnas
        
        #print observables
        for i in range(len(observables)): 
            #print i, observables[i].nombre,observables[i].tipo,observables[i].valoresPermitidos
            item1 = QtWidgets.QTableWidgetItem(observables[i].nombre) #Crea un item y le asigna el nombre de la observable
            item1.setCheckState(QtCore.Qt.Checked) # Establece propiedades a las celdas de la primera columna de la tabla
            item1.setFlags(QtCore.Qt.ItemIsUserCheckable|QtCore.Qt.ItemIsEnabled) #Establece propiedades a las celdas de la primera columna

            if observables[i].tipo=='multiple':#Si el tipo de observable es múltiple creamos un combox
                combobox = QtWidgets.QComboBox()
                for j in observables[i].valoresPermitidos:#añadimmos al combox los valeores permitidos
                    combobox.addItem(j) 
                self.tableWidgetPosiblesFallos.setCellWidget(i, 1, combobox)#Establecemos en la celda i el combox
            elif observables[i].tipo=='boleano':#Si es boleano creamos otro combox con dos posibles valores
                combobox = QtWidgets.QComboBox()
                combobox.addItem('True') 
                combobox.addItem('False') 
                self.tableWidgetPosiblesFallos.setCellWidget(i, 1, combobox)

            self.tableWidgetPosiblesFallos.setItem(i, 0, item1)#Establecemos el item en la columna 0
        
     
        #ListWidget para las hipótesis  
        labelHipotesisL=QtWidgets.QLabel("Posibles Hipotesis",self)#Creamos un listwidget para las posibles hipótesis
        labelHipotesisR=QtWidgets.QLabel("",self)
        self.listWidgetHipotesis = QtWidgets.QListWidget()#Lista de hipótesis
        
        #ListWidget para el diagnóstico
        labelDiagnosticoL=QtWidgets.QLabel("Diagnóstico",self)
        labelDiagnosticoR=QtWidgets.QLabel("",self)
        self.listWidgetDiagnosticos = QtWidgets.QListWidget()#Lista de diagnósticos
        
        #Texto para la explicación
        labelExplicacionL=QtWidgets.QLabel("Explicacion",self)
        labelExplicacionR=QtWidgets.QLabel("     ",self)
        self.PlainTextEditExplicacion = QtWidgets.QPlainTextEdit()#Cuadro de texto    de la explicación 
          
        #Botones
        self.coberturaCausalButton=QtWidgets.QPushButton('Cobertura Causal')#Para invocar el método de cobretura causal
        self.diagnosticaButton=QtWidgets.QPushButton('Diagnostica') #Para ejecutar el diagnóstico
        self.exitButton=QtWidgets.QPushButton('Exit') #Para salir del programa
        
        self.buttonsLayout = QtWidgets.QHBoxLayout() #Gestor de diseño horizontal
        #http://stackoverflow.com/questions/20452754/how-exactly-does-addstretch-work-in-qboxlayout
        self.buttonsLayout.addStretch() #Añade un espacio estiranle
        self.buttonsLayout.addWidget(self.coberturaCausalButton)
        self.buttonsLayout.addWidget(self.diagnosticaButton)
        self.buttonsLayout.addWidget(self.exitButton)
        self.buttonsLayout.addStretch()
        
        #Rejilla de distribución de los controles
        #========================================
        #Ver http://srinikom.github.io/pyside-docs/PySide/QtWidgets/QGridLayout.html
        grid = QtWidgets.QGridLayout()
        grid.setSpacing(5)
        grid.addWidget(labelListA, 0, 0)
        grid.addWidget(self.tableWidgetPosiblesFallos, 1, 0,1,2)
        grid.addWidget(labelListB, 0, 1)
        
        grid.addWidget(labelHipotesisL, 2, 0)
        grid.addWidget(labelHipotesisR, 2, 1)
        grid.addWidget(self.listWidgetHipotesis, 3, 0,1,2)
        
        grid.addWidget(labelDiagnosticoL, 4, 0)
        grid.addWidget(labelDiagnosticoR, 4, 1)
        grid.addWidget(self.listWidgetDiagnosticos, 5, 0,1,2)
        grid.addWidget(labelExplicacionL, 6, 0)
        grid.addWidget(labelExplicacionR, 6, 1)
        grid.addWidget(self.PlainTextEditExplicacion, 7, 0,1,2)
        
        #Diseño principal
        mainLayout = QtWidgets.QVBoxLayout() #Se crea el diseño principal en forma vertical
        mainLayout.addLayout(grid) #Le añadimos la rejilla de los controles
        mainLayout.addLayout(self.buttonsLayout) #Añadimos la disposición de controles horizontal
        self.setLayout(mainLayout) #Asignar a la ventana la distribución de los controles
        
    
        self.setGeometry(300, 300, 900, 1200)
        self.setWindowTitle("TAREA DE DIAGNOSTICO".format(self.name))
        self.show()
 
        self.center()
        
        #Conexiones de los botones y eventos en las listas:
        #==================================================
        #self.tableWidgetPosiblesFallos.itemDoubleClicked.connect(self.moveRight)
        #self.listWidgetFallos.itemDoubleClicked.connect(self.moveLeft)
        self.coberturaCausalButton.clicked.connect(self.coberturaCausal)
        self.diagnosticaButton.clicked.connect(self.diagnostica)
        self.exitButton.clicked.connect(self.close)


    def dl(self,item):
        print (item.text())

    def moveLeft(self):
        '''NO USADO'''
        #Pasa el elemento seleccionado a la izquierda
        #Falta->
        return
        row = self.listWidgetFallos.currentRow()
        item = self.listWidgetFallos.item(row)
        if item is None:
            return
        print (item.text())
        self.listWidgetPosiblesFallos.insertItem(0,item.text() )
        self.listWidgetPosiblesFallos.sortItems()
        item = self.listWidgetFallos.takeItem(row)
        del item
        pass

    def moveRight(self):
        '''NO USADO'''
        #Pasa el elemento seleccionado a la derecha
        return
        print (self.tableWidgetPosiblesFallos.currentRow())
        row = self.tableWidgetPosiblesFallos.currentRow()
        column = self.tableWidgetPosiblesFallos.currentColumn()
        print (row)
        item = self.tableWidgetPosiblesFallos.item(row,0)
        if item is None:
            return
        print (item.text())
        #Comprobar que no se repitan síntomas->Falta
        
        #insert una fila
        self.tableWidgetFallos.insertRow(0)
        newItem1=QtWidgets.QTableWidgetItem(item.text())
        self.tableWidgetFallos.setItem(0, 0, newItem1)
        newItem1.setFlags(QtCore.Qt.ItemIsSelectable|QtCore.Qt.ItemIsEnabled)
        newItem2=QtWidgets.QTableWidgetItem('Valor')
        self.tableWidgetFallos.setItem(0, 1, newItem2)
        
        pass
    
    def diagnostica(self):
        ckCtrlDiagnostico.eventDiagnostica(self) #Se invoca al gestor del controlador
        
        
    def coberturaCausal(self):
        #Recolecta datos de las vistas y se lo pasamos al controlador
        # Al pasar self pasamos toda la información de la ventana
        ckCtrlDiagnostico.eventCoberturaCausal(self)
    
    def center(self):        
        qr = self.frameGeometry()
        cp = QtWidgets.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topRight())


print ("Prueba")
        
if __name__ == "__main__":
    
    if True:
        #Podemos probar el módulo de vistas de forma autónoma
        #Obtenemos los observables desde la base de conocimiento
        print ("Empezamos")
        observables =  ckCtrlDiagnostico.ckModApDiagnostico.cd.observables()
        #creamos la aplicación
        app = QtWidgets.QApplication(sys.argv)
        form = DiagnosticDlg("Fallos", observables)
        sys.exit(app.exec_()) #Lanzamos la aplicación
    if False:
        observables =  ckCtrlDiagnostico.ckModApDiagnostico.cd.observables()
        print (observables)
        l = [(f.nombre , f.valor)  for f in observables]
        print (l)
        header = ['Nombre', 'Valor']
         
    

 