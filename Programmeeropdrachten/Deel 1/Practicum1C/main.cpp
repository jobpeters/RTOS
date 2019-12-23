#include <iostream>
#include <pthread.h>
#include <ctime>
#include <chrono>
#include <thread>

pthread_t tid1, tid2;
pthread_attr_t tattr;

void *thread1(void *arg) {
    std::string threadnaam = "thread1";
    int periodenummer = 0;
    struct timespec deadline;
    const auto timeWindow = std::chrono::milliseconds(500);
    do {
        auto start = std::chrono::steady_clock::now();
        std::cout << "naam: " << threadnaam << ", Periodenummer: " << std::to_string(periodenummer) << std::endl << std::flush;
        periodenummer++;
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;

        auto timeToWait = timeWindow - elapsed;
        if(timeToWait > std::chrono::milliseconds::zero())
        {
            std::this_thread::sleep_for(timeToWait);
        }
    }while(1);
}
void *thread2(void *arg) {
    std::string threadnaam = "thread2";
    int periodenummer = 0;
    struct timespec deadline;
    const auto timeWindow = std::chrono::milliseconds(1300);
    do {
        auto start = std::chrono::steady_clock::now();
        std::cout << "naam: " << threadnaam << ", Periodenummer: " << std::to_string(periodenummer) << std::endl << std::flush;
        periodenummer++;
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;

        auto timeToWait = timeWindow - elapsed;
        if(timeToWait > std::chrono::milliseconds::zero())
        {
            std::this_thread::sleep_for(timeToWait);
        }
    }while(1);
}
int main() {
    pthread_attr_init(&tattr);
    pthread_create(&tid1, &tattr, thread1, NULL);
    pthread_create(&tid2, &tattr, thread2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}