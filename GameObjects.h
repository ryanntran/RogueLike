#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include <iostream>
using namespace std;

const int MACE = 0;
const int SHORTSWORD = 1;
const int LONGSWORD = 2;
const int SCROLLARMOR = 3;
const int SCROLLSTR = 4;
const int SCROLLHP = 5;
const int SCROLLDEX = 6;
const int MAGICAXE = 7;
const int MAGICFANGS = 8;
const int SCROLLTELE = 9;
const int STAIRCASE = 10;

class GameObject {
public:
	GameObject(string n, int r, int c, string log) : m_name(n), m_row(r), m_col(c), m_log(log) {};
	GameObject(string n, string log) : m_name(n), m_log(log) {};

	virtual ~GameObject() {}
	
	// Getter functions
	int getRow();
	int getCol();
	string getName();
	string getLog();

	// Setter functions
	void setRow(int r);
	void setCol(int c);
	void setLog(string x);

private:
	string m_name;
	string m_log;
	int m_row;
	int m_col;
};

class Weapon : public GameObject {
public:
	Weapon(int dex, int dmg, string n, int r, int c, string log) : 
		m_dexBonus(dex), m_damage(dmg), GameObject(n, r, c, log){};

	Weapon(int dex, int dmg, string n, string log) : 
		m_dexBonus(dex), m_damage(dmg), GameObject(n, log) {};

	virtual ~Weapon() {}

	// Getter
	int getDex();
	int getStr();

	// Setter
	void setDex(int x);
	void setStr(int x);

private:
	int m_dexBonus;
	int m_damage;
};

	class Mace : public Weapon {
	public:
		Mace(int r, int c) : Weapon(0, 2, "mace", r, c, "swings mace at") {} ;
		Mace() : Weapon(0, 2, "mace", "swings mace at") {};
		virtual ~Mace() {}
	private:
	};

	class ShortSword : public Weapon {
	public:
		ShortSword(int r, int c) : Weapon(0, 2, "short sword", r, c, "slashes short sword at") {};
		ShortSword() : Weapon(0, 2, "short sword", "slashes short sword at") {};
		virtual ~ShortSword() {}
	private:
	};

	class LongSword : public Weapon {
	public:
		LongSword(int r, int c) : Weapon(2, 4, "long sword", r, c, "swings long sword at") {};
		LongSword() : Weapon(2, 4, "long sword", "swings long sword at") {};
		virtual ~LongSword() {}
	private:
	};

	class MagicAxe : public Weapon {
	public:
		MagicAxe(int r, int c) : Weapon(5, 5, "magic axe", r, c, "chops magic axe at") {};
		MagicAxe() : Weapon(5, 5, "magic axe", "chops magic axe at") {};
		virtual ~MagicAxe() {}
	private:
	};

	class MagicFangs : public Weapon {
	public:
		MagicFangs(int r, int c) : Weapon(3, 2, "magic fangs of sleep", r, c, "strikes magic fangs at") {};
		MagicFangs() : Weapon(3, 2, "magic fangs of sleep", "strikes magic fangs at") {};
		virtual ~MagicFangs() {}
	private:
	};

class Scroll : public GameObject {
public:
	Scroll(string n, int r, int c, string log) : GameObject(n, r, c, log) {};
	Scroll(string n, string log) : GameObject(n, log) {};

	virtual ~Scroll() {}
private:
};

	class Teleportation : public Scroll {
	public:
		Teleportation(int r, int c) : Scroll("scroll of teleportation", r, c, "You feel your body wrenched in space and time.") {};
		Teleportation() : Scroll("scroll of teleportation", "You feel your body wrenched in space and time.") {};
		virtual ~Teleportation() {}
	private:

	};

	class ImproveArmor : public Scroll {
	public:
		ImproveArmor(int r, int c) : Scroll("scroll of enhance armor", r, c, "Your armor glows blue.") {};
		ImproveArmor() : Scroll("scroll of enhance armor", "Your armor glows blue.") {};
		virtual ~ImproveArmor() {}
	private:

	};

	class RaiseStrength : public Scroll {
	public:
		RaiseStrength(int r, int c) : Scroll("scroll of strength", r, c, "Your muscles bulge.") {};
		RaiseStrength() : Scroll("scroll of strength", "Your muscles bulge.") {};
		virtual ~RaiseStrength() {}
	private:

	};

	class EnhanceHealth : public Scroll {
	public:
		EnhanceHealth(int r, int c) : Scroll("scroll of enhance health", r, c, "You feel your heart beating stronger.") {};
		EnhanceHealth() : Scroll("scroll of enhance health", "You feel your heart beating stronger.") {};
		virtual ~EnhanceHealth() {}
	private:

	};

	class EnhanceDex : public Scroll {
	public:
		EnhanceDex(int r, int c) : Scroll("scroll of enhance dexterity", r, c, "You feel like less of a klutz.") {};
		EnhanceDex() : Scroll("scroll of enhance dexterity", "You feel like less of a klutz.") {};
		virtual ~EnhanceDex() {}
	private:

	};

class Staircase : public GameObject {
public:
	Staircase() : GameObject("staircase", "") {}
	virtual ~Staircase() {}
};

class goldenIdol : public GameObject {
public:
	goldenIdol() : GameObject("the golden idol", "") {}	
	virtual ~goldenIdol() {}
};

#endif // !GAMEOBJECTS_H
