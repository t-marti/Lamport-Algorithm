#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <iostream>
#include <thread>
#include <mutex>

static void lamport_mutex_lock(int thread_id);
static void lamport_mutex_unlock(int thread_id);
void sleep();
int max_ticket(int ticket[], int n);
void lamport_mutex_init();
void *thread_process_mutex_lamport(void *arg);
void mutex_init();
void *thread_process_mutexpthread(void *arg);

#endif // MY_HEADER_H