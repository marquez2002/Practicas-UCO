#!/usr/bin/python

"""
This example is a try to know more about 
signal.

Author: i02matog
"""

import model as model

# Retornamos lo que nos devuelva el método del modelo
def doubleClickedTreeView(self, index):  # Retornamos lo que nos devuelva el método del modelo
    data = model.doubleClickedTreeView(self, index)
    return data

# Retornamos lo que nos devuelva el método del modelo
def openFolder(self):  
    data = model.openFolder(self)
    return data

# Retornamos lo que nos devuelva el método del modelo
def saveFile(self):  
    data = model.saveFile(self)
    return data

# Retornamos lo que nos devuelva el método del modelo
def saveAsFile(self): 
    data = model.saveAsFile(self)
    return data

def addFila(self):
    data = model.addFila(self)
    return data