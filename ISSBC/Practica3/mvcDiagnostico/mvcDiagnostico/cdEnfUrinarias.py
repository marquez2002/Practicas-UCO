#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun Jan 19 12:19:10 2014

@author: acalvo
"""

class Observable():
    '''Definicion generica de una observable'''
    def __init__(self,nombre=None,tipo=None,valoresPermitidos=None,valor=None):
        #print 'observable->',valor
        self.nombre=nombre
        self.valor=valor
        self.tipo=tipo
        self.valoresPermitidos=valoresPermitidos

class Fiebre(Observable):
    def __init__(self,valor=None):
        nombre='fiebre'
        tipo='multiple'
        valoresPermitidos=['normal','alta','muy alta']
        Observable.__init__(self,nombre ,tipo ,valoresPermitidos,valor)
        self.valor=valor

class Disuria(Observable):
    def __init__(self,valor=None):
        Observable.__init__(self) 
        nombre='disuria'
        tipo='boleano'
        valoresPermitidos=None
        Observable.__init__(self,nombre,tipo,valoresPermitidos,valor)
        self.ayuda=u'''Descripción de la disuria'''
              
class DolorPerineal(Observable):
    def __init__(self,valor=None):
        nombre='dolor perineal'
        tipo='multiple'
        valoresPermitidos=[u'sin dolor',u'agudo',u'crónico']
        Observable.__init__(self,nombre,tipo,valoresPermitidos,valor)
        self.ayuda=u'''Descripción del  ldolor perineal'''
        
class DolorLumbar(Observable): 
    
    def __init__(self,valor=None):
        #print valor
        nombre='dolor lumbar'
        tipo='multiple'
        valoresPermitidos=['sin dolor','bajo','alto','muy alto']
        Observable.__init__(self,nombre,tipo,valoresPermitidos,valor) 
              
class Hematuria(Observable):
    def __init__(self,valor=None):
        nombre='hematuria'
        tipo='boleano'
        valoresPermitidos=None
        Observable.__init__(self,nombre,tipo,valoresPermitidos,valor)               
        
def observables():
    '''Devuelve la lista de observables de la BC
    '''
    obs=[]
    obs.append(Fiebre())
    obs.append(Disuria())
    obs.append(Hematuria())
    obs.append(DolorPerineal())
    obs.append(DolorLumbar())
    return obs

def creaObservable(tp):
    '''Crea una instancia de un observable si la tupla coincide con la base de conocimiento. 
    Si la observable es correcta devuelve una instancia de la observable.
    Corregir. Hay que mejorar esta función'''
    
    print (tp)
    if tp[0]==u'fiebre':
        ob=Fiebre(tp[1])
        return ob
    elif tp[0]==u'disuria':
        ob=Disuria(tp[1])
        if tp[1]=='True':
            ob.valor=True
        return ob
    elif tp[0]==u'dolor perineal':
        ob=DolorPerineal(tp[1])
        if tp[1]=='True':
            ob.valor=True
        return ob
    elif tp[0]==u'dolor lumbar':
        ob=DolorLumbar(tp[1])
        print (ob,ob.valoresPermitidos,tp[1])
        if tp[1] in ob.valoresPermitidos:
            ob.valor=tp[1]
            return ob
        else:
            print ('no esta')
    elif tp[0]==u'hematuria':
        ob=Hematuria(tp[1])
        if tp[1]=='True':
            ob.valor=True
        return ob
    return None


class Enfermedad():
    '''Clase Enfermedad
    '''
    def __init__(self,nombre):
        self.nombre=nombre
        self.ayuda=u''

class ProstatitisAguda(Enfermedad):
    def __init__(self):
        Enfermedad.__init__(self,nombre='Prostatitis aguda')
        #Creamos instancias de observables
        self.debePresentar =[Fiebre([u'alta',u'muy alta']),Disuria(True)]
        self.puedePresentar = [DolorPerineal('agudo')]
        self.noPuedePresentar = [Hematuria(False)]
        self.ayuda=u'Ayuda sobre prostatitis aguda'.encode(encoding='iso-8859-1')


class ProstatitisCronica(Enfermedad):
    def __init__(self):
        Enfermedad.__init__(self,nombre='Prostatitis crónica')
        #Creamos instancias de observables
        self.debePresentar =[DolorPerineal('agudo')]
        self.puedePresentar = [Fiebre('alta')]
        self.noPuedePresentar = [Hematuria(True)]
        self.ayuda=u'Ayuda sobre prostatitis crónica'.encode(encoding='iso-8859-1')

class CalculoRenal(Enfermedad):
    def __init__(self):
        Enfermedad.__init__(self,nombre='Cálculo renal')
        #Creamos instancias de observables
        self.ayuda=u'Ayuda sobre cálculo renal'.encode(encoding='iso-8859-1')
        self.debePresentar =[DolorLumbar([u'alto',u'muy alto'])]
        self.puedePresentar = [DolorPerineal(u'agudo'),Hematuria(True)]
        self.noPuedePresentar = [Disuria(True),Fiebre(['alta','muy alta'])]
        self.ayuda=u'Ayuda sobre el cálculo renal'.encode(encoding='iso-8859-1')

def hipotesis():
    '''
    Posibles enfermedades o averías que pueden darse
    '''
    prAg=ProstatitisAguda()
    prCr=ProstatitisCronica()
    cr=CalculoRenal()
    lHp=[prAg,prCr,cr]
    return lHp

if __name__ == '__main__':
    cont ='s'
    while cont=='s':
        ej=int(input('Prueba: '))
        
        if ej==1:
            e=ProstatitisCronica()
            for s in e.debePresentar:
                print (s.nombre, s.valor)
            print (e.ayuda)
        if ej==2:
            f=Fiebre('alta')
            print (f.nombre)
            print (f.valor)
            f.valor='baja'
            print (f.valor)
            print (f.valoresPermitidos)
        if ej==3:
            for o in observables():
                print (o.nombre,o.tipo,o.valoresPermitidos)
        if ej==4:
            c=creaObservable(('dolor lumbar','muy alto'))
            if not c==None:
                print (c.nombre)
                print (c.valor)
                print (c.tipo)
                print (c.valoresPermitidos)
            else:
                print ('error')
        if ej==5:
            cr=CalculoRenal()
            print (cr.debePresentar)
            print (cr.puedePresentar)
        if ej==6:
            #hs=hipotesis()
            #print hs[2].debePresentar[0].valor
            dl=DolorLumbar(valor=['alto','muy alto'])
            print (dl.valor)
        if ej==7:
            hipotesis= hipotesis()
            for h in hipotesis:
                print (h.nombre,h.debePresentar,h.noPuedePresentar)
            #print (hipotesis     )     
        cont=input('Desea continuar: (s/n)')
