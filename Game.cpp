#ifndef GAME_CPP
#define GAME_CPP

#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
#include <vector>
#include <string>
#include "Character.cpp"
#include "Player.cpp"
#include <algorithm>
#include <limits>
#include <unistd.h>

class Game{
    public:
    
        void Play(){
            while(true){
                next:
                int option;
                cout << "\n1. Play\n2. Exit\nEnter option : ";

                // checks for only int input
                while(!(cin >> option)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n***** Wrong input *****\n";
                    goto next;
                }

                // main menu of game
                switch(option){
                    case 1:
                        PlayGame();
                        break;
                    case 2:
                        return;
                    default:
                        cout << "\n***** Wrong input *****\n";
                        break;
                }
            }
        }


        void PlayGame(){
            WalkableCharacter wc1("Knight","Sword",60,10,1,1);
            WalkableCharacter wc2("Goblin","Orcrist",60,20,1,1);
            WalkableCharacter wc3("Lumberjack","Axe",50,25,1,1);
            WalkableCharacter wc4("Barbarians","Battle Axe",80,40,1,1);
            WalkableCharacter wc5("Archer","Bow & Arrow",50,20,4,1);
            WalkableCharacter wc6("Bomb Thrower","Bomb",50,100,2,1);
            WalkableCharacter wc7("Dart Goblin","Crown Tower arrows",60,20,3,1);
            FlyableCharacter fc1("Dragon","Fire",100,30,2,2);
            FlyableCharacter fc2("Flying Witch","Magic Spells",80,40,2,2);
            FlyableCharacter fc3("Death","Soul",100,30,1,4);
            SpecialCharacter sc1("Heat Spirit","Flamethrower",200,50,2,INT_MAX-100,"Lava",150);
            SpecialCharacter sc2("Ice Spirit","Ice Daggers",200,50,2,INT_MAX-100,"Ice Crusher",150);
            SpecialCharacter sc3("King","Royal Sword",500,50,1,INT_MAX-100,"Death Sword",200);

            vector<Character*> characters_list {&wc1,&wc2,&wc3,&wc4,&wc5,&wc6,&wc7,&fc1,&fc2,&fc3,&sc1,&sc2,&sc3};

            Player player("Player"); // player1
            Player computer("Computer"); // player2

            Random_Characters(player, computer, characters_list);

            // making playable area
            int playable_area_size = 35;
            Character* playable_area[playable_area_size];
            Ground ground(" - ");
            for(int index = 0; index < playable_area_size; index++){
                playable_area[index] = &ground;
            }

            cout << "***** Game Started *****";

            while(true){
                DisplayPlayableArea(playable_area,playable_area_size);


                // displays randomly selected characters of both players
                cout << player.get_name() << " : ";
                DisplayCharacters(player.playerCharacters);
                cout << computer.get_name() << " : ";
                DisplayCharacters(computer.playerCharacters);


                // checks weather player is lost or not
                if((player.playerCharacters).size()==0){
                    cout << "\n*****Game Over*****\n";
                    break;
                }

                // checks weather player is won or not
                if((computer.playerCharacters).size()==0){
                    cout << "\n*****You Won*****\n";
                    break;
                }


                next:
                int choice;
                cout << "Select your player : ";

                // checks for only int input
                while(!(cin >> choice)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n***** Wrong input *****\n";
                    goto next;
                }

                // checks for valid index of player's character list
                if(choice < 0 || choice >= player.playerCharacters.size()){
                    cout << "\n***** Wrong input *****\n";
                    continue;
                }
                
                // else select random computer to fight with selected player character
                else {
                    srand(time(0));
                    int random = rand() % player.playerCharacters.size();
                    Fight(player,computer,(player.playerCharacters[choice]),(computer.playerCharacters[random]),playable_area,playable_area_size,ground);
                }
            }
        }


        // fight between two characters
        void Fight(Player &player1, Player &player2, Character* player1character, Character* player2character, Character* playable_area[], int playable_area_size, Ground &ground){
            cout << "\n" << player1.get_name() <<" selected : " << (*player1character).get_name();
            cout << "\n" << player2.get_name() << " selected : " << (*player2character).get_name();


            // both index used for spawning both character at their respective side of playable area
            int player_index = 1;
            playable_area[player_index] = player1character;
            int computer_index = playable_area_size - 2;
            playable_area[computer_index] = player2character;

            while(true){
                usleep(400000); // delay of 0.4 sec

                cout << "\n";
                DisplayPlayableArea(playable_area, playable_area_size);
                cout << "\n--> " << player1.get_name() << " Character's Health: " << (*player1character).get_health() << "\n--> " << player2.get_name() << " Character's Health: " << (*player2character).get_health();


                // checks weather player1's character dead or not
                if((*player1character).get_health() <= 0){
                    cout << "\n*****" << player1.get_name() << "'s Character is dead*****";
                    playable_area[player_index] = &ground;
                    playable_area[computer_index] = &ground;
                    player1.playerCharacters.erase(remove(player1.playerCharacters.begin(), player1.playerCharacters.end(), player1character), player1.playerCharacters.end());
                    return;
                }
                

                // checks weather player2's character dead or not
                if((*player2character).get_health() <= 0){
                    cout << "\n*****" << player2.get_name() << "'s Character is dead*****";
                    playable_area[player_index] = &ground;
                    playable_area[computer_index] = &ground;
                    player2.playerCharacters.erase(remove(player2.playerCharacters.begin(), player2.playerCharacters.end(), player2character), player2.playerCharacters.end());
                    return;
                }


                // desides which character attack first by its level
                if((*player1character).get_level()>=(*player2character).get_level()){
                    Forward_Attack(player1character,player2character, playable_area, playable_area_size, player_index, computer_index, ground);
                    if((*player2character).get_health() > 0){
                        Backward_Attack(player2character,player1character, playable_area, playable_area_size, computer_index, player_index, ground);
                    }
                } else {
                    Backward_Attack(player2character,player1character, playable_area, playable_area_size, computer_index, player_index, ground);
                    if((*player1character).get_health() > 0){
                        Forward_Attack(player1character,player2character, playable_area, playable_area_size, player_index, computer_index, ground);
                    }
                }
            }
        }


        // attack from left to right
        void Forward_Attack(Character* player1character,Character* player2character, Character* playable_area[], int playable_area_size, int &player_index, int &computer_index, Ground &ground){
            if(player_index < computer_index){

                // attacks opponent
                if((player_index + (*player1character).get_range()) >= computer_index){
                    (*player1character).Attack((player2character));
                }

                // move beside opponent
                else if((player_index + (*player1character).get_speed()) >= computer_index){
                    playable_area[computer_index - 1] = playable_area[player_index];
                    playable_area[player_index] = &ground;
                    player_index = computer_index - 1;
                    (*player1character).Move();
                }

                // move at its speed
                else{
                    playable_area[player_index + (*player1character).get_speed()] = playable_area[player_index];
                    playable_area[player_index] = &ground;
                    player_index += (*player1character).get_speed();
                    (*player1character).Move();
                }
            }
        }
        
        
        // attack from right to left
        void Backward_Attack(Character* player2character,Character* player1character, Character* playable_area[], int playable_area_size, int &computer_index, int &player_index, Ground &ground){
            if(computer_index > player_index){

                // attacks opponent
                if((computer_index - (*player2character).get_range()) <= player_index){
                    (*player2character).Attack((player1character));
                }

                // move beside opponent
                else if((computer_index - (*player2character).get_speed()) <= player_index){
                    playable_area[player_index + 1] = playable_area[computer_index];
                    playable_area[computer_index] = &ground;
                    computer_index = player_index + 1;
                    (*player2character).Move();
                }

                // move at its speed
                else{
                    playable_area[computer_index - (*player2character).get_speed()] = playable_area[computer_index];
                    playable_area[computer_index] = &ground;
                    computer_index -= (*player2character).get_speed();
                    (*player2character).Move();
                }
            }
        }

        // assign random characters to both player
        void Random_Characters(Player &player1, Player &player2, vector<Character*> characters_list){
            srand(time(0));
            int random;

            // assign 4 random characters in player1 character_list
            for(int player1_count = 0; player1_count<4;){
                random = rand() % 13;
                if(!(find(player1.playerCharacters.begin(), player1.playerCharacters.end(), characters_list[random]) != player1.playerCharacters.end())){
                    player1.playerCharacters.push_back(characters_list[random]);
                    player1_count++;
                }
            }

            // assign 4 random characters in player2 character_list
            for(int player2_count = 0; player2_count<4;){
                random = rand() % 13;
                if(!(find(player2.playerCharacters.begin(), player2.playerCharacters.end(), characters_list[random]) != player2.playerCharacters.end()) && !(find(player1.playerCharacters.begin(), player1.playerCharacters.end(), characters_list[random]) != player1.playerCharacters.end())){
                    player2.playerCharacters.push_back(characters_list[random]);
                    player2_count++;
                }
            }
        }


        // display playable character list of any player
        void DisplayCharacters(vector<Character*> characters_list){
            for(int index = 0; index < characters_list.size(); index++){
                cout << index << "-" << characters_list[index]->get_name() << "(" << characters_list[index]->get_health() << ")" << "  ";
            }
            cout << endl;
        }


        // display playable area (playing field)
        void DisplayPlayableArea(Character* playable_area[], int size){
            cout << "\n[ ";
            for(int index = 0; index < size; index++){

                // prints ground (" - ")
                if(playable_area[index]->get_name() == " - "){
                    cout << playable_area[index]->get_name();
                }

                // prints playing charcter (playing character name)
                else{
                    cout << "[" << playable_area[index]->get_name() << "(" << playable_area[index]->get_health() << ")]";
                }
            }
            cout << " ]\n" << endl;
        }
};

#endif