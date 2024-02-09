#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <iostream>
using namespace std;
#include <vector>
#include "Character.cpp"

class Player{
    private:
        string name;
    public:
        string get_name(){
            return name;
        }
        vector<Character*> playerCharacters;
        Player(string name){
            this->name = name;
        }
        Player(Player& copy){
            this->name = copy.name;
        }
};

#endif