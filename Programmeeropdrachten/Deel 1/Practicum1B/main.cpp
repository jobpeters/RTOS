//
// Created by job_p on 13-9-2019.
//
// start practicum 1B
//

#include <pthread.h>
#include <sched.h>
#include <stdio.h>

pthread_attr_t tattr;
pthread_t tid;
int ret;
int inf;
int newprio = 20;
sched_param param;


void *arg;

void* finite(void *pVoid) {
    int counter = 10;
    int i, j, m, n;
    while (counter != 0) {
        printf("counter:  %i\n", counter);
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
                /* De for-lussen dienen om een vertraging te
                realiseren, zodater een aantal keer een context
                switch naar taak 2 optreedt */
            }
        }
        counter--;
    }
}

void* infinite(void *pVoid) {
    int *taak = (int *)pVoid;
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak %i %i\n",taak,  j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
                /* De for-lussen dienen om een vertraging te
                realiseren, zodater een aantal keer een context
                switch naar taak 2 optreedt */

            }
        }
    }
}
int main() {
    /* initialized with default attributes */
    ret = pthread_attr_init(&tattr);

    /* safe to get existing scheduling param */
    ret = pthread_attr_getschedparam (&tattr, &param);

    /* set the priority; others are unchanged */
    param.sched_priority = newprio;

    /* setting the new scheduling param */
    ret = pthread_attr_setschedparam (&tattr, &param);
    ret = pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    /* with new priority specified */
    ret = pthread_create (&tid, &tattr, finite, NULL);
    ret = pthread_create (&tid, &tattr, finite, NULL);
    ret = pthread_join(tid, NULL);

    inf = pthread_attr_init(&tattr);
    inf = pthread_attr_setschedpolicy(&tattr, SCHED_RR);
    inf = pthread_create (&tid, &tattr, infinite, (void *)1);
    inf = pthread_create (&tid, &tattr, infinite, (void *)2);
    inf = pthread_join(tid, NULL);
    return 0;
}

//
// end practicum 1B
//