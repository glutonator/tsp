#include <iostream>
#include <algorithm>
#include <numeric>
#include "graph.h"

Graph::Graph(int numberOfNodes) {
    this->numberOfNodes = numberOfNodes;
    adjacencyList = vector<vector<pair<int, int> > >(numberOfNodes);
}

// To add an edge
void Graph::addEdge(int node1, int node2, int weight) {
    adjacencyList[node1].push_back(make_pair(node2, weight));
    adjacencyList[node2].push_back(make_pair(node1, weight));

}

// Print adjacency list representaion ot graph
void Graph::printGraph() {
    int nodeNumber2, weight;
    for (int nodeNumber = 0; nodeNumber < this->numberOfNodes; nodeNumber++) {
        cout << "Node " << nodeNumber << " makes an edge with \n";
        for (auto it = adjacencyList[nodeNumber].begin(); it != adjacencyList[nodeNumber].end(); it++) {
            nodeNumber2 = it->first;
            weight = it->second;
            cout << "\tNode " << nodeNumber2 << " with edge weight ="
                 << weight << "\n";
        }
        cout << "\n";
    }
}

list<vector<int>> Graph::findShortestPath() {
    //list of all possible permutations
    list<vector<int>> out = list<vector<int>>();

    int shortestPathValue;
    vector<int> shortestPath;

    //popluation of vector
    vector<int> singlePermutation = vector<int>(numberOfNodes);
    iota(std::begin(singlePermutation), std::end(singlePermutation), 0);
    //sorting, not necessary
    sort(begin(singlePermutation), end(singlePermutation));
    //add first element
    shortestPath = singlePermutation;
    out.push_back(singlePermutation);
    shortestPathValue = countWeightOfPath(singlePermutation);

    //add all other elements
    while (std::next_permutation(singlePermutation.begin(), singlePermutation.end())) {
        int count = countWeightOfPath(singlePermutation);
        if (count < shortestPathValue) {
            shortestPathValue = count;
            shortestPath = singlePermutation;
        }
        out.push_back(singlePermutation);
    }
    std::cout << "shortestPathValue" << " " << shortestPathValue << endl;
    std::cout << "shortestPath" << " ";

    for (auto it = shortestPath.begin(); it != shortestPath.end(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
    return out;
}

void Graph::findShortestPathBetter() {

    int shortestPathValue;
    vector<int> shortestPath;

    //population of vector
    vector<int> singlePermutation = vector<int>(numberOfNodes);
    iota(std::begin(
            singlePermutation),
                    std::end(singlePermutation), 0);
    //sorting, not necessary
    sort(begin(singlePermutation), end(singlePermutation));
    //add first element
    shortestPath = singlePermutation;
    shortestPathValue = countWeightOfPath(singlePermutation);

    //add all other elements
    while (std::next_permutation(
            singlePermutation.begin(),
            singlePermutation.end())) {
        int count = countWeightOfPath(singlePermutation);
        if (count < shortestPathValue) {
            shortestPathValue = count;
            shortestPath = singlePermutation;
        }
    }
    std::cout << shortestPathValue << endl;
//    std::cout << "shortestPath" << " ";

//    for (int &it : shortestPath) {
//        std::cout << it << " ";
//    }
//    std::cout << std::endl;
}

void Graph::createComleteGraph() {
    int numberOfNodes = this->numberOfNodes;
    //weight increase by one
    int count = 1;
    //all combinations od nodes
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = i + 1; j < numberOfNodes; j++) {
            addEdge(i, j, count);
            count = count + 1;
        }
    }
}

int Graph::countWeightOfPath(vector<int> singlePermutation) {
    int count = 0;
    int node1 = singlePermutation[0];
    int beginAndEndNode = node1;
    int node2 = -1;
    for (auto it = singlePermutation.begin() + 1; it != singlePermutation.end(); ++it) {
        node2 = *it;
        count += getWeight(node1, node2);
        node1 = node2;
    }
    //we need to go back to begining node
    count += getWeight(node1, beginAndEndNode);
    return count;
}

int Graph::getWeight(int node1, int node2) {
    int out = -1;
    for (auto it = this->adjacencyList[node1].begin(); it != this->adjacencyList[node1].end(); ++it) {
        if (it->first == node2) {
            out = it->second;
            break;
        }
    }
    if (out == -1) throw "Edge not found";
    return out;
}







