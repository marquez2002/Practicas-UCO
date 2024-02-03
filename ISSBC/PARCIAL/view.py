import sys
import controller as controlador
from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QLineEdit, QVBoxLayout, QHBoxLayout, QPushButton, QGridLayout, QTableWidget, QTableWidgetItem



class calificaciones(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.title = QLabel('Carpeta')
        self.titleEdit = QLineEdit()
        self.openFileButton = QPushButton("Abrir")
        self.files = QLabel('Calificaciones')

        # Creamos dos tablas, una para clasificaciones y otra para clasificaciones por encima del 5
        self.tableWidget = QTableWidget()
        self.tableWidget2 = QTableWidget()

        # Creacion de una tabla con 30 filas
        self.tableWidget.setRowCount(30)
        self.tableWidget2.setRowCount(30)
        
        # Creacion de 3 columnas, indicando el nombre de cada una de ellas.
        self.tableWidget.setColumnCount(3)
        self.tableWidget2.setColumnCount(3)
        self.tableWidget.setItem(0, 0, QTableWidgetItem(" Nombre"))
        self.tableWidget.setItem(0, 1, QTableWidgetItem("Apellidos"))
        self.tableWidget.setItem(0, 2, QTableWidgetItem("Calificación"))
        self.tableWidget2.setItem(0, 0, QTableWidgetItem(" Nombre"))
        self.tableWidget2.setItem(0, 1, QTableWidgetItem("Apellidos"))
        self.tableWidget2.setItem(0, 2, QTableWidgetItem("Calificación"))
        
        # Obtenemos la cabecera de la tabla y la hacemos fija
        header = self.tableWidget.horizontalHeader()
        header.setSectionsMovable(False)
        header = self.tableWidget2.horizontalHeader()
        header.setSectionsMovable(False)

        # Introducimos los botones indicados
        self.orderButton = QPushButton("Ordenar")        
        self.passButton = QPushButton("Seleccionar aprobados")
        self.saveButton = QPushButton("Guardar")
        self.openButton = QPushButton("Abrir")
        self.addButton = QPushButton("Añadir")
        self.deleteButton = QPushButton("Borrar")

        mainVbox = QVBoxLayout()
        mainVbox.setSpacing(25)

        folderHbox = QHBoxLayout()
        folderHbox.addWidget(self.title)
        folderHbox.addWidget(self.titleEdit)
        folderHbox.addWidget(self.openFileButton)

        mainVbox.addLayout(folderHbox)
        grid = QGridLayout()
        grid.setSpacing(10)

        # Colocamos cada una de las tablas y botones.
        grid.addWidget(self.files, 0, 0)
        grid.addWidget(self.tableWidget, 1, 0, 1, 5)
        grid.addWidget(self.tableWidget2, 1, 3, 1, 5)
        
        grid.addWidget(self.orderButton, 2, 0)
        grid.addWidget(self.passButton, 2, 1)
        grid.addWidget(self.saveButton, 2, 2)
        grid.addWidget(self.openButton, 2, 3)
        grid.addWidget(self.addButton, 3, 0)
        grid.addWidget(self.deleteButton, 3, 1)
        
        mainVbox.addLayout(grid)
        self.setLayout(mainVbox)

        # Geometria y titulo de la ventana
        self.setGeometry(500, 500, 740, 500)
        self.setWindowTitle('Calificaciones')
        self.show()

        # Conectamos los botones con ciertas señales
        self.openFileButton.clicked.connect(self.openFile)
        self.orderButton.clicked.connect(self.order)
        self.passButton.clicked.connect(self.passA)
        self.saveButton.clicked.connect(self.save)
        self.openButton.clicked.connect(self.openFile)
        self.addButton.clicked.connect(self.add)
        self.deleteButton.clicked.connect(self.delete)
        
        
    # Ordenacion de los elementos en funcion del nombre
    def order(self):
        self.tableWidget.sortItems(0)
        self.tableWidget2.sortItems(0)
        
    # Pasar aquellos alumnos que se encuentren aprobados (nota >=5)
    def passA(self):
        valor = 1     
        for row in range(1, self.tableWidget.rowCount()):
            nombre = self.tableWidget.item(row, 0)
            apellido = self.tableWidget.item(row, 1)
            calificacion_txt = self.tableWidget.item(row, 2)
            calificacion = int(self.tableWidget.item(row, 2).text())
            if calificacion >= 5: 
                self.tableWidget2.setItem(valor, 0, QTableWidgetItem(nombre))
                self.tableWidget2.setItem(valor, 1, QTableWidgetItem(apellido))
                self.tableWidget2.setItem(valor, 2, QTableWidgetItem(calificacion_txt))
                valor += 1
                
    # Añadir una fila en la primera tabla
    def add(self):
        current_row_count = self.tableWidget.rowCount()
        self.tableWidget.insertRow(current_row_count)

    # Guardar fichero
    def save(self):
        controlador.eventSave(self)
    
    # Abrir fichero
    def openFile(self):
        controlador.eventOpenFile(self)
    
    # Borrar una fila selecionada
    def delete(self):
        selecionada = self.tableWidget.currentRow()
        if selecionada >= 0:
            self.tableWidget.removeRow(selecionada)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = calificaciones()
    sys.exit(app.exec_())
