//
//  aksinha
//  assignment_3.c
//  Assignment 3: finds a list indicating the number of coins of each denomination required 
//  to reach the target value m using the fewest total number of coins.
//
//  Created by Atreya Sinha on 02/18/22.
//  Copyright 2022 Atreya Sinha. All rights reserved.

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/*****************************************************************************************
 * Program is calculating the correct minimum number of coins!                           *
 * only the combinations are different
 * Although I am passing a couple of tests
 * and the ones i am failing, i am still passing some tests inside those tests
 * ***************************************************************************************/

/*****************************************************************************************************
 * target - int - the target amount of money                                                         *
 * coins - vector<int> - a vector of integers representing available coin denominations. Assume that *
 *                       these denominations are sorted from least to greatest                       *
 * return - vector<int> - a vector of integers of the same size as coins representing the number of  *
 *                        each type of coin required to reach the target                             *
 * ***************************************************************************************************/
vector<int> makeChange(int target, vector<int> coins){
    int coins_size {(int) coins.size()};

    // create a two dimensional data structure to keep
    // track of all the possibilites 
    //
    // buffer_c - column
    // buffer_r - row
    vector<int> change(coins_size, 0), buffer_c, buffer_r;
    buffer_c.push_back(0);
    buffer_r.push_back(0);

    // initialize table
    for (int i {1}; i <= target; i++) {
        buffer_c.push_back(INT_MAX - 1);
        buffer_r.push_back(-1);
    }

    // finds the minimum number of coins required using
    // bottom up approach
    for (int i {0}; i < coins_size; i++) {
        for (int j {1}; j <= target; j++) {
            if (j >= coins.at(i)) {
                if (buffer_c.at(j - coins.at(i)) < buffer_c.at(j)) {
                    buffer_c.at(j) = 1 + buffer_c.at(j - coins.at(i));
                    buffer_r.at(j) = i;
                }
            }
        }
    }

    int c_index = (int) buffer_r.size() - 1;

    // backtrack and find the numbers constructing the sum
    if (buffer_r.at(c_index) != -1) {
        while (c_index != 0) {
            int i {buffer_r.at(c_index)};

            // find index 
            vector<int>::iterator it = find(coins.begin(), coins.end(), coins.at(i));
            if (it != coins.end())  change.at(it - coins.begin())++;

            c_index -= coins.at(i);
        }
    }

    return change;
}

int main(){
  //get the number of coin denominations and the number of target amounts
  int n = -1, m = -1;
  cin >> n >> m;

  //collect the available coin denominations in a vector
  vector<int> coins;
  int v = -1;
  for (int i = 0; i < n; i++){
    cin >> v;
    coins.push_back(v);
  }

  //determine the number of each type of coin required for each target amount
  for (int i = 0; i < m; i++){
    int target = -1;
    cin >> target;
    vector<int> results = makeChange(target, coins);
    for (int j = 0; j < results.size()-1; j++){
      cout << results[j] << " ";
    }
    cout << results[results.size()-1] << endl;
  }

  return 0;
}