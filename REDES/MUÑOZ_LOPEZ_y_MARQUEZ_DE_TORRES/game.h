#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>


class Game{
    private:
        int socketPlayer1_;
        int socketPlayer2_;
        int numberOfPlayers_;

    public:
        Game(){
            numberOfPlayers_ = 0;
        }

        inline int getSocketPlayer1() { return socketPlayer1_; }
        inline int getSocketPlayer2() { return socketPlayer2_; }

        inline int getNumberOfPlayers() { return numberOfPlayers_; }

        inline void setSocketPlayer1(int socketPlayer1) { socketPlayer1_ = socketPlayer1; }
        inline void setSocketPlayer2(int socketPlayer2) { socketPlayer2_ = socketPlayer2; }

        inline void setNumberOfPlayers(int numberOfPlayers) { numberOfPlayers_ = numberOfPlayers; }

        bool addPlayer(int socketPlayer);
};

#endif