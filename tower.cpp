//tower.cpp
#include "tower.h"

tower::tower() {           // default constructor
  m_color = EMPTY;
  m_size = 0;
  m_used = false;
}
tower::tower(const tower &t) {
  m_color = t.m_color;
  m_size = t.m_size;
  m_used = false; // may change to be = t.m_used
}

void tower::copyTower(const tower &t) {
  m_color = t.m_color;
  m_size = t.m_size;
  m_used = t.m_used;
}

void tower::initTower(colors c, int s) {
  m_color = c;
  m_size = s;
  m_used = false;
}

void tower::addTower() {
  m_used = true;
}

void tower::removeTower() {
  m_used = false;
}