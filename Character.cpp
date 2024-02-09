#ifndef CHARACTER_CPP
#define CHARACTER_CPP

#include <iostream>
using namespace std;

class Character{
    protected:
        string name;
        string weapon;
        string special_weapon;
        int health;
        int damage;
        int special_damage;
        int level;
        int range;
        int speed;
        
    public:
        int get_health(){
            return health;
        }
        void set_health(int value){
            this->health = value;
        }

        int get_damage(){
            return damage;
        }
        string get_name(){
            return name;
        }
        string get_weapon(){
            return weapon;
        }
        string get_special_weapon(){
            return special_weapon;
        }
        int get_special_damage(){
            return special_damage;
        }
        int get_range(){
            return range;
        }
        int get_speed(){
            return speed;
        }
        int get_level(){
            return level;
        }

        Character(string name){
            this->name = name;
        }
        
        Character(string name, string weapon, int health, int damage, int range, int speed){
            this->name = name;
            this->weapon = weapon;
            this->health = health;
            this->damage = damage;
            this->range = range;
            this->speed = speed;
        }

        Character(string name, string weapon, int health, int damage, int range, int speed, string special_weapon, int special_damage){
            this->name = name;
            this->weapon = weapon;
            this->special_weapon = special_weapon;
            this->health = health;
            this->damage = damage;
            this->special_damage = special_damage;
            this->range = range;
            this->speed = speed;
        }
        
        Character(Character& copy){
            this->name = copy.name;
            this->weapon = copy.weapon;
            this->special_weapon = copy.special_weapon;
            this->health = copy.health;
            this->damage = copy.damage;
            this->special_damage = copy.special_damage;
            this->range = copy.range;
            this->speed = copy.speed;
        }

        virtual void Move(){};

        virtual void Attack(Character* opponent){
            cout << "\n" << this->name << " Attacks with " << this->weapon << " for damage of " << this->damage << endl;
            GiveDamage(opponent);
        }

        void GiveDamage(Character* opponent){
            cout << "\n" << (*opponent).get_name() << " takes damage. Health : " << (*opponent).get_health() << endl;
            if(((*opponent).get_health()) >= (damage)){
                (*opponent).set_health((*opponent).get_health() - damage);
            } else {
                (*opponent).set_health(0);
            }
        }
};

class Ground : public Character{
    public:
        Ground(string name)
        : Character(name){}
        Ground(Ground& copy) : Character(copy){}
};


class WalkableCharacter : public Character{
    public:
        WalkableCharacter(string name, string weapon, int health, int damage, int range, int speed)
        : Character(name, weapon, health, damage, range, speed){
            level = 1;
        }
        WalkableCharacter(WalkableCharacter& copy) : Character(copy){
            level = 1;
        }
        void Move() override{
            cout << "\n" << this->name << " goes towards enemy by Walking with speed of " << this->speed << endl;
        }
};


class FlyableCharacter : public Character{
    public:
        FlyableCharacter(string name, string weapon, int health, int damage, int range, int speed)
        : Character(name, weapon, health, damage, range, speed){
            level = 2;
        }
        FlyableCharacter(FlyableCharacter& copy) : Character(copy){
            level = 2;
        }
        void Move() override{
            cout << "\n" << this->name << " goes towards enemy by Flying with speed of " << this->speed << endl;
        }
};


class SpecialCharacter : public Character{
    public:
        SpecialCharacter(string name, string weapon, int health, int damage, int range, int speed, string special_weapon, int special_damage)
        : Character(name, weapon, health, damage, range, speed, special_weapon, special_damage){
            level = 3;
        }
        SpecialCharacter(SpecialCharacter& copy) : Character(copy){
            level = 3;
        }
        void Move() override{
            cout << "\n" << this->name << " Teleported towards the enemy" << endl;
        }

        int count = 0;
        void Attack(Character* opponent) override{
            if(count<1){
                if(count==-1){
                    count=0;
                    damage -= special_damage;
                }
                Character::Attack(opponent);
                count++;
            }
            else{
                damage += special_damage;
                count = -1;
                cout << "\n" << this->name << " Attacks with " << this->weapon << " for damage of " << this->damage << endl;
                GiveDamage(opponent);
            }
        }
};

#endif