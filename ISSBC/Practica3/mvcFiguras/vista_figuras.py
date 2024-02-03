#!/usr/bin/python
#!/usr/bin/python

import sys
import controlador_figuras as controller
from PyQt5.QtWidgets import (
    QWidget, QApplication, QGridLayout, QLabel, QVBoxLayout, QHBoxLayout, 
    QRadioButton, QPushButton, QLineEdit, QListWidget,
)


class Figuras(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):


        grid = QGridLayout()
        grid.setSpacing(10)

        label1Item = QLabel("Introduzca los datos:", self)
        labelDatoAltura = QLabel("Altura: ",self)
        labelDatoLado = QLabel("Lado: ",self)
        labelDatoRadio = QLabel("Radio: ",self)
        self.label = QLabel('', self)

        self.DatoAltura = QLineEdit()
        self.DatoLado = QLineEdit()
        self.DatoRadio = QLineEdit()
        self.listWidget = QListWidget()

        # Botones
        self.botonArea = QPushButton('Calcular Área')
        self.botonPerimetro = QPushButton('Calcular Perímetro')
        self.botonAdd = QPushButton('Añadir datos')
        self.figurasmayorarea = QPushButton('Figuras Mayor Area')

        cuadrado = QRadioButton("Cuadrado", self)
        rectangulo = QRadioButton("Rectangulo", self)
        triangulo = QRadioButton("Triangulo", self)
        circulo = QRadioButton("Circulo", self)

        self.buttomsLayout = QHBoxLayout()
        self.buttomsLayout.addStretch()

        self.buttomsLayout.addWidget(self.botonAdd)
        self.buttomsLayout.addWidget(self.figurasmayorarea)
        self.buttomsLayout.addWidget(self.botonArea)
        self.buttomsLayout.addWidget(self.botonPerimetro)
        self.buttomsLayout.addWidget(cuadrado)
        self.buttomsLayout.addWidget(rectangulo)
        self.buttomsLayout.addWidget(triangulo)
        self.buttomsLayout.addWidget(circulo)
        self.buttomsLayout.addStretch()

        grid = QGridLayout()
        grid.setSpacing(5)
        grid.addWidget(label1Item, 0, 0)
        grid.addWidget(labelDatoAltura, 1, 0)
        grid.addWidget(self.DatoAltura, 1, 1)
        grid.addWidget(labelDatoLado, 2, 0)
        grid.addWidget(self.DatoLado, 2, 1)
        grid.addWidget(labelDatoRadio, 3, 0)
        grid.addWidget(self.DatoRadio, 3, 1)
        grid.addWidget(self.listWidget, 4, 1, 3, 1)
        mainLayout = QVBoxLayout()
        mainLayout.addLayout(grid)
        mainLayout.addLayout(self.buttomsLayout)

        self.setLayout(mainLayout)
        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle('Calculador de Figuras')
        self.show()

        cuadrado.toggled.connect(self.actualizarRadiobutton)
        rectangulo.toggled.connect(self.actualizarRadiobutton)
        triangulo.toggled.connect(self.actualizarRadiobutton)
        circulo.toggled.connect(self.actualizarRadiobutton)
        self.botonAdd.clicked.connect(self.addDatos)

        self.figuraseleccionada = ""

    def actualizarRadiobutton(self, value):
        seleccion = self.sender()
        if seleccion.isChecked() == True:  
            self.figuraseleccionada = seleccion


    def obtenerDatos(self):
        Altura = self.DatoAltura.text()
        Lado = self.DatoLado.text()
        Radio = self.DatoRadio.text()
        return Altura, Lado


    def addDatos(self):
        a, b= self.obtenerDatos()
        controller.addDatos(a, b, self)


def main():
    app = QApplication(sys.argv)
    ex = Figuras()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
