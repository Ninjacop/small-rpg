// attack.cpp
// Teegan Lutze
#include "attack.h"

// Attack constructor -- sets up ubound placeholder attack
Attack::Attack() {
    name = "UNBOUND";
    type = ATTACK_UNBOUND;
    phy_damage = 0;
    mag_damage = 0;
    crit = 0;
}

// Attack constructor -- sets up a certain attack with a name, type, damage, and crit chance
Attack::Attack(std::string atkname, attackTypes atktype, int phydmg, int magdmg, int critchance) {
    name = atkname;
    type = atktype;
    phy_damage = phydmg;
    mag_damage = magdmg;
    crit = critchance;
}