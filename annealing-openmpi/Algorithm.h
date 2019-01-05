#ifndef SALESMAN_SEQ_ALGORITHM_H
#define SALESMAN_SEQ_ALGORITHM_H

#include <vector>
#include "Graph.h"

using namespace std;

class Algorithm {
private:

    double temperature;

    int loopSteps;

    int numberOfNodes;

    double alpha;

    //zawiera uporzadkowne rosnąco numery nodów
    std::vector<int> simpleOrderedPermutation;

    //poprzednia permutacja - x^0
    std::vector<int> previousPermutation;
    int previousPermutationValue;

    //permutajca z najkrótszą drogą - x_opt
    std::vector<int> bestPermutation;
    int bestPermutationValue;

    Graph *graph;

    int parallel;

public:
    Algorithm(double temperature, int loopSteps, int numberOfNodes, double alpha, int parallel);

    vector<int> nextPermutation();

    void changeValuesOfPermutations(vector<int> newPermutation);

    double randomValueZeroToOne(const int &min, const int &max);

    void annealingMethod(int mynum, int nprocs);

    void changeTemp();

    void printEnd();

    //MPI
    void func(int mynum, int nprocs,int *msgSend, int size,int iter);
    void func222(int mynum, int nprocs,int *msgSend, int size,int iter);

    void printTable(int table[], int size);

    int *addToTable(int table[], int size,int number);

    void setBestPermutation(vector<int> &bestPermutation);
};


#endif //SALESMAN_SEQ_ALGORITHM_H
