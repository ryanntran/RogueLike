// Game.cpp

#include "Game.h"
#include "Dungeon.h"
#include "utilities.h"
#include "Actors.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game() {
    m_dungeon = new Dungeon();
    m_dungeon->setGoblinSmell(15);
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(0, 17);
        cPlayer = randInt(0, 69);
    } while (m_dungeon->getCellStatus(rPlayer,cPlayer) != EMPTY);
    m_dungeon->addPlayer(rPlayer, cPlayer);
}

Game::Game(int goblinSmellDistance)
{
    m_dungeon = new Dungeon();
    m_dungeon->setGoblinSmell(goblinSmellDistance);
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(0, 17);
        cPlayer = randInt(0, 69);
    } while (m_dungeon->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_dungeon->addPlayer(rPlayer, cPlayer);
}

Game::~Game() {
    delete m_dungeon;
}

void Game::play()
{
    m_dungeon->display("");
    Player* player = m_dungeon->player();


    while (!(player->getHp() <= 0) && !m_dungeon->getWin()) {
        char input = getCharacter();
        switch (input) {
        case 'q':
            return;
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case 'c':
        case 'g':
        case 'i': {
            player->playerMoves(input);
            break;
        }
        case 'w': {
            m_dungeon->showInventory();
            char wieldinput = getCharacter();
            m_dungeon->wieldWeapon(wieldinput);
            player->playerMoves(input);
            break;
        }
        case 'r': {
            m_dungeon->showInventory();
            char scrollinput = getCharacter();
            m_dungeon->readScroll(scrollinput);
            player->playerMoves(input);
            break;
        }
        case '>': {
            player->playerMoves(input);
            break;
        }
        default:
            player->playerMoves(input);
            break;
        }
    }
    if (player->getHp() <= 0) {
        cout << "You lose." << endl << "Press q to exit game." << endl;
        while (getCharacter() != 'q') {
        }
        return;
    }
    else if (m_dungeon->getWin()) {
        cout << "Congratulations, you won!" << endl << "Press q to exit game." << endl;
        while (getCharacter() != 'q') {
        }
        return;
    }
    else {
        cout << "You lose." << endl << "Press q to exit game." << endl;
        while (getCharacter() != 'q') {
        }
        return;
    }
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
