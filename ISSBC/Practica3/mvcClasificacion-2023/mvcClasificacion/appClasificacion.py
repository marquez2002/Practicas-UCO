#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Sat Jan 18 11:29:53 2014

@author: acalvo
"""

import sys
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QWidget, QCheckBox, QApplication
import ckVtsClasificacion as vts
import mcFrutos as mc #Cambiar al cambiar el MC
#import mcIris as mc #Cambiar al cambiar el MC

lct1=[[vts.ctrl.ma.mc.Atributo('Ancho sepalo','int','mm'),25],
       [vts.ctrl.ma.mc.Atributo('Largo sepalo','int','mm'),110],
       [vts.ctrl.ma.mc.Atributo('Ancho petalo','int','mm'),30],
       [vts.ctrl.ma.mc.Atributo('Largo petalo','int','mm'),95]]
llct1=vts.ctrl.ma.mc.creaCaracteristicas(lct1)
ob1=vts.ctrl.ma.mc.Objeto('ob1',llct1)
#ob1.describeObjeto()


lct2=[[vts.ctrl.ma.mc.Atributo('diametro','int','cm'),180],
     [vts.ctrl.ma.mc.Atributo('peso','int','gr'),8000],
     [vts.ctrl.ma.mc.Atributo('color','str',None),'verde']]


llct2=vts.ctrl.ma.mc.creaCaracteristicas(lct2)
ob2=vts.ctrl.ma.mc.Objeto('ob2',llct2)

ob=ob1
ob.describeObjeto()

app =  QtWidgets.QApplication(sys.argv)
form = vts.ClasificacionDlg(ob)
sys.exit(app.exec_())



