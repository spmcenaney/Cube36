//main.h
#ifndef MAIN_H
#define MAIN_H

/**
This is to enumerate the directions.
Gets passed into one function below.
**/
enum colors {
  EMPTY,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  PURPLE
};

//char colSym[7] = {' ','R','O','Y','G','B','P'};

struct position {          // struct for position
  int X;                   // X coordinate
  int Y;                   // Y coordinate
};

#endif