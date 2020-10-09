#include "Actors.h"
#include <iostream>
using namespace std;

// Getter Functions
int Actor::getHp() const { return hitPoints; }
int Actor::getStr() const { return strength; }
int Actor::getDex() const { return dexerity; }
int Actor::getArmor() const { return armor; }
int Actor::getSleep() const { return sleeptime; }
int Actor::getRow() const { return m_row; }
int Actor::getCol() const { return m_col; }
Weapon* Actor::getWeapon() const {
    return m_weapon;
}
string Actor::getName() const {
    return m_name;
}
list<GameObject*>& Player::getInventory() {
    return inventory;
}
int Player::getMaxHP() const {
    return maxHP;
}

// Setter Functions
void Actor::setHp(int x) { hitPoints = x; }
void Actor::setStr(int x) { strength = x; }
void Actor::setDex(int x) { dexerity = x; }
void Actor::setArmor(int x) { armor = x; }
void Actor::setSleep(int x) { sleeptime = x; }
void Actor::setRow(int x) { m_row = x; }
void Actor::setCol(int x) { m_col = x; }
void Actor::setWeapon(Weapon* x) {
    m_weapon = x;
}
void Player::setMaxHP(int x) {
    maxHP = x;
}

void Player::increaseMaxHP(int x) {
    maxHP += x;
}

// ============================

void Actor::playerMoves(char move) {
    Player* player = m_dungeon->player();

    if (player->getSleep() > 0) {
        setSleep(player->getSleep() - 1);
        if (player->getHp() < player->getMaxHP()) {
            int heal = randInt(1, 10);
            if (heal == 1) {
                player->setHp(player->getHp() + 1);
            }
        }
        this->m_dungeon->monstersMove();
        this->m_dungeon->display("");
        return;
    }

    switch (move) {
    case(UP):
    case ARROW_UP: // Moves up
        if (m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == EMPTY) {
            player->setRow(player->getRow() - 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), ACTOR);
            m_dungeon->setCellStatus(player->getRow() + 1, player->getCol(), EMPTY);
        }
        if (m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == BOGEYMAN ||
            m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == DRAGON ||
            m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == GOBLIN ||
            m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == SNAKEWOMAN) {

            if (m_dungeon->getMonster(player->getRow() - 1, player->getCol()) != nullptr) {
                Monster* a = m_dungeon->getMonster(player->getRow() - 1, player->getCol());
                m_dungeon->attack(player, a);
            }
        }

        break;
    case(DOWN):
    case ARROW_DOWN: // Moves down
        if (m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == EMPTY) {
            player->setRow(player->getRow() + 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), ACTOR);
            m_dungeon->setCellStatus(player->getRow() - 1, player->getCol(), EMPTY);
        }
        if (m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == BOGEYMAN ||
            m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == DRAGON ||
            m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == GOBLIN ||
            m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == SNAKEWOMAN) {

            if (m_dungeon->getMonster(player->getRow() + 1, player->getCol()) != nullptr) {
                Monster* a = m_dungeon->getMonster(player->getRow() + 1, player->getCol());
                m_dungeon->attack(player, a);
            }
        }
        break;
    case(LEFT):
    case ARROW_LEFT: // Moves left
        if (m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == EMPTY) {
            player->setCol(player->getCol() - 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), ACTOR);
            m_dungeon->setCellStatus(player->getRow(), player->getCol() + 1, EMPTY);
        }
            if (m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == BOGEYMAN ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == DRAGON ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == GOBLIN ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == SNAKEWOMAN) {

                if (m_dungeon->getMonster(player->getRow(), player->getCol() - 1) != nullptr) {
                    Monster* a = m_dungeon->getMonster(player->getRow(), player->getCol() - 1);
                    m_dungeon->attack(player, a);
                
            
        }
        break;
    case(RIGHT):
    case ARROW_RIGHT: // Moves right
        if (m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == EMPTY) {
            player->setCol(player->getCol() + 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), ACTOR);
            m_dungeon->setCellStatus(player->getRow(), player->getCol() - 1, EMPTY);
        }
            if (m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == BOGEYMAN ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == DRAGON ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == GOBLIN ||
                m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == SNAKEWOMAN) {

                if (m_dungeon->getMonster(player->getRow(), player->getCol() + 1) != nullptr) {
                    Monster* a = m_dungeon->getMonster(player->getRow(), player->getCol() + 1);
                    m_dungeon->attack(player, a);
                }
            }
            break;
    case 'c':
        player->setStr(9);
        player->setMaxHP(50);
        player->setHp(50);
        break;
    case 'g':
        this->m_dungeon->pickUpItem(player);
        break;
    case 'i':
        this->m_dungeon->showInventory();
        getCharacter();
        this->m_dungeon->monstersMove();
        this->m_dungeon->display("");
        return;
    case 'w':
    case 'r':
        this->m_dungeon->monstersMove();
        this->m_dungeon->display("");
        return;
    case '>': {
        this->m_dungeon->nextLevel(player);
        this->m_dungeon->display("");
        return;
    }
    default:
        break;
        }
    }
    if (player->getHp() < player->getMaxHP()) {
        int heal = randInt(1, 10);
        if (heal == 1) {
            player->setHp(player->getHp() + 1);
        }
    }

    this->m_dungeon->monstersMove();
    this->m_dungeon->display("");
}

void Actor::readScroll(Scroll* x) {
    string name = x->getName();
    Player* player = m_dungeon->player();

    if (name == "scroll of teleportation") {
        int rPlayer;
        int cPlayer;
        m_dungeon->setCellStatus(player->getRow(), player->getCol(), EMPTY);
        do
        {
            rPlayer = randInt(0, 17);
            cPlayer = randInt(0, 69);
        } while (m_dungeon->getCellStatus(rPlayer, cPlayer) != EMPTY);
        m_dungeon->player()->setCol(cPlayer);
        m_dungeon->player()->setRow(rPlayer);
        m_dungeon->setCellStatus(player->getRow(), player->getCol(), ACTOR);
    }
    if (name == "scroll of enhance armor") {
        player->setArmor(player->getArmor() + randInt(1, 3));
    }
    if (name == "scroll of strength") {
        player->setStr(player->getStr() + randInt(1, 3));
    }
    if (name == "scroll of enhance health") {
        player->increaseMaxHP(player->getMaxHP() + randInt(3, 8));
    }
    if (name == "scroll of enhance dexterity") {
        player->setDex(player->getDex() + 1);
    }
}