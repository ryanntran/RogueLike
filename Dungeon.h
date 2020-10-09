#ifndef DUNGEON_H
#define DUNGEON_H
#include <iostream>
#include "utilities.h"
#include <list>
#include <queue>
#include <vector>
using namespace std;

const int EMPTY = 100;
const int WALL = 200;
const int ACTOR = 300;

class Actor;
class Monster;
class GameObject;
class Player;



struct Room {
    int height;
    int width;
    int row;
    int col;
};

bool compare(const Room& x, const Room& y);

class Dungeon
{
public:
    /////// Constructor and Destructor ///////
    Dungeon();
    ~Dungeon();

    /////// Creating Dungeon Level Functions ///////
    
    void randomAssign(int& r, int& c);
    void addObjects();
    void setObjects();
    void addMonster();
    void nextLevel(Player* p);
    void clearLevel(Player* p);
    void createGrid();
    bool compare(Room x, Room y);

    ///// Getter Functions
    int     rows() const;
    int     cols() const;
    void    display(string msg);
    int     getCellStatus(int r, int c) const;
    Player* player() const;
    Monster* getMonster(int row, int col);
    int getLevel() const;
    bool getWin() const;

    
    ///// Setter Functions
    bool    addPlayer(int r, int c);
    void    setCellStatus(int r, int c, int status);
    void setLevel(int x);
    void setWin(bool x);

    ///// Game Turn
    void attack(Actor* att, Actor* def);


        // Monsters Turn
    void monstersMove();
    bool smell(Monster* mon, int x);
    char towardsPlayer(int r, int c);
    bool goblinSmell(Monster* mon, int r, int c, int x);
    void setGoblinSmell(int x);
    bool isNext(Monster* it);
    bool isDead(Monster* it);
    void monsterDrop(Monster* x);

        // Players Turn
    void pickUpItem(Player* p);
    void showInventory();
    void wieldWeapon(char a);
    void readScroll(char a);

private:
    // Dungeon Grid
    int     m_grid[18][70];
    int      m_rows;
    int      m_cols;
    bool     win;

    // About Dungeon Level
    int     m_level;
    int m_MonsterAmt;
    int     m_objAmt;
    queue<string> actionLog;

    // Game Objects
    list<GameObject*> m_objects;
   
    // Actors
    Player* m_player;
    list<Monster*> m_monsters;
    queue<char> goblinMap;
    int goblinSmellDist;
};



#endif 