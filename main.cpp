#include "cube.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <bits/stdc++.h>

#define TRUE 1
#define FALSE 0

#define MULTI 50

int main() {
  // CONSTANTS
  const int KEEP_MIN = 1; // amount of best mutants kept
  const int KEEP_MAX = 12;
  const int KEEP_DIF = KEEP_MAX - KEEP_MIN + 1;
  const int RUNS = 360; // make this multiple of KEEP
  const int REMOVE_MIN = 2; // amount of towers removed from best cases
  const int REMOVE_MAX = 7;
  const int REMOVE_DIF = REMOVE_MAX - REMOVE_MIN + 1;
  const int TESTS = 100;

  bool PRINT_DEBUG = FALSE;
  bool PRINT_BEST = FALSE;
  bool PRINT_ANALYSIS = TRUE;

  int countRuns = 0;

  // variables
  cube *c = nullptr; // pointer for cubes
  cube cc; // main copy of cube
  cube ccc; // mutants of main copy
  int score;
  int diff[36];
  int bestScores[KEEP_DIF][REMOVE_DIF][6] = {0};

  string s = "";
  priority_queue<pair<int,cube*>> Q; // mutants
  priority_queue<pair<int,cube*>> Q2; // best copy
  pair<int,string> p;

  srand(time(0));
  for (int keep = KEEP_MIN; keep <= KEEP_MAX; keep++) {
    if (keep == 7 || keep == 11) {
      keep++;
    }
    for (int remove = REMOVE_MIN; remove <= REMOVE_MAX; remove++) {
      for (int test = 0; test < TESTS; test++) {

        // initial runs
        for (int i = 0; i < RUNS; i++) {
          c = new cube();
          score = c->score();
          Q.push(make_pair(score,c));
        }

        for (int i = 0; i < 36; i++) {
          diff[i] = 0;
        }

        // best of initial runs kept
        for (int i = 0; i < keep; i++) {
          cc.copyCube(*Q.top().second);
          Q2.push(Q.top());
          Q.pop();
        }
        
        if (PRINT_DEBUG) {
          cout << "Initial amount " << Q2.top().first << endl << endl;
        }

        while (Q2.top().first != 36) {
          for (int i = 0; i < RUNS - keep; i++) { // remove least fit mutants
            delete Q.top().second;
            Q.pop(); // probably need to do some delete here b/c of liley mem leak
          }
          for (int i = 0; i < keep; i++) { // copies 10 best cases and make mutants
            cc.copyCube(*Q2.top().second);
            if (PRINT_DEBUG) {
              cout << Q2.top().first << endl;
              cout << "Org " << cc.printString() << endl; // only for reference
            }
            cc.removeRandomTowers(remove);
            if (PRINT_DEBUG) {
              cout << "Mut " << cc.printString()<< endl; // only for reference
            }
            for (int j = 0; j < RUNS/keep; j++) { // creates mutants
              ccc.copyCube(cc);
              ccc.addNewTowers();
              score = ccc.score();
              Q.push(make_pair(score, new cube(ccc))); // probably creates memory leaks
            }
            delete Q2.top().second;
            Q2.pop();
          }
          for (int i = 0; i < keep; i++) {
            cc.copyCube(*Q.top().second);
            Q2.push(Q.top());
            Q.pop();
          }
          countRuns++;
          if (countRuns > 100) {
            break;
          }
        }
        cc.copyCube(*Q2.top().second);
        score = Q2.top().first;
        if (PRINT_BEST) {
          cout << score << endl;;
          cout << "final " << cc.printString() << endl;
          cc.printMatrix();
        }
        if (score < 31) {
          bestScores[keep-KEEP_MIN][remove-REMOVE_MIN][0] = bestScores[keep-KEEP_MIN][remove-REMOVE_MIN][0] + 1;
        } else {
          bestScores[keep-KEEP_MIN][remove-REMOVE_MIN][score-31] = bestScores[keep-KEEP_MIN][remove-REMOVE_MIN][score-31] + 1;
        }
        for (int i = 0; i < keep; i++) {
          delete Q2.top().second;
          Q2.pop();
        }
        for (int i = 0; i < RUNS - keep; i++) { // remove least fit mutants
          delete Q.top().second;
          Q.pop(); // probably need to do some delete here b/c of liley mem leak
        }
        //cout << "size: " << Q.size() << " " << Q2.size() << endl;

        /*for (int i = 0; i < 36; i++) {
          diff[i] += strings[0][i];
          cout << diff[i] << " ";
        }*/

      }
    }
  }

  if (PRINT_ANALYSIS) {
    cout << "For an average of " << TESTS << " tests ";
    cout << "with " << RUNS << " run-throughs ";
    cout << "keeping the best " << KEEP_MIN << " to " << KEEP_MAX << " trials ";
    cout << "while removing " << REMOVE_MIN << " to " << REMOVE_MAX;
    cout << " towers at each run;" << endl;
    cout << "The best scores are:" << endl;
    for (int h = 0; h < KEEP_MAX - KEEP_MIN + 1; h++) {
      if ((h + KEEP_MIN) == 7 || (h + KEEP_MIN) == 11) {
        h++;
      }
      cout << h + KEEP_MIN << ":: ";
      for (int j = REMOVE_MIN; j <= REMOVE_MAX; j++) {
        cout << "   " << j;
      }
      cout << endl;
      for (int i = 5; i >= 0; i--) {
        cout << " " << i + 31 << ": ";
        for (int j = 0; j < REMOVE_MAX-REMOVE_MIN+1; j++) {
          cout << setw(3) << bestScores[h][j][i] << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
    //cout << " (includes less than 30)" << endl;
  }

  return 0;
}

    //cout << Q.top().first << " " << Q.top().second << endl;
    //cout << "          Y           O" <<endl;