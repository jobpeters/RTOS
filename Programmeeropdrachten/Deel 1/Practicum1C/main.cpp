#include <iostream>
#include <pthread.h>
#include <ctime>

pthread_t tid1, tid2;
pthread_attr_t tattr;

void *thread1(void *arg) {
    std::string threadnaam = "thread1";
    int periodenummer = 1;
    struct timespec deadline;
    long period=100000L;
    clock_gettime(CLOCK_MONOTONIC, &deadline);
    std::time_t t = std::time(0);
    do {

        std::cout << "naam: " << threadnaam << ", Periodenummer: " << std::to_string(periodenummer) << ", timestamp: " << t << std::endl << std::flush;
        deadline.tv_nsec=deadline.tv_nsec+period;
        if (deadline.tv_nsec>=1000000000L) {
            deadline.tv_nsec-=1000000000L;
            ++deadline.tv_sec;
        }
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
        periodenummer++;
    }while(1);
}
void *thread2(void *arg) {
    std::string threadnaam = "thread2";
    int periodenummer = 1;
    struct timespec deadline;
    long period=100000L;
    clock_gettime(CLOCK_MONOTONIC, &deadline);
    std::time_t t = std::time(0);
    do {

        std::cout << ", naam: " << threadnaam << ", Periodenummer: " << std::to_string(periodenummer) << ", timestamp: " << t << std::endl << std::flush;
        deadline.tv_nsec=deadline.tv_nsec+period;
        if (deadline.tv_nsec>=1000000000L) {
            deadline.tv_nsec-=1000000000L;
            ++deadline.tv_sec;
        }
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
        periodenummer++;
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