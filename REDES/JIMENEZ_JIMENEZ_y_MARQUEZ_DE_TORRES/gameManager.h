#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "user.h"
#include "game.h"
using namespace std;

class GameManager{
private:    
    inline GameManager() { numberOfGames_ = 0; }
    static GameManager *instance;
    vector<User> users_;
    vector<Game> games_;
    int numberOfGames_;

public:
    static GameManager *getInstance();

    inline vector<User> getUsers() { return users_; }

    inline void setUsers(vector<User> users) { users_ = users; }

    inline void addUser(User user) { users_.push_back(user); }

    bool addGame(Game game);

    int matchUser(int socketPlayer);

    int findPair(int socketPlayer);

    bool nameExist(char *name);
    bool nameExist(const char *name);

    bool logUser(int userSocket, char *name);
    bool logUser(int userSocket, const char *name);

    bool unlogUser(int userSocket);

    bool checkPassword(int userSocket, char *password);
    bool checkPassword(int userSocket, const char *password);

    bool deleteGame(int userSocket);

    Game getGame(int userSocket);

    char *getName(int userSocket);
};

#endif