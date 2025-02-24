#include <mpi.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    int number = dist(gen);
    const int numIter = 10;
    std::vector<double> rttValues;

    for (int i = 0; i < numIter; i++) {
        double startTime, endTime, rtt;

        if (rank == 0) {
            startTime = MPI_Wtime();

            MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            endTime = MPI_Wtime();
            rtt = (endTime - startTime) * 1e6;
        } 
        else {
            int received_data;

            startTime = MPI_Wtime();

            MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            received_data += 1;
            MPI_Send(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

            endTime = MPI_Wtime();
            rtt = (endTime - startTime) * 1e6;
        }

        rttValues.push_back(rtt);
    }

    
    MPI_Barrier(MPI_COMM_WORLD);

    std::cout << "\n----------------------------------------\n";
    std::cout << "  Nodo " << rank << " - RTT por iteración (μs)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "   Iteración   |    RTT (microsegundos) \n";
    std::cout << "----------------------------------------\n";
    for (int i = 0; i < numIter; i++) {
        std::cout << std::setw(10) << i << "   |   " << std::setw(10) << rttValues[i] << "\n";
    }
    std::cout << "----------------------------------------\n";

    MPI_Finalize();
    return 0;
}

