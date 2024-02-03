#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 18 11:29:53 2014

@author: acalvo
"""

import sys
from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QWidget,  QApplication

import ckVtsDiagnosticoD
import ckCtrlDiagnostico

observables =  ckCtrlDiagnostico.ckModApDiagnostico.cd.observables()
app = QtWidgets.QApplication(sys.argv) #Se crea una instancia de aplicación
form = ckVtsDiagnosticoD.DiagnosticDlg("Fallos", observables) #Se crea una instancia de de una ventana
sys.exit(app.exec_())


 

 