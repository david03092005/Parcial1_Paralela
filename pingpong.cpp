#include <mpi.h>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 10000);

int main(int argc, char** argv) {
        MPI_Init(&argc, &argv);

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int number = dist(gen);
        for(int i = 0; i < 10; i++){
                if (rank == 0) {
                        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                        std::cout << "Process 0 sent data: " << number << std::endl;
                        MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        std::cout << "Process 0 received data: " << number << std::endl;
                        number += 1;
                }
                else {
                        int received_data;
                        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        std::cout << "Process 1 received data: " << received_data << std::endl;
                        received_data += 1;
                        MPI_Send(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                        std::cout << "Process 1 sent data: " << received_data << std::endl;
                }
        }

        MPI_Finalize();
        return 0;
}
