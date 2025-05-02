#include <iostream>
#include "libmutex.h"
#define N 3

using namespace std; 
int main(int argc, char **argv) {  
        int thread_num, ret;
        pthread_t tinfo_process[N];
        int tinfo_id[N];
        pthread_attr_t attr;
        void *res;
        
        ret = pthread_attr_init(&attr);
        /*bloco parte trabalho a*/
        lamport_mutex_init();
        for (thread_num = 0; thread_num < N; thread_num++) {
            tinfo_id [thread_num] = thread_num;
            ret = pthread_create(&tinfo_process[thread_num], &attr, &thread_process_mutex_lamport, &tinfo_id[thread_num]);
        }

        ret = pthread_attr_destroy(&attr);
        
        for (thread_num = 0; thread_num < N; thread_num++) {
            ret = pthread_join(tinfo_process[thread_num], &res);
            printf("Joined with thread id %d\n", thread_num);
            free(res);
        }
    
        /*bloco parte trabalho b */
        mutex_init();
        for (thread_num = 0; thread_num < N; thread_num++) {
            tinfo_id [thread_num] = thread_num;
            ret = pthread_create(&tinfo_process[thread_num], &attr, &thread_process_mutexpthread, &tinfo_id[thread_num]);
        }

        ret = pthread_attr_destroy(&attr);
        
        for (thread_num = 0; thread_num < N; thread_num++) {
            ret = pthread_join(tinfo_process[thread_num], &res);
            printf("Joined with thread id %d\n", thread_num);
            free(res);
        }
    return(0);
    }