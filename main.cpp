#include "cube.h"
#include <iostream>
#include <string>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int main() {
  srand(time(0));
  cube c;
  int score;
  int keep = 9;
  int runs = 54;
  //int div = 10;
  int diff[36];
  //while (true) {
  string s = "";
  string strings[keep];
  priority_queue<pair<int,string>> Q;
  pair<int,string> p;
  for (int i = 0; i < keep; i++) {
    s = c.test();
    score = 36 - c.countTowers();
    Q.push(make_pair(score,s));
  }
  for (int i = 0; i < runs - keep; i++) {
    s = c.test();
    score = 36 - c.countTowers();
    if (score < Q.top().first) {
      Q.pop();
      Q.push(make_pair(score,s));
    }
  }
  cout << "sc: " << Q.top().first << endl;

  for (int i = 0; i < 36; i++) {
    diff[i] = 0;
  }
  for (int i = 0; i < keep - 1; i++) {
    strings[keep - i - 1] = Q.top().second;
    //cout << Q.top().first << " " << Q.top().second << endl;
    //cout << "          Y           O" <<endl;
    for (int j = 0; j < 36; j++) {
      diff[j] += strings[keep - i - 1][j];
    }
    Q.pop();
  }
  strings[0] = Q.top().second;
  cout << Q.top().first << " " << Q.top().second << endl;
  //Q.pop();
  c.printMatrix();
  c.removeRandomTowers();
  //c.test();
  cout << endl;
  c.printMatrix();

  while (Q.top().first != 0) {
    Q.pop();
    for (int i = 0; i < runs - keep; i++) {
      c.clearTowers();
      c.addTowers(strings[i%keep]);
      //c.removeRandomTowers(7);
      score = 36 - c.countTowers();
      if (i >= keep) {
        if (score < Q.top().first) {
          Q.pop();
          Q.push(make_pair(score,s));
        }
      } else {
        Q.push(make_pair(score,s));
      }
    }

  for (int i = 0; i < keep - 1; i++) {
      strings[keep - i - 1] = Q.top().second;
      Q.pop();
    }
    strings[0] = Q.top().second;
    c.printMatrix();
    //c.removeRandomTowers(15);
  }
  /*for (int i = 0; i < 36; i++) {
    diff[i] += strings[0][i];
    cout << diff[i] << " ";
  }*/

  //if (Q.top().first == 0)
  //break;
//}
  return 0;
}