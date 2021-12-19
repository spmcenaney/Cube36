//Cube.cpp
#include "cube.h"

cube::cube() {           // default constructor
  createTowers();
  initTowerPos();
}
cube::cube(const cube &c) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      m_matrix[i][j] = c.m_matrix[i][j];
      m_towers[i][j] = c.m_towers[i][j];
    }
  }
  //createTowers();
  //initTowerPos();
}

void cube::copyCube(const cube &c) {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      m_matrix[i][j] = c.m_matrix[i][j];
      m_towers[i][j].copyTower(c.m_towers[i][j]);
    }
  }
  //createTowers();
  //initTowerPos();
}

int cube::score() {
  return countTowers();
}

string cube::test() {
  createTowers();
  initTowerPos();
  //printMatrix();
  //cout << countTowers() << endl << endl;
  return printString();
}

void cube::createTowers() {
  for (int c = RED; c <= PURPLE; c++) {
    for (int s = 1; s <= 6; s++) {
      m_towers[c-1][s-1].initTower(static_cast<colors>(c),s);
    }
  }
}

void cube::initTowerPos() {
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      m_matrix[row][col] = colSym[EMPTY];
    }
  }
  placeTowers();
}

void cube::addTowers(string s, const cube &c) {
  char ss[36];
  strcpy(ss,s.c_str());
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      m_matrix[i][j] = ss[6*i+j];
      m_towers[i][j].copyTower(c.m_towers[i][j]);
    }
  }
  placeTowers();
}

void cube::addNewTowers() {
  placeTowers();
}

bool cube::checkValid(colors c, int row, int col) {
  for (int i = col + 1; i <= col + 5; i++) {
    if (colSym[c] == toupper(m_matrix[row][i%6])) {
      return false;
    }
  }
  for (int i = row + 1; i <= row + 5; i++) {
    if (colSym[c] == toupper(m_matrix[i%6][col])) {
      return false;
    }
  }
  return true;
}

void cube::clearTowers() {
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
      m_matrix[row][col] = colSym[EMPTY];
      m_towers[row][col].removeTower();
    }
  }
}

void cube::removeRandomTowers(int num) {
  Utilities util;
  int row;
  int col;
  char c;
  int b;
  int index;
  for (int i = 0; i < num;) {
    row = util.randNum(0,5);
    col = util.randNum(0,5);
    c = m_matrix[row][col];
    b = m_cube_levels[row][col];
    char *itr = find(colSym,colSym+6,c);
    index = distance(colSym,itr);
    if (m_matrix[row][col] != colSym[EMPTY]) {
      if (m_matrix[row][col] == colSym[SPECIAL_ORANGE]) {
        //cout << "*****special orange removed: " << 1 << " " << 5 << " from (" << row << "," << col << ")" << endl;
        //m_towers[1][5].removeTower();
        //throw 20;
      } else if (m_matrix[row][col] == colSym[SPECIAL_YELLOW]) {
        //cout << "*****special yellow removed: " << 2 << " " << 4 << " from (" << row << "," << col << ")" << endl;
        //m_towers[2][4].removeTower();
        //throw 20;
      } else {
        //cout << "removed: " << index-1 << " " << 5-b << " from (" << row << "," << col << ")" << endl;
        m_towers[index-1][5-b].removeTower();
        m_matrix[row][col] = colSym[EMPTY];
        i++;
      }
      //m_matrix[row][col] = colSym[EMPTY];
      //i++;
    }
  }
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

string cube::printString() {
  string s = "";
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      s = s + m_matrix[i][j];
    }
  }
  return s;
}

void cube::printTowers() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (m_towers[i][j].available()) {
        cout << "N";
      } else {
        cout << "U";
      }
    }
    cout << endl;
  }
}

int cube::countTowers() {
  int count = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (m_matrix[i][j] != ' ')
      count++;
    }
  }
  return count;
}


void cube::placeTowers() {
  Utilities util;
  int rand;
  int stop;
  int b; // base hieght
  int rowOffset;
  int colOffset;
  /*m_towers[YELLOW-1][4].addTower();
  m_matrix[1][2] = colSym[SPECIAL_YELLOW];
  m_towers[ORANGE-1][5].addTower();
  m_matrix[3][2] = colSym[SPECIAL_ORANGE];*/
  rowOffset = util.randNum(0,5);
  colOffset = util.randNum(0,5);
  for (int r = rowOffset; r < 6 + rowOffset; r++) {
    for (int c = colOffset; c < 6 + colOffset; c++) {
      int row = r%6;
      int col = c%6;
      if (m_matrix[row][col] == colSym[EMPTY]) {
        if((col == 2) && ((row == 1) || (row == 3))) {
          rand = util.randNum(-1,5);
          rand = -1;
        } else {
          rand = util.randNum(0,5);
        }
        stop = rand + 6;
        b = m_cube_levels[row][col];
        do {
          if (rand == -1) { // special case
            if (row == 1) { // yellow special case
              if (m_towers[YELLOW-1][4].available() && checkValid(static_cast<colors>(YELLOW),row,col)) {
                m_towers[YELLOW-1][4].addTower();
                m_matrix[row][col] = colSym[SPECIAL_YELLOW];
                //cout << "yellow special " << row << col << m_matrix[row][col] << endl;
                break;
              }
            } else { // orange special case
              if (m_towers[ORANGE-1][5].available() && checkValid(static_cast<colors>(ORANGE),row,col)) {
                m_towers[ORANGE-1][5].addTower();
                m_matrix[row][col] = colSym[SPECIAL_ORANGE];
                //cout << "orange special " << row << col << m_matrix[row][col] << endl;
                break;
              }
            }
            rand++;
          }
          if (m_towers[rand%6][5-b].available() && checkValid(static_cast<colors>(rand%6+1),row,col)) {
            m_towers[rand%6][5-b].addTower();
            m_matrix[row][col] = colSym[(rand%6)+1];
            break;
          }
          rand++;
        } while (rand < stop);
      }
    }
  }
}