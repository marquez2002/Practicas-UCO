#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <locale.h>
#include <string.h>

/* --------------------------------------------------------------------------------------
 
 Env�a un n�mero aleatorio al servidor, quien el devuelve el n�mero incrementado

---------------------------------------------------------------------------------------- */
 
int main(){
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer para datos 
	-----------------------------------------------------*/
	int Socket_Cliente;
   
   	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
   	struct sockaddr_in Servidor;  
   	socklen_t Longitud_Servidor;
  
  
   	/* --------------------------------------------------
		Se abre el socket cliente
	---------------------------------------------------*/
	Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
	if (Socket_Cliente == -1)
	{
		printf ("No se puede abrir el socket cliente\n");
    		exit (-1);	
	}

	/*---------------------------------------------------------------------
		Necesitamos una estructura con la informaci\ufffdn del Servidor
		para poder solicitarle un servicio.
	----------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr =  inet_addr("127.0.0.1");
 	Longitud_Servidor = sizeof(Servidor);

	/*-----------------------------------------------------------------------
		Se env\ufffda mensaje al Servidor
	-----------------------------------------------------------------------*/

	
	char cadena[256];
	printf("\nMENU SELECIONABLE:\n1.- Indica la fecha del servidor.\n2.- Indica la hora del servidor.\n3.- Indica la fecha y la hora del servidor\n\nTU ELECCION:");
	int eleccion;
	scanf("%d", &eleccion);
	
	if(eleccion==1){
		strcpy(cadena,"DAY");
	}
	else if(eleccion==2){
		strcpy(cadena,"TIME");
	}
	else if(eleccion==3){
		strcpy(cadena,"DAYTIME");
	}
	else{
		printf("El parametro seleccionado no se encuentra disponible. Inténtelo de nuevo.\n");
		return 0;
	}


	int contador=0;


	while(contador<3){
		
		struct timeval timeout;
		fd_set lectura;
		int salida;
	
		//Inicializar la estructua timeval
		timeout.tv_sec = 5;
		timeout.tv_usec = 0; //Microsegundos, hay que inicializarlo siempre
		
		//Inicializar los conjuntos fd_set
		FD_ZERO(&lectura);
		FD_SET(0,&lectura);

		int enviado = sendto (Socket_Cliente, (char *)&cadena, sizeof(cadena), 0, (struct sockaddr *) &Servidor, Longitud_Servidor);
			if (enviado < 0){
				printf("Error al solicitar el servicio\n");
			}
    		else{
				/*----------------------------------------------------------------------
				Esperamos la respuesta del Servidor
				----------------------------------------------------------------------- */ 
				
				salida=select(Socket_Cliente+1, &lectura,NULL,NULL,&timeout);
					if(salida==-1){
					printf("Se ha producido un error en el select.\n");
					}
					else if(salida==0){
    					printf ("Se ha agotado el tiempo del select.\n");
					}
					int recibido=recvfrom(Socket_Cliente, (char *)&cadena, sizeof(cadena),0, (struct sockaddr *)&Servidor, &Longitud_Servidor);
					if(recibido>0){
						printf ("Leido: %s\n", cadena);
						contador=4;
				}
			}	
		}
	close(Socket_Cliente);
	return 0;
}
