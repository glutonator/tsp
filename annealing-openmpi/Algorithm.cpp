#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include "Algorithm.h"
#include "RandomVector.h"
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

    previousPermutation = nextPermutation();
    previousPermutationValue = graph->countWeightOfPath(previousPermutation);

    bestPermutation = previousPermutation;
    bestPermutationValue = previousPermutationValue;

}

vector<int> Algorithm::nextPermutation() {
    auto randomVector = new RandomVector();

    vector<int> out;
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

    //zapisywanie najmniejszej temperatiry startowej
    double lowestTemp;
    lowestTemp = this->temperature;
    for (int p = nprocs - (0 + 1); p > 0; p--) {
        lowestTemp = changeLowestTemp(lowestTemp);
    }

    //ustawienie temperatury najmniejszej dla procesu 0 - by uniknąc zakleszczenia i odebrać wszystkie wysłane wiadomości
    for (int p = nprocs - (mynum + 1); p > 0; p--) {
        changeTemp();
    }


    double epsilon = 0.5;
    //wykonuje się aż temp nie spadnie poniżej epsilon
    int i = 0;
    while (this->temperature > epsilon) {
        //sprawdzenie czy następna zmiana temeperatury spowoduje zakończenie algorytmu
        if (lowestTemp <= epsilon) {
//            cout << mynum << " mynum " << "BREAK" << endl;
            break;
        }

        //k - liczba kroków podczas szukania minimum
        // wokół jednego rozwiązania
        for (int k = 0; k < this->loopSteps; ++k) {
            std::vector<int> nextPer = this->nextPermutation();
            changeValuesOfPermutations(nextPer);
        }

        //konwertowanie kopii vectora bestPermutation do obiektu nadającego się do przesłania
        vector<int> tmpvector = bestPermutation;
        int *sendVector = &tmpvector[0];
        this->processSynchronization(mynum, nprocs, sendVector, tmpvector.size(), i);
        i++;

        // petla zminiająca temperaturę w zalężności od liczby procesów
        for (int p = 0; p < nprocs; p++) {
            lowestTemp = changeLowestTemp(lowestTemp);
            changeTemp();
        }
    }
    //czekanie aż wsyzstkie procesy skończą się - wyświetlanie wyniku dla procesu głownego
    MPI_Barrier(MPI_COMM_WORLD);
    if (mynum == 0) {
//        cout << "Jestem procesem 0..wynik to: ";
        printEnd();
    }
}


double Algorithm::changeLowestTemp(double lowestTemp) {
    double alpha = this->alpha;
    lowestTemp *= (1 - alpha);
    return lowestTemp;
}

void Algorithm::changeTemp() {
    double temp = this->temperature;
    double alpha = this->alpha;
    temp *= (1 - alpha);
    this->temperature = temp;
}

void Algorithm::printEnd() {
    cout << bestPermutationValue << "\t";
    cout << endl;
}


void Algorithm::processSynchronization(int mynum, int nprocs, int *msgSend, int size, int iter) {
    int i, info, source, dest = 0;
    int msgRecv[size];
    int msgRecv222[size];
    MPI_Status status;
    if (mynum == 0) {
        //odbieranie wiadomości z bestPermutation z pozostałych procesów
        for (i = 1; i < nprocs; i++) {
            source = i;
            info = MPI_Recv(&msgRecv, size, MPI_INT, source, 3, MPI_COMM_WORLD, &status);
            if (info != 0) {
                printf("instance no, %d failed to recive\n", mynum);
                exit(0);
            }

            //wybranie najlepszej permutacji
            //***************************
            vector<int> values = vector<int>(size);
            for (int q = 0; q < size; q++) {
                values[q] = msgRecv[q];
            }
            changeValuesOfPermutations(values);
            //**********************
        }

        //przesłanie wybranej najlepszej bestPermutation z otrzymanych procesów do wszsytkich innych niż proces-0 procesów
        vector<int> tmpvector222 = this->bestPermutation;
        int *sendVector222 = &tmpvector222[0];
        info = MPI_Bcast(sendVector222, size, MPI_INT, 0, MPI_COMM_WORLD);
        if (info != 0) {
            printf("instance no, %d failed to send\n", mynum);
            exit(0);
        }
    } else {
        //wysyłąnie wiadomości z bestPermutation do procesu-0
        info = MPI_Send(msgSend, size, MPI_INT, dest, 3, MPI_COMM_WORLD);
        if (info != 0) {
            printf("instance no, %d failed to send\n", mynum);
            exit(0);
        }

        //odebranie bestPermutation przez wszsytkie procesy poza procesem-0
        info = MPI_Bcast(&msgRecv222, size, MPI_INT, 0, MPI_COMM_WORLD);
        if (info != 0) {
            printf("instance no, %d failed to recive\n", mynum);
            exit(0);
        }

        //zapisanie najlepszej permutacji
        //***************************
        vector<int> values = vector<int>(size);
        for (int q = 0; q < size; q++) {
            values[q] = msgRecv222[q];
        }
        changeValuesOfPermutations(values);
        //**********************

    }
}

void Algorithm::printTable(int *table, int size) {
    for (int i = 0; i < size; i++)
        std::cout << table[i] << "";
    std::cout << std::endl;

}









