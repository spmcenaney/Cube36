//cube.h
#ifndef CUBE_H
#define CUBE_H

#include "tower.h"
#include "Utilities.h"
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
//using namespace std;

class cube;
class Utilities;

class cube {
  public:
    //Purpose: Default constructor for the cube
    //Pre:
    //Post: initilized towers and positions
    cube();
    //Purpose: constructor for the cube
    //Pre:
    //Post: copies towers and initilized matrix
    cube(const cube &c);

    //Purpose: copy cube
    //Pre:
    //Post: copies towers and matrix of cube
    void copyCube(const cube &c);

    //Purpose: return amount of toweres scored in cube
    //Pre:
    //Post: returns tower count
    int score();

    //Purpose: function to test functions
    //Pre:
    //Post: retruns string of current cube
    string test();

    //Purpose: step 1 of EC; remove towers for mutation
    //Pre: amount of towers to remove
    //Post: removes random towers from current cube
    void removeRandomTowers(int num = 10);

    //Purpose: adds specific towers to cube
    //Pre: string of cube and cube
    //Post: adds tower to current cube
    void addTowers(string s, const cube &c);

    //Purpose: adds new towers generally after random towers removed
    //Pre: generally removes random towers first
    //Post: adds new towers to create new mutation
    void addNewTowers();

    //Purpose: clears cube of towers
    //Pre:
    //Post: clears cube towers
    void clearTowers();

    //Purpose: print towers is used or available
    //Pre:
    //Post: prints U or N or used or not
    void printTowers();
    //Purpose: returns cube in string form
    //Pre:
    //Post: returns cube in string form
    string printString();
    //Purpose: print matrix
    //Pre:
    //Post: print matrix of cube
    void printMatrix();

  private:
    const int m_cube_levels[6][6] = {
    1,3,4,5,2,0,
    2,5,0,4,1,3,
    0,1,3,2,5,4,
    5,4,1,3,0,2,
    4,2,5,0,3,1,
    3,0,2,1,4,5
    };

    char colSym[9] = {' ','R','O','Y','G','B','P','o','y'};

    char m_matrix[6][6] = {};

    tower m_towers[6][6];

    void createTowers();
    void initTowerPos();
    void placeTowers();

    int countTowers();
    
    bool checkValid(colors c, int row, int col);

};
#endif