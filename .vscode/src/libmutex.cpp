#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <iostream>
#include "libmutex.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#define N 3
using namespace std;
#define EXEC 1000
int choosing [N];
int ticket [N];
int contador=0; 
pthread_mutex_t *mutex;


/*O objetivo é fazer o comportamento de um mutex com as threads
---
O algoritmo de Lamport é um algoritmo de exclusão mútua que usa um
vetor de tickets para controlar o acesso à seção crítica.
Cada thread solicita um ticket, e o thread com o menor ticket pode
entrar na seção crítica.*/

// estrutura do mutex 
class Mutex {
  public:
    static void lamport_mutex_lock(int thread_id) {
        int max= 0;
        choosing[thread_id]=1;
    __sync_synchronize();    // Memory barrier (garante ordem de execução)
        for(int i=0; i<N; i++){
            if(ticket[i]>max)
                max = ticket[i];
        }
        ticket[thread_id] = max + 1; 
        choosing[thread_id]=0;
        for(int j=0; j<N; j++){
            while(choosing[j]);
            while(ticket[j] != 0 && 
                  (ticket[j] < ticket[thread_id] || 
                   (ticket[j] == ticket[thread_id] && j < thread_id)));
        }
    }

    static void lamport_mutex_unlock(int thread_id) {
        __sync_synchronize(); // Memory barrier
        ticket[thread_id] = 0; // Libera a seção crítica
    }
};


void sleep () {
        usleep((rand() % 11) * 100000); /* dormir 0, 100, 200, ..., 1000 milissegundos */
      }
      

int max_ticket() {
        int i, max = ticket[0];
        for (i = 1; i < N; i++)
          max = ticket[i] > max ? ticket[i] : max;
        return max;
      }
      
void lamport_mutex_init()
{
        int arg = 0;
        for (int i = 0; i < N; i++) {
            ticket[i] = 0;
            choosing[i] = 0;
        }
        cout << "Mutex initialized" << endl;  
}

void *thread_process_mutex_lamport(void *arg){

  int thread_id = *((int*) arg);
  for(int i=0; i<EXEC; i++){
    Mutex::lamport_mutex_lock(thread_id);
    contador++;
    Mutex::lamport_mutex_unlock(thread_id);
  }

}
// estrutura padrão c++
void mutex_init(){
  pthread_mutex_init(mutex, NULL);
}


void *thread_process_mutexpthread(){

  for(int i=0; i<EXEC; i++){
    pthread_mutex_lock(mutex);
    contador++;
    pthread_mutex_unlock(mutex);
  }

}


#endif // MY_HEADER_H