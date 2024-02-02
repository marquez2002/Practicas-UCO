#ifndef USER_H
#define USER_H

#include <string.h>
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
#include <iostream>
#include <vector>


class User{
    private:
        int userSocket_;
        char name_[250];
        char password_[250];
        bool isWaiting_;

    public:
        User(){
            userSocket_ = -1;
            isWaiting_ = true;
        }

        inline int getUserSocket() { return userSocket_; }

        inline char *getUserName() { return name_; }

        inline char *getUserPassword() { return password_; }

        inline bool getUserStatus() { return isWaiting_; }

        inline void setUserSocket(int userSocket) { userSocket_ = userSocket; }

        inline void setUserName(char *name) { strncpy(name_, name, 250); }
        inline void setUserName(const char *name) { strncpy(name_, name, 250); }

        inline void setUserPassword(char *password) { strncpy(password_, password, 250); }
        inline void setUserPassword(const char *password) { strncpy(password_, password, 250); }

        inline void setUserStatus(bool isWaiting) { isWaiting_ = isWaiting; }
};

#endif