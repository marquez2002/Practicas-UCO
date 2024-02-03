from PyQt5.QtWidgets import QTableWidgetItem
FILE_NAME = "tabla.txt"

def openFile(self):
    num = 0
    fila = 1
    valor = 0
    with open(FILE_NAME, 'r') as f:
        lines = f.readlines()
        self.tableWidget.setRowCount(len(lines))
        for i, line in enumerate(lines):
            if num == 2:
                line = line.strip()
                item = QTableWidgetItem(line)
                self.tableWidget.setItem(fila, num, item)
                fila += 1
                num = 0
                valor = 1
            if num == 1:
                line = line.strip()
                item = QTableWidgetItem(line)
                self.tableWidget.setItem(fila, num, item)
                num = 2
            if num == 0:
                if valor == 0:
                    line = line.strip()
                    item = QTableWidgetItem(line)
                    self.tableWidget.setItem(fila, num, item)
                    num = 1
                if valor == 1:
                    valor = 0
                
# Guarda el archivo
def save(self):
    linea = 1
    with open(FILE_NAME, 'w') as f:
           for i in range(self.tableWidget.rowCount()):
               line = ''
               for j in range(self.tableWidget.columnCount()):
                   item = self.tableWidget.item(linea, j)
                   if item is not None:
                       line += item.text() + '\n'
               linea += 1
               f.write(line)





