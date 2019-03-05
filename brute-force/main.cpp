#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include "graph.h"

using namespace std;


int main(int argc,  char** argv) {

    int numberOfNodes = atoi(argv[1]);

    Graph *graph = new Graph(numberOfNodes);

    graph->createComleteGraph();

    double start = omp_get_wtime();

    graph->findShortestPathBetter();

    double finish = omp_get_wtime();
    std::cout << finish-start << endl;

    return 0;
}