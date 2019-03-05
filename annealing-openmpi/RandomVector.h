//
// Created by filip on 15.11.18.
//

#ifndef SALESMAN_SEQ_RANDOMVECTOR_H
#define SALESMAN_SEQ_RANDOMVECTOR_H

#include <algorithm>

using namespace std;

class RandomVector {

public:

    RandomVector();

    vector<int> generateRandVector(vector<int> singlePermutation, int numberOfNodes);

    vector<int> generateShuffle(vector<int> singlePerm, int nr);

    vector<int> generateSwap(vector<int> singlePerm, int nr);

    };


#endif //SALESMAN_SEQ_RANDOMVECTOR_H
