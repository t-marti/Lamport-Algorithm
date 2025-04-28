#ifndef MY_HEADER_H
#define MY_HEADER_H
#include <iostream>
#include "lamport_mutex.h"

using namespace std;

class MyClass {
public:
    void myMethod();
};

int my_function(int a, int b);

#endif // MY_HEADER_H