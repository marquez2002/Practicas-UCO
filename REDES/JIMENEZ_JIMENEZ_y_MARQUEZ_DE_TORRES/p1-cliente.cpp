#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


using namespace std;

bool user = false;
bool password = false;
bool playing = false;
bool myTurn = false;


int main(){
   system("clear");

   /*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
   int sd;
   struct sockaddr_in sockname;
   char buffer[250];
   socklen_t len_sockname;
   fd_set readfds, auxfds;
   int salida;
   int fin = 0;

   /* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
   sd = socket(AF_INET, SOCK_STREAM, 0);
   if (sd == -1)
   {
      perror("–ERR. No se puede abrir el socket cliente\n");
      exit(1);
   }

   /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2060);
   sockname.sin_addr.s_addr = inet_addr("192.168.1.39");//IP

   /* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
   len_sockname = sizeof(sockname);

   if(connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
   {
      perror("–ERR. Al establecer la conexión");
      exit(1);
   }

   //Inicializamos las estructuras
   FD_ZERO(&auxfds);
   FD_ZERO(&readfds);

   FD_SET(0, &readfds);
   FD_SET(sd, &readfds);

   /* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
   printf("Bienvenido al 4 en raya online.\n");
   printf("Una vez se haya conectado al servidor introduzca:\n");
   printf(" - Para registrarse en la aplicación por primera vez: \n");
   printf("   REGISTRO -u usuario -p password\n");
   printf(" - Para iniciar sesión: \n");
   printf("   USUARIO usuario\n");
   do{
      auxfds = readfds;
      salida = select(sd + 1, &auxfds, NULL, NULL, NULL);

      //Tengo mensaje desde el servidor
      if (FD_ISSET(sd, &auxfds)){

         bzero(buffer, sizeof(buffer));
         recv(sd, buffer, sizeof(buffer), 0);
         printf("%s", buffer);

         if (strcmp(buffer, "–ERR. Demasiados clientes conectados\n") == 0){
            fin = 1;
         }
         if (strcmp(buffer, "–ERR. Desconectado por el servidor\n") == 0){
            fin = 1;
         }
         if (strcmp(buffer, "+Ok. Usuario correcto\n") == 0){
            user = true;
            printf("Introduzca ahora su contraseña así:\n");
            printf("   PASSWORD password\n");
         }
         if (strcmp(buffer, "+Ok. Usuario validado\n") == 0){
            password = true;
            system("clear");
            printf("%s", buffer);
            printf("Para empezar a jugar introduzca:\n");
            printf("   INICIAR-PARTIDA\n");
            printf("Para salir introduzca:\n");
            printf("   SALIR\n");
         }
         if (strncmp(buffer, "+Ok. Empieza la partida.", strlen("+Ok. Empieza la partida.")) == 0){
            playing = true;
            system("clear");
            printf("%s", buffer);
            printf("En su turno podrá:\n");
            printf(" - Para introducir la ficha en una columna:\n");
            printf("   COLOCAR-FICHA c\n");
            printf(" - Enviar un mensaje a su oponente:\n");
            printf("   CHAT msg\n");
            printf(" - Para salir de la partida introduzca:\n");
            printf("   SALIR\n");
            if (myTurn == true){
               printf("+Ok. Turno de partida\n");
               //imprimirMatriz(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
            }
            else if (myTurn == false){
               printf("+Ok. Turno del otro jugador\n");
               //imprimirMatriz(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
            }
         }

         //ESPERA
         if (strcmp(buffer, "+Ok. Esperando jugadores\n") == 0){
            myTurn = true;
         }

         //INTRODUCIR COLOCA-FICHA
         if (strncmp(buffer, "+Ok. COLOCA-FICHA: ", strlen("+Ok. COLOCA-FICHA: ")) == 0){
            if (myTurn == false){
               printf("+Ok. Turno de partida\n");
               myTurn = true;
            }
            else if (myTurn == true)
            {
               printf("+Ok. Turno del otro jugador\n");
               myTurn = false;
            }
         }

         if (strncmp(buffer, "+Ok. Nuevo tablero.\n", strlen("+Ok. Nuevo tablero.\n")) == 0){
            if(myTurn == false){
               printf("+Ok. Turno de partida\n");
               myTurn = true;
            }
            else if(myTurn == true){
               printf("+Ok. Turno del otro jugador\n");
               myTurn = false;
            }
         }

         if(strncmp(buffer, "-Err. Debe seleccionar otra columna que tenga alguna casilla disponible\n", strlen("-Err. Debe seleccionar otra columna que tenga alguna casilla disponible\n\n")==0) && (myTurn==true)){
            if(myTurn==false){
               myTurn==false;
            }
            else if(myTurn==true){
               printf("Introduce un valor en el rango indicado\n");
            }
         }

         if (strcmp(buffer, "+Ok. Tu oponente ha salido de la partida.\n") == 0){
            playing = false;
         }
         if (strcmp(buffer, "+Ok. Desconexión procesada.\n") == 0){
            fin = 1;
         }
         if (strcmp(buffer, "+Ok. Turno del otro jugador\n") == 0){
            myTurn = false;
         }
         if (strcmp(buffer, "+Ok. Turno de partida\n") == 0){
            myTurn = true;
         }
         if (strncmp(buffer, "+Ok. Jugador ", strlen("+Ok. Jugador ")) == 0){
            playing=false;
            system("clear");
            printf("%s", buffer);
            printf("Para empezar a jugar introduzca:\n");
            printf("   INICIAR-PARTIDA\n");
            printf("Para salir introduzca:\n");
            printf("   SALIR\n");
         }
      }

      else{
         //ERRORES AL INTRODUCIR ALGO POR TECLADO
         if (FD_ISSET(0, &auxfds)){
            bzero(buffer, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);

            //CONTRASEÑA
            if ((strncmp(buffer, "PASSWORD", strlen("PASSWORD")) == 0) && (user == false)){
               printf("-Err. No puede introducir la contraseña antes que el nombre de usuario\n");
            }
            else if ((strncmp(buffer, "PASSWORD", strlen("PASSWORD")) == 0) && (password == true)){
               printf("-Err. Ya ha iniciado sesión\n");
            }

            //REGISTRO
            else if ((strncmp(buffer, "REGISTRO", strlen("REGISTRO")) == 0) && (user == true)){
               printf("-Err. Ya está registrado\n");
            }

            //USUARIO
            else if ((strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0) && (user == true)){
               printf("-Err. Ya ha iniciado sesión\n");
            }

            //INICIAR-PARTIDA
            else if ((strcmp(buffer, "INICIAR-PARTIDA\n") == 0) && (password == false)){
               printf("-Err. No puede iniciar partida antes de iniciar sesión\n");
            }
            else if ((strcmp(buffer, "INICIAR-PARTIDA\n") == 0) && (playing == true)){
               printf("-Err. No puede volver a iniciar partida\n");
            }
            
            //COLOCA-FICHA
            else if ((strncmp(buffer, "COLOCAR-FICHA ", strlen("COLOCAR-FICHA ")) == 0) && ((playing == false) || (myTurn == false))){
               if (playing == false){
                  printf("-Err. Debe estar en una partida para hacer eso\n");
               }
               else if (myTurn == false){
                  printf("-Err. Debe esperar su turno\n");
               }
            }
      
            //CHAT
            else if ((strncmp(buffer, "CHAT ", strlen("CHAT ")) == 0) && ((playing == false) || (myTurn == false))){
               if (playing == false){
                  printf("-Err. Debe estar en una partida para hacer eso\n");
               }
               else if (myTurn == false){
                  printf("-Err. Debe esperar su turno\n");
               }
            }
            else{
               send(sd, buffer, sizeof(buffer), 0);
            }
         }
      }
   }while(fin == 0);
   close(sd);
   return 0;
}