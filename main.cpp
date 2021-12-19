#include "cube.h"
#include <iostream>
#include <string>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int main() {
  srand(time(0));
  cube *c = nullptr;
  cube cc;
  cube ccc;
  int score;
  int keep = 8;
  int runs = 80;
  int REMOVE = 9;
  int diff[36];
  string s = "";
  string mutation;
  string original;
  priority_queue<pair<int,cube*>> Q;
  priority_queue<pair<int,cube*>> Q2;
  pair<int,string> p;

  // initial runs
  for (int i = 0; i < runs; i++) {
    c = new cube();
    score = c->score();
    Q.push(make_pair(score,c));
  }
  
  cout << "sc: " << Q.top().first << endl;

  for (int i = 0; i < 36; i++) {
    diff[i] = 0;
  }
  // best of initial runs kept
  for (int i = 0; i < keep; i++) {
    cc.copyCube(*Q.top().second);
    //cout << Q.top().first << " " << Q.top().second << endl;
    //cout << "          Y           O" <<endl;
    Q2.push(Q.top());
    Q.pop();
  }
  /*for (int i = 0; i < runs - keep; i++) {
    Q.pop();
  }*/
  //cc.copyCube(Q.top().second);
  //strings[0] = cc.score();
  cout << Q2.top().first << endl;
  //Q.pop();
  //c.printMatrix();
  ////c.removeRandomTowers();
  //c.test();
  cout << endl;
  //c.printMatrix();

  while (Q2.top().first != 36) {
    for (int i = 0; i < runs - keep; i++) {
      Q.pop();
    }
    for (int i = 0; i < keep; i++) {
      //Q.push(Q2.top());
      cc.copyCube(*Q2.top().second);
      cout << Q2.top().first << endl;;
      cout << "Org " << cc.printString() << endl;
      original = cc.printString();
      cc.removeRandomTowers(REMOVE);
      mutation = cc.printString();
      cout << "Mut " << mutation << endl;
      ccc.copyCube(cc);
      for (int j = 0; j < runs/keep; j++) {
        //cc.printTowers();
        cc.clearTowers();
        //cc.printMatrix();
        
        cc.addTowers(mutation,ccc);
        //cc.printMatrix();
        //cc.printTowers();
        //cout << "-------------------" <<endl;
        score = cc.score();
        Q.push(make_pair(score, new cube(cc))); // probably creates memory leaks
      }
      Q2.pop();
    }
    for (int i = 0; i < keep; i++) {
      cc.copyCube(*Q.top().second);
      Q2.push(Q.top());
      //c = &cc;
      //delete c; // probably fixes mem leaks
      Q.pop();
    }
    cout << "size: " << Q.size() << " " << Q2.size() << endl;
    //cc.printMatrix();
    //c.removeRandomTowers(15);
  }
  cc.copyCube(*Q2.top().second);
      cout << Q2.top().first << endl;;
      cout << "final " << cc.printString() << endl;
      cc.printMatrix();
  /*for (int i = 0; i < 36; i++) {
    diff[i] += strings[0][i];
    cout << diff[i] << " ";
  }

  //if (Q.top().first == 0)
  //break;
//}

  /*for (int i = 0; i < runs; i++) {
    delete c;
  }*/
  return 0;
}