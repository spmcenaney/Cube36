//tower.h
#ifndef TOWER_H
#define TOWER_H

#include "main.h"
#include <cstdlib>

using namespace std;

class tower;       //forward declaration of tower
//class Utilities;

class tower {
  public:
    //Purpose: Default constructor for tower
    //Pre:
    //Post: initializes to no color, size 0, and unused
    tower();
    //Purpose: copy constructor for tower
    //Pre: a tower
    //Post: initializes to t color, size of t, and unused
    tower(const tower &t);
    //Purpose: copy tower
    //Pre: a tower
    //Post: initializes to t color, size of t, and t available
    void copyTower(const tower &t);
    //Purpose: Init tower
    //Pre:  color and height of tower
    //Post: sets tower to available
    void initTower(colors c, int s);
    //Purpose: Getter for color
    //Pre: Nothing required
    //Post: Returns color of tower
    colors getColor() {return m_color;}
    //Purpose: Getter for size
    //Pre: Nothing required
    //Post: Returns size of tower
    int getSize() {return m_size;}
    //Purpose: Getter for use
    //Pre: Nothing required
    //Post: Returns availability
    bool available() {return !m_used;}
    //Purpose: Use tower
    //Pre: Nothing required
    //Post: marks tower as used
    void addTower();
    //Purpose: Remove tower
    //Pre: Nothing required
    //Post: marks tower as availabe
    void removeTower();
  private:
    colors m_color;
    int m_size;
    bool m_used;
};
#endif