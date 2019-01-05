#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include "Algorithm.h"
#include "RandomVector.h"
#include <omp.h>
#include <mpi.h>


Algorithm::Algorithm(double temperature, int loopSteps, int numberOfNodes, double alpha, int parallel) {

    Graph *graph = new Graph(numberOfNodes);
    graph->createComleteGraph();
//    graph->printGraph();

    //to jest ważne!!!!
    this->graph = graph;


    //temperature = T
    this->temperature = temperature;
    //loopSteps = L
    this->loopSteps = loopSteps;

    this->numberOfNodes = numberOfNodes;

    this->parallel = parallel;

    this->alpha = alpha;

    //popluation of vector
    simpleOrderedPermutation = vector<int>(numberOfNodes);
    iota(std::begin(simpleOrderedPermutation), std::end(simpleOrderedPermutation), 0);
    //sorting, not necessary
    sort(begin(simpleOrderedPermutation), end(simpleOrderedPermutation));

    bestPermutation = simpleOrderedPermutation;

    //TODO: uproszczenie na czas testów by zaczynało zawsze od tego samego vectora na wszystkich procesach
//    previousPermutation = nextPermutation();
//    previousPermutationValue = graph->countWeightOfPath(previousPermutation);
//
//    bestPermutation = previousPermutation;
//    bestPermutationValue = previousPermutationValue;

    previousPermutation = simpleOrderedPermutation;
    previousPermutationValue = graph->countWeightOfPath(simpleOrderedPermutation);

    bestPermutation = previousPermutation;
    bestPermutationValue = previousPermutationValue;
}

vector<int> Algorithm::nextPermutation() {
    auto randomVector = new RandomVector();

    vector<int> out;
//    #pragma omp critical
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

void Algorithm::annealingMethod(int mynum, int nprocs) {
    double epsilon = 0.5;
    //wykonuje się aż temp nie spadnie poniżej epsilon
//    while (this->temperature > epsilon) {
    for (int i = 0; i < 10; i++) {
        //k - liczba kroków podczas szukania minimum
        // wokół jednego rozwiązania
        //TODO: zminić k na k/liczba procesów uruchomionych
        for (int k = 0; k < this->loopSteps / nprocs; ++k) {
            //TODO: nextPermutation swapuje najlepszą permutację aktualną - trzeba zrobić przesyłanie jej między procesami
            // + sprawdzanie czy otrzmana jest lepsza czy gorsza od tej która jest aktualnie zapisana
            cout << "ttt ";
            for (int ttt: this->bestPermutation) {
                cout << ttt;
            }
            cout << endl;
            std::vector<int> nextPer = this->nextPermutation();
            changeValuesOfPermutations(nextPer);
//            this->bestPermutation
//            RandomVector *randomVector = new RandomVector();
            vector<int> tmpvector = bestPermutation;
            int *sendVector = &tmpvector[0];
//            cout<<"sendVector";
//            this->printTable(sendVector,tmpvector.size());
//            this->func(mynum, nprocs, sendVector, 5, i);
            this->func222(mynum, nprocs, sendVector, tmpvector.size(), i);
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
//    for (auto it = bestPermutation.begin(); it != bestPermutation.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//    cout << "bestPermutationValue  " << bestPermutationValue << endl;
    cout << bestPermutationValue << "\t";
    cout << endl;
}


void Algorithm::func(int mynum, int nprocs, int *msgSend, int size, int iter) {
//    cout<<size;
    int i, info, source, dest = 0;
    int NumIter = 1;
//    int
    size = 5;
    size = 5;
//
//    int *msgSend = new int[size];
//    for (int i = 0; i < size; i++)
//        msgSend[i] = i;

    int msgRecv[size];

    MPI_Status status;


    for (int j = 0; j < NumIter; j++) {
        if (mynum == 0) {
            std::cout << " Main instances" << std::endl;
            for (i = 1; i < nprocs; i++) {
                source = i;
//            std::cout<<" Main instances: "+std::to_string(msgRecv[8])+" "+std::to_string(msgRecv[9])<<std::endl;
                info = MPI_Recv(&msgRecv, size, MPI_INT, source, 3, MPI_COMM_WORLD, &status);
                if (info != 0) {
                    printf("instance no, %d failed to recive\n", mynum);
                    exit(0);
                }
                std::cout << "iter: " + std::to_string(iter);
                std::cout << " Main instances: ";
//                printTable(msgRecv, size);
            }

        } else {

//            addToTable(msgSend, size, mynum);

            std::cout << " Other instances: " << mynum << std::endl;
            info = MPI_Send(msgSend, size, MPI_INT, dest, 3, MPI_COMM_WORLD);
            if (info != 0) {
                printf("instance no, %d failed to send\n", mynum);
                exit(0);
            }
            std::cout << "iter: " + std::to_string(iter);
            std::cout << " Other instances: " << mynum << "::: ";
            printTable(msgSend, size);

            //seting new value of bestPermutation
            //todo: dorobić warunki żeby była lepsza od porpzedniej plus poprzednia wartość jezszcze
            vector<int> qqqqq = vector<int>(size);
            std::iota(std::begin(qqqqq), std::end(qqqqq), 0);
//            setBestPermutation(qqqqq);
            this->bestPermutation = qqqqq;
//            int* a = &tmp[0];
            printTable(&this->bestPermutation[0], size);

//            addToTable(msgSend, size, 10);

        }
    }
}

void Algorithm::printTable(int *table, int size) {
    for (int i = 0; i < size; i++)
        std::cout << table[i] << " ";
    std::cout << std::endl;

}

int *Algorithm::addToTable(int *table, int size, int number) {
    for (int i = 0; i < size; i++)
        table[i] = table[i] + number;
    return table;
}

void Algorithm::setBestPermutation(vector<int> &bestPermutation) {
    Algorithm::bestPermutation = bestPermutation;
}

void Algorithm::func222(int mynum, int nprocs, int *msgSend, int size, int iter) {
//    cout<<"msgSend ";
//    printTable(msgSend, size);

    int i, info, source, dest = 0;
    int NumIter = 1;
//    size = 5;
//
//    int *msgSend = new int[size];
//    for (int i = 0; i < size; i++)
//        msgSend[i] = i;

    int msgRecv[size];

    MPI_Status status;

    for (int j = 0; j < NumIter; j++) {
//        addToTable(msgSend, size, mynum);

//        std::cout << " Other instances: " << mynum << std::endl;
//            info = MPI_Send(msgSend, size, MPI_INT, dest, 3, MPI_COMM_WORLD);
        cout<<"broadcast:"<<mynum<<":"<<iter<<endl;
        printTable(msgSend,size);
        info = MPI_Bcast(&msgSend, size, MPI_INT, mynum, MPI_COMM_WORLD);
        cout<<"broadcast:"<<mynum<<":"<<iter<<endl;
        printTable(msgSend,size);

        if (info != 0) {
            printf("instance no, %d failed to send\n", mynum);
            exit(0);
        }
        std::cout << "iter: " + std::to_string(j);
        std::cout << " Other instances: " << mynum << "::: ";
        printTable(msgSend, size);
        //            //seting new value of bestPermutation
        //todo: dorobić warunki żeby była lepsza od porpzedniej plus poprzednia wartość jezszcze
//        vector<int> qqqqq = vector<int>(size);
//        std::iota(std::begin(qqqqq), std::end(qqqqq), 0);
//            setBestPermutation(qqqqq);
//        this->bestPermutation = qqqqq;

//        vector<int> values(msgSend, msgSend + size);
        vector<int> values = vector<int>(size);
        for (int q = 0; q < size; q++) {
//            cout << msgSend[q] << " ||";
//            int tmp =msgSend[q];
//            values[q]=tmp;
            values[q] = msgSend[q];
        }
//        cout << "hellooooo" << " ||";

        changeValuesOfPermutations(values);
//        this->bestPermutation = values;
//            int* a = &tmp[0];
//        printTable(&this->bestPermutation[0], size);
        cout << mynum << ": ";
        printEnd();
//            addToTable(msgSend, size, 10);
    }


//    for (int j = 0; j < NumIter; j++) {
//        if (mynum == 0) {
//            std::cout << " Main instances" << std::endl;
//            for (i = 1; i < nprocs; i++) {
//                source = i;
////            std::cout<<" Main instances: "+std::to_string(msgRecv[8])+" "+std::to_string(msgRecv[9])<<std::endl;
//                info = MPI_Recv(&msgRecv, size, MPI_INT, source, 3, MPI_COMM_WORLD, &status);
//                if (info != 0) {
//                    printf("instance no, %d failed to recive\n", mynum);
//                    exit(0);
//                }
//                std::cout << "iter: " + std::to_string(iter);
//                std::cout << " Main instances: ";
////                printTable(msgRecv, size);
//            }
//
//        } else {
//
////            addToTable(msgSend, size, mynum);
//
//            std::cout << " Other instances: " << mynum << std::endl;
//            info = MPI_Send(msgSend, size, MPI_INT, dest, 3, MPI_COMM_WORLD);
//            if (info != 0) {
//                printf("instance no, %d failed to send\n", mynum);
//                exit(0);
//            }
//            std::cout << "iter: " + std::to_string(iter);
//            std::cout << " Other instances: " << mynum << "::: ";
//            printTable(msgSend, size);
//
//            //seting new value of bestPermutation
//            //todo: dorobić warunki żeby była lepsza od porpzedniej plus poprzednia wartość jezszcze
//            vector<int> qqqqq = vector<int>(size);
//            std::iota(std::begin(qqqqq), std::end(qqqqq), 0);
////            setBestPermutation(qqqqq);
//            this->bestPermutation=qqqqq;
////            int* a = &tmp[0];
//            printTable(&this->bestPermutation[0], size);
//
////            addToTable(msgSend, size, 10);
//
//        }
//    }
}





