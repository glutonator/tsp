#include <iostream>
#include <random>
#include <chrono>
#include "Graph.h"
#include "Algorithm.h"
#include "RandomVector.h"
#include <sys/time.h>
#include <omp.h>

#include <mpi.h>


void measureParallelShuffleTime(int numberOfNodes);

void measureShuffleTime(int numberOfNodes);

using namespace std;

static int numprocs;


int main(int argc, char **argv) {



//    int my_rank;
    int mynum, nprocs;

// MPI initializations
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
//    std::cout << "mynum: " + std::to_string(mynum) << std::endl;
//    std::cout << "nprocs: " + std::to_string(nprocs) << std::endl;

    double time_start = MPI_Wtime();

    int numberOfNodes = atoi(argv[1]);
    double temperature = atof(argv[2]);
    int loopSteps = atoi(argv[3]);
    double alpha = atof(argv[4]);
    int parallel = atoi(argv[5]);

    Algorithm algorithm = Algorithm(temperature, loopSteps, numberOfNodes, alpha, parallel);

    double t1=MPI_Wtime();
    algorithm.annealingMethod(mynum,nprocs);
    double t2=MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (mynum == 0) {
        cout << "Jestem procesem 0...";
        cout<<"Czas obliczeń: "<<t2-t1<<" sekund\n";
    }

//    std::cout << "Hello World, my rank is " << mynum << " " << MPI_Wtime() - time_start << std::endl;

//    RandomVector *randomVector = new RandomVector();
//    randomVector->func(mynum, nprocs);
// End MPI
    MPI_Finalize();
    return 0;
}

//int main(int argc, char **argv) {
//
//    int numberOfNodes = atoi(argv[1]);
//    double temperature = atof(argv[2]);
//    int loopSteps = atoi(argv[3]);
//    double alpha = atof(argv[4]);
//    int parallel = atoi(argv[5]);
//
//    Algorithm algorithm = Algorithm(temperature, loopSteps, numberOfNodes, alpha, parallel);
//
//    // Record start time
//    double start = omp_get_wtime();
//
//    // Portion of code to be timed
//    algorithm.annealingMethod();
//
//    double finish = omp_get_wtime();
//    std::cout << "Elapsed time: " << finish-start << " s\n";
////    std::cout << finish-start << endl;
//
//    return 0;
//}

void measureParallelShuffleTime(int numberOfNodes) {

    vector<int> simpleOrderedPermutation = vector<int>(numberOfNodes);
    iota(std::begin(simpleOrderedPermutation), std::end(simpleOrderedPermutation), 0);

    RandomVector *randomVector = new RandomVector();

    auto start = chrono::_V2::system_clock::now();

    randomVector->generateRandVector(simpleOrderedPermutation, numberOfNodes);

    // Record end time
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
//    std::cout << "Elapsed parallel shuffle time: " << elapsed.count() << " s\n";

}

void measureShuffleTime(int numberOfNodes) {

    vector<int> simpleOrderedPermutation = vector<int>(numberOfNodes);
    iota(std::begin(simpleOrderedPermutation), std::end(simpleOrderedPermutation), 0);

    RandomVector *randomVector = new RandomVector();

    auto start = chrono::_V2::system_clock::now();

    randomVector->generateShuffle(simpleOrderedPermutation, numberOfNodes);

    auto finish = chrono::_V2::system_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed shuffled time: " << elapsed.count() << " s\n";
}