#!/usr/bin/python

"""
This example is a try to know more about 
edit docs.

Author: i02matog
"""

import sys
from PyQt5.QtWidgets import QApplication
import view as view

app = QApplication(sys.argv)  # Crea la app
form = view.EditorTextosDlg()  # Crea un formulario
sys.exit(app.exec_())  # Se inicia la app y se esperan eventos