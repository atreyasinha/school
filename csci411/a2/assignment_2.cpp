//
//  aksinha
//  assignment_2.c
//  Assignment 2: find the set of nodes that belong to the set I, that is, the set of vertices v such that there *
//                is at least one path of length negative infinity ending at v.
//
//  Created by Atreya Sinha on 02/13/22.
//  Copyright 2022 Atreya Sinha. All rights reserved.

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
using namespace std;

/******************************************************************************
 * A simple Node struct                                                       *
 * id - int - the id or name of the node                                      *
 * dist - int - the distance from some given node to this node                *
 * inI - bool - true if the node is a member of the set I and false otherwise *
 * visited - bool - whether or not this node has been visited                 *
 * ****************************************************************************/
struct Node {
    int id;
    int dist;
    bool inI;
    bool visited;
};

/**************************************************************************
 * A simple Edge struct                                                   *
 * from - Node* - the node where this edge starts                         *
 * to - Node* - the node where this edge ends                             *
 * weight - int - the weight of this edge                                 *
 * ************************************************************************/
struct Edge {
    Node* from;
    Node* to;
    int weight;
};



/*****************************************************************************************************************
 * Given a graph, find the set of nodes that belong to the set I, that is, the set of vertices v such that there *
 * is at least one path of length negative infinity ending at v.                                                 *
 * A - vector<vector<Edge*>> - an adjacency list representation of a graph where each element is a weighted edge *
 * return - vector<int> - the integer ids of nodes in the set I                                                  *
 * ***************************************************************************************************************/
vector<int> infinity_nodes(int updated_path, int distance_list[], int a_size);
void bellman(int &updated_path, int a_size, vector<vector<Edge*>> A, int distance_list[]);
bool contain_path(vector<int> infinite_path, int v);

vector<int> findSetI(vector<vector<Edge*>> A){
    int a_size { (int) A.size() }, flag {-1};
    int distance_list[a_size];

    // initialize distance list. O(n)
    for (int i {0}; i < a_size; i++)    distance_list[i] = INT_MAX;

    // source node
    A.at(0).at(1)->from->dist = 0;

    // O(n^3)
    int updated_path {0}, i {0};
    while (i < a_size) {
        updated_path = flag;
        // O(n^2)
        bellman(updated_path, a_size, A, distance_list);
        i++;
    }

    return infinity_nodes(updated_path, distance_list, a_size); // O(n^2)
}

int main(){
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //in this case, A[i] is a vector of all edges leaving A[i]
    //note that A[0] is a list of self loops representing all nodes in the graph
    //these are not actual edges in the graph, just a way to keep track of all nodes
    //Furthermore, A[0][0] is a dummy edge with a dummy node
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Edge*>> A(n+1);
    A[0].push_back(new Edge());
    for (int i=1; i<n+1; i++){
        Node* v = new Node();
        v->id = i;
        v->dist = INT_MAX;
        v->inI = false;
        v->visited = false;
        Edge* e = new Edge();
        e->from = v;
        e->to = v;
        e->weight = 0;
        A[0].push_back(e);
    }

    //get edges from cin and add them to the adjacency list
    //the start, end, and weight of a single edge are on the same line separated by spaces
    int u = -1, v = -1, w = -1;
    for (int i=0; i<m; i++){
        cin >> u >> v >> w;
        Edge* e = new Edge();
        e->from = A[0][u]->from;
        e->to = A[0][v]->to;
        e->weight = w;
        A[u].push_back(e);
    }

    //find nodes belonging to the set I and print them out in ascending order
    vector<int> I = findSetI(A);
    sort(I.begin(), I.end());
    for (int i=0; i<(int)I.size()-1; i++){
        cout << I[i] << " ";
    }
    if (I.size() > 1){ cout << I[I.size()-1] << endl; }

    return 0;
}

vector<int> infinity_nodes(int updated_path, int distance_list[], int a_size) {
    vector<int> infinite_path;
    if (updated_path != -1) {
        int i {updated_path};
        // O(n^2)
        while (i != distance_list[i]) {
            infinite_path.push_back(i);
            // O(n)
            if (contain_path(infinite_path, distance_list[i]))  break;
            i = distance_list[i];
        }
        
        // O(n^2)
        for (int i {1}; i < a_size; i++) {
            // O(n)
            if (contain_path(infinite_path, i))     continue;
            for (int j {0}; j < (int) infinite_path.size(); j++) {
                if (distance_list[i] == infinite_path.at(j))  infinite_path.push_back(i);
            }
        }
    }

    return infinite_path;
}

void bellman(int &updated_path, int a_size, vector<vector<Edge*>> A, int distance_list[]) {
    Edge* e {};
    // vertex O(n^2)
    for (int j {1}; j < a_size; j++) {
        // edge O(n)
        for (int k {0}; k < (int) A.at(j).size(); k++) {
            e = A.at(j).at(k);

            if (e->from->dist + e->weight >= e->to->dist)   continue;
            
            e->to->dist = e->from->dist + e->weight;
            distance_list[e->to->id] = e->from->id;
            updated_path = e->to->id;
        }
    }
}

bool contain_path(vector<int> infinite_path, int v) {
    // O(n)
    for (int i {0}; i < (int) infinite_path.size(); i++) {
        if (infinite_path.at(i) == v)   return true;
    }
    return false;
}