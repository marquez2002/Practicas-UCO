//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <regex.h>
#include <ctype.h>
#include <vector>

#include "gameManager.cpp"
#include "gameManager.h"
#include "user.h"
#include "game.h"
#include "p1-servidor-funciones.cpp"

//DEFINES
#define MSG_SIZE 350
#define MAX_CLIENTS 30

//Inicializamos las variables del programa
int Server_Socket, New_Server_Socket;
struct sockaddr_in sockname, from;
char buffer[MSG_SIZE];
socklen_t from_len;
fd_set readfds, auxfds;
int salida;
int arrayClientes[MAX_CLIENTS];
int numClientes = 0;
int i, j, k;
int recibidos;
char identificador[MSG_SIZE];
int linea0[7];
int linea1[7];
int linea2[7];
int linea3[7];
int linea4[7];
int linea5[7];
int linea6[7];

int on, ret;

regex_t regex;
int result;

GameManager *gameManager = GameManager::getInstance();

void closedClient(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]){
   //CARGA EL SISTEMA
   #include "gameManager.h"
   printf("El socket %d, se ha desconectado\n", i);
   char buffer[250];
   int j;
   strcpy(buffer, "+Ok. Desconexión procesada.\n");
   send(i, buffer, sizeof(buffer), 0);
   strcpy(buffer, "+Ok. Tu oponente ha salido de la partida.\n");
   send(gameManager->findPair(i), buffer, sizeof(buffer), 0);

   close(socket);
   FD_CLR(socket, readfds);

   //Reestructura el array de clientes
   for (j = 0; j < (*numClientes) - 1; j++)
      if (arrayClientes[j] == socket)
         break;
   for (; j < (*numClientes) - 1; j++)
      (arrayClientes[j] = arrayClientes[j + 1]);

   (*numClientes)--;
   gameManager->unlogUser(i);
   gameManager->deleteGame(i);
}

void exitHandler(int signum){
   saveSystem();
   printf("\nApagando el servidor...\n");
   signal(SIGINT, exitHandler);
   for (j = 0; j < numClientes; j++){
      bzero(buffer, sizeof(buffer));
      strcpy(buffer, "–ERR. Desconectado por el servidor\n");
      send(arrayClientes[j], buffer, sizeof(buffer), 0);
      close(arrayClientes[j]);
      FD_CLR(arrayClientes[j], &readfds);
   }
   close(Server_Socket);
   regfree(&regex);
   exit(-1);
}

//IMPRIME TABLERO DE 4 EN RAYA
void imprimirMatriz(int* linea0, int* linea1, int* linea2, int* linea3, int* linea4, int* linea5, int* linea6){
   system("clear");
   printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
   for(int i=0; i<7; i++){
      printf("| ");
      if(linea6[i]==0){
          printf("  ");
      }
      if(linea6[i]==1){
          printf("o ");
      }
      if(linea6[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea5[i]==0){
          printf("  ");
      }
      if(linea5[i]==1){
          printf("o ");
      }
      if(linea5[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea4[i]==0){
          printf("  ");
      }
      if(linea4[i]==1){
          printf("o ");
      }
      if(linea4[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea3[i]==0){
          printf("  ");
      }
      if(linea3[i]==1){
          printf("o ");
      }
      if(linea3[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea2[i]==0){
          printf("  ");
      }
      if(linea2[i]==1){
          printf("o ");
      }
      if(linea2[i]==2){
          printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea1[i]==0){
          printf("  ");
      }
      if(linea1[i]==1){
          printf("o ");
      }
      if(linea1[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }

   for(int i=0; i<7; i++){
      printf("| ");
      if(linea0[i]==0){
          printf("  ");
      }
      if(linea0[i]==1){
          printf("o ");
      }
      if(linea0[i]==2){
         printf("x ");
      }
      if(i==6){
         printf("|\n");
      }
   }
}

//COMPRUEBA 4 EN RAYA
int comprobarGanador(int* linea0, int* linea1, int* linea2, int* linea3, int* linea4, int* linea5, int* linea6){
   //Cuatro en raya en fila
   for(int i=0; i<4; i++){
      if(linea0[i]==1 && linea0[i+1]==1 && linea0[i+2]==1 && linea0[i+3]==1){
             return 1;
         }
      if(linea0[i]==2 && linea0[i+1]==2 && linea0[i+2]==2 && linea0[i+3]==2){
             return 2;
         }
      if(linea1[i]==1 && linea1[i+1]==1 && linea1[i+2]==1 && linea1[i+3]==1){
             return 1;
         }
      if(linea1[i]==2 && linea1[i+1]==2 && linea1[i+2]==2 && linea1[i+3]==2){
             return 2;
         }
      if(linea2[i]==1 && linea2[i+1]==1 && linea2[i+2]==1 && linea2[i+3]==1){
             return 1;
         }
      if(linea2[i]==2 && linea2[i+1]==2 && linea2[i+2]==2 && linea2[i+3]==2){
             return 2;
         }
      if(linea3[i]==1 && linea3[i+1]==1 && linea3[i+2]==1 && linea3[i+3]==1){
             return 1;
         }
      if(linea3[i]==2 && linea3[i+1]==2 && linea3[i+2]==2 && linea3[i+3]==2){
             return 2;
         }
      if(linea4[i]==1 && linea4[i+1]==1 && linea4[i+2]==1 && linea4[i+3]==1){
             return 1;
         }
      if(linea4[i]==2 && linea4[i+1]==2 && linea4[i+2]==2 && linea4[i+3]==2){
             return 2;
         }
      if(linea5[i]==1 && linea5[i+1]==1 && linea5[i+2]==1 && linea5[i+3]==1){
             return 1;
         }
      if(linea5[i]==2 && linea5[i+1]==2 && linea5[i+2]==2 && linea5[i+3]==2){
             return 2;
         }
      if(linea6[i]==1 && linea6[i+1]==1 && linea6[i+2]==1 && linea6[i+3]==1){
             return 1;
         }
      if(linea6[i]==2 && linea6[i+1]==2 && linea6[i+2]==2 && linea6[i+3]==2){
             return 2;
         }
   }

   //Cuatro en raya en columna
   for(int i=0; i<7; i++){
      if(linea0[i]==1 && linea1[i]==1 && linea2[i]==1 && linea3[i]==1){
         return 1;
      }
      if(linea0[i]==2 && linea1[i]==2 && linea2[i]==2 && linea3[i]==2){
         return 2;
      }
      if(linea1[i]==1 && linea2[i]==1 && linea3[i]==1 && linea4[i]==1){
         return 1;
      }
      if(linea1[i]==2 && linea2[i]==2 && linea3[i]==2 && linea4[i]==2){
         return 2;
      }
      if(linea2[i]==1 && linea3[i]==1 && linea4[i]==1 && linea5[i]==1){
         return 1;
      }
      if(linea2[i]==2 && linea3[i]==2 && linea4[i]==2 && linea5[i]==2){
         return 2;
      }
      if(linea3[i]==1 && linea4[i]==1 && linea5[i]==1 && linea6[i]==1){
         return 1;
      }
      if(linea3[i]==2 && linea4[i]==2 && linea5[i]==2 && linea6[i]==2){
         return 2;
      }
   }

   //Cuatro en raya en diagonal
   for(int i=0; i<4; i++){
      if(linea0[i]==1 && linea1[i+1]==1 && linea2[i+2]==1 && linea3[i+3]==1){
         return 1;
      }
      if(linea0[i]==2 && linea1[i+1]==2 && linea2[i+2]==2 && linea3[i+3]==2){
         return 2;
      }
      if(linea1[i]==1 && linea2[i+1]==1 && linea3[i+2]==1 && linea4[i+3]==1){
         return 1;
      }
      if(linea1[i]==2 && linea2[i+1]==2 && linea3[i+2]==2 && linea4[i+3]==2){
         return 2;   
      }
      if(linea2[i]==1 && linea3[i+1]==1 && linea4[i+2]==1 && linea5[i+3]==1){
         return 1;
      }
      if(linea2[i]==2 && linea3[i+1]==2 && linea4[i+2]==2 && linea5[i+3]==2){
         return 2;
      }
      if(linea3[i]==1 && linea4[i+1]==1 && linea5[i+2]==1 && linea6[i+3]==1){
         return 1;
      }
      if(linea3[i]==2 && linea4[i+1]==2 && linea5[i+2]==2 && linea6[i+3]==2){
         return 2;
      }
   }

   //Cuatro en raya en diagonal invertido
   for(int i=0; i<4; i++){
      if(linea0[i+3]==1 && linea1[i+2]==1 && linea2[i+1]==1 && linea3[i]==1){
         return 1;
      }
      if(linea0[i+3]==2 && linea1[i+2]==2 && linea2[i+1]==2 && linea3[i]==2){
         return 2;
      }
      if(linea1[i+3]==1 && linea2[i+2]==1 && linea3[i+1]==1 && linea4[i]==1){
         return 1;
      }
      if(linea1[i+3]==2 && linea2[i+2]==2 && linea3[i+1]==2 && linea4[i]==2){
         return 2;
      }
      if(linea2[i+3]==1 && linea3[i+2]==1 && linea4[i+1]==1 && linea5[i]==1){
         return 1;
      }
      if(linea2[i+3]==2 && linea3[i+2]==2 && linea4[i+1]==2 && linea5[i]==2){
         return 2;
      }
      if(linea3[i+3]==1 && linea4[i+2]==1 && linea5[i+1]==1 && linea6[i]==1){
         return 1;
      }
      if(linea3[i+3]==2 && linea4[i+2]==2 && linea5[i+1]==2 && linea6[i]==2){
         return 2;
      }
   }

   //Si no devuelve 0
   return 0;
}

//COLOCA LA FICHA EN LA COLUMNA INDICADA
void ponerFicha(int* linea0, int* linea1, int* linea2, int* linea3, int* linea4, int* linea5, int* linea6, int columna, int i){
      if(linea0[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea0[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea0[columna]=2;
         }
      }

      else if(linea1[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea1[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){//w* ha ganado la partida
            linea1[columna]=2;
         }
      }

      else if(linea2[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea2[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea2[columna]=2;
         }
      }

      else if(linea3[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea3[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea3[columna]=2;
         }
      }

      else if(linea4[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea4[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea4[columna]=2;
         }
      }

      else if(linea5[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea5[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea5[columna]=2;
         }
      }

      else if(linea6[columna]==0){
         if(gameManager->findPair(i)%2!=0){
            linea6[columna]=1;
         }
         if(gameManager->findPair(i)%2==0){
            linea6[columna]=2;
         }
      }
}

int ultimafilallena(int* linea6){
   for(int i=0; i<7; i++){
      if(linea6[i]==0){
         return 0;
      }
   }
   return 1;
}

void resettablero(int* linea0, int* linea1, int* linea2, int* linea3, int* linea4, int* linea5, int* linea6){
   for(int i=0; i<7; i++){
      linea0[i]=0;
      linea1[i]=0;
      linea2[i]=0;
      linea3[i]=0;
      linea4[i]=0;
      linea5[i]=0;
      linea6[i]=0;
   }
}

char imprimirLetra(int* linea, int posicion){
   if(linea[posicion]==0){
      return '-';
   }
   if(linea[posicion]==1){
      return 'o';
   }
   if(linea[posicion]==2){
      return 'x';
   }
   return 0;   
}

int main(){
   resettablero(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
   result = regcomp(&regex, "REGISTRO -u \\w* -p \\w*", REG_EXTENDED);
   loadSystem();

   //Incializamos los sockets y preparamos el servidor para la lectura

   Server_Socket = socket(AF_INET, SOCK_STREAM, 0);
   if (Server_Socket == -1){
      perror("–ERR. No se puede abrir el socket cliente\n");
      exit(1);
   }

   on = 1;
   ret = setsockopt(Server_Socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2060);
   sockname.sin_addr.s_addr = INADDR_ANY;

   if (bind(Server_Socket, (struct sockaddr *)&sockname, sizeof(sockname)) == -1){
      perror("–ERR. No se ha podido realizar la operación bind");
      exit(1);
   }

   from_len = sizeof(from);

   if (listen(Server_Socket, 1) == -1){
      perror("–ERR. No se ha podido realizar la operación listen");
      exit(1);
   }

   FD_ZERO(&readfds);
   FD_ZERO(&auxfds);
   FD_SET(Server_Socket, &readfds);
   FD_SET(0, &readfds);

   signal(SIGINT, exitHandler);

   while (1){

      //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
      auxfds = readfds;
      salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

      if (salida > 0){
         for (i = 0; i < FD_SETSIZE; i++){

            //Buscamos el socket por el que se ha establecido la comunicación
            if (FD_ISSET(i, &auxfds)){

               if (i == Server_Socket){
                  if ((New_Server_Socket = accept(Server_Socket, (struct sockaddr *)&from, &from_len)) == -1){
                     perror("–ERR. No se han podido aceptar peticiones");
                  }
                  else{
                     if (numClientes < MAX_CLIENTS){
                        arrayClientes[numClientes] = New_Server_Socket;
                        numClientes++;
                        FD_SET(New_Server_Socket, &readfds);

                        strcpy(buffer, "+Ok. Usuario conectado\n");
                        send(New_Server_Socket, buffer, sizeof(buffer), 0);
                     }
                    
                    else{
                        bzero(buffer, sizeof(buffer));
                        strcpy(buffer, "–ERR. Demasiados clientes conectados\n");
                        send(New_Server_Socket, buffer, sizeof(buffer), 0);
                        close(New_Server_Socket);
                     }
                  }
               }
              
               else if (i == 0){
                  //Se ha introducido información de teclado
                  bzero(buffer, sizeof(buffer));
                  fgets(buffer, sizeof(buffer), stdin);

                  //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor.
                  if (strcmp(buffer, "SALIR\n") == 0){
                     exitHandler(SIGINT);
                     FILE *f;
                     GameManager *gameManager = GameManager::getInstance();
                     f = fopen("users.txt", "w");
                     char input[512];
                     for (int i = 0; i < (int)gameManager->getUsers().size(); i++){
                        snprintf(input, 512, "%s,%s\n", gameManager->getUsers()[i].getUserName(), gameManager->getUsers()[i].getUserPassword());
                        fputs(input, f);
                     }
                     fclose(f);
                  }
               }

               else{
                  bzero(buffer, sizeof(buffer));
                  recibidos = recv(i, buffer, sizeof(buffer), 0);
                  if (recibidos > 0){
                     result = regexec(&regex, buffer, 0, NULL, 0);
                     if (strcmp(buffer, "SALIR\n") == 0){

                        closedClient(i, &readfds, &numClientes, arrayClientes);
                     }
                     else if (!result){
                        User user;
                        char *aux;
                        const char *name;
                        const char *password;
                        const char *flag;
                        aux = strtok(buffer, " ");
                        aux = strtok(NULL, " ");
                        aux = strtok(NULL, " ");
                        name = aux;
                        aux = strtok(NULL, " ");
                        flag = aux;
                        aux = strtok(NULL, "\n");
                        password = aux;

                        if (gameManager->nameExist(name)){
                           strcpy(buffer, "–Err. Usuario ya registrado\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else{
                           user.setUserName(name);
                           user.setUserPassword(password);
                           gameManager->addUser(user);
                           strcpy(buffer, "+Ok. Usuario registrado\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                     }
                     else if (strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0){
                        if (strncmp(buffer, "USUARIO \n", strlen("USUARIO \n")) == 0){
                           strcpy(buffer, "-Err. No se ha podido completar el login\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else{
                           char *aux;
                           aux = strtok(buffer, " ");
                           aux = strtok(NULL, "\n");
                           if (gameManager->nameExist(aux)){
                              if (gameManager->logUser(i, aux)){
                                 strcpy(buffer, "+Ok. Usuario correcto\n");
                              }
                              else{
                                 strcpy(buffer, "-Err. No se ha podido completar el login\n");
                              }
                              send(i, buffer, sizeof(buffer), 0);
                           }
                           else{
                              strcpy(buffer, "–Err. Usuario incorrecto\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                        }
                     }

                     else if (strncmp(buffer, "PASSWORD ", strlen("PASSWORD ")) == 0){
                        if (strncmp(buffer, "PASSWORD \n", strlen("PASSWORD \n")) == 0){
                           strcpy(buffer, "–ERR. Error en la validación\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else
                        {
                           char *aux;
                           aux = strtok(buffer, " ");
                           aux = strtok(NULL, "\n");
                           if (gameManager->checkPassword(i, aux))
                           {
                              strcpy(buffer, "+Ok. Usuario validado\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                           else
                           {
                              strcpy(buffer, "–ERR. Error en la validación\n");
                              send(i, buffer, sizeof(buffer), 0);
                           }
                        }
                     }
                     else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0)
                     {
                        resettablero(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
                        int status = gameManager->matchUser(i);
                        if (status == 1){
                           sprintf(buffer, "+Ok. Empieza la partida.\n");
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else if (status == 0){
                           strcpy(buffer, "+Ok. Esperando jugadores\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }

                        else{
                           strcpy(buffer, "-Err. Todas las salas están llenas vuelva a intentarlo más tarde\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                     }
                     else if (strncmp(buffer, "SALIR", strlen("SALIR")) == 0){
                        closedClient(i, &readfds, &numClientes, arrayClientes);
                     }


                     else if (strncmp(buffer, "CHAT ", strlen("CHAT ")) == 0){
                        send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                     }

                     else if (strncmp(buffer, "COLOCAR-FICHA ", strlen("COLOCAR-FICHA ")) == 0){
                        int valor = buffer[14];
                        if(valor<49 || valor>55){
                           valor=-1;
                        }
                        if(valor==49){
                           valor=0;
                        }
                        if(valor==50){
                           valor=1;
                        }
                        if(valor==51){
                           valor=2;
                        }
                        if(valor==52){
                           valor=3;
                        }
                        if(valor==53){
                           valor=4;
                        }
                        if(valor==54){
                           valor=5;
                        }
                        if(valor==55){
                           valor=6;
                        }
                        if (valor==-1 || linea6[valor]==1 || linea6[valor]==2){
                           sprintf(buffer, "-Err. Debe seleccionar otra columna que tenga alguna casilla disponible\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        else if(ultimafilallena(linea6)==1){
                           resettablero(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
                           ponerFicha(linea0, linea1, linea2, linea3, linea4, linea5, linea6, valor, i);
                           sprintf(buffer, "+Ok. Nuevo tablero.\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }
                        
                        ponerFicha(linea0, linea1, linea2, linea3, linea4, linea5, linea6, valor, i);
                        imprimirMatriz(linea0, linea1, linea2, linea3, linea4, linea5, linea6);
                        if(comprobarGanador(linea0, linea1, linea2, linea3, linea4, linea5, linea6)==1){
                              sprintf(buffer, "+Ok. Jugador %s ha ganado la partida.\n", gameManager->getName(i));
                              send(i, buffer, sizeof(buffer), 0);
                              send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                        }                    
                        if(comprobarGanador(linea0, linea1, linea2, linea3, linea4, linea5, linea6)==2){
                              sprintf(buffer, "+Ok. Jugador %s ha ganado la partida.\n", gameManager->getName(i));
                              send(i, buffer, sizeof(buffer), 0);
                              send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                              gameManager->deleteGame(i);
                        }
                           sprintf(buffer, "+Ok. COLOCA-FICHA: %d\n\n1|2|3|4|5|6|7\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n%c|%c|%c|%c|%c|%c|%c\n", valor+1, imprimirLetra(linea6, 0), imprimirLetra(linea6, 1), imprimirLetra(linea6, 2), imprimirLetra(linea6, 3), imprimirLetra(linea6, 4), imprimirLetra(linea6, 5), imprimirLetra(linea6, 6), imprimirLetra(linea5, 0), imprimirLetra(linea5, 1), imprimirLetra(linea5, 2), imprimirLetra(linea5, 3), imprimirLetra(linea5, 4), imprimirLetra(linea5, 5), imprimirLetra(linea5, 6), imprimirLetra(linea4, 0), imprimirLetra(linea4, 1), imprimirLetra(linea4, 2), imprimirLetra(linea4, 3), imprimirLetra(linea4, 4), imprimirLetra(linea4, 5), imprimirLetra(linea4, 6), imprimirLetra(linea3, 0), imprimirLetra(linea3, 1), imprimirLetra(linea3, 2), imprimirLetra(linea3, 3), imprimirLetra(linea3, 4), imprimirLetra(linea3, 5), imprimirLetra(linea3, 6), imprimirLetra(linea2, 0), imprimirLetra(linea2, 1), imprimirLetra(linea2, 2), imprimirLetra(linea2, 3), imprimirLetra(linea2, 4), imprimirLetra(linea2, 5), imprimirLetra(linea2, 6), imprimirLetra(linea1, 0), imprimirLetra(linea1, 1), imprimirLetra(linea1, 2), imprimirLetra(linea1, 3), imprimirLetra(linea1, 4), imprimirLetra(linea1, 5), imprimirLetra(linea1, 6), imprimirLetra(linea0, 0), imprimirLetra(linea0, 1), imprimirLetra(linea0, 2), imprimirLetra(linea0, 3), imprimirLetra(linea0, 4), imprimirLetra(linea0, 5), imprimirLetra(linea0, 6));
                           send(i, buffer, sizeof(buffer), 0);
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);          
                     }

                  //Si el cliente introdujo ctrl+c
                  if (recibidos == 0)
                  {
                     //Eliminar ese socket
                     closedClient(i, &readfds, &numClientes, arrayClientes);
                  }
               }
            }
         }
      }
   }
   }
   close(Server_Socket);
   return 0;
}

