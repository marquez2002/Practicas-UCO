#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Sun Jan 19 12:19:10 2014

@author: acalvo
"""
import cdEnfUrinarias as cd
class MetodoCoberturaCausal():
    '''Método de cobertura causal para la tarea de diagnóstico'''
    def __init__(self,fallos):
        self.fallos=fallos
        self.explicacion=''
        self.diferencial=[]
        self.diagnostico=[]
        pass
    def obtenerConjuntoDiferencial(self):
        '''
        Obtiene el conjunto diferencial a partir de unos observables dados os fallos.
        @rtype:   list
        @return:  Conjunto de hipótesis compatible con los fallos.
        '''
        #Crear un conjunto diferencial con todos los fallos
        cc=CoberturaCausal(self.fallos)#Invoca la inferencia de cobertura causal
        self.diferencial=cc.execute()
        return self.diferencial
    def execute(self,tr=False):
        
        '''Ejecución del método de cobertura causal para la tarea de diagnóstico.
        @rtype:   bolean
        @return:  Devuelve True si se ha realizado con éxito.
        '''
        tab0='    '
        tab1='    '
        self.explicacion+='Ejectutando cobertura causal.'
        #Se obtiene el conjunto diferencial invocando a la inferencia de cobertura causal
        cc=CoberturaCausal(self.fallos)
        self.diferencial=cc.execute(tr=tr)
        self.explicacion+=u'Se obtiene el conjunto diferencial: \n'
        self.observablesCaso=self.fallos#Modificar
        for f in self.diferencial: #Va construyendo la explicación
            self.explicacion+=f.nombre+'\n'
        self.lObNoUs=cd.observables() #Lista de observables no usadas
        self.evidencias=[]#Lista de evidencias
        if tr:
            print 
            print ('Entramos en la iteración')
            print 
         
        while (len(self.diferencial)>0 and len(self.lObNoUs)>0):
            #Mientras haya hipótesis que observar
            if tr:
                print ('#Seleccionamos una hipotesis no seleccionada antes')
                print ('======================>')
                print 
            seleccionar=Seleccionar(self.diferencial)#Invoca a la inferencia de seleccionar
            hipotesis=seleccionar.execute()#Selecciona una hipótesis a evaluar
            if tr:
                print ('hipotesis seleccionada', hipotesis)
                print ('======================')
                print 
            
            self.explicacion+=u'\nProbamos la  hipótesis de '
            self.explicacion+=hipotesis.nombre+'\n'
            if tr:            
                #print self.explicacion
                print
                print ('antes de verificar evidencias e hipotesis:', self.evidencias,hipotesis)
                print ('hipotesis debe de presentar->',hipotesis.debePresentar)
                print 
            
                print ('#A partir de una hipótesis especificamos un observable de la lista de observables no usadas')
                print
            esp=Especificar(hipotesis,self.lObNoUs)
            tObservable=esp.execute()
            self.observable=tObservable[0]
            self.lObUs=tObservable[1]
            if tr:
                print 
                print ('observable a utilizar', self.observable.nombre,self.observable.valor )
                print ('Nueva lista de Observables no usadas:',self.lObUs)
                print 
            
                print ('#Obtenemos el valor de un observable dentro de las observables del caso')
                print 
            
            obt=Obtener(self.observable, self.observablesCaso)
            hallazgo=obt.execute(tr=False)
            if tr:
                print ('Hallazgo: ',hallazgo)
                print 
            if not hallazgo==None:
                #print 'hallazgo:', self.observable.nombre, hallazgo
                self.observable.valor=hallazgo
                self.evidencias.append(self.observable)
                if tr:
                    print (self.evidencias)
                    print ('Nuevo conjunto de Evidencias:----------->')
                    for ev in self.evidencias:
                        print (ev.nombre, ev.valor)
                        print
                        print
                        print 
            else:
                continue
            
            if tr:
                print ('#Para cada hipótesis en el conjunto diferncial')
            listaSupresion=[]
            self.explicacion+=u'\nEvidencias:'
            for ev in self.evidencias:
                self.explicacion+='\n'+'  '+ev.nombre 
                if isinstance(ev.valor,bool):
                    self.explicacion+='->'+str(ev.valor)
                elif isinstance(ev.valor,list):
                    texto=''
                    for v in ev.valor:
                        texto=texto+v
                    self.explicacion+='->'+texto
                elif isinstance(ev.valor,str):
                    self.explicacion+='->'+ev.valor          
            self.explicacion+='\n'
                
            for hipotesis in self.diferencial:
                if tr:
                    print (tab1+'****Probando la hipotesis: ',hipotesis)
                    #print tab1+'Evidencia: ', self.evidencia
                    print 
                verifica=Verificar(self.evidencias,hipotesis)#Con los fallos observados invoca la inferencia verificar
                verifica.execute(tr=tr)
                
                
                if tr:
                    print (tab1+'resultado de verificar')
                    print (tab1+'verifica.resultado=', verifica.resultado)
                    print (tab1+'verifica.justificacion=', verifica.justificacion)
                    
                    print (tab1+'===================')
                    print 
                self.explicacion+=verifica.justificacion+'\n'
                
                if verifica.resultado==False:#Si el resultado de la verificación elimina la hipótesis del conjunto diferencial
                    listaSupresion.append(hipotesis)
                    if tr:
                        print 
                        print (tab1+'Verifica False.')
                        print 
                    pass
                else:
                    pass
                    if tr:
                        print (tab1+'Resultado True---------------->')
                    #self.diagnostico.append(hipotesis)#Añade a la lista de diagnósticos compatibles la hipotesis
                    #self.diferencial.remove(hipotesis)#Suprime la hipótesis evaluada
                    #Añadimos la justificación de verifica
                    #self.explicacion+=verifica.justificacion  #Añade a la justificación la justificación de la verificación
                #return
            for h in listaSupresion:
                self.diferencial.remove(h)
            if tr:
                print ('Nueva lista diferencial->>>>>>>>>>>',self.diferencial)
                print ('Fin de las pruebas con la evidencia ', self.evidencias)
                print ('====================================================>>>>>>>>>>>>>>>>>>>')
        if tr:
            print ('EL DIAGNOSTICO ES :',self.diferencial)
            print ('LA EXPLICACION ES :',self.explicacion)
        
        
     

class Inferencia():
    def __init__(self):
        pass
    def execute(self):
        pass
    
class CoberturaCausal(Inferencia):
    '''
    Se presenta una lista de fallos y proporciona una lista de posibles 
    hipótesis
    '''
    def __init__(self,fallos):
        Inferencia.__init__(self)
        self.fallos=fallos
        self.listaHipotesis=[]
    def execute(self,tr=False):
        '''
         Mostrar todas las compatibles con los fallos. 
         Mejorar
        '''
        hipotesis= cd.hipotesis()
        self.listaHipotesis=hipotesis
        return hipotesis

        

class Seleccionar(Inferencia):
    '''
    Selecciona una hipótesis del conjunto diferencial
    '''
    def __init__(self,conjuntoDiferencial):
        Inferencia.__init__(self)
        self.conjuntoDiferencial=conjuntoDiferencial
    def execute(self):
        if len(self.conjuntoDiferencial)>0:#Se selecciona la primera
            return self.conjuntoDiferencial[0]
        else:
            return None
            

class Especificar(Inferencia):
    '''Dada una hipótesis especifica un observable'''
    def __init__(self,hipotesis,observablesNoUsadas):
        Inferencia.__init__(self)
        self.Hipotesis=hipotesis
        self.observablesNoUsadas=observablesNoUsadas
        #print 'Observables No usadas: ',self.observablesNoUsadas
        #print 
        
        
    def execute(self,tr=False):
        if len(self.observablesNoUsadas)>0:
            ob=self.observablesNoUsadas[0]
            self.observablesNoUsadas.remove(ob)
            if tr:
                print (ob,self.observablesNoUsadas)
            return ob,self.observablesNoUsadas
        
        #for ob in cd.observables():
        #    if ob.nombre not in [obu.nombre for obu in self.observablesUsadas]:
        #        self.observablesUsadas.append(ob)
        #        return (ob,self.observablesUsadas) #Se retorna el observable
                #y la lista de observables ya usadas.
        return None, None
  


class Obtener(Inferencia):
    '''Dado un observable obtiene el hallazgo (valor) para ese observable
    dentro de una lista de observables del caso'''
    def __init__(self,observable,observablesCaso):
        Inferencia.__init__(self)
        self.observable=observable
        self.observablesCaso=observablesCaso
        self.hallazgo=None
    def execute(self,tr=True):
        if tr:
            print ('Inferencia Obtener----------------------------->')
            print ('Observable: ', self.observable)
            print ('Observables del Caso',self.observablesCaso)
        
        for obCaso in self.observablesCaso:
            if tr:
                print (obCaso.nombre,self.observable.nombre)
            if obCaso.nombre == self.observable.nombre:
                if tr:
                    print ('son igual nombre')
                self.hallazgo=obCaso.valor
                return self.hallazgo            
        return None
        
            

    
class Verificar(Inferencia):
    '''
    Verifica si una hipótesis de avería es compatible con un conjunto de evidencias.
    '''
    def __init__(self,evidencias,hipotesis):
        Inferencia.__init__(self)
        self.evidencias=evidencias
        self.resultado=None
        self.hipotesis=hipotesis
        self.justificacion=''
    def execute(self,tr=False):
        #Eliminar aquellas hipotesis que no tengan todos los sintomas en debe de estar
        tab='        ->'
        resultado=True
        if tr:
            print (tab+'verificando la hipotesis:',self.hipotesis.nombre, self.hipotesis)
        for fh in self.hipotesis.debePresentar:#Cada observable  de la hipotesis debePresentar debe de estar en evidencia
                                              # con sus valores apropiados
             if tr:
                 #print tab+'debe presentar:', fh,fh.nombre, fh.valor,'->',self.evidencias
                 print (tab+'debe presentar:', (fh.nombre, fh.valor) ,'->',[(f.nombre,f.valor) for f in self.evidencias])
              
             if not (fh.nombre in [f.nombre for f in self.evidencias]):#Si el nombre del observable de la hipótesis no está
                                                                   #en la lista de nombres de las evidencias presentados
                                                                   #Construye la explicación
                 #self.resultado=False
                 self.resultado=None
                 resultado=None
                 self.justificacion+=u'    Podría ser  '
                 self.justificacion+=self.hipotesis.nombre
                 
                 #print 'observable no esta en la lista de evidncias', self.justificacion
                 
                 continue #No es concluyente que pueda eliminarse la hipótesis del conjunto diferencial
                 #Quitar
                 self.justificacion+=u'    No puede ser  '
                 self.justificacion+=self.hipotesis.nombre
                 self.justificacion+=u' porque debería presentar el fallo '
                 self.justificacion+=fh.nombre+' \n'
                 #print type(f.valor)
                 if isinstance(fh.valor,bool):
                     self.justificacion+=str(fh.valor)+'\n'
                 elif isinstance(fh.valor,str):
                     self.justificacion+= fh.valor+'\n'
                 resultado=False
             else: #El nombre del observable de la hipótesis está pero debe de coincidir los valores
                 falla=False #Bandera
                 for e in self.evidencias:
                     if e.nombre==fh.nombre:#comprueba que coincide en valores
                         if  isinstance(fh.valor,list):#Si el valor del fallo de la hipótesis es de tipo lista
                             if not e.valor in fh.valor:#Comprueba que el valor del fallo presentado está en esa lista
                                 falla=True #El valor del fallo presentado no está en la lista
                                 break
                         else:#El valor del fallo de la hipótesis no es de tipo lista
                             if not e.valor==fh.valor:#Si no coincide los valores falla
                                 falla=True
                                 break
                 if falla:#Si se ha fallado se añade a la justificación--->Mejorar
                     self.justificacion+=u'    No puede ser  '
                     self.justificacion+=self.hipotesis.nombre
                     self.justificacion+=u' porque debería presentar el fallo '
                     self.justificacion+=fh.nombre+' \n con con valor apropiado.'
                     resultado=False
                     
             if resultado==False:#Si ha resultado fallida la verificación salimos de la verificación.
                 self.resultado=False
                 return (False,self.justificacion)
             else:
                 self.justificacion+=u' Puede ser  '+self.hipotesis.nombre+'.\n'
                 
                 
        #Eliminar aquellas hipotesis que tenga algun fallo en no debe tener
        for fh in self.hipotesis.noPuedePresentar:
            if tr:
                 #print tab+'debe presentar:', fh,fh.nombre, fh.valor,'->',self.evidencias
                 print (tab+' No debe presentar:', (fh.nombre, fh.valor) ,'->',[(f.nombre,f.valor) for f in self.evidencias])

            if (fh.nombre, fh.valor) in [(e.nombre,e.valor) for e in self.evidencias]:
                 self.resultado=False
                 self.justificacion+=u'    No puede ser  '
                 self.justificacion+=self.hipotesis.nombre
                 #self.justificacion+=f.nombre+' '
                 self.justificacion+=u' porque esta enfermedad no puede presentar el fallo '
                 self.justificacion+=fh.nombre+' con valor '
                 if isinstance(fh.valor,bool):
                     self.justificacion+=str(fh.valor)+'\n'
                 elif isinstance(f.valor,str):
                     self.justificacion+= fh.valor+'\n'                                 
                 resultado=False
        if resultado==False:
            self.resultado=False
            return (False,self.justificacion)

        self.resultado=True
        return (True,self.justificacion)
        
             
        
def diagnostico(hipotesis,fallos):
    
    
    if hipotesis=='PROSTATITIS':
        diagnostico='PROSTATITIS'
        justificacion = u'es una justificación'
        return (diagnostico,justificacion)
    else:
        return (None,None)

def identificaSignosSintomas(ltFallos):
    '''Identifica una lista de tuplas como signos y sintomas (fallos:atributo,valor)
    y compureba que son observables correctas de la base de conocimiento.
    '''
    obs=[]
    for tf in ltFallos:#Comprobar que cada fallo está en la base de conocimiento
        
        print (tf)
        ob=cd.creaObservable(tf)
        print (ob)
        if not ob==None:
            obs.append(ob)
        else:
            return None
    return obs 
    
 
    

if __name__ == '__main__':
    observablesCaso=[cd.Fiebre('normal'),cd.Hematuria(True),cd.DolorLumbar('alto'),
                     cd.DolorPerineal('sin dolor'),cd.Disuria(False)]
    print ('Ejecutando el modelo de la aplicacion')
    cont ='s'
    while cont=='s':
        ej=int(input('Prueba: '))
        if ej==1:#Prueba de la inferencia de cobertura
            cc=CoberturaCausal(observablesCaso)
            cc.execute()  
            for n in cc.listaHipotesis:
                print (n.nombre,n,n.debePresentar[0].nombre,n.debePresentar[0].valor)
        if ej==2:#Prueba de la inferencia seleccionar, especificarr y obtener
            evidencia=[]
            cc=CoberturaCausal(observablesCaso)
            cDiferencial=cc.execute()

            sl=Seleccionar(cDiferencial)
            hipotesis=sl.execute()
            
            print ('hipotesis:', hipotesis.nombre)
            
            lObNoUs=cd.observables()
            esp=Especificar(hipotesis,lObNoUs)
            observable=esp.execute()
            print ('observable', observable[0].nombre,observable[0].valor)
            print
            print ('Obtener un valor')
            obt=Obtener(observable[0], observablesCaso)
            hallazgo=obt.execute()
            print (hallazgo)
            if not hallazgo==None:
                print ('hallazgo:', observable[0].nombre, hallazgo)
                observable[0].valor=hallazgo
                evidencia.append(observable[0])
                print (evidencia)
        if ej==3:
            observablesCaso=[cd.Fiebre('normal'),cd.Hematuria(True),cd.DolorLumbar('alto'),
                     cd.DolorPerineal('sin dolor'),cd.Disuria(False)]
            mcc=MetodoCoberturaCausal(observablesCaso)
            mcc.execute(tr=False)
            print ('resultado')
            print (mcc.diferencial)
            print (mcc.explicacion)
        if ej==4:
            print ('Pruebas de la inferencia de verificación')
            dolorPerineal=cd.DolorPerineal('sin dolor')
            dolorLumbar=cd.DolorLumbar('alto')
            fiebre=cd.Fiebre('normal')
            hematuria=cd.Hematuria(True)
            disuria=cd.Disuria(False)
            evidencias=[cd.Fiebre('normal'),cd.DolorLumbar('alto'),cd.Disuria(True)]
            verifica=Verificar(evidencias,cd.CalculoRenal())#Con los fallos observados invoca la inferencia verificar
            print (verifica.execute(tr=True) )
            
            pass
            
        if ej==10:
            dolorPerineal=cd.DolorPerineal(True)
            dolorLumbar=cd.DolorLumbar(True)
            cc=CoberturaCausal([dolorLumbar])
            cc.execute()
            for n in cc.listaHipotesis:
                print (n.nombre,n,n.debePresentar[0].nombre,n.debePresentar[0].valor)
            pass
        if ej==20:
            dolorPerineal=cd.DolorPerineal(True)
            dolorLumbar=cd.DolorLumbar(True)
            mcc=MetodoCoberturaCausal([dolorPerineal,dolorLumbar])
            #diferencial=mcc.obtenerConjuntDiferencial()
            #print 'diferencial', diferencial
            mcc.execute()
            print ('Justificación')
            print ('=============')
            print (mcc.explicacion)
            print ('Diagnóstico: ',mcc.diagnostico)
            print ('fin')
        if ej==30:
            fiebre=cd.Fiebre('alta')
            disuria=cd.Disuria(True)
            mcc=MetodoCoberturaCausal([fiebre, disuria])
            mcc.execute()
            print ('Justificación')
            print ('=============')
            print( mcc.explicacion)
            print 
            print ('Diagnóstico: ' )
            for d in mcc.diagnostico:
                print (d.nombre)
            print ('fin')
        if ej==40:
            #dolorLumbar=cd.creaObservable(('dolor lumbar','agudo'))
            #dolorLumbar=cd.DolorLumbar('agudo')
            #print 'el dolor lumbar es',dolorLumbar.valor
            #disuria=cd.Disuria(True)
            print
            fiebre=cd.Fiebre('alta')
            disuria=cd.Disuria(True)
            mcc=MetodoCoberturaCausal([fiebre,disuria])
            mcc.execute(tr=False)
            print ('Justificación')
            print ('=============')
            print (mcc.explicacion)
            print 
            print ('Diagnóstico: ' )
            for d in mcc.diagnostico:
                print (d.nombre)
            print ('fin')
        if ej==5:
            ls=identificaSignosSintomas([(u'fiebre','alta'),(u'dolor lumbar','alto')])
            print ('imprimiendo resultados',ls)
        
        cont=input('Desea continuar: (s/n)')
            
            
            
            
        
    
        
        
        