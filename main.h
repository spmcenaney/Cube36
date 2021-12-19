//main.h
#ifndef MAIN_H
#define MAIN_H

/**
This is to enumerate the tower colors
**/
enum colors {
  EMPTY,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  PURPLE,
  SPECIAL_ORANGE,
  SPECIAL_YELLOW
};

//char colSym[7] = {' ','R','O','Y','G','B','P'};

struct position {          // struct for position
  int X;                   // X coordinate
  int Y;                   // Y coordinate
};

#endif
