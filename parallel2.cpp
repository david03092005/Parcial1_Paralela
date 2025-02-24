#include <iostream>
#include <pthread.h>
#include <chrono>

float A = 0, B = 0, C = 0, D = 0, E = 0, F = 0;
pthread_t threadA, threadB, threadC, threadF, threadD;

auto startTime = std::chrono::steady_clock::now(); // Marca de tiempo inicial

void printTime(const std::string& function_name) {
    auto endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << function_name << " terminó en " << elapsed.count() << " ms" << std::endl;
}

void* funcionA(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionA" << std::endl;
    for (int i = 0; i < 10; i++) {
        A += 1;
    }
    printTime("funcionA");
    pthread_exit(NULL);
}

void* funcionB(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionB" << std::endl;
    B = 1;
    for (int i = 1; i <= 10; i++) {
        B *= i;
    }
    printTime("funcionB");
    pthread_exit(NULL);
}

void* funcionC(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionC" << std::endl;
    C = 123 * (C + 1000);
    printTime("funcionC");
    pthread_exit(NULL);
}

void* funcionD(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionD" << std::endl;
    D = B * C;
    printTime("funcionD");
    pthread_exit(NULL);
}

void funcionE() {
    std::cout << "main: Ejecutando funcionE" << std::endl;
    E = F / D;
    printTime("funcionE");
}

void* funcionF(void* id) {
    std::cout << "Thread " << (long)id << ": Ejecutando funcionF" << std::endl;
    F = A * B * 100;
    printTime("funcionF");
    pthread_exit(NULL);
}

int main() {
    pthread_create(&threadA, NULL, funcionB, (void*)(long)0);
    pthread_create(&threadB, NULL, funcionC, (void*)(long)1);
    pthread_create(&threadC, NULL, funcionA, (void*)(long)2);

    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    pthread_create(&threadD, NULL, funcionD, (void*)(long)3);
    pthread_join(threadA, NULL);
    pthread_create(&threadF, NULL, funcionF, (void*)(long)4);

    pthread_join(threadD, NULL);
    pthread_join(threadF, NULL);

    funcionE();

    std::cout << "Resultado: " << E << std::endl;

    return 0;
}

