#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun Jan 19 10:28:45 2014

@author: acalvo
"""
#from PyQt4 import QtGui
from PyQt5 import QtCore
from PyQt5.QtWidgets import QWidget
import ckModApDiagnostico

def eventCoberturaCausal(cdDiagnostico,tr=False):
    '''
    Inferenvia de cobretura causal.
    En función de los datos observados en la lista de fallos observados
    se obtiene de ka inferencia de cobertura causal el conjunto diferencial
    o lista de posibles alteraciones del sistema que expliquen esos fallos.
    Una vez obtenida la lista se muestra dicha lista en la ventana de hipotesis
    '''
    
    cdDiagnostico.PlainTextEditExplicacion.clear() #Borra información
    cdDiagnostico.listWidgetHipotesis.clear()#Borramos la información del listWidgetHipótesis
    cdDiagnostico.PlainTextEditExplicacion.clear()
    
    fallos=[]#Vamos a captar los fallos del cuadro de diálogo
    if tr:
        print ('entra')
    for i in range(cdDiagnostico.tableWidgetPosiblesFallos.rowCount()):
        item1=cdDiagnostico.tableWidgetPosiblesFallos.item(i,0)
        print (item1.checkState())
        #print QtCore.Qt.CheckState.Checked
        
        #if item1.checkState()==QtCore.Qt.CheckState.Checked:
        if item1.checkState()==QtCore.Qt.Checked:
            #print item1.checkState()
            item2=cdDiagnostico.tableWidgetPosiblesFallos.cellWidget(i, 1)
            print (item2, item2.currentText())
            fallos.append( (item1.text(),item2.currentText()) )
    if tr:
        print (fallos)
    cc=ckModApDiagnostico.CoberturaCausal(fallos)#Creamos una  inferencia de cobertura causal del diagnóstico
    cc.execute() #Ejecutamos el método de la inferencia
    lHipotesis=[]
    for h in cc.listaHipotesis:
        lHipotesis.append(h.nombre)#Obtenemos la lista de hipótesis
     
    cdDiagnostico.listWidgetHipotesis.clear()#Borramos la información del listWidget
    
    
    #lHipotesis=['a','b']
    print (lHipotesis)
    cdDiagnostico.listWidgetHipotesis.addItems(lHipotesis)#añadimos la nueva información al listWidgwet
    
            
def eventDiagnostica(cdDiagnostico,tr=False):
    '''
    Controla el evento de diagnóstico.
    
    
    '''
    cdDiagnostico.PlainTextEditExplicacion.clear()
    pass
    eventCoberturaCausal(cdDiagnostico,tr=False)
    fallos=[]
        #print cdDiagnostico.listWidgetFallos.count()
    if tr:
        print ('entra')
    for i in range(cdDiagnostico.tableWidgetPosiblesFallos.rowCount()):
        item1=cdDiagnostico.tableWidgetPosiblesFallos.item(i,0)
        #if item1.checkState()==QtCore.Qt.CheckState.Checked:
        if item1.checkState()==QtCore.Qt.Checked:
            #print item1.checkState()
            item2=cdDiagnostico.tableWidgetPosiblesFallos.cellWidget(i, 1)
            #print item2, item2.currentText()
            fallos.append( (item1.text(),item2.currentText()) )#Creamos una tupla del fallo y sus posibles
                                                               #valores
    if tr:        
        print ('Presentando los fallos',fallos)
        print ('======================')
    
    #Comprueba que los fallos captados son compatibles con la base de conocimiento
    observables=ckModApDiagnostico.identificaSignosSintomas(fallos)
    if tr:
        print ('Obteniendo Observables:', observables)
    if not observables==None:#Continuo porque todo es correcto
        pass
        mcc=ckModApDiagnostico.MetodoCoberturaCausal(observables)#Creamos una instancia del método cc
        mcc.execute()
        if tr:
            pass
        print ('Justificación')
        print ('=============')
        print (mcc.explicacion)
        print 
        print ('Diagnóstico: ' )
        print ( '============ ')
        for d in mcc.diferencial:
            print (d.nombre)
        print ( 'fin')
        cdDiagnostico.PlainTextEditExplicacion.clear()
        cdDiagnostico.PlainTextEditExplicacion.appendPlainText(mcc.explicacion)
        cdDiagnostico.PlainTextEditExplicacion.moveCursor(QWidget.QTextCursor.Start)
        
        
        #tc=cdDiagnostico.PlainTextEditExplicacion.textCursor()
        #tc.movePosition(QtGui.QTextCursor.Start)
        #print tc.position()
        cdDiagnostico.listWidgetDiagnosticos.clear()
        lDiag=[]
        for d in mcc.diferencial:
            lDiag.append(d.nombre)
            cdDiagnostico.listWidgetDiagnosticos.addItems(lDiag)

    return
    #mcc=ckModApDiagnostico.MetodoCoberturaCausal(fallos)
    #mcc.execute()(
    #print (mcc.diagnostico)
    #print (mcc.explicacion)
    

def observables():
    
   pass
   return 
       
    

if __name__=='__main__':  
    
    print ("Prueba")
    pass

            
        
        