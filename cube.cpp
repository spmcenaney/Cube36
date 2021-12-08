//Cube.cpp
#include "cube.h"
#include<stdio.h>

cube::cube() {           // default constructor
  createTowers();
}
cube::cube(const cube &c) {
  //
}

void cube::test() {
  createTowers();
  initTowerPos();
  printMatrix();
}

void cube::createTowers() {
  for (int c = RED; c <= PURPLE; c++) {
    for (int s = 1; s <= 6; s++) {
      m_towers[c-1][s-1].initTower(static_cast<colors>(c),s);
    }
  }
}

void cube::initTowerPos() {
  Utilities util;
  int rand;
  int stop;
  int b; // base hieght
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      m_matrix[row][col] = colSym[0];
    }
  }
  /*rand = util.randNum(0,5);
      stop = rand + 6;
      b = m_cube_levels[row][col];
      do {
        if (m_towers[rand%6][6-b].available() && checkValid(static_cast<colors>(rand%6+1),row,col)) {
          m_towers[rand%6][6-b].addTower();
          m_matrix[row][col] = colSym[(rand%6)+1];
          break;
        }
         rand++;
      } while (rand < stop);*/
      
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      if((col == 2) && ((row == 0) || (row == 2))) {
        col++;
      }
      rand = util.randNum(0,5);
      stop = rand + 6;
      b = m_cube_levels[row][col];
      do {
        if (m_towers[rand%6][6-b].available() && checkValid(static_cast<colors>(rand%6+1),row,col)) {
          m_towers[rand%6][6-b].addTower();
          m_matrix[row][col] = colSym[(rand%6)+1];
          break;
        }
         rand++;
      } while (rand < stop);
    }
  }
}

bool cube::checkValid(colors c, int row, int col) {
  for (int i = row; i < row + 5; i++) {
    if (colSym[c] == m_matrix[row][i%6]) {
      return false;
    }
  }
  for (int i = col; i < col + 5; i++) {
    if (colSym[c] == m_matrix[i%6][col]) {
      return false;
    }
  }
  return true;
}

void cube::printMatrix() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      cout << m_matrix[i][j];
    }
    cout << endl;
  }
  //cout << endl;
}