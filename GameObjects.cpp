#include "GameObjects.h"

//// Getter Functions

string GameObject::getName() {
	return m_name;
}

int GameObject::getCol() {
	return m_col;
}

int GameObject::getRow() {
	return m_row;
}

int Weapon::getDex() {
	return m_dexBonus;
}

int Weapon::getStr() {
	return m_damage;
}

string GameObject::getLog() {
	return m_log;
}


//// Setter Functions

void GameObject::setCol(int c) {
	m_col = c;
}

void GameObject::setRow(int r) {
	m_row = r;
}

void Weapon::setDex(int x) {
	m_dexBonus = x;
}
void Weapon::setStr(int x) {
	m_damage = x;
}

void GameObject::setLog(string x) {
	m_log = x;
}