#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Thu Feb 16 17:30:46 2023

@author: i02matog
"""

from PyQt5.QtCore import QDate, QTime, QDateTime, Qt

#HORA Y FECHA
# Asocia a la variable now la fecha actual
now = QDate.currentDate() # Devuelve fecha actual

# Muestra la fecha actual del sistema en diferentes formatos
print('Fecha: ', now.toString(Qt.ISODate))  # YY-MM-dd
print('Fecha: ',now.toString(Qt.DefaultLocaleLongDate)) ## dia, dd de MM de YY

datetime = QDateTime.currentDateTime() # Devuelve fecha y hora actual
print('Fecha y Hora: ',datetime.toString()) # dia mes dd HH:MM:SS YY

time = QTime.currentTime() # Devuelve hora actual
print('Hora: ',time.toString(Qt.DefaultLocaleLongDate)) # HH:MM:SS
print('\n')

#DIAS Y MES
xmas1 = QDate(2019, 12, 24) # Asocia la fecha 24-12-2019 a xmas1
xmas2 = QDate(2020, 12, 24) # Asocia la fecha 24-12-2020 a xmas2

dayspassed = xmas1.daysTo(now)
print(f'{dayspassed} dias han pasado desde el ultimo XMas')

nofdays = now.daysTo(xmas2) 
print(f'Quedan {nofdays} dias hasta la proxima XMas\n') # Da un resultado negativo, puesto que el dia ya ha pasado
 