//
//  aksinha
//  assignment_5.c
//  Assignment 5: hotelSequence(A) which returns the minimum total penalty
//
//  Created by Atreya Sinha on 03/04/22.
//  Copyright 2022 Atreya Sinha. All rights reserved.

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

/*****************************************************************************************************
 * A simple struct to keep track of the sequence of hotels visited as well as the associated penalty *
 * seq - vector<int> - the sequence of hotels visited                                                *
 * penalty - int - the penalty associated with the sequence of hotels visited                        *
 * ***************************************************************************************************/
struct TripCost{
  vector<int> seq;
  int penalty;
};


/********************************************************************************************************
 * A simple struct to keep track of the minimum penalty and previous hotel for a potential ending hotel *
 * penalty - int - the minimum penalty associated with reaching this hotel                              *
 * prev - int - the hotel visited before this one                                                       *
 * ******************************************************************************************************/
struct HotelCell{
  int penalty;
  int prev;
};

TripCost* hotelSequence(vector<int> hotels, int m);
int calculate(int base, int expo);
void fill_buffer(vector<HotelCell> &buffer, vector<int> hotels, int m);
TripCost* backtrack(vector<HotelCell> buffer);

int main(){
  //get the total number of hotels and the ideal number of miles traveled per day
  cout << "Enter the number of hotels and the ideal number of miles to travel per day: ";
  int n = -1, m = -1;
  cin >> n >> m;

  //collect the hotel distances
  cout << "Enter " << n << " hotel distances each on a separate line: ";
  vector<int> hotels(n);
  hotels.push_back(0);
  for (int i = 1; i <= n; i++){
    int d = -1;
    cin >> d;
    hotels[i] = d;
  }

  //determine the route that minimizes the overall penalty and print out the results
  cout << "Hotels to visit: ";
  TripCost* solution = hotelSequence(hotels, m);
  for (int i = 0; i < solution->seq.size(); i++){
    cout << solution->seq[i] << " ";
  }
  cout << endl;
  cout << "Total penalty: " << solution->penalty << endl;

  return 0;
}

/************************************************************************************************
 * Given a sequence of hotel distances and an ideal number of miles to travel per day, return a *
 * TripCost pointer representing the sequence of hotels to visit with minimum penalty           *
 * hotels - vector<int> - the number of miles to each hotel from the starting point of the trip *
 * m - int - the ideal number of miles to travel per day                                        *
 * **********************************************************************************************/
TripCost* hotelSequence(vector<int> hotels, int m) {
    vector<HotelCell> buffer;
    for (int i {0}; i < (int) hotels.size(); i++) {
        HotelCell temp;
        temp.prev = 0;
        buffer.push_back(temp);
    }

    buffer.at(0).penalty = calculate(m, 2);
    buffer.at(0).prev = INT_MAX;

    fill_buffer(buffer, hotels, m);
    return backtrack(buffer);
}

// Given a base and an exponent, return the power                                               
int calculate(int base, int expo) {
    int result {1};
    while (expo != 0) {
        result *= base;
        expo--;
    }
    
    return result;
}

void fill_buffer(vector<HotelCell> &buffer, vector<int> hotels, int m) {
    int i {1}, j {0}, min_i {0}, min_j {0}, prev {0}, distance_diff {0};
    for (; i < (int) buffer.size(); i++) {
        min_i = calculate(m - hotels.at(i), 2);
        prev = 0;

        while (j < i) {
            distance_diff = m - (hotels.at(i) - hotels.at(j));
            min_j = buffer.at(j).penalty + calculate(distance_diff, 2);
            if (min_i >= min_j) {
                min_i = min_j;
                prev = j;
            }
            j++;
        } 
        j = 0;

        buffer.at(i).penalty = min_i;
        buffer.at(i).prev = prev;
    }
}

TripCost* backtrack(vector<HotelCell> buffer) {
    TripCost *trip_cost = new TripCost;
    int last_index {(int) buffer.size() - 1};

    HotelCell hotel_cell = buffer.at(last_index);
    trip_cost->penalty = hotel_cell.penalty;
    trip_cost->seq.push_back(last_index);

    int prev_cell {0}, trip_seq {0};
    while (buffer.at(hotel_cell.prev).prev != INT_MAX) {
        prev_cell = hotel_cell.prev;
        trip_cost->seq.insert(trip_cost->seq.begin(), prev_cell);
        hotel_cell = buffer.at(prev_cell);
    }

    return trip_cost;
}