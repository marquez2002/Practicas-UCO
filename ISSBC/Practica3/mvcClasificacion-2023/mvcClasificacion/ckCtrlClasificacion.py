#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
"""
Created on Sun Jan 19 10:28:45 2014

@author: acalvo
"""
from PyQt5.QtWidgets import QWidget
import ckModApClasificacion as ma

def eventGenerar(clasificacionDlg):
    '''
    '''
    print ('ctrl', 'event generar')
    print (ma.mc.clases())
    
        
def eventClasificar(clasificacionDlg):
    pass
    print ('Objeto:', clasificacionDlg.objeto)
    print ('================================\n')
    mp=ma.MetodoPoda(clasificacionDlg.objeto) #Se crea la instancia del método de la poda
    r,exp=mp.execute()#se ejecuta el método
    clasificacionDlg.plainTextEditExplicacion.clear()#Se borra la explicación
    clasificacionDlg.plainTextEditExplicacion.appendPlainText(exp)#Se presenta la nueva explicación
    #clasificacionDlg.plainTextEditExplicacion.moveCursor(QWidget.QTextCursor.Start)
    cs=[]
    for cc in r:
        print ('         ->',cc.nombre)
        cs.append(cc.nombre)
    clasificacionDlg.listWidgetClasesSeleccionadas.clear()
    clasificacionDlg.listWidgetClasesSeleccionadas.addItems(cs) #Se añaden las clases resultado de la clasificación 
    # al control listbox para que lo presente.
    
    print ('Las clases candidatas: ',r)
    return
        


