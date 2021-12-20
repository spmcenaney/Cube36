#include "cube.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <bits/stdc++.h>

#define TRUE 1
#define FALSE 0

int main() {
  // CONSTANTS
  const int KEEP_DIF = 8;
  const int RUNS = 120; // make this multiple of KEEP; amount in queue
  const int REMOVE_MIN = 1; // amount of towers removed from best cases
  const int REMOVE_MAX = 20;
  const int REMOVE_DIF = REMOVE_MAX - REMOVE_MIN + 1;
  const int TESTS = 60; // trials for solving puzz;e
  const int ATTEMPTS = 6; // attempts made in each test to complete puzzle

  // what to print
  bool PRINT_DEBUG = FALSE;
  bool PRINT_BEST = FALSE;
  bool PRINT_ANALYSIS = FALSE;
  bool PRINT_CSV = TRUE;

  // array for amount of towers kept
  int keepers[KEEP_DIF] = {5,10,15,20,24,30,40,60}; // multiples of RUNS

  // variables
  cube *c = nullptr; // pointer for cubes
  cube cc; // main copy of cube
  cube ccc; // mutants of main copy

  int initScore;
  int score;
  int bestScore;

  int averageRuns;
  int countRuns;

  int ECworked = 0;
  int keep;

  // for analysis
  int diff[36]; // was used to comparing output distance of letters
  int bestScores[KEEP_DIF][REMOVE_DIF][6] = {0};
  int totalRuns[KEEP_DIF][REMOVE_DIF][6] = {0};

  // Priority queue sorting highest score first
  priority_queue<pair<int,cube*>> QueMutants; // mutants queue
  priority_queue<pair<int,cube*>> QueBest; // best copy queue

  // randomize
  srand(time(0));

  // loop different amount of towere kept
  for (int kk = 0; kk < KEEP_DIF; kk++) {
    keep = keepers[kk];
    // loop different amounts of towers removed
    for (int remove = REMOVE_MIN; remove <= REMOVE_MAX; remove++) {
      // run multiple trials
      for (int test = 0; test < TESTS; test++) {

        // initial runs to start puzzle
        for (int i = 0; i < RUNS; i++) {
          c = new cube();
          score = c->score();
          QueMutants.push(make_pair(score,c));
        }

        for (int i = 0; i < 36; i++) { // was for anaylsis
          diff[i] = 0;
        }

        // best of initial runs kept
        for (int i = 0; i < keep; i++) {
          cc.copyCube(*QueMutants.top().second);
          QueBest.push(QueMutants.top());
          QueMutants.pop();
        }
        
        bestScore = QueBest.top().first;
        initScore = bestScore;
        if (bestScore < 31) {
          bestScore = 30;
        }
        if (PRINT_DEBUG) {
          cout << "Initial amount: " << initScore << endl;
        }

        /**
         * This is the main loop for running attempts 
         * 
         * Here is where the test runs are attempted to solve the puzzle
         * If the puzzle is not solved in set number of attempts,
         * the test will end and loop back with new initial values
         * 
         * Within this loop, EC is applied. A set number of the runs are kept
         * and used to create mutants. This is done by taking these best cases
         * and modifying them randomly. This is done in two steps:
         * 
         * 1. A set number a random towers are removed from each best case
         * 2. Each best case is filled with random towers for modified "DNA"
         **/
        for (countRuns = 0; countRuns < ATTEMPTS; countRuns++) {
          while (QueBest.top().first > bestScore) {
            totalRuns[kk][remove-REMOVE_MIN][bestScore-30] += countRuns;
            bestScore++;
            ECworked++;
          }
          if (bestScore == 36) {
            break; // exit case for attempts
          }
          for (int i = 0; i < RUNS - keep; i++) { // remove least fit mutants
            delete QueMutants.top().second;
            QueMutants.pop();
          }
          // for loop for mutation
          for (int i = 0; i < keep; i++) { // copies best cases and make mutants
            cc.copyCube(*QueBest.top().second);
            if (PRINT_DEBUG) {
              cout << QueBest.top().first << endl;
              cout << "Org " << cc.printString() << endl; // only for reference
            }
            cc.removeRandomTowers(remove);
            if (PRINT_DEBUG) {
              cout << "Mut " << cc.printString() << endl; // only for reference
            }
            // Note: RUNS must be multiple of keep
            for (int j = 0; j < RUNS/keep; j++) { // creates mutants
              ccc.copyCube(cc); // copy cube made so original be mutated again
              ccc.addNewTowers(); // mutant in filled with modified "DNA"
              score = ccc.score();
              QueMutants.push(make_pair(score, new cube(ccc)));
            }
            delete QueBest.top().second;
            QueBest.pop();
          } // end for loop for mutation

          // loop to keep best mutants (includes originals)
          for (int i = 0; i < keep; i++) {
            cc.copyCube(*QueMutants.top().second);
            QueBest.push(QueMutants.top());
            QueMutants.pop();
          }
        } // end for loop for attempts

        /**
         * This section is for calculations and emptying queues
         * */
        cc.copyCube(*QueBest.top().second);
        score = QueBest.top().first;
        if (PRINT_BEST) {
          cout << "final amount: " << score << endl;;
          cout << "final " << cc.printString() << endl;
          cc.printMatrix();
          cout << endl;
        }
        if (bestScore == initScore) {
          bestScores[kk][remove-REMOVE_MIN][0]++; // used for failed attempts
        } else if (score > 31){
          bestScores[kk][remove-REMOVE_MIN][score-31]++;
        } // I do not need cases with scores less than 31
        
        // loops to empty out queues
        for (int i = 0; i < keep; i++) {
          delete QueBest.top().second;
          QueBest.pop();
        }
        for (int i = 0; i < RUNS - keep; i++) { // removes rest of "junk" "DNA"
          delete QueMutants.top().second;
          QueMutants.pop();
        }

        /*for (int i = 0; i < 36; i++) {
          diff[i] += strings[0][i];
          cout << diff[i] << " ";
        }*/

      }
    }
  }

  /**
   * This section is to print the analysis
   * */
  if (PRINT_ANALYSIS) {
    cout << "For an average of " << TESTS << " tests ";
    cout << "with " << RUNS << " run-throughs ";
    cout << "keeping the best " << keepers[0] << " to " << keepers[KEEP_DIF-1];
    cout << " range of trials ";
    cout << "while removing " << REMOVE_MIN << " to " << REMOVE_MAX;
    cout << " towers at each run;" << endl;
    cout << "The best scores are:" << endl;
    for (int h = 0; h < KEEP_DIF; h++) {
      cout << keepers[h] << ":: ";
      for (int again = 0; again < 2; again++) {
        for (int j = REMOVE_MIN; j <= REMOVE_MAX; j++) {
          cout << "   " << j;
        }
        cout << " | ";
      }
      cout << endl;
      for (int i = 5; i >= 0; i--) {
        cout << " " << i + 31 << ": ";
        for (int j = 0; j < REMOVE_MAX-REMOVE_MIN+1; j++) {
          cout << setw(3) << bestScores[h][j][i] << " ";
        }
        cout << " | ";
        for (int j = 0; j < REMOVE_MAX-REMOVE_MIN+1; j++) {
          if (bestScores[h][j][i] != 0) {
            averageRuns = totalRuns[h][j][i]/bestScores[h][j][i];
          } else {
            averageRuns = 0;
          }
          cout << setw(3) << averageRuns << " ";
        }
        cout << endl;
      }
      cout << "last row includes failed attempts" << endl;
      cout << endl;
    }
    cout << "worked: " << ECworked << endl;

    
  }
  /**
   * This section is to print csv format for graphs
   * */
  if (PRINT_CSV) {
    for (int i = 0; i < KEEP_DIF; i++) {
      for (int j = 0; j < REMOVE_MAX-REMOVE_MIN+1; j++) {
        cout << bestScores[i][j][0] << ",";
      }
      cout << "\n";
    }
  }
  return 0;
}