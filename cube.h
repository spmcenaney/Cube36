//cube.h
#ifndef CUBE_H
#define CUBE_H

#include "tower.h"
#include "Utilities.h"
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class cube;
class Utilities;

class cube {
  public:
    //Purpose: Default constructor for the ghost
    //Pre:
    //Post:
    cube();
    //Purpose: constructor for the ghost
    //Pre:
    //Post:
    cube(const cube &c);

    void test();

  private:
      const int m_cube_levels[6][6] = {
      1,3,4,5,2,0,
      2,5,0,4,1,3,
      0,1,3,2,5,4,
      5,4,1,3,0,2,
      4,2,5,0,3,1,
      3,0,2,1,4,5
      };

      char colSym[7] = {' ','R','O','Y','G','B','P'};

      char m_matrix[6][6] = {};
      //tower m_cube_spots[6][6];

      tower m_towers[6][6];

    void createTowers();
    void initTowerPos();
    void printMatrix();
    bool checkValid(colors c, int row, int col);

};
#endif