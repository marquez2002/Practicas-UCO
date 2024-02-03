import sys
from PyQt5 import QtWidgets
import view as vts

app = QtWidgets.QApplication(sys.argv)  # Crea una aplicacion
form = vts.calificaciones()  
sys.exit(app.exec_())  # Se inicia la aplicacion