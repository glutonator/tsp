#include <chrono>
#include <algorithm>
#include <random>
#include <iostream>
#include "RandomVector.h"
#include <mpi.h>

vector<int> RandomVector::generateRandVector(vector<int> singlePermutation, int numberOfNodes) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    auto first = std::begin(singlePermutation);
    auto last = std::end(singlePermutation);

    int size = numberOfNodes;

    int temp;

    for (int i = size - 1; i > 0; --i) {
        std::uniform_int_distribution<decltype(i)> d(0, i);

        auto r = d(rng);

        if (i != r) {
            temp = first[i];
            first[i] = first[r];
            first[r] = temp;
        }
    }


//    return singlePermutation;
}

vector<int> RandomVector::generateShuffle(vector<int> singlePerm, int nr) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(std::begin(singlePerm), std::end(singlePerm), rng);

    return singlePerm;
}

vector<int> RandomVector::generateSwap(vector<int> vec, int nr) {

    auto v = std::begin(vec);

    long seed;

    std::uniform_int_distribution<> d(0, nr - 1);

    seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    swap(v[d(rng)], v[d(rng)]);

    return vec;

}

RandomVector::RandomVector() {

}




