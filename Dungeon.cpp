
#include "Dungeon.h"
#include "utilities.h"
#include "Actors.h"
#include "GameObjects.h"
#include <list>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

/////// Constructor and Destructor ///////

Dungeon::Dungeon() : m_rows(18), m_cols(70), m_level(0), goblinSmellDist(15), win(false)
{
    m_MonsterAmt = randInt(2, 5 * (m_level + 1) + 1);
    m_objAmt = randInt(2, 3);

    createGrid();

    addObjects();
    addMonster();
}

Dungeon::~Dungeon() {
    for (list<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end();) {
        if (*it != nullptr) {
            delete (*it);
            it = m_objects.erase(it);
        }
        else
            it++;

    }
    for (list<Monster*>::iterator it = m_monsters.begin(); it != m_monsters.end(); ) {
        if (*it != nullptr) {
            delete (*it);
            it = m_monsters.erase(it);
        }
        else
            it++;
    }
    delete m_player;
}

void Dungeon::display(string msg)
{
    char displayGrid[18][70];
    int r, c;

    for (r = 0; r < 18; r++) {
        for (c = 0; c < 70; c++) {
            switch (getCellStatus(r, c)) {
            case EMPTY:
                displayGrid[r][c] = ' ';
                break;
            case WALL:
                displayGrid[r][c] = '#';
                break;
            case SCROLLARMOR:
            case SCROLLDEX:
            case SCROLLHP:
            case SCROLLSTR:
            case SCROLLTELE:
                displayGrid[r][c] = '?';
                break;
            case STAIRCASE:
                displayGrid[r][c] = '>';
                break;
            case DRAGON:
                displayGrid[r][c] = 'D';
                break;
            case GOBLIN:
                displayGrid[r][c] = 'G';
                break;
            case SNAKEWOMAN:
                displayGrid[r][c] = 'S';
                break;
            case BOGEYMAN:
                displayGrid[r][c] = 'B';
                break;
            default:
                break;
            }
        }
    }
    // Game Objects
    for (list<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
        if ((*it)->getName() == "short sword" || (*it)->getName() == "mace" || ((*it)->getName() == "magic fangs of sleep")
            || ((*it)->getName() == "long sword") || ((*it)->getName() == "magic axe")) {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = ')';
        }
        else if ((*it)->getName() == "staircase") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '>';
        }
        else if ((*it)->getName() == "the golden idol") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '&';
        }
        else {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '?';
        }
    }

    // Monsters
    for (list<Monster*> ::iterator it = m_monsters.begin(); it != m_monsters.end(); it++) {
        if ((*it)->getName() == "the Goblin") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'G';
        }
        if ((*it)->getName() == "the Snakewoman") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'S';
        }
        if ((*it)->getName() == "the Bogeyman") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'B';
        }
        if ((*it)->getName() == "the Dragon") {
            displayGrid[(*it)->getRow()][(*it)->getCol()] = 'D';
        }
    }


    if (m_player != nullptr) {
        displayGrid[m_player->getRow()][m_player->getCol()] = '@';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < 18; r++)
    {
        for (c = 0; c < 70; c++)
            cout << displayGrid[r][c];
        cout << endl;
    }
    cout << "Dungeon Level: " << getLevel() << ", Hit points: " << m_player->getHp() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStr() << ", Dexterity: " << m_player->getDex();
    cout << endl << endl;

    while (!actionLog.empty()) {
        cout << actionLog.front() << endl;
        actionLog.pop();
    }
}

/////// Creating Dungeon Level Functions ///////

void Dungeon::randomAssign(int& r, int& c) {
    do
    {
        r = randInt(0, 17);
        c = randInt(0, 69);
    } while (getCellStatus(r, c) != EMPTY);
}

bool Dungeon::addPlayer(int r, int c) {
    m_player = new Player(this, r, c);
    setCellStatus(r, c, ACTOR);
    return true;
}

void Dungeon::addObjects() {
    for (int i = 0; i < m_objAmt; i++)
    {
        int randObj = randInt(6);
        switch (randObj) {
        case MACE:
            m_objects.emplace_back(new Mace());
            break;
        case SHORTSWORD:
            m_objects.emplace_back(new ShortSword());
            break;
        case LONGSWORD:
            m_objects.emplace_back(new LongSword());
            break;
        case SCROLLARMOR:
            m_objects.emplace_back(new ImproveArmor());
            break;
        case SCROLLSTR:
            m_objects.emplace_back(new RaiseStrength());
            break;
        case SCROLLHP:
            m_objects.emplace_back(new EnhanceHealth());
            break;
        case SCROLLDEX:
            m_objects.emplace_back(new EnhanceDex());
            break;
        default:
            break;
        }
    }
    if (m_level < 4) {
        m_objects.emplace_back(new Staircase());
    }
    if (m_level == 4) {
        m_objects.emplace_back(new goldenIdol());
    }

    setObjects();
}

void Dungeon::setObjects() {
    for (list<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
        int row, col;
        randomAssign(row, col);
        (*it)->setCol(col);
        (*it)->setRow(row);
    }
}

void Dungeon::addMonster() {
    for (int i = 0; i < m_MonsterAmt; i++) {
        if (m_level == 0 || m_level == 1) {
            int n = randInt(101, 102);
            int r, c;
            do
            {
                r = randInt(0, 17);
                //   cout<< rPlayer<<endl;
                c = randInt(0, 69);
                //  cout<<cPlayer<<endl;
            } while (getCellStatus(r, c) != EMPTY);

            switch (n) {
            case 101:
                m_monsters.emplace_back(new Goblin(this, r, c));
                setCellStatus(r, c, GOBLIN);
                break;
            case 102:
                m_monsters.emplace_back(new Snakewoman(this, r, c));
                setCellStatus(r, c, SNAKEWOMAN);
                break;
            }
        }
        if (m_level == 2) {
            int n = randInt(101, 103);
            int r, c;
            do
            {
                r = randInt(0, 17);
                //   cout<< rPlayer<<endl;
                c = randInt(0, 69);
                //  cout<<cPlayer<<endl;
            } while (getCellStatus(r, c) != EMPTY);

            switch (n) {
            case 101:
                m_monsters.emplace_back(new Goblin(this, r, c));
                setCellStatus(r, c, GOBLIN);
                break;
            case 102:
                m_monsters.emplace_back(new Snakewoman(this, r, c));
                setCellStatus(r, c, SNAKEWOMAN);
                break;
            case 103:
                m_monsters.emplace_back(new Bogeyman(this, r, c));
                setCellStatus(r, c, BOGEYMAN);
                break;
            }
        }
        if (m_level == 3 || m_level == 4) {
            int n = randInt(101, 104);
            int r, c;
            do
            {
                r = randInt(0, 17);
                //   cout<< rPlayer<<endl;
                c = randInt(0, 69);
                //  cout<<cPlayer<<endl;
            } while (getCellStatus(r, c) != EMPTY);

            switch (n) {
            case 101:
                m_monsters.emplace_back(new Goblin(this, r, c));
                setCellStatus(r, c, GOBLIN);
                break;
            case 102:
                m_monsters.emplace_back(new Snakewoman(this, r, c));
                setCellStatus(r, c, SNAKEWOMAN);
                break;
            case 103:
                m_monsters.emplace_back(new Bogeyman(this, r, c));
                setCellStatus(r, c, BOGEYMAN);
                break;
            case 104:
                m_monsters.emplace_back(new Dragon(this, r, c));
                setCellStatus(r, c, DRAGON);
                break;
            }
        }

    }
}

void Dungeon::clearLevel(Player* p) {

    m_level++;              // Increments the dung level

    for (list<Monster*>::iterator it = m_monsters.begin(); it != m_monsters.end(); )
        if (*it != nullptr) {
            delete (*it);
            it = m_monsters.erase(it);
        }
        else
            it++;
    for (list<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); )
        if (*it != nullptr) {
            delete (*it);
            it = m_objects.erase(it);
        }
        else
            it++;

    createGrid();

    m_MonsterAmt = randInt(2, 5 * (m_level + 1) + 1);
    m_objAmt = randInt(2, 3);

    int rPlayer;                                          // Places player
    int cPlayer;
    do
    {
        rPlayer = randInt(0, 17);
        cPlayer = randInt(0, 69);
    } while (getCellStatus(rPlayer, cPlayer) != EMPTY);
    p->setRow(rPlayer);
    p->setCol(cPlayer);
    setCellStatus(p->getRow(), p->getCol(), ACTOR);


    addObjects();           // Add level items and monsters
    addMonster();
}

void Dungeon::nextLevel(Player* p) {
    list<GameObject*>::iterator it = m_objects.begin();
    while (it != m_objects.end()) {
        if ((*it)->getRow() == p->getRow() && (*it)->getCol() == p->getCol()) {
            if ((*it)->getName() == "staircase") {
                clearLevel(p);
                return;
            }
        }
        it++;
    }
    return;
}

void Dungeon::createGrid() {
    int numberOfRooms = randInt(4, 6);
    vector<Room> rooms(numberOfRooms);
    for (int r = 0; r < 18; r++)
        for (int c = 0; c < 70; c++)
            setCellStatus(r, c, WALL);

    for (int i = 0; i < numberOfRooms; ) {
        rooms[i].width = randInt(11, 15);
        rooms[i].height = randInt(6,9);
        rooms[i].row = randInt(1, 18 - rooms[i].height - 1); // Y Coord
        rooms[i].col = randInt(1, 70 - rooms[i].width- 1); // X Coord
        int minX = rooms[i].col;
        int minY = rooms[i].row;
        int maxY = rooms[i].row + rooms[i].height;
        int maxX = rooms[i].col + rooms[i].width;
        // Row and col are the TOP RIGHT of the room

        bool overlap = false;
        if (i > 0) {
            for (int h = 0; h < rooms[i].height; h++)
                for (int w = 0; w < rooms[i].width; w++) {
                    if (getCellStatus(rooms[i].row + h, rooms[i].col + w) == EMPTY) {
                        overlap = true;
                        break;
                    }
                    if (getCellStatus(minY - 1, minX -1) == WALL &&
                        getCellStatus(maxY + 1, minX - 1) == WALL &&
                        getCellStatus(maxY + 1, maxX + 1) == WALL &&
                        getCellStatus(minY - 1, maxX + 1)
                        ) {
                        overlap = true;
                        break; 
                    }
                }
        }
        if (!overlap) {
            for (int h = 1; h < rooms[i].height - 1; h++)
                for (int w = 1; w < rooms[i].width - 1; w++) {
                    setCellStatus(rooms[i].row + h, rooms[i].col + w, EMPTY);
                }
            i++;
        }
    }
    for (int c = 0; c < numberOfRooms - 1; c++)
    {
        int middleRow1 = rooms[c].row + (rooms[c].height / 2);
        int middleRow2 = rooms[c + 1].row + (rooms[c + 1].height / 2);
        int middleCol1 = rooms[c].col + (rooms[c].width / 2);
        int middleCol2 = rooms[c + 1].col + (rooms[c + 1].width / 2);
        if (middleCol1 <= middleCol2 && middleRow1 <= middleRow2)
        {
            for (int d = 0; d < middleCol2 - middleCol1 + 1; d++)
            {
                setCellStatus(middleRow1, d + middleCol1, EMPTY);
            }
            for (int e = 0; e < middleRow2 - middleRow1; e++)
            {
                setCellStatus(middleRow2 - e, middleCol2, EMPTY);
            }
        }
        if (middleCol1 <= middleCol2 && middleRow1 > middleRow2)
        {
            for (int f = 0; f < middleCol2 - middleCol1 + 1; f++)
            {
                setCellStatus(middleRow1, f + middleCol1, EMPTY);
            }
            for (int g = 0; g < middleRow1 - middleRow2; g++)
            {
                setCellStatus(middleRow2 + g, middleCol2, EMPTY);
            }
        }
        if (middleCol1 > middleCol2&& middleRow1 <= middleRow2)
        {
            for (int h = 0; h < middleCol1 - middleCol2 + 1; h++)
            {
                setCellStatus(middleRow2, h + middleCol2, EMPTY);
            }
            for (int i = 0; i < middleRow2 - middleRow1; i++)
            {
                setCellStatus(middleRow1 + i, middleCol1, EMPTY);
            }
        }
        if (middleCol1 > middleCol2&& middleRow1 > middleRow2)
        {
            for (int j = 0; j < middleCol1 - middleCol2 + 1; j++)
            {
                setCellStatus(middleRow2, j + middleCol2, EMPTY);
            }
            for (int k = 0; k < middleRow1 - middleRow2; k++)
            {
                setCellStatus(middleRow1 - k, middleCol1, EMPTY);
            }
        }
    }
}

bool compare(const Room& x, const Room& y) {
    return x.row > y.row;
}

/////// Setter Functions /////////

void Dungeon::setGoblinSmell(int x) {
    goblinSmellDist = x;
}

void Dungeon::setWin(bool x) {
    win = x;
}

void Dungeon::setCellStatus(int r, int c, int status) {
    if (r > 18 || c > 70) {
        return;
    }
    m_grid[r][c] = status;
}

void Dungeon::setLevel(int x) {
    m_level = x;
}

/////// Getter Functions ///////

int Dungeon::rows() const
{
    return m_rows;
}

int Dungeon::cols() const
{
    return m_cols;
}

int Dungeon::getCellStatus(int r, int c) const {
    return m_grid[r][c];
}

int Dungeon::getLevel() const {
    return m_level;
}

Player* Dungeon::player() const {
    return m_player;
}

Monster* Dungeon::getMonster(int row, int col) {
    for (list<Monster*> ::iterator it = m_monsters.begin(); it != m_monsters.end(); it++) {
        if ((*it)->getRow() == row && (*it)->getCol() == col) {
            return *it;
        }
    }
    return nullptr;
}

bool Dungeon::getWin() const {
    return win;
}

/////// Game Turn Functionns ////////

void Dungeon::attack(Actor* att, Actor* def) {
    Weapon* attWep = att->getWeapon();
    string actionLine = "";
    string hit = "";

    if (attWep->getName() != "magic fangs of sleep") {
        int attackerPoints = att->getDex() + attWep->getDex();
        int defenderPoints = def->getDex() + def->getArmor();

        actionLine += (att->getName() + " " + att->getWeapon()->getLog() + " " + def->getName());

        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
            int hpAfterDamage = def->getHp() - randInt(0, att->getStr() + attWep->getStr() - 1);
            def->setHp(hpAfterDamage);
            hit += " and hits.";
        }
        else
            hit += " and missees.";
    }
    else {
        int attackerPoints = att->getDex() + attWep->getDex();
        int defenderPoints = def->getDex() + def->getArmor();

        actionLine += (att->getName() + " " + att->getWeapon()->getLog() + " " + def->getName());

        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
            int hpAfterDamage = def->getHp() - randInt(0, att->getStr() + attWep->getStr() - 1);
            def->setHp(hpAfterDamage);
            hit += " and hits.";

            int sleepChance = (randInt(1, 5));
            if (sleepChance == 1) {
                int sleepTime = (randInt(2, 6));
                hit = " and hits, putting " + def->getName() + " to sleep.";
                if (def->getSleep() > 0) {
                    def->setSleep(max(def->getSleep(), sleepTime));
                }
                else {
                    def->setSleep(sleepTime);
                }
            }
        }
        else {
            hit += " and missees.";
        }
    }
    Monster* b = dynamic_cast<Monster*>(def);
    if (b != nullptr) {
        if (isDead(b)) {
            monsterDrop(b);
            setCellStatus(b->getRow(), b->getCol(), EMPTY);
            list<Monster*>::iterator it = m_monsters.begin();
            while (it != m_monsters.end()) {
                if ((*it) == b) {
                    delete* it;
                    list <Monster*> ::iterator q = m_monsters.erase(it);
                    it = q;
                }
                else
                    it++;
                hit = " dealing a final blow.";
            }
        }
    }
    actionLine += hit;
    actionLog.push(actionLine);
}

    /////// Monster Moves ////////

void Dungeon::monstersMove() {
    for (list<Monster*> ::iterator it = m_monsters.begin(); it != m_monsters.end(); it++) {
        int r = (*it)->getRow();
        int c = (*it)->getCol();
        char dir = '\0';
        if ((*it)->getName() == "the Goblin") {
            if (goblinSmell((*it), r, c, goblinSmellDist)) {
                dir = goblinMap.front();
                goblinMap.pop();
                switch (dir) {
                case ARROW_DOWN:
                    if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                        setCellStatus((*it)->getRow() - 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_UP:
                    if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                        setCellStatus((*it)->getRow() + 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_LEFT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_RIGHT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), GOBLIN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() - 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                }
            }
            queue<char> empty;
            goblinMap.swap(empty);
        }
        if ((*it)->getName() == "the Snakewoman") {
            if (smell((*it), 3)) {
                dir = towardsPlayer(r, c);
                switch (dir) {
                case ARROW_DOWN:
                    if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                        setCellStatus((*it)->getRow() - 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_UP:
                    if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                        setCellStatus((*it)->getRow() + 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_LEFT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_RIGHT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), SNAKEWOMAN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() - 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                }
            }
        }
        if ((*it)->getName() == "the Bogeyman") {
            if (smell((*it), 5)) {
                dir = towardsPlayer(r, c);
                switch (dir) {
                case ARROW_DOWN:
                    if (getCellStatus((*it)->getRow() + 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                        setCellStatus((*it)->getRow() - 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_UP:
                    if (getCellStatus((*it)->getRow() - 1, (*it)->getCol()) == EMPTY) {
                        (*it)->setRow(((*it)->getRow() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                        setCellStatus((*it)->getRow() + 1, (*it)->getCol(), EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_LEFT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() - 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() - 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() + 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                case ARROW_RIGHT:
                    if (getCellStatus((*it)->getRow(), (*it)->getCol() + 1) == EMPTY) {
                        (*it)->setCol(((*it)->getCol() + 1));
                        setCellStatus((*it)->getRow(), (*it)->getCol(), BOGEYMAN);
                        setCellStatus((*it)->getRow(), (*it)->getCol() - 1, EMPTY);
                        break;
                    }
                    if (isNext(*it)) {
                        attack(*it, m_player);
                    }
                    break;
                }
            }
        }
        if ((*it)->getName() == "the Dragon") {
            Dragon* b = dynamic_cast<Dragon*>(*it);
            if (b != nullptr) {
                if (b->getHp() < b->getMaxHP()) {
                    int heal = randInt(1, 10);
                    if (heal == 1) {
                        b->setHp(b->getHp() + 1);
                    }
                }
            }
            if (isNext(*it)) {
                attack(*it, m_player);
            }
        }
    }
}

bool Dungeon::smell(Monster* it, int x) {
    int playerRow = m_player->getRow();
    int playerCol = m_player->getCol();
    int monsterRow = it->getRow();
    int monsterCol = it->getCol();
    int rowDiff = abs(playerRow - monsterRow);
    int colDiff = abs(playerCol - monsterCol);
    int spacesFromPlayer = rowDiff + colDiff;
    if (spacesFromPlayer <= x) {
        return true;
    }
    else {
        return false;
    }
}

char Dungeon::towardsPlayer(int r, int c) {
    int rowP = m_player->getRow();
    int colP = m_player->getCol();
    int rowM = r;
    int colM = c;

    int dRow = rowP - rowM;
    int dCol = colP - colM;

    char dir = '\0';

    // if rowDiff is positive, monster needs to move DOWN
    //    rowDiff    negative,                       UP

    // if colDiff is positive, monster needs to move RIGHT
    //    colDiff    negative                        LEFT

    if (dRow > 0 && dCol >= 0) { //monster is above player and not at same column; needs to move down
        if (dRow >= dCol && dCol != 0) // if player is right of monster, then monster moves right
        {
            if ((getCellStatus(r, c + 1) == WALL))
                dir = ARROW_DOWN;
            else
                dir = ARROW_RIGHT;
        }
        else
        {
            if ((getCellStatus(r + 1, c) == WALL)) //if the row+1 is empty that means we can move right
                dir = ARROW_RIGHT;
            else
                dir = ARROW_DOWN;
        }
    }
    else if (dRow >= 0 && dCol < 0)
    {
        if (dRow >= (-dCol) || dRow == 0)
        {
            if ((getCellStatus(r, c - 1) == WALL))
                dir = ARROW_DOWN;
            else
                dir = ARROW_LEFT;
        }
        else
        {
            if ((getCellStatus(r + 1, c) == WALL))
                dir = ARROW_LEFT;
            else
                dir = ARROW_DOWN;
        }
    }
    else if (dRow < 0 && dCol <= 0)
    {
        if ((-dRow) >= (-dCol) && dCol != 0)
        {
            if ((getCellStatus(r, c - 1) == WALL))
                dir = ARROW_UP;
            else
                dir = ARROW_LEFT;
        }
        else
        {
            if ((getCellStatus(r - 1, c) == WALL))
                dir = ARROW_LEFT;
            else
                dir = ARROW_UP;
        }
    }

    else if (dRow <= 0 && dCol > 0)
    {
        if ((-dRow) >= dCol || dRow == 0)
        {
            if ((getCellStatus(r, c + 1) == WALL))
                dir = ARROW_UP;
            else
                dir = ARROW_RIGHT;
        }
        else
        {
            if ((getCellStatus(r - 1, c) == WALL))
                dir = ARROW_RIGHT;
            else
                dir = ARROW_UP;
        }
    }

    return dir;
}

bool Dungeon::goblinSmell(Monster* it, int r, int c, int goblinDist) {
    int playerRow = m_player->getRow();
    int playerCol = m_player->getCol();

    if (goblinDist < 1) {
        return false;
    }
    if (r == playerRow && c == playerCol) {
        return true;
    }
    // Go south
    if (r < playerRow) {
        if (goblinSmell(it, r + 1, c, goblinDist - 1) && (getCellStatus(r + 1, c) == ACTOR || (getCellStatus(r + 1, c) == EMPTY))) {
            goblinMap.push(ARROW_DOWN);
            return true;
        }
    }
    // Go west
    if (c > playerCol) {
        if (goblinSmell(it, r, c - 1, goblinDist - 1) && (getCellStatus(r, c - 1) == ACTOR || (getCellStatus(r, c - 1) == EMPTY))) {
            goblinMap.push(ARROW_LEFT);
            return true;
        }
    }
    // go north
    if (r > playerRow) {
        if (goblinSmell(it, r - 1, c, goblinDist - 1) && (getCellStatus(r - 1, c) == ACTOR || (getCellStatus(r - 1, c) == EMPTY))) {
            goblinMap.push(ARROW_UP);
            return true;
        }
    }
    // go east
    if (c < playerCol) {
        if (goblinSmell(it, r, c + 1, goblinDist - 1) && (getCellStatus(r, c + 1) == ACTOR || (getCellStatus(r, c + 1) == EMPTY))) {
            goblinMap.push(ARROW_RIGHT);
            return true;
        }
    }
    return false;
}

bool Dungeon::isNext(Monster* it) {
    int mRow = it->getRow();
    int mCol = it->getCol();
    int pRow = m_player->getRow();
    int pCol = m_player->getCol();

    // If monster is directly south of player
    if (mRow + 1 == pRow && mCol == pCol) {
        return true;
    }
    // If monster is directly north of player
    if (mRow - 1 == pRow && mCol == pCol) {
        return true;
    }
    // If monster is directly right of player
    if (mRow == pRow && mCol + 1 == pCol) {
        return true;
    }
    // If monster is directly left of player
    if (mRow == pRow && mCol - 1 == pCol) {
        return true;
    }
    return false;
}

void Dungeon::monsterDrop(Monster* m) {
    string name = m->getName();
    list<GameObject*>::iterator it = m_objects.begin();
    while (it != m_objects.end()) {
        if ((*it)->getRow() == m->getRow() && (*it)->getCol() == m->getCol()) {
            return;
        }
        else
            it++;
    }
    int x;
    if (name == "the Dragon") {
        x = randInt(1, 5);
        switch (x) {
        case 1:
            m_objects.emplace_back(new ImproveArmor(m->getRow(), m->getCol()));
            break;
        case 2:
            m_objects.emplace_back(new EnhanceDex(m->getRow(), m->getCol()));
            break;
        case 3:
            m_objects.emplace_back(new EnhanceHealth(m->getRow(), m->getCol()));
            break;
        case 4:
            m_objects.emplace_back(new RaiseStrength(m->getRow(), m->getCol()));
            break;
        case 5:
            m_objects.emplace_back(new Teleportation(m->getRow(), m->getCol()));
            break;
        default:
            break;
        }
    }
    if (name == "the Snakewoman") {
        x = randInt(1, 3);
        if (x == 1) {
            m_objects.emplace_back(new MagicFangs(m->getRow(), m->getCol()));
        }
    }
    if (name == "the Bogeyman") {
        x = randInt(1, 10);
        if (x == 1) {
            m_objects.emplace_back(new MagicAxe(m->getRow(), m->getCol()));
        }
    }
    if (name == "the Goblin") {
        x = randInt(1, 3);
        if (x == 1) {
            {
                int p = randInt(1, 2);
                switch (p) {
                case 1:
                    m_objects.emplace_back(new MagicFangs(m->getRow(), m->getCol()));
                    break;
                case 2:
                    m_objects.emplace_back(new MagicAxe(m->getRow(), m->getCol()));
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool Dungeon::isDead(Monster* it) {
    if (it->getHp() <= 0) {
        return true;
    }
    else
        return false;
}

    /////// Player Moves ////////

void Dungeon::pickUpItem(Player* p) {
    list<GameObject*>::iterator it = m_objects.begin();
    while (it != m_objects.end()) {
        if ((*it)->getRow() == p->getRow() && (*it)->getCol() == p->getCol()) {
            if ((*it)->getName() == "staircase")
                return;
            if ((*it)->getName() == "the golden idol") {
                string action = "You pick up " + (*it)->getName();
                actionLog.push(action);
                setWin(true);
                return;
            }
            if (p->getInventory().size() > 25) {
                actionLog.push("Your knapsack is full; you can't pick that up.");
                return;
            }
            p->getInventory().push_back(*it);
            Scroll* b = dynamic_cast<Scroll*>(*it);
            if (b != nullptr) {
                string action = "You pick up a scroll called " + b->getName();
                actionLog.push(action);
            }
            else {
                string action = "You pick up a " + (*it)->getName();
                actionLog.push(action);
            }
            it = m_objects.erase(it);
        }
        else
            it++;
    }
}

void Dungeon::showInventory() {
    clearScreen();
    list<GameObject*> inv = m_player->getInventory();
    cout << "Inventory: " << endl;
    char counter = 'a';
    for (list<GameObject*>::iterator it = inv.begin(); it != inv.end(); it++, counter++) {
        cout << counter << ". " << (*it)->getName() << endl;
    }
}

void Dungeon::wieldWeapon(char a) {
    list<GameObject*> inv = m_player->getInventory();
    int answer = a - 'a';
    int w = 0;
    for (list<GameObject*>::iterator it = m_player->getInventory().begin(); it != m_player->getInventory().end(); it++) {
        if (w > answer)
            break;
        if (w == answer) {
            Weapon* b = dynamic_cast<Weapon*>(*it);
            if (b != nullptr) {
                m_player->setWeapon(b);
                string action = "You are wielding " + b->getName();
                actionLog.push(action);
                return;
            }
            else {
                string action = "You can't wield " + (*it)->getName();
                actionLog.push(action);
                return;
            }
        }
        else
            w++;
    }

}

void Dungeon::readScroll(char a) {
    int answer = a - 'a';
    int w = 0;
    for (list<GameObject*>::iterator it = m_player->getInventory().begin(); it != m_player->getInventory().end(); it++) {
        if (w > answer)
            break;
        if (w == answer) {
            Scroll* s = dynamic_cast<Scroll*>(*it);
            if (s != nullptr) {
                m_player->readScroll(s);
                string action = "You read the scroll called " + s->getName();
                actionLog.push(action);
                delete(*it);
                m_player->getInventory().erase(it);
                return;
            }
            else {
                string action = "You can't read a " + (*it)->getName();
                actionLog.push(action);
                return;
            }
        }
        else
            w++;
    }
}
