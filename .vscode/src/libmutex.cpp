#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <iostream>
#include "libmutex.h"
#include <iostream>
#include <thread>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#define NUM_THREADS 3
using namespace std;
/*O objetivo é fazer o comportamento de um mutex com as threads
O algoritmo de Lamport é um algoritmo de exclusão mútua que usa um
vetor de tickets para controlar o acesso à seção crítica.
Cada thread solicita um ticket, e o thread com o menor ticket pode
entrar na seção crítica.*/


class Mutex {
    void lamport_mutex_lock(int thread_id, int choosing[], int ticket[], int n) {
        int max= 0;
        choosing[thread_id]=1;
    __sync_synchronize();    // Memory barrier (garante ordem de execução)
        for(int i=0; i<NUM_THREADS; i++){
            if(ticket[i]>max)
                max = ticket[i];
        }
        ticket[thread_id] = max + 1; 
        choosing[thread_id]=0;
        for(int j=0; j<NUM_THREADS; j++){
            while(choosing[j]);
            while(ticket[j] != 0 && 
                  (ticket[j] < ticket[thread_id] || 
                   (ticket[j] == ticket[thread_id] && j < thread_id)));
        }
    }

    void lamport_mutex_unlock(int ticket[], int thread_id) {
        __sync_synchronize(); // Memory barrier
        ticket[thread_id] = 0; // Libera a seção crítica
    }
};



void sleep () {
        usleep((rand() % 11) * 100000); /* dormir 0, 100, 200, ..., 1000 milissegundos */
      }
      

int max_ticket(int ticket[], int n ) {
        int i, max = ticket[0];
        for (i = 1; i < n; i++)
          max = ticket[i] > max ? ticket[i] : max;
        return max;
      }
      
void  lamport_mutex_init(int &arg, int n, int *ticket, int *choosing)
{
    int j, i = *((int *) arg);

    printf("Hello! I'm threaddormir %d!\n", i);

    do {
      choosing[i] = 1;
      ticket[i] = max_ticket(ticket, n) + 1;
      choosing[i] = 0;
      for (j = 0; j < n; j++) {
              while (choosing[j]) /* nao fazer nada */;
	      while (ticket[j] != 0 && (
				      (ticket[j] < ticket[i]) || (ticket[j] == ticket[i] && j < i)
			)) /* nao fazer nada */;
      }
      
      printf("I'm thread %d and I'm entering my critical region!\n", i);
      sleep();
      printf("I'm thread %d and I'm leaving my critical region!\n", i);

      ticket[i] = 0; /* indicar que saimos da secao critica */
    } while (1);

}


#endif // MY_HEADER_H