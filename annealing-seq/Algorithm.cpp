#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include "Algorithm.h"
#include "RandomVector.h"
#include <omp.h>


Algorithm::Algorithm(double temperature, int loopSteps, int numberOfNodes, double alpha) {

    Graph *graph = new Graph(numberOfNodes);
    graph->createComleteGraph();

    this->graph = graph;

    //temperature = T
    this->temperature = temperature;
    //loopSteps = L
    this->loopSteps = loopSteps;

    this->numberOfNodes = numberOfNodes;

    this->alpha = alpha;

    //popluation of vector
    simpleOrderedPermutation = vector<int>(numberOfNodes);
    iota(std::begin(simpleOrderedPermutation), std::end(simpleOrderedPermutation), 0);
    //sorting, not necessary
    sort(begin(simpleOrderedPermutation), end(simpleOrderedPermutation));

    bestPermutation = simpleOrderedPermutation;

    previousPermutation = nextPermutation();
    previousPermutationValue = graph->countWeightOfPath(previousPermutation);

    bestPermutation = previousPermutation;
    bestPermutationValue = previousPermutationValue;
}

vector<int> Algorithm::nextPermutation() {
    auto randomVector = new RandomVector();

    vector<int> out;
    #pragma omp critical
    {
        out = randomVector->generateSwap(bestPermutation, numberOfNodes);
    }

    return out;
}

void Algorithm::changeValuesOfPermutations(vector<int> newPermutation) {

    int newPermutationValue = graph->countWeightOfPath(newPermutation);
    int diff = newPermutationValue - this->previousPermutationValue;

    if (diff <= 0) {
        //x0 = x*
        this->previousPermutation = newPermutation;
        this->previousPermutationValue = newPermutationValue;
        //x_opt = x*
        this->bestPermutation = newPermutation;
        this->bestPermutationValue = newPermutationValue;
    } else {
        double r = randomValueZeroToOne(0, 1);
        double exponent = exp(-(diff / this->temperature));
        if (r < exponent) {
            //x0 = x*
            this->previousPermutation = newPermutation;
            this->previousPermutationValue = newPermutationValue;
        }
    }


}

double Algorithm::randomValueZeroToOne(const int &min, const int &max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static thread_local std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

void Algorithm::annealingMethod() {
    double epsilon = 0.5;
    //wykonuje się aż temp nie spadnie poniżej epsilon
    while (this->temperature > epsilon) {

        //k - liczba kroków podczas szukania minimum
        // wokół jednego rozwiązania
        for (int k = 0; k < this->loopSteps; ++k) {
            changeValuesOfPermutations(this->nextPermutation());
        }
        changeTemp();
    }
    printEnd();
}

void Algorithm::changeTemp() {
    double temp = this->temperature;
    double alpha = this->alpha;
    temp *= (1 - alpha);
    this->temperature = temp;
}

void Algorithm::printEnd() {
    cout << bestPermutationValue << "\t";
}







