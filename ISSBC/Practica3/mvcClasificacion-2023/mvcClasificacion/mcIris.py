#!/usr/bin/env python3
# -*- coding: iso-8859-1 -*-
"""
Created on Sun Jan 19 12:19:10 2014

@author: acalvo
"""
#----LA CLASE GENERAL ------------------------------------------- 
class Clase():
    u'''Clase en la jerarquía más alta.
    '''
    def __init__(self,nombre):
        u'''
        @param: Nombre de la clase.
        '''
        self.nombre=nombre #La clase tiene un nombre
        self.reglas=[]#Lista de reglas que caracteriza a la clase
        #self.reglas=reglas #los elementos de la clase deben de cumplir unas reglas
    def descripcion(self):
        '''Devuelve el texto de la descripción de una clase.
        
        '''
        descripcion=u''
        #print 'Nombre: ', self.nombre
        descripcion+=self.nombre+'\n'
        for r in self.reglas:
            #print r.idRegla,r.tipo, r.subtipo, r.atributo.nombre, r.valorEsperado
            descripcion+=r.idRegla+' '+r.tipo+' '+ 'None' +' ' + r.atributo.nombre+' '
            if isinstance(r.valorEsperado,str):
                descripcion+=' '+r.valorEsperado+'\n'
            elif isinstance(r.valorEsperado,int)or isinstance(r.valorEsperado,float):
                descripcion+=' '+str(r.valorEsperado)+'\n'
            elif isinstance(r.valorEsperado,list):
                for i in r.valorEsperado:
                    descripcion+=' '+str(i)+' '
                descripcion+='\n'
        return descripcion    
                
    
#----LAS CLASES DE LA BASE DE CONOCIMIENTO DE IRIS-----------
class Flor(Clase):
    '''Describe los atributos por los que se caracterizará a un fruto.
    '''
    def __init__(self,nombre):
        '''
        @param nombre: Nombre de la flor
        '''
        Clase.__init__(self,nombre=nombre)
        
        self.atAS=Atributo('Ancho sepalo','int','mm')
        self.atLS=Atributo('Largo sepalo','int','mm')
        self.atAP=Atributo('Ancho petalo','int','mm')
        self.atLP=Atributo('Largo petalo','int','mm')
 
        
        #Se establece la lista de atributos que posee esta clase
        self.atributos=[self.atAS,self.atLS,self.atAP,self.atLP]

#Setosa,Virginica, Versicolor
class Setosa(Flor):
    '''
    El objeto es una  flor .
    
    '''
    def __init__(self):
        Flor.__init__(self,nombre='setosa')# Se inicia con el nombre naranja
        #Reglas que debe de verificar la  flor Setosa
        r1=Rverifica(idRegla='r1',tipo='rango',subtipo=None,atributo=self.atAS,valorEsperado=[10,30])
        r2=Rverifica(idRegla='r2',tipo='rango',subtipo=None,atributo=self.atLS,valorEsperado=[100,120])
        r3=Rverifica(idRegla='r3',tipo='rango',subtipo=None,atributo=self.atAP,valorEsperado=[10,40])
        r4=Rverifica(idRegla='r4',tipo='rango',subtipo=None,atributo=self.atLP,valorEsperado=[90,100])
        self.reglas=[r1,r2,r3,r4]
        pass
        
class Virginica(Flor):
    def __init__(self):
        Flor.__init__(self,nombre='vrginica')
        r1=Rverifica(idRegla='r1',tipo='rango',subtipo=None,atributo=self.atAS,valorEsperado=[10,30])
        r2=Rverifica(idRegla='r2',tipo='rango',subtipo=None,atributo=self.atLS,valorEsperado=[100,200])
        r3=Rverifica(idRegla='r3',tipo='rango',subtipo=None,atributo=self.atAP,valorEsperado=[10,30])
        r4=Rverifica(idRegla='r4',tipo='rango',subtipo=None,atributo=self.atLP,valorEsperado=[100,200])

        self.reglas=[r1,r2,r3,r4]


class Versicolor(Flor):
    def __init__(self):
        Flor.__init__(self,nombre='versicolor')
        r1=Rverifica(idRegla='r1',tipo='rango',subtipo=None,atributo=self.atAS,valorEsperado=[10,30])
        r2=Rverifica(idRegla='r2',tipo='rango',subtipo=None,atributo=self.atLS,valorEsperado=[100,200])
        r3=Rverifica(idRegla='r3',tipo='rango',subtipo=None,atributo=self.atAP,valorEsperado=[10,30])
        r4=Rverifica(idRegla='r4',tipo='rango',subtipo=None,atributo=self.atLP,valorEsperado=[100,200])
        self.reglas=[r1,r2,r3,r4]

        
         

#-----------------------TIPOS DE REGLAS----------------------------------------
class Regla():
    '''
    Describe aspectos generales de una regla
    '''
    def __init__(self,idRegla,tipo):
        self.idRegla=idRegla
        self.tipo=tipo
        pass
    
class Rverifica(Regla):
    '''
    Esta regla verifica si los valores de un atributo satisfacen 
    las restricciones de la regla de la clase. P.e. 
    -  La clase naranja debe de tener el atributo cuyo nombre es color naranja
    '''
    def __init__(self,idRegla,tipo,subtipo,atributo,valorEsperado):
        Regla.__init__(self,idRegla,tipo)
        self.subtipo=subtipo
        self.atributo=atributo
        self.valorEsperado=valorEsperado
    def execute(self,at):
        '''
        Verifica que un atributo-valor satisface la regla de una clase.
        '''
        if self.atributo.nombre==at.nombre: #Deben de coincidor los nombres de los atributos

            if self.tipo=='igual':#Si el atributo es de tipo igual
                if self.valorEsperado==at.valor:
                    return True
                else:
                    return False
                    
            if self.tipo=='rango':#Si el atributo es de tipo rango
                print ('evaluo rango')
                if at.valor <self.valorEsperado[1] and at.valor >=self.valorEsperado[0]:
                    return True
                else:
                    return False
        else:               
            return None
            
    def descripcion(self):
        descripcion=u''
        descripcion+='idRegla: '+self.idRegla+'\n'
        descripcion+='Tipo: '+self.tipo+'\n'
        descripcion+='Atributo: '+self.atributo.nombre+'\n'
        if isinstance(self.valorEsperado,str):
            descripcion+='Valor esperado: '+self.valorEsperado+'\n'
        elif isinstance(self.valorEsperado,int) or isinstance(self.valorEsperado,float):
            descripcion+='Valor esperado: '+str(self.valorEsperado)+'\n'
        elif isinstance(self.valorEsperado,list) :
            for ve in self.valorEsperado:
                descripcion+='Valor esperado: '+str(self.valorEsperado)+'  '
                
        return descripcion
        #print 'idRegla: ',self.idRegla
        #print 'Tipo: ',self.tipo
        #print 'Atributo: ', self.atributo.nombre
        #print 'Valor esperado: ', self.valorEsperado
        
        
                                                                                                                                            



#--------------------------LOS OBJETOS-----------------------------------------
class Objeto():
    def __init__(self,identificador,caracteristicas):
        '''Se inicia la clase especificando el nombre y los atributos del objeto'''
        print ('e va a crear')
        self.identificador=identificador
        self.caracteristicas=caracteristicas
        self.clase=None
        print ('objeto creado')
        pass
    def describeObjeto(self):
        print ('Identificador= ',self.identificador)
        for ct in self.caracteristicas:
            print (ct.atributo.nombre, ct.atributo.tipo, ct.valor, ct.atributo.unidad)
#------------------------LOS ATRIBUTOS----------------------------------------- 
class Atributo():
    '''Clase Atributo. permite especificar las propiedades
    de los atributos que van a usarse en la base de conocimiento para 
    describir un objeto.
    '''
    def __init__(self,nombre,tipo,unidad):
        self.nombre=nombre
        self.tipo=tipo
        self.unidad=unidad

class Caracteristica():
    u'''Clase característica que establece el valor para un atributo'''
    def __init__(self,atributo,valor):
        self.atributo=atributo
        self.valor=valor
        


#-----------------------FUNCIONES----------------------------------------------


    
def clases():
    '''
    Crea una lista de clases candidatas de la base de conocimiento.
    '''
    #Setosa,Virginica, Versicolor
    setosa=Setosa()
    virginica=Virginica()
    versicolor=Versicolor()
    lClases=[setosa,virginica,versicolor]
    return lClases

    
def creaCaracteristicas(lct=[[Atributo('diametro','int','cm'),30]]):
    '''Dada una lista de atributos en forma de lista donde
    se especifica el  atributo y el valor
   se crean las instancias de dichos atributos
    @return: Devuelve una lista de caracteristicas.
    '''
    print (lct)
    carats=[]
    for ct in lct:
        caract=Caracteristica(ct[0],ct[1])
        carats.append(caract)
    return carats
    
def creaAtributosBC(lat=[('atAS','int','mm')]):
    '''Dada una lista de atributos en forma de tupla donde
    se especifica el nombre del atributo, el tipo se  obtiene la lista de 
    atributos con la que se trabaja en la base de conocimiento.'''
    ats=[]
    for at in lat:
        nat=Atributo(at[0],at[1],at[2])
        ats.append(nat)
    return ats



def buscaReglaComparableEnUnaClase(ct,clase):
    for r in clase.reglas:
        print (r.atributo.nombre, ct.atributo.nombre)
        if r.atributo.nombre==ct.atributo.nombre:
            rb=r
            break
                    
    print (rb.atributo.nombre)
    return rb
    

if __name__ == '__main__':
    cont='s'
    while cont=='s':
        ej=int(input('Entre la prueba (1,2,3,4,5):' ))
        
        if ej==1:#Crea la lista de atributos que va a usar la base de conocimiento
            atributos=creaAtributosBC([('atAS','int','mm'),('atLS','int','mm'),('atAP','int','mm'),('atLP','int','mm')])
            print (atributos)
            for at in atributos:
                print (at.nombre, at.tipo, at.unidad)
                
        if ej==2:#Crear un objeto porporcionando una lista de atributos
            lcts=[]
            ct1=Caracteristica(Atributo('atAS','int','mm'),30)
            lcts.append(ct1)
            ct2=Caracteristica(Atributo('atAP','int','mm'),60)
            lcts.append(ct2)
            ob=Objeto('ob1',lcts) #Crea el objeto
            for ct in ob.caracteristicas:
                print (ct.atributo.nombre,ct.atributo.tipo, ct.valor,ct.atributo.unidad)
            print 
            ob.describeObjeto()
            #print clases()
        if ej==25:#Crear un conjunto de características
            c1=Caracteristica(Atributo('atAS','int','mm'),30)
            print  ( c1.atributo.nombre, c1.atributo.tipo,c1.atributo.unidad,c1.valor)
            pass
        if ej==3:#Crea un objeto pasando su identificador y los valores de los atributos
            
            lct=[[Atributo('atAS','int','mm'),30],[Atributo('atAP','int','mm'),30],[Atributo('atLP','int','mm'),45]]
            print (lct)
            llct=creaCaracteristicas(lct)#Se crean instancias de la lista de atributos
            ob=Objeto('p1',llct)#se crea un objeto a partir de las instancias de la lista de atributos
            ob.describeObjeto()#de describe el objeto.
 
            pass
        if ej==4:#Crea el conjunto de clases candidatas
            print (clases())
            for c in clases():
                print (c.nombre)
            cls=clases()
            
        if ej==5:
           
            cVirginica=Virginica()
            print ('descripcion de Naranja', cVirginica.descripcion())
            lct=[[Atributo('Ancho Sepalo','int','mm'),30],[Atributo('Largo sepalo','int','mm'),30],[Atributo('Ancho petalo','int','mm'),45]]
            print (lct)
            llct=creaCaracteristicas(lct)#Se crean instancias de la lista de atributos

            
            ob=Objeto('p1',llct)#se crea un objeto a partir de las instancias de la lista de atributos
            ob.describeObjeto()#de describe el objeto.
            
            #r2.descripcion()
            #print r2.execute(ob.atributos[1])
            
            #Probar si los atributos de un objeto satisface una regla comparable de una clase
            #Buscar una ragla comparable para un atributo de una regla
            #for r in cNaranja.reglas:
            #    if r.atributo.nombre==ob.atributos[1].nombre:
            #        rb=r
            #        break
                    
            #print rb.atributo.nombre
            #print
            #print 'buscando regla'
            rb=buscaReglaComparableEnUnaClase(ob.caracteristicas[2],cVirginica)
                        
        cont = input('Desea continuar(s/n): ')
        print (cont)
        #mydata = input('Prompt :')
        #print (mydata)
        
        
        
        
        