#include "cube.h"
#include <iostream>
#include <string>
#include <queue>
#include <bits/stdc++.h>

int main() {
  // CONSTANTS
  int KEEP = 8; // amount of best mutants kept
  int RUNS = 80; // make this multiple of KEEP
  int REMOVE = 9; // amount of towers removed from best cases

  // variables
  cube *c = nullptr; // pointer for cubes
  cube cc; // main copy of cube
  cube ccc; // mutants of main copy
  int score;
  int diff[36];
  string s = "";
  string mutation;
  string original;
  priority_queue<pair<int,cube*>> Q; // mutants
  priority_queue<pair<int,cube*>> Q2; // best copy
  pair<int,string> p;

  srand(time(0));

  // initial runs
  for (int i = 0; i < RUNS; i++) {
    c = new cube();
    score = c->score();
    Q.push(make_pair(score,c));
  }
  
  cout << "score: " << Q.top().first << endl;

  for (int i = 0; i < 36; i++) {
    diff[i] = 0;
  }

  // best of initial runs kept
  for (int i = 0; i < KEEP; i++) {
    cc.copyCube(*Q.top().second);
    Q2.push(Q.top());
    Q.pop();
  }
  
  cout << Q2.top().first << endl << endl;

  while (Q2.top().first != 36) {
    for (int i = 0; i < RUNS - KEEP; i++) { // remove least fit mutants
      Q.pop(); // probably need to do some delete here b/c of liley mem leak
    }
    for (int i = 0; i < KEEP; i++) { // copies 10 best cases and make mutants
      cc.copyCube(*Q2.top().second);
      cout << Q2.top().first << endl;
      cout << "Org " << cc.printString() << endl; // only for reference
      original = cc.printString();
      cc.removeRandomTowers(REMOVE);
      mutation = cc.printString();
      cout << "Mut " << mutation << endl; // only for reference
      for (int j = 0; j < RUNS/KEEP; j++) { // creates mutants
        ccc.copyCube(cc);
        ccc.addNewTowers();
        score = ccc.score();
        Q.push(make_pair(score, new cube(ccc))); // probably creates memory leaks
      }
      Q2.pop();
    }
    for (int i = 0; i < KEEP; i++) {
      cc.copyCube(*Q.top().second);
      Q2.push(Q.top());
      //delete c; // probably fixes mem leaks
      Q.pop();
    }
    cout << "size: " << Q.size() << " " << Q2.size() << endl;
  }
  cc.copyCube(*Q2.top().second);
      cout << Q2.top().first << endl;;
      cout << "final " << cc.printString() << endl;
      cc.printMatrix();
  /*for (int i = 0; i < 36; i++) {
    diff[i] += strings[0][i];
    cout << diff[i] << " ";
  }

  /*for (int i = 0; i < RUNS; i++) {
    delete c;
  }*/
  return 0;
}

    //cout << Q.top().first << " " << Q.top().second << endl;
    //cout << "          Y           O" <<endl;