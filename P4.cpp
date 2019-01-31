/*
 * G. Yu(Mark)
 * Nov 14, 2018
 */

/*
 * Library use: iostream
 * UI: No user interface is required.
 * uses a random number generator(Generated 100 integers from 1 to 200)
 * enqueues enough integers to exceed capacity(the default capacity is 15)
 * flushes all even numbers(actually flushed 2, because all other even number did not get stored in the queue, because the queue stores only nonprime number)
 * dequeues at least half the flushQ object’s contents
 * enqueues enough integers to exceed capacity again
 * flushes all odd numbers(most of odd numbers are prime, The number left are all non primes, but some odd numbers are left,
 * such as 9,27,21, when flushing, if flush all odd is needed, pass in true for second parameter for flush function)
 * dequeues and outputs to Console the first 5 numbers from the flushQ object
 */
#include <iostream>
#include "flushQ.h"

using namespace std;

void init(int tests[], const int &size) {
    srand(time(NULL));
    const int MAX = 100;
    const int MIN = 1;
    for (int i = 0; i < size; i++) {
        tests[i] = rand() % MAX + MIN;
    }
}

void enqueue(int tests[], const int &size, flushQ &prioQ) {
    for (int i = 0; i < size; i++) {
        prioQ.enqueue(tests[i]);
    }
}

void dequeue(flushQ &prioQ, const double &deQ_Fact) {
    int size = prioQ.getSize();
    for (unsigned int i = 0; i < size * deQ_Fact; i++) {
        prioQ.deque();
    }
}

void enQ_flushEven_DeQ(flushQ &prioQ, const int &size, int tests[]) {
    enqueue(tests, size, prioQ);
    const int X = 2;
    const double DEQ_FACTOR = 0.50;
    //Flushing all even numbers
    prioQ.flush(X,false);
    //Dequeue at least half of it
    dequeue(prioQ, DEQ_FACTOR);

}

void enQ_FlushOdd_output(flushQ &prioQ, const int &size, int tests[]) {
    //enqueue again
    enqueue(tests, size, prioQ);
    //flush all odd numbers
    const int X = 1;
    prioQ.flush(X,true);
    //Output the first 5 elements, if the priority queue is empty, print nothing
    const int OUTPUT = 5;
    bool done = prioQ.isEmpty();
    for (int i = 0; i < OUTPUT && !done; i++) {
        cout << prioQ.deque() << " ";
        done = prioQ.isEmpty();
    }
    cout << endl;
}

int main() {
    flushQ prioQ;

    const int TEST_CAP_1 = 35;

    int tests_1[TEST_CAP_1];
    init(tests_1,TEST_CAP_1);
    enQ_flushEven_DeQ(prioQ,TEST_CAP_1,tests_1);

    //Generate numbers again
    const int TEST_CAP_2 = 80;
    int tests_2[TEST_CAP_2];
    init(tests_2,TEST_CAP_2);
    enQ_FlushOdd_output(prioQ,TEST_CAP_2,tests_2);
    return 0;
}

