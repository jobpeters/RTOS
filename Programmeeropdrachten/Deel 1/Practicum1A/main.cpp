//
// Created by job_p on 13-9-2019.
//

#include <stdio.h>
#include <pthread.h>

pthread_attr_t tattr;
pthread_t tid;

void* taskOne(void *Pvoid)
{
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 1 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodater een aantal keer een context
switch naar taak 2 optreedt */
            }
        }
    }
}
void* taskTwo(void *Pvoid)
{
    int i,j,m,n;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            for(j=1;j<=8;j++)
            {
                printf("taak 2 %i\n",j);
                for (m=0;m<=1000;m++)
                    for(n=0;n<=10000;n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 4 optreedt */
            }
        }
    }
}
void* taskThree(void *Pvoid)
{
    int i,j,m,n;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            for(j=1;j<=8;j++)
            {
                printf("taak 3 %i\n",j);
                for (m=0;m<=1000;m++)
                    for(n=0;n<=10000;n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 4 optreedt */
            }
        }
    }
}

void* taskFour(void *Pvoid)
{
    int i,j,m,n;
    while(1)
    {
        for(i=0;i<5;i++)
        {
            for(j=1;j<=8;j++)
            {
                printf("taak 4 %i\n",j);
                for (m=0;m<=1000;m++)
                    for(n=0;n<=10000;n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 3 optreedt */
            }
        }
    }
}

int main() {
    pthread_attr_init(&tattr); //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);// sched policy aanpassen
    pthread_create(&tid, &tattr, taskOne, NULL);
    pthread_create(&tid, &tattr, taskTwo, NULL);
    pthread_create(&tid, &tattr, taskThree, NULL);
    pthread_create(&tid, &tattr, taskFour, NULL);

    pthread_join( tid, NULL);
    return 0;
}
