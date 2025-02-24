#include <iostream>
#include <omp.h>
#include <chrono>

float a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
auto startTime = std::chrono::steady_clock::now(); // Marca de tiempo inicial

void printTime(const std::string& functionName) {
    auto endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << functionName << " terminó en " << elapsed.count() << " ms" << std::endl;
}

void funcionA() {
    std::cout << "Ejecutando funcionA" << std::endl;
    for (int i = 0; i < 10; i++) {
        a += 1;
    }
    printTime("funcionA");
}

void funcionB() {
    std::cout << "Ejecutando funcionB" << std::endl;
    b = 1;
    for (int i = 1; i <= 10; i++) {
        b *= i;
    }
    printTime("funcionB");
}

void funcionC() {
    std::cout << "Ejecutando funcionC" << std::endl;
    c = 123 * (c + 1000);
    printTime("funcionC");
}

void funcionD() {
    std::cout << "Ejecutando funcionD" << std::endl;
    d = b * c;
    printTime("funcionD");
}

void funcionE() {
    std::cout << "Ejecutando funcionE" << std::endl;
    e = f / d;
    printTime("funcionE");
}

void funcionF() {
    std::cout << "Ejecutando funcionF" << std::endl;
    f = a * b * 100;
    printTime("funcionF");
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        funcionB();

        #pragma omp section
        funcionC();

        #pragma omp section
        funcionA();
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        funcionD();

        #pragma omp section
        funcionF();
    }

    funcionE();

    std::cout << "Resultado: " << e << std::endl;

    return 0;
}

