//
//  aksinha
//  assignment_4.c
//  Assignment 4: Given two strings a and b along with costs associated with insertions, deletions, *
//                and substitutions, find an optimal alignment (of minimum cost) of a and b
//
//  Created by Atreya Sinha on 02/24/22.
//  Copyright 2022 Atreya Sinha. All rights reserved.

#include <iostream>
#include <vector>
using namespace std;

/*******************************************************************************************
 * A simple struct to describe alignments. Insertions are denoted with an underscore ("_") *
 * a, b - strings - two strings representing an alignment. The strings being aligned may   *
 *                - be extracted by removing underscores                                   *
 * score - float - the score of the alignment given costs associated with insertions,      *
 *                 deletions, and substitutions                                            *
 * *****************************************************************************************/
struct Alignment{
  string a;
  string b;
  float score;
};

/***************************************************************************************
 * A simple struct to keep track of subproblem solutions                               *
 * act - string - the action taken to reach this Cell: "match", "ins", "del", or "sub" *
 * score - float - the score of the alignment of prefixes up to this point given costs *
 *                 associated with insertions, deletions, and substitutions            *
 * *************************************************************************************/
struct Cell{
  string act;
  float score;
};

Alignment* editDistance(string a, string b, float ins, float del, float sub);
void c_min(vector<vector<Cell> > &buffer, float ins, float del, float sub, int i, int j);
void initialize_table_cost(vector<vector<Cell> > &buffer, float ins, float del, float sub, int i, 
                                            int j, int a_size, int b_size);
Alignment* modify_strings(vector<vector<Cell> > buffer, int i, int j, 
                string a, string b, Cell temp, int a_size, int b_size);

int main(){
  //get the number of tests
  int n = -1;
  cin >> n;

  //get the costs associated with insertions, deletions, and substitutions
  int ins = -1, del = -1, sub = -1;
  cin >> ins >> del >> sub;

  //for each test, print the resulting alignment along with its score
  for (int i = 0; i < n; i++){
    string a = "", b = "";
    cin >> a >> b;

    Alignment* align = editDistance(a, b, ins, del, sub);
    cout << align->a << endl;
    cout << align->b << endl;
    cout << align->score << endl;
  }

  return 0;
}

/*************************************************************************************
 * Given two strings a and b along with costs associated with insertions, deletions, *
 * and substitutions, find an optimal alignment (of minimum cost) of a and b         *
 * a, b - strings - two strings for which we want an alignment                       *
 * ins, del, sub - floats - the cost of performing insertion, deletion, and          *
 *                          substitution opertations respectively on string a        *
 * return - Alignment* - an optimal alignment of a and b given the matrix T along    *
 *                       with the score or cost of the alignment                     *
 * ***********************************************************************************/
Alignment* editDistance(string a, string b, float ins, float del, float sub) {
    // store results of subproblems
    vector<vector<Cell> > buffer;
    int i {0};
    int a_size {(int) a.size()}, b_size {(int) b.size()};
    for (i = 0; i <= a_size; i++) {
        vector<Cell> inner_buffer(b_size + 1); 
        buffer.push_back(inner_buffer);
    }
    Cell temp;
    temp = buffer.at(0).at(0);
    temp.act = "match";
    temp.score = 0;

    int j {0};
    // intialize table with initial cost
    initialize_table_cost(buffer, ins, del, sub, i, j, a_size, b_size);

    // intialize table with 0's
    for (i = 1; i <= a_size; i++) {
        for (j = 1; j <= b_size; j++) {
            if (a.at(i - 1) != b.at(j - 1)) {
                c_min(buffer, ins, del, sub, i, j);
                continue;
            }
            buffer.at(i).at(j).act = "match";
            buffer.at(i).at(j).score = buffer.at(i - 1).at(j - 1).score;
        }
    }

    // back track to modify the input strings
    return modify_strings(buffer, i, j, a, b, temp, a_size, b_size);
}

void c_min(vector<vector<Cell> > &buffer, float ins, float del, float sub, int i, int j) {
    bool condition {buffer.at(i - 1).at(j - 1).score + sub > buffer.at(i - 1).at(j).score + del};
    if (condition) {
        condition = buffer.at(i).at(j - 1).score + ins < buffer.at(i - 1).at(j).score + del;
        if (!condition) {
            buffer.at(i).at(j).act = "delete";
            buffer.at(i).at(j).score = buffer.at(i - 1).at(j).score + del;
        } else {
            buffer.at(i).at(j).act = "insert";
            buffer.at(i).at(j).score = buffer.at(i).at(j - 1).score + ins;
        }
        return;
    } 

    condition = buffer.at(i - 1).at(j - 1).score + sub <= buffer.at(i).at(j - 1).score + ins;
    if (condition) {
        buffer.at(i).at(j).act = "substitute";
        buffer.at(i).at(j).score = buffer.at(i - 1).at(j - 1).score + sub;
    } else {
        buffer.at(i).at(j).act = "insert";
        buffer.at(i).at(j).score = buffer.at(i).at(j - 1).score + ins;
    }
}

void initialize_table_cost(vector<vector<Cell> > &buffer, float ins, float del, float sub, int i, 
                                            int j, int a_size, int b_size) {
    for (i = 1; i <= a_size; i++) {
        buffer.at(i).at(0).act = "delete";
        buffer.at(i).at(0).score = buffer.at(i - 1).at(0).score + del;
    }

    for (i = 1; i <= b_size; i++) {
        buffer.at(0).at(i).act = "insert";
        buffer.at(0).at(i).score = buffer.at(0).at(i - 1).score + ins;
    }
}

/*************************************************************************************
 * return - Alignment* - an optimal alignment of a and b given the matrix T along    *
 *                       with the score or cost of the alignment                     *
 * ***********************************************************************************/
Alignment* modify_strings(vector<vector<Cell> > buffer, int i, int j, 
                string a, string b, Cell temp, int a_size, int b_size) {
    // last index stores the total min cost
    i = a_size, j = b_size;
    temp = buffer.at(i).at(j);

    Alignment *result = new Alignment;
    result->score = temp.score;
    
    string modified_a {""}, modified_b {""}, temp_act {""};   
    while (i > 0 || j > 0) {
        temp_act = temp.act;        
        if (temp_act == "insert") {
            modified_a.insert(modified_a.begin(), '_');
            modified_b.insert(modified_b.begin(), b.at(j - 1));
            j--;
        } else if (temp_act == "delete") {
            modified_a.insert(modified_a.begin(), a.at(i - 1));
            modified_b.insert(modified_b.begin(), '_');
            i--;
        } else {
            modified_a.insert(modified_a.begin(), a.at(i - 1));
            modified_b.insert(modified_b.begin(), b.at(j - 1));
            i--, j--;
        }
        temp = buffer.at(i).at(j);
    }

    // stores the final string after modification
    result->a = modified_a, result->b = modified_b;

    return result;
}
