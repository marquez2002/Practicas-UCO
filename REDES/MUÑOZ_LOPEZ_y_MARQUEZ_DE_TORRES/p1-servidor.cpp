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
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

#include "gameManager.cpp"
#include "gameManager.h"
#include "user.h"
#include "game.h"
#include "p1-servidor-funciones.cpp"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[39m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_MAG "\x1B[35m"
#define ANSI_COLOR_BLUE "\x1B[34m"

//DEFINES
#define MSG_SIZE 300
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
const int filas = 10;
const int columnas = 10;
const int num_match = 15;
int tablero1a[filas][columnas]; // MAPA PROPIO DONDE ESTAN COLOCADOS TUS BARCOS
int tablero1b[filas][columnas]; // MAPA PROPIO DONDE ESTAN COLOCADOS TUS BARCOS
int tablero2a[filas][columnas]; // MAPA RIVAL DONDE SOLO VES AGUA O TOCADO
int tablero2b[filas][columnas]; // MAPA RIVAL DONDE SOLO VES AGUA O TOCADO
int vector_match[num_match];
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
   strcpy(buffer, "+Ok. Tu oponente ha terminado de la partida.\n");
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
void inicializarTablero(int x){
   if(x==1){
      for(int i=0; i<filas; i++){
         for(int j=0; j<columnas; j++){
            tablero1a[i][j]=1; // TODO AGUA
         }
      }
   }
   if(x==2){
      for(int i=0; i<filas; i++){
         for(int j=0; j<columnas; j++){
            tablero1b[i][j]=1; // TODO AGUA
         }
      }
   }
}

void inicializarTableroRival(int x){
   if(x==1){
      for(int i=0; i<filas; i++){
         for(int j=0; j<columnas; j++){
            tablero2a[i][j]=4; // No conocemos su contenido
         }
      }
   }
   if(x==2){
      for(int i=0; i<filas; i++){
         for(int j=0; j<columnas; j++){
            tablero2b[i][j]=4; // No conocemos su contenido
         }
      }
   }
}

bool verificarHundido(int w, int x, int y) {
   if(w==1){
      if (tablero1a[x][y] == 2 || tablero1a[x][y] == 3) {
         int longitudHorizontal = 1;
         int longitudVertical = 1;
         int tocados = 1;

         // Verificar horizontalmente hacia la derecha
         for (int i = y+1; i<=9; i++) {
            if (tablero1a[x][i] == 2){
                longitudHorizontal++;
            }
            else if (tablero1a[x][i] == 3){
                longitudHorizontal++;
                tocados++;
            }
            else {
               break;
            }
         }

         // Verificar horizontalmente hacia la izquierda
         for (int i = y-1; i>=0; i--) {
            if (tablero1a[x][i] == 2){
               longitudHorizontal++;
            }
            else if (tablero1a[x][i] == 3){
               longitudHorizontal++;
               tocados++;
            }
            else {
               break;
            }
         }

         // Verificar verticalmente hacia abajo
         for (int i = x+1; i<=9; i++) {
             if (tablero1a[i][y] == 2){
                 longitudVertical++;
             }
             else if (tablero1a[i][y] == 3){
                 longitudVertical++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar verticalmente hacia arriba
         for (int i = x-1; i>=0; i--) {
             if (tablero1a[i][y] == 2){
                 longitudVertical++;
             }
             else if (tablero1a[i][y] == 3){
                 longitudVertical++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar si la longitud en cualquier dirección es igual o mayor que 2 y menor o igual que 4
         if ((longitudHorizontal >= 2 && longitudHorizontal <= 4) || (longitudVertical >= 2 && longitudVertical <= 4)){
            if (longitudVertical==1){
               if(tocados==longitudHorizontal){
                  return true;
               }
               else{
                  false;
               }
            }
            if(longitudHorizontal==1){
               if(tocados==longitudVertical){
                  return true;
               }
               else{
                  false;
               }
            }        
         }
      }
      return false;
   }
   else{
      if (tablero1b[x][y] == 2 || tablero1b[x][y] == 3) {
         int longitudHorizontal = 1;
         int longitudVertical = 1;
         int tocados = 1;

         // Verificar horizontalmente hacia la derecha
         for (int i = y+1; i<=9; i++) {
             if (tablero1b[x][i] == 2){
                 longitudHorizontal++;
             }
             else if (tablero1b[x][i] == 3){
                 longitudHorizontal++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar horizontalmente hacia la izquierda
         for (int i = y-1; i>=0; i--) {
             if (tablero1b[x][i] == 2){
                 longitudHorizontal++;
             }
             else if (tablero1b[x][i] == 3){
                 longitudHorizontal++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar verticalmente hacia abajo
         for (int i = x+1; i<=9; i++) {
             if (tablero1b[i][y] == 2){
                 longitudVertical++;
             }
             else if (tablero1b[i][y] == 3){
                 longitudVertical++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar verticalmente hacia arriba
         for (int i = x-1; i>=0; i--) {
             if (tablero1b[i][y] == 2){
                 longitudVertical++;
             }
             else if (tablero1b[i][y] == 3){
                 longitudVertical++;
                 tocados++;
             }
             else {
                 break;
             }
         }

         // Verificar si la longitud en cualquier dirección es igual o mayor que 2 y menor o igual que 4
         if ((longitudHorizontal >= 2 && longitudHorizontal <= 4) || (longitudVertical >= 2 && longitudVertical <= 4)){
            if (longitudVertical==1){
               if(tocados==longitudHorizontal){
                  return true;
               }
               else{
                  false;
               }
            }
            if(longitudHorizontal==1){
               if(tocados==longitudVertical){
                  return true;
               }
               else{
                  false;
               }
            }        
         }
      }
      else{
         return false;
      }
   }
   return false;
}

bool checkLibresLateral(int w, int a, int x, int y){
   if(w==1){
      if(a==0){
         if((y-1)!=-1){
            if(tablero1a[x][y-1]==2){
               return false;
            }
         }  
         if((y+1)!=10){
            if(tablero1a[x][y+1]==2){
               return false;
            }
         }  
      }
      else{
         if((x-1)!=-1){
            if(tablero1a[x-1][y]==2){
               return false;
            }
         }
         if((x+1)!=10){
            if(tablero1a[x+1][y]==2){
               return false;
            }
         }  
      }
      return true;
   }
   if(w==2){
      if(a==0){
         if((y-1)!=-1){
            if(tablero1b[x][y-1]==2){
               return false;
            }
         }  
         if((y+1)!=10){
            if(tablero1b[x][y+1]==2){
               return false;
            }
         }  
      }
      else{
         if((x-1)!=-1){
            if(tablero1b[x-1][y]==2){
               return false;
            }
         }
         if((x+1)!=10){
            if(tablero1b[x+1][y]==2){
               return false;
            }
         }  
      }
      return true;
   }
   return false;
}

bool checkLibresCabeza(int w, int a, int x, int y){
   if(w==1){
      if(a==0){
         if(tablero1a[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int xb = x-1;
         if(xb!=-1){
            if(tablero1a[xb][y]==2){
               return false;
            }
            if(checkLibresLateral(w, a, xb, y)==false){
                  return false;
            }
         }
      }
      else{
         if(tablero1a[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int yb = y-1;
         if(yb!=-1){
            if(tablero1a[x][yb]==2){
               return false;
            }
            if(checkLibresLateral(w, a, x, yb)==false){
               return false;
            }
         }
      } 
      return true;
   }
   if(w==2){
      if(a==0){
         if(tablero1b[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int xb = x-1;
         if(xb!=-1){
            if(tablero1b[xb][y]==2){
               return false;
            }
            if(checkLibresLateral(w, a, xb, y)==false){
               return false;
            }
         }
      }
      else{
         if(tablero1b[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int yb = y-1;
         if(yb!=-1){
            if(tablero1b[x][yb]==2){
               return false;
            }
            if(checkLibresLateral(w, a, x, yb)==false){
               return false;
            }
         }
      } 
      return true;
   }
   return false;
}
bool checkLibresFinal(int w, int a, int x, int y){
   if(w==1){
      if(a==0){
         if(tablero1a[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int xb = x+1;
         if(xb!=10){
            if(tablero1a[xb][y]==2){
               return false;
            }
            if(checkLibresLateral(w, a, xb, y)==false){
               return false;
            }
         }
      }
      else{
         if(tablero1a[x][y]==2){
            return false;
         }
        if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int yb = y+1;
         if(yb!=10){
            if(tablero1a[x][yb]==2){
               return false;
            }
            if(checkLibresLateral(w, a, x, yb)==false){
               return false;
            }
         }
      }
      return true; 
   }
   if(w==2){
      if(a==0){
         if(tablero1b[x][y]==2){
            return false;
         }
         if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int xb = x+1;
         if(xb!=10){
            if(tablero1b[xb][y]==2){
               return false;
            }
            if(checkLibresLateral(w, a, xb, y)==false){
               return false;
            }
         }
      }
      else{
         if(tablero1b[x][y]==2){
            return false;
         }
        if(checkLibresLateral(w, a, x, y)==false){
            return false;
         }
         int yb = y+1;
         if(yb!=10){
            if(tablero1b[x][yb]==2){
               return false;
            }
            if(checkLibresLateral(w, a, x, yb)==false){
               return false;
            }
         }
      }
      return true; 
   }
   return false;
}

void generarBarcos(int w){
   if(w==1){
      // BARCO DE 4 PLAZAS
      int a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
      int x = rand()%10; // Selecconar la columna 
      int y = rand()%10; //  Seleccionar la fila 
      if(a==0){ // BARCO COLOCADO EN HORIZONTAL
         if(x>=6){
            x = rand()%7;
         }
         tablero1a[x][y]=2;
         tablero1a[x+1][y]=2;
         tablero1a[x+2][y]=2;
         tablero1a[x+3][y]=2;
      }
      else{ //BARCO COLOCADO EN VERTICAL
         if(y>=6){
            y = rand()%7;
         }
         tablero1a[x][y]=2;
         tablero1a[x][y+1]=2;
         tablero1a[x][y+2]=2;
         tablero1a[x][y+3]=2;
      }
      // BARCO DE 3 PLAZAS
      for(int i=1; i<=2;i++){
         a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
         x = rand()%10; // Seleccionar la columna 
         y = rand()%10; //  Seleccionar la fila 
         if(a==0){
            // BARCO COLOCADO EN HORIZONTAL
            if(x>=7){
               x = rand()%8;
            }
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresLateral(w, a, x+1, y)==true) && (checkLibresFinal(w, a, x+2, y)==true)){
                  situado = true;
                  tablero1a[x][y]=2;
                  tablero1a[x+1][y]=2;
                  tablero1a[x+2][y]=2;
               }
               else{
                     x = rand()%8;
                     y = rand()%10; 
               }
            }               
         }
         else{
            if(y>=7){
               y = rand()%8;
            }
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresLateral(w, a, x, y+1)==true) && (checkLibresFinal(w, a, x, y+2)==true)){
                  situado = true;
                  tablero1a[x][y]=2;
                  tablero1a[x][y+1]=2;
                  tablero1a[x][y+2]=2;
               }
               else{
                  x = rand()%10;
                  y = rand()%8; 
               }
            }   
         }
      }
      
      // BARCO DE 2 PLAZAS
      for(int i=1; i<=2;i++){
         a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
         x = rand()%10; // Seleccionar la columna 
         y = rand()%10; //  Seleccionar la fila 
         if(a==0){
            // BARCO COLOCADO EN HORIZONTAL
            if(x>=8){
                  x = rand()%9;
            } 
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresFinal(w, a, x+1, y)==true)){
                  situado = true;
                  tablero1a[x][y]=2;
                  tablero1a[x+1][y]=2;
               }
               else{
                  x = rand()%9;
                  y = rand()%10; 
               }
            }               
         }
         else{
            bool situado = false;
            if(x>=8){
               x = rand()%9;
            }
            while(situado == false){   
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresFinal(w, a, x, y+1)==true)){
                  situado = true;
                  tablero1a[x][y]=2;
                  tablero1a[x+1][y]=2;
               }
               else{
                  x = rand()%10;
                  y = rand()%9; 
               }
            }
         }
      }
   }

   if(w==2){
      // BARCO DE 4 PLAZAS
      int a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
      int x = rand()%10; // Selecconar la columna 
      int y = rand()%10; //  Seleccionar la fila 
      if(a==0){ // BARCO COLOCADO EN HORIZONTAL
         if(x>=6){
            x = rand()%7;
         }
         tablero1b[x][y]=2;
         tablero1b[x+1][y]=2;
         tablero1b[x+2][y]=2;
         tablero1b[x+3][y]=2;
      }
      else{ //BARCO COLOCADO EN VERTICAL
         if(y>=6){
            y = rand()%7;
         }
         tablero1b[x][y]=2;
         tablero1b[x][y+1]=2;
         tablero1b[x][y+2]=2;
         tablero1b[x][y+3]=2;
      }
      // BARCO DE 3 PLAZAS
      for(int i=1; i<=2;i++){
         a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
         x = rand()%10; // Seleccionar la columna 
         y = rand()%10; //  Seleccionar la fila 
         if(a==0){
            // BARCO COLOCADO EN HORIZONTAL
            if(x>=7){
               x = rand()%8;
            }
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresLateral(w, a, x+1, y)==true) && (checkLibresFinal(w, a, x+2, y)==true)){
                     situado = true;
                     tablero1b[x][y]=2;
                     tablero1b[x+1][y]=2;
                     tablero1b[x+2][y]=2;
               }
               else{
                  x = rand()%8;
                  y = rand()%10; 
               }
            }               
         }
         else{
            if(y>=7){
               y = rand()%8;
            }
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresLateral(w, a, x, y+1)==true) && (checkLibresFinal(w, a, x, y+2)==true)){
                  situado = true;
                  tablero1b[x][y]=2;
                  tablero1b[x][y+1]=2;
                  tablero1b[x][y+2]=2;
               }
               else{
                  x = rand()%10;
                  y = rand()%8; 
               }
            }   
         }
      }

      // BARCO DE 2 PLAZAS
      for(int i=1; i<=2;i++){
         a = rand()%2; //  Para ver si el barco iría en posición vertical u horizontal
         x = rand()%10; // Seleccionar la columna 
         y = rand()%10; //  Seleccionar la fila 
         if(a==0){
            // BARCO COLOCADO EN HORIZONTAL
            if(x>=8){
                  x = rand()%9;
            } 
            bool situado = false;
            while(situado == false){
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresFinal(w, a, x+1, y)==true)){
                  situado = true;
                  tablero1b[x][y]=2;
                  tablero1b[x+1][y]=2;
               }
               else{
                  x = rand()%9;
                  y = rand()%10; 
               }
            }               
         }
         else{
            bool situado = false;
            if(y>=8){
               y = rand()%9;
            }
            while(situado == false){   
               if((checkLibresCabeza(w, a, x, y)==true) && (checkLibresFinal(w, a, x, y+1)==true)){
                  situado = true;
                  tablero1b[x][y]=2;
                  tablero1b[x+1][y]=2;
               }
               else{
                  x = rand()%10;
                  y = rand()%9; 
               }
            }
         }
      }
   }
}       

bool comprobarValor(int w, int x, int y){
   bool verdad = false;
   if(w==1){
      if(tablero1a[x][y]==1 || tablero1a[x][y]==2){
         verdad = true;
      }
      else{
         return false;
      }
   }
   if(w==2){
      if(tablero1b[x][y]==1 || tablero1b[x][y]==2){
         verdad = true;
      }
      else{
         return false;
      }
   }
   return verdad;
}
int comprobante(int w, int x, int y){
   if(w==1){
      if(tablero2b[x][y]==1){
         return 0;
      }
      else if(verificarHundido(w, x, y)==true){
         return 2;
      }
      else if(tablero2b[x][y]==3){
         return 1;
      }
   }
   else{
      if(tablero2a[x][y]==1){
         return 0;
      }
      else if(verificarHundido(w, x, y)==true){
         return 2;
      }
      else if(tablero2a[x][y]==3){
         return 1;
      }
   }
   return -1;
}
void imprimirTableroPropio(int w){
   if(w==1){
      printf("TABLERO 1A\n");
      printf("| - | A | B | C | D | E | F | G | H | I | J |\n");
      for(int i=0; i<filas; i++){
         printf("| %d ", i);
         for(int j=0; j<columnas; j++){
            printf("| "); 
            if(tablero1a[i][j]==1){
               printf(ANSI_COLOR_BLUE "A " ANSI_COLOR_RESET);
            }  
            if(tablero1a[i][j]==2){
               printf(ANSI_COLOR_MAG "B " ANSI_COLOR_RESET);
            }
            if(tablero1a[i][j]==3){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            }
            if(tablero1a[i][j]==4){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            }
            if(j==(columnas-1)){
               printf("|\n");
            }  
         }
      }
   }

   if(w==2){
      printf("TABLERO 1B\n");
      printf("| - | A | B | C | D | E | F | G | H | I | J |\n");
      for(int i=0; i<(filas); i++){
         printf("| %d ", i);
         for(int j=0; j<(columnas); j++){
            printf("| "); 
            if(tablero1b[i][j]==1){
               printf(ANSI_COLOR_BLUE "A " ANSI_COLOR_RESET);
            }  
            if(tablero1b[i][j]==2){
               printf(ANSI_COLOR_MAG "B " ANSI_COLOR_RESET);
            }
            if(tablero1b[i][j]==3){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            } 
            if(tablero1b[i][j]==4){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            } 
            if(j==(columnas-1)){
               printf("|\n");
            }   
         }
      }
   }
   printf("\n");
}

void imprimirTableroRival(int w){
   if(w==1){
      printf("TABLERO 2A\n");
      printf("| - | A | B | C | D | E | F | G | H | I | J |\n");
      for(int i=0; i<filas; i++){
         printf("| %d ", i);
         for(int j=0; j<columnas; j++){
            printf("| "); 
            if(tablero2a[i][j]==1){
               printf(ANSI_COLOR_BLUE "A " ANSI_COLOR_RESET);
            }  
            if(tablero2a[i][j]==2){
               printf(ANSI_COLOR_MAG "B " ANSI_COLOR_RESET);
            }
            if(tablero2a[i][j]==3){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            }
            if(tablero2a[i][j]==4){
               printf("? ");
            }
            if(j==(columnas-1)){
               printf("|\n");
            }  
         }
      }
   }
         
   if(w==2){
      printf("TABLERO 2B\n");
      printf("| - | A | B | C | D | E | F | G | H | I | J |\n");
      for(int i=0; i<(filas); i++){
         printf("| %d ", i);
         for(int j=0; j<(columnas); j++){
            printf("| "); 
            if(tablero2b[i][j]==1){
               printf(ANSI_COLOR_BLUE "A " ANSI_COLOR_RESET);
            }  
            if(tablero2b[i][j]==2){
               printf(ANSI_COLOR_MAG "B " ANSI_COLOR_RESET);
            }
            if(tablero2b[i][j]==3){
               printf(ANSI_COLOR_RED "X " ANSI_COLOR_RESET);
            }
            if(tablero2b[i][j]==4){
               printf("? ");
            }
            if(j==(columnas-1)){
               printf("|\n");
            }   
         }
      }
   }
   printf("\n");
}
void dispara(int w, int x, int y){
   if(w==1){
      if(tablero1a[x][y]==1){
         tablero1a[x][y]=4;
         tablero2b[x][y]=1;
      }
      if(tablero1a[x][y]==2){
         tablero1a[x][y]=3;
         tablero2b[x][y]=3;
      }
   }
   if(w==2){
      if(tablero1b[x][y]==1){
         tablero1b[x][y]=4;
         tablero2a[x][y]=1;
      }
      if(tablero1b[x][y]==2){
         tablero1b[x][y]=3;
         tablero2a[x][y]=3;
      }
   }
}

char imprimirLetraTablero3(int x, int y){
   if(tablero2a[x][y]==1){
      return 'A';
   }
   if(tablero2a[x][y]==2){
      return 'B';
   }
   if(tablero2a[x][y]==3){
      return 'X';
   }
   if(tablero2a[x][y]==4){
      return '?';
   }
   return '-';
}

char imprimirLetraTablero4(int x, int y){
   if(tablero2b[x][y]==1){
      return 'A';
   }
   if(tablero2b[x][y]==2){
      return 'B';
   }
   if(tablero2b[x][y]==3){
      return 'X';
   }
   if(tablero2b[x][y]==4){
      return '?';
   }
   return '-';
}


bool compruebaGanador1(){
   for(int i=0; i<filas; i++){
      for(int j=0; j<columnas;j++){
         if(tablero1a[i][j]==2){
            return false;
         }
      }
   }
   return true;
}

bool compruebaGanador2(){
   for(int i=0; i<filas; i++){
      for(int j=0; j<columnas;j++){
         if(tablero1b[i][j]==2){
            return false;
         }
      }
   }
   return true;
}

int main(){
   std::srand(static_cast<unsigned int>(std::time(nullptr)));
   int num_disp1 = 0;
   int num_disp2 = 0;
   inicializarTablero(1);
   inicializarTablero(2);
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
   sockname.sin_port = htons(2065);
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
                  int i=0;
                  if ((New_Server_Socket = accept(Server_Socket, (struct sockaddr *)&from, &from_len)) == -1){
                     perror("–ERR. No se han podido aceptar peticiones");
                  }
                  else{
                     if (numClientes < MAX_CLIENTS){
                        arrayClientes[numClientes] = New_Server_Socket;
                        numClientes++;
                        FD_SET(New_Server_Socket, &readfds);                        
                        while(i!=0){
                           strcpy(buffer, "+Ok. Usuario conectado\n");
                           send(New_Server_Socket, buffer, sizeof(buffer), 0);
                        }
                        i++;
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
                     
                     else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0){
                        sprintf(buffer, "+Ok. Empieza la partida.\n");
                        inicializarTablero(1);
                        inicializarTablero(2);
                        generarBarcos(1);                           
                        generarBarcos(2);
                        inicializarTableroRival(1);
                        inicializarTableroRival(2);                                                                                              
                        num_disp1 = 0;
                        num_disp2 = 0;
                        int status = gameManager->matchUser(i);
                        if (status == 1){
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

                     else if (strncmp(buffer, "DISPARA ", strlen("DISPARA ")) == 0) {
                        int valorX1 = buffer[8] - '0';
                        char letraY1 = buffer[10];
                        int valorY1 = letraY1 - 'A';
                        if(valorY1<0 || 9<valorY1 || valorX1 < 0 || 9 < valorX1){
                           valorX1 = -1;
                           valorY1 = -1;
                           sprintf(buffer, "-Err. Debe seleccionar otra casilla que se encuentre disponible\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }                                                                          
                  
                        else if(i%2==0 && comprobarValor(1, valorX1, valorY1)==true){
                           dispara(1, valorX1, valorY1);
                           num_disp1++;
                           imprimirTableroPropio(1);
                           printf("\n");
                           imprimirTableroRival(2);
                           if(comprobante(1, valorX1, valorY1)==0){
                              sprintf(buffer, "+Ok. AGUA: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }  
                           else if(comprobante(1, valorX1, valorY1)==1){
                              sprintf(buffer, "+Ok. TOCADO: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }
                           else if(comprobante(1, valorX1, valorY1)==2){
                              sprintf(buffer, "+Ok. HUNDIDO: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }                                                                     
                           for (int i=0; i<=9; i++){
                              sprintf(buffer + strlen(buffer), "%d|", i);
                              for(int j=0; j<=9; j++){
                                 if(j<=8){
                                    sprintf(buffer + strlen(buffer), "%c|", imprimirLetraTablero4(i, j));
                                 }
                                 else{
                                    sprintf(buffer + strlen(buffer), "%c\n", imprimirLetraTablero4(i, j));
                                 }
                              }
                           }  
                           
                           send(i, buffer, sizeof(buffer), 0);
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                           if(compruebaGanador1()==true){
                              sprintf(buffer, "+Ok. Jugador %s ha ganado la partida con %d disparos.\n", gameManager->getName(i), num_disp1);
                              send(i, buffer, sizeof(buffer), 0);
                              send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                              gameManager->deleteGame(i);
                           }            
                        }
                        else if(i%2!=0 && comprobarValor(2, valorX1, valorY1)==true){
                           dispara(2, valorX1, valorY1);
                           num_disp2++;
                           imprimirTableroPropio(2);
                           printf("\n");
                           imprimirTableroRival(1);
                           if(comprobante(2, valorX1, valorY1)==0){
                              sprintf(buffer, "+Ok. AGUA: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }  
                           else if(comprobante(2, valorX1, valorY1)==1){
                              sprintf(buffer, "+Ok. TOCADO: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }  
                           else if(comprobante(2, valorX1, valorY1)==2){
                              sprintf(buffer, "+Ok. HUNDIDO: %d %c\n\n-|A|B|C|D|E|F|G|H|I|J\n", valorX1, letraY1);
                           }   
                           for (int i=0; i<=9; i++){
                              sprintf(buffer + strlen(buffer), "%d|", i);
                              for(int j=0; j<=9; j++){
                                 if(j<=8){
                                    sprintf(buffer + strlen(buffer), "%c|", imprimirLetraTablero3(i, j));
                                 }
                                 else{
                                    sprintf(buffer + strlen(buffer), "%c\n", imprimirLetraTablero3(i, j));
                                 }
                              }
                           }
                           send(i, buffer, sizeof(buffer), 0);
                           send(gameManager->findPair(i), buffer, sizeof(buffer), 0);   
                           if(compruebaGanador2()==true){
                                 sprintf(buffer, "+Ok. Jugador %s ha ganado la partida con %d disparos.\n", gameManager->getName(i), num_disp2);
                                 send(i, buffer, sizeof(buffer), 0);
                                 send(gameManager->findPair(i), buffer, sizeof(buffer), 0);
                                 gameManager->deleteGame(i);
                           }       
                        }  
                        else{
                           sprintf(buffer, "-Err. Debe seleccionar otra casilla no seleccionada anteriormente.\n");
                           send(i, buffer, sizeof(buffer), 0);
                        }                     
                  }

                  //Si el cliente introdujo CTRL+C
                  if (recibidos == 0){
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
