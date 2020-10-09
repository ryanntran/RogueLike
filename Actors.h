#ifndef ACTORS_H
#define ACTORS_H

#include <iostream>
#include "utilities.h"
#include "Game.h"
#include "GameObjects.h"
#include "Dungeon.h"
using namespace std;

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;

const int GOBLIN = 101;
const int SNAKEWOMAN = 102;
const int BOGEYMAN = 103;
const int DRAGON = 104;

class Dungeon;

class Actor {
public:
	Actor(Dungeon* level, int row, int col, int hp, int str, int dex, int arm, int sleep, string name) :
		m_dungeon(level),
		m_row(row),
		m_col(col),
		hitPoints(hp),
		strength(str),
		dexerity(dex),
		armor(arm),
		sleeptime(sleep),
		m_name(name)

	{}
	
	virtual ~Actor() { delete m_weapon; }

	void playerMoves(char move);

	// Setter Functions
	void setHp(int x);
	void setStr(int x);
	void setDex(int x);
	void setArmor(int x);
	void setSleep(int x);
	void setRow(int x);
	void setCol(int x);
	void setWeapon(Weapon* x);
	void readScroll(Scroll* x);
	
	// Getter Functions
	int getHp() const;
	int getStr() const;
	int getDex() const;
	int getArmor() const;
	int getSleep() const;
	int getRow() const;
	int getCol() const;
	Weapon* getWeapon() const;
	string getName() const;

private:
	int hitPoints;	// 0-99
	int strength;
	int dexerity;
	int armor;
	int sleeptime;	// 0-9
	int m_row;		// Position
	int m_col;
	Weapon* m_weapon;
	Dungeon* m_dungeon;
	string m_name;

	// Item weapon;
};

class Player : public Actor {
public:
	Player(Dungeon* game, int r, int c) : Actor(game, r, c, 20, 2, 2, 2, 0, "Player") {
		Weapon* initial = new ShortSword();
		setWeapon(initial);
		inventory.push_back(initial);
	}
	virtual ~Player() {
		for (list<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); ) {
			if ((*it) != nullptr && (*it) != getWeapon()) {
				delete (*it);
				it = inventory.erase(it);
			}
			else
				it++;
		}
	}
	
	void setMaxHP(int x);
	void increaseMaxHP(int x);
	int getMaxHP() const;

	list<GameObject*>& getInventory();

private:
	int maxHP = 20;
	list<GameObject*> inventory;
};

class Monster : public Actor 
{
public:
	Monster(Dungeon* ap, int r, int c, int hitP, int str, int dext, int armP, int sleepT, string name) :
		 Actor(ap, r, c, hitP, str, dext, armP, sleepT, name) {}

private:

};

	class Bogeyman : public Monster {
	public:
		Bogeyman(Dungeon* ap, int row, int col) : 
			Monster(ap, row, col, randInt(5, 10), randInt(2, 3), randInt(2, 3), 2, 0, "the Bogeyman") {
			Weapon* initial = new ShortSword();
			setWeapon(initial);
		}
		virtual ~Bogeyman() {}

	};

	class Snakewoman : public Monster {
	public:
		Snakewoman(Dungeon* ap, int row, int col) : 
			Monster(ap, row, col, randInt(3, 6), 2, 3, 3, 0, "the Snakewoman") {
			Weapon* initial = new MagicFangs();
			setWeapon(initial);
		}
		virtual ~Snakewoman() {}
	};

	class Dragon : public Monster {
	public:
		Dragon(Dungeon* ap, int row, int col) : 
			Monster(ap, row, col, randInt(20, 25), 4, 4, 4, 0, "the Dragon") {
			Weapon* initial = new LongSword();
			setWeapon(initial);
			setMaxHP(getHp());
		}
		virtual ~Dragon() {}

		void setMaxHP(int x) { maxDragHP = x; }
		int getMaxHP() { return maxDragHP; }

	private:
		int maxDragHP;
	};

	class Goblin : public Monster {
	public:
		Goblin(Dungeon* ap, int row, int col) : 
			Monster(ap, row, col, randInt(15, 20), 3, 1, 1, 0, "the Goblin") {
			Weapon* initial = new ShortSword();
			setWeapon(initial);
		}
		virtual ~Goblin() {}

	};

#endif 