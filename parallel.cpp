#include <iostream>
#include <pthread.h>

float A = 0;
float B = 0;
float C = 0;
float D = 0;
float E = 0;
pthread_t threadA, threadB, threadC;

void* funcionA(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionA" << std::endl;
    for (int i = 0; i < 10; i++) {
        A += 1;
    }
    pthread_exit(NULL);
}

void* funcionB(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionB" << std::endl;
    B = 1;
    for (int i = 1; i <= 10; i++) {
        B *= i;
    }
    pthread_exit(NULL);
}

void* funcionC(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionC" << std::endl;
    C = C * C;
    pthread_exit(NULL);
}

void funcionD() {
    std::cout << "main: Ejecutando funcionD" << std::endl;
    D = B - C;
}

void funcionE() {
    std::cout << "main: Ejecutando funcionE" << std::endl;
    E = A / D;
}

int main() {
    pthread_create(&threadA, NULL, funcionB, (void*)(long)0);
    pthread_create(&threadB, NULL, funcionC, (void*)(long)1);
    pthread_create(&threadC, NULL, funcionA, (void*)(long)2);

    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    funcionD();

    pthread_join(threadA, NULL);

    funcionE();

    std::cout << "Resultado: " << E << std::endl;

    return 0;
}

