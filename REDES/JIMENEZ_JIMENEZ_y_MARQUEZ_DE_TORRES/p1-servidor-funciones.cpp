#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <regex.h>
#include <ctype.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace std;
#include "gameManager.h"


void clear()
{ //Funcion que limpia la terminal en función del sistema operativo que estemos utilizando
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}

void saveSystem()
{
   FILE *f;
   GameManager *gameManager = GameManager::getInstance();
   f = fopen("users.txt", "w");
   char input[512];
   for (int i = 0; i < (int)gameManager->getUsers().size(); i++)
   {
      snprintf(input, 512, "%s,%s\n", gameManager->getUsers()[i].getUserName(), gameManager->getUsers()[i].getUserPassword());
      fputs(input, f);
   }
   fclose(f);
}

void loadSystem(){
   GameManager *gameManager = GameManager::getInstance();
   FILE *f;
   f = fopen("users.txt", "r");
   if (!f)
   {
      std::cout << "Error al abrir el archivo\n";
      EXIT_FAILURE;
   }
   char cadena[512];
   while (fgets(cadena, 512, f) != NULL){
      User user;
      char *aux;
      aux = strtok(cadena, ",");
      user.setUserName(aux);
      aux = strtok(NULL, "\n");
      user.setUserPassword(aux);
      gameManager->addUser(user);
   }
   fclose(f);
}