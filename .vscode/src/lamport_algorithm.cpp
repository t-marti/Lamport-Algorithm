#include <iostream>
#include "libmutex.h"
#define N 3
#include <chrono>
#include <time.h>

using namespace std; 

int main(int argc, char **argv) {  
        int thread_num;
        pthread_t tinfo_process[N];
        int tinfo_id[N];
        pthread_attr_t attr;
        void *res;
        struct timespec inicio, fim;

        
        pthread_attr_init(&attr);
        /*bloco parte trabalho a*/
        cout << "rodando lamport mutex" << endl; 
        clock_gettime(CLOCK_MONOTONIC, &inicio);

        lamport_mutex_init();
        clear();
        for (thread_num = 0; thread_num < N; thread_num++) {
            tinfo_id [thread_num] = thread_num;
            pthread_create(&tinfo_process[thread_num], &attr, &thread_process_mutex_lamport, &tinfo_id[thread_num]);
        }

        pthread_attr_destroy(&attr);
        for (thread_num = 0; thread_num < N; thread_num++) {
            pthread_join(tinfo_process[thread_num], &res);
            printf("Joined with thread id %d\n", thread_num);
            free(res);
        }
        clock_gettime(CLOCK_MONOTONIC, &fim);

        double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        cout <<"Tempo de execução com mutex feito do algoritmo:" << tempo <<"segundos" << endl;



        /*bloco parte trabalho b */
        cout << " rodando mutex padrão" << endl; 
        clock_gettime(CLOCK_MONOTONIC, &inicio);
        mutex_init();
        clear();
        for (thread_num = 0; thread_num < N; thread_num++) {
            tinfo_id [thread_num] = thread_num;
            pthread_create(&tinfo_process[thread_num], &attr, &thread_process_mutexpthread, &tinfo_id[thread_num]);
        }

        pthread_attr_destroy(&attr);

        for (thread_num = 0; thread_num < N; thread_num++) {
            pthread_join(tinfo_process[thread_num], &res);
            printf("Joined with thread id %d\n", thread_num);
            free(res);
        }
        clock_gettime(CLOCK_MONOTONIC, &fim);
        tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        cout <<"Tempo de execução do algoritmo com pthread:" << tempo <<"segundos" << endl;

    return(0);
    }