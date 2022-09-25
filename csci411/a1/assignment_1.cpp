// CSCI 411 - Spring 2022
// Assignment 1 
// Author: Atreya Sinha
// CSU CHICO ID: aksinha

#include <iostream>
#include <vector>
using namespace std;

/**************************************************************************
 * A simple Node struct                                                   *
 * id - int - the id or name of the node                                  *
 * SCC - int - the strongly connected component that this node belongs to *
 * visited - bool - whether or not this node has been visited             *
 * ************************************************************************/
struct Node {
    int id;
    int SCC;
    bool visited;
};

/**************************************************************************************************
 * A simple struct of strongly connected component (SCC) graph nodes                              *
 * id - int - the id or name of the node (this corresponds to the SCC id)                         *
 * size - int - the number of nodes from the original graph that belong to this SCC               *
 * hasInEdges - bool - true if there are edges with end points in this SCC and false otherwise    *
 * hasOutEdges - bool - true if there are edges with start points in this SCC and false otherwise *
 * ************************************************************************************************/
struct SCCNode {
    int id;
    int size;
    bool hasInEdges;
    bool hasOutEdges;
};

/*********************************************************
 * A simple struct to hold the sizes of sets A, B, and C *
 * A - int - the size of set A                           *
 * B - int - the size of set B                           *
 * C - int - the size of set C                           *
 * *******************************************************/
struct Result {
    int A;
    int B;
    int C;
};

/***************************************************************************************
 * Given the adjacency list of a graph, generate a new adjacency list with the         *
 * same nodes but with edges reversed                                                  *
 * A - vector<vector<Node*>> - an adjacency list representation of a graph. Note that  * 
 *   A[0] is a list of all the Nodes in the graph with an additional dummy Node at     * 
 *   A[0][0]. As a result, A[i] are the neighbors of the Node with id i where these    *
 *   ids go from 1 to n, the size of the graph.                                        *
 * return - vector<vector<Node*>> - an adjacency list of a new graph equivalent to the *
 *        original but with edges reversed.                                            *
 * *************************************************************************************/
vector<vector<Node*>> reverseEdges(vector<vector<Node*>> A){
    vector<vector<Node *> > result;
    vector<Node *> temp;

    for (int i {0}; i < (int) A.size(); i++)            result.push_back(temp);
    for (int i {0}; i < (int) A.at(0).size(); i++)      result.at(0).push_back(A.at(0).at(i));

    for (int i {1}; i < (int) A.size(); i++) {
        for (int j {0}; j < (int) A.at(i).size(); j++) {
            result.at(A.at(i).at(j)->id).push_back(result.at(0).at(i));
        }
    }

    for (int i {0}; i < (int) A.size(); i++) {
        for (int j {0}; j < (int) A.at(i).size(); j++) {
            result.at(A.at(i).at(j)->id).push_back(result.at(0).at(i));
        }
    }
    
    return result;
}

/********************************************************************************************************
 * A variation of DFS for the first pass over a graph looking for strongly connected components.        *
 * The goal is to fill the vector L with nodes in decreasing order with respect to finishing time       *
 * A - vector<vector<Node*>> - an adjacency list                                                        *
 * v - Node* - the start node for the DFS                                                               *
 * &L - vector<Node*> - a list of nodes to be filled in decreasing order with respect to finishing time *
 * ******************************************************************************************************/
void DFSSCC(vector<vector<Node*>> A, Node* v, vector<Node*> &L){
    v->visited = true;
    for (int i {0}; i < (int) A.at(v->id).size(); i++) {
        Node *u { A.at(v->id).at(i) };
        if (!u->visited)    DFSSCC(A, u, L);
    }

    L.push_back(v);
    return;
}

/******************************************************************************************************************
 * A variation of DFS for the second pass over a graph looking for strongly connected components.                 *
 * There are three goals (1) to label nodes with a SCC id (2) to generate nodes of a SCC metagraph (3) and to     *
 * determine which nodes in this metagraph have incoming and outgoing edges.                                      *
 * A - vector<vector<Node*>> - an adjacency list representing the transpose or edge reverse of the original graph *
 * v - Node* - the start node for the DFS                                                                         *
 * scc - int - the current strongly connected component id                                                        *
 * &SCCs - vector<SCCNode*> - the nodes of a SCC metagraph                                                        *
 ******************************************************************************************************************/
void DFSAssign(vector<vector<Node*>> A, Node* v, int scc, vector<SCCNode*> &SCCs){
    v->SCC = scc;

    for (int i {0}; i < (int) A.at(v->id).size(); i++) {
        Node *u { A.at(v->id).at(i) };
        scc++;
        if (u->SCC == 0)  DFSAssign(A, u, scc, SCCs);
    }
}

/******************************************************************************************************
 * Find the strongly connected components (SCCs) of a graph. The SCC of each Node is added to the SCC *
 * member of the Node struct. In addition, a vector of SCCNode* is returned.                          *
 * A - vector<vector<Node*>> - an adjacency list                                                      *
 * return - vector<SCCNode*> - a vector of nodes in the SCC metagraph of A                            *
 * ****************************************************************************************************/
vector<SCCNode*> SCC(vector<vector<Node*>> A){
    for (int i {0}; i < (int) A.at(0).size(); i++) {
        A.at(0).at(i)->visited = false;
        A.at(0).at(i)->SCC = 0;
    }
    vector<Node*> L;
    for (int i {0}; i < (int) A.at(0).size(); i++) {
        if (!A.at(0).at(i)->visited)    DFSSCC(A, A.at(0).at(i), L);
    }
    vector<vector<Node *> > g_R = reverseEdges(A);
    vector<SCCNode*> s;
    for (int i {0}; i < (int) L.size(); i++) {
        SCCNode* temp = new SCCNode;
        if (L.at(i)->SCC == 0) {
            temp->id = A.at(0).at(i)->id;
            s.push_back(temp);
            DFSAssign(g_R, L.at(i), 0, s);
        }
    }
    return s;
}

/************************************************************************************************
 * Given the adjacency list representation of a graph, fill and return a Result struct with the *
 * number of nodes that belong to the three sets A, B, and C as described in assignment 1       *
 * A - vector<vector<Node*>> - an adjacency list                                                *
 * return - Result - a Result struct holding the sizes of sets A, B, and C                      *
 * **********************************************************************************************/
Result* getSetSizes(vector<vector<Node*>> A){
    Result* r;

    vector<SCCNode*> sccA = SCC(A);

    for (int i {0}; i < (int) sccA.size(); i++) {
        r->A += sccA[i]->id;
    }
    
    return r;
}

int main(){
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //note that A[0] is a list of nodes with a dummy node in A[0][0]
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Node*>> A(n+1);
    A[0].push_back(new Node());
    for (int i=1; i<n+1; i++){
        Node* v = new Node();
        v->id = i;
        v->SCC = -1;
        v->visited = false;
        A[0].push_back(v);
    }

    //get edges from cin and add them to the adjacency list
    //the start and end of a single edge are on the same line separated by a space
    int u = -1, v = -1;
    for (int i=0; i<m; i++){
        cin >> u >> v;
        A[u].push_back(A[0][v]);
    }

    //call getSetSizes to determine the size of the sets A, B, and C and print the results
    Result* R = getSetSizes(A);
    cout << R->A << " " << R->B << " " << R->C;

    return 0;
}
