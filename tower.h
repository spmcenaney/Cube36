//tower.h
#ifndef TOWER_H
#define TOWER_H

#include "main.h"
#include <cstdlib>
//#include <string>
//#include <vector>

using namespace std;

class tower;       //forward declaration of tower
//class Utilities;

class tower {
  public:
    //Purpose: Default constructor for tower
    //Pre:
    //Post:
    tower();
    //Purpose: constructor for tower
    //Pre:
    //Post:
    tower(const tower &t);
    //Purpose: constructor for tower
    //Pre:
    //Post:
    void copyTower(const tower &t);
    //Purpose: Init tower
    //Pre:
    //Post:
    void initTower(colors c, int s);
    //Purpose: Getter for color
    //Pre: Nothing required
    //Post: Returns position
    colors getColor() {return m_color;}
    //Purpose: Getter for size
    //Pre: Nothing required
    //Post: Returns position
    int getSize() {return m_size;}
    //Purpose: Getter for use
    //Pre: Nothing required
    //Post: Returns position
    bool available() {return !m_used;}
    //Purpose: marks tower as used
    //Pre:
    //Post:
    void addTower();
    //Purpose: marks tower as availabe
    //Pre:
    //Post:
    void removeTower();
  private:
    colors m_color;
    int m_size;
    bool m_used;
};
#endif