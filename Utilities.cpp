//Utilites.cpp
#include "Utilities.h"

int Utilities::randNum(const int min, const int max) {    //RNG
  const int NUM_DIS = 1;                       // number displacement
  return min + rand() % (max - min + NUM_DIS); //Random number in range
}
