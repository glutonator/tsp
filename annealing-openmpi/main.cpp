#include <iostream>
#include <random>
#include <chrono>
#include "Graph.h"
#include "Algorithm.h"
#include "RandomVector.h"
#include <sys/time.h>
#include <mpi.h>


using namespace std;

int main(int argc, char **argv) {
    int mynum, nprocs;

// MPI initializations
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int numberOfNodes = atoi(argv[1]);
    double temperature = atof(argv[2]);
    int loopSteps = atoi(argv[3]);
    double alpha = atof(argv[4]);

    Algorithm algorithm = Algorithm(temperature, loopSteps, numberOfNodes, alpha);

    double start=MPI_Wtime();
    algorithm.annealingMethod(mynum,nprocs);
    double finish=MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    if (mynum == 0) {
        std::cout << finish-start << endl;
    }

// End MPI
    MPI_Finalize();
    return 0;
}

