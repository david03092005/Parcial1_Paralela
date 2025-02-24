#include <iostream>
#include <omp.h>

float A = 0;
float B = 0;
float C = 0;
float D = 0;
float E = 0;

void funcionA() {
    std::cout << "Ejecutando funcionA" << std::endl;
    for (int i = 0; i < 10; i++) {
        A += 1;
    }
}

void funcionB() {
    std::cout << "Ejecutando funcionB" << std::endl;
    B = 1;
    for (int i = 1; i <= 10; i++) {
        B *= i;
    }
}

void funcionC() {
    std::cout << "Ejecutando funcionC" << std::endl;
    C = C * C;
}

void funcionD() {
    std::cout << "Ejecutando funcionD" << std::endl;
    D = B - C;
}

void funcionE() {
    std::cout << "Ejecutando funcionE" << std::endl;
    E = A / D;
}

int main() {
    #pragma omp parallel sections
    {
    	#pragma omp section
        {
            funcionA();
        }

        #pragma omp section
        {
            funcionB();
        }

        #pragma omp section
        {
            funcionC();
        }
    }

    funcionD();
    funcionE();

    std::cout << "Resultado: " << E << std::endl;

    return 0;
}

