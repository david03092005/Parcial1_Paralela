#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

std::string get_container_id() {
    std::ifstream file("/etc/hostname");
    std::string container_id;

    if (file.is_open()) {
        std::getline(file, container_id);
        file.close();
    } else {
        container_id = "UNKNOWN";
    }
    return container_id;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string container_id = get_container_id();
    char id_buffer[100];
    snprintf(id_buffer, sizeof(id_buffer), "Proceso %d en contenedor ID: %s", rank, container_id.c_str());

    if (rank == 0) {
        std::cout << id_buffer << std::endl;
        for (int i = 1; i < size; i++) {
            char recv_buffer[100];
            MPI_Recv(recv_buffer, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << recv_buffer << std::endl;
        }
    } else {
        MPI_Send(id_buffer, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
