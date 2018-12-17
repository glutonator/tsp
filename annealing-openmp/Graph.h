#ifndef SALESMAN_SEQ_GRAPH_H
#define SALESMAN_SEQ_GRAPH_H

#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int numberOfNodes;
    vector<vector<pair<int, int> > > adjacencyList;

    bool isPermRight;

public:

    Graph(int numberOfNodes);

    void addEdge(int node1, int node2, int weight);

    void printGraph();

    void createComleteGraph();

    int countWeightOfPath(vector<int> singlePermutation);

    int getWeight(int node1, int node2);

};


#endif //SALESMAN_SEQ_GRAPH_H
