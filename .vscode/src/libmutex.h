#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <iostream>
#include <thread>
#include <mutex>


void sleep();
int max_ticket(int ticket[], int n);
void lamport_mutex_init();
void *thread_process_mutex_lamport(void *arg);
void mutex_init();
void *thread_process_mutexpthread(void *arg);
void clear();

#endif // MY_HEADER_H