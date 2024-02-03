import sys
from PyQt5 import QtWidgets
import vista_figuras as view

app = QtWidgets.QApplication(sys.argv)  
form = view.Figuras()  
sys.exit(app.exec_())  # Iniciamos la aplicacion