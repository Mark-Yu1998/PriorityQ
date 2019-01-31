/*
 * G. Yu(Mark)
 * Nov 14, 2018
 */

/*
 * Assume the bigger the number is, the more prioritized it it on the heap(queue)
 * Library used: iostream, cmath for square root
 * default constructor would set the capacity to 15 automatically, and the overloaded constructor would take a integer from user as the maximum capacity.
 * Copy constructor and overloaded assignment operator would set the current priority queue equal to another priority queue.
 * enqueue would take a number from the user, and check if it's a prime number, if it is, return, do not add it to the queue, otherwise, proceed. Add the new element at the end of the queue
 * then heapify it up, until it got to its current position (parent > children)
 * Deque method would remove the element in priority queue, return the maximum value from the queue, which is the first element, then reorganize the queue, so it goes back to a max heap
 * If the queue is empty, it would return negative one as value.
 * Flush method will remove all multiple of x from the user. The method will do nothing if there is a empty queue. Otherwise, it would put all the non multiple of x into an array, then copy it back
 * to the heap array after clearing it.
 *
 * Swap method would simple switch two element in the array by swapping elements in the given index
 * Resize method will invoke only if the size exceed the capacity. It would move all element to a new array allocated on the heap, then delete the current array, set it equal to the new one
 * isPrime method is a internal filtering method, it would determine if a number is prime or not. It also allow the user to flush only odd numbers by accepting a boolean for the odd only state
 * Clear method would "clear" the queue by setting the access index(size) to 0
 * isEmpty would return true if the queue is empty, otherwise, return false
 * get size will return the size of the heap
 *
 * The destructor would delete the memory allocation of the heap on the heap;
 */

#include "flushQ.h"
#include <iostream>
#include <cmath>

using namespace std;

flushQ::flushQ() {
    size = 0;
    MAX_CAP = 15;
    heap = new int[MAX_CAP + 1];
}

flushQ::flushQ(const unsigned int CAP) {
    size = 0;
    MAX_CAP = CAP;
    heap = new int[MAX_CAP + 1];
}

flushQ::flushQ(const flushQ &ref) {
    size = ref.size;
    MAX_CAP = ref.MAX_CAP;
    heap = new int[MAX_CAP + 1];
    for (unsigned int i = 1; i < ref.size + 1; i++) {
        heap[i] = ref.heap[i];
    }
}

flushQ flushQ::operator=(const flushQ &rhs) {
    if (this != &rhs) {
        delete[] this->heap;
        size = rhs.size;
        MAX_CAP = rhs.MAX_CAP;
        heap = new int[MAX_CAP + 1];
        for (unsigned int i = 1; i < rhs.size + 1; i++) {
            heap[i] = rhs.heap[i];
        }
        return *this;
    }
    return *this;
}

void flushQ::enqueue(int num) {
    if (isPrime(num)) {
        return;
    }
    size++;
    if (size > MAX_CAP) {
        resize();
    }

    heap[size] = num;
    unsigned int current = size;
    unsigned int parent = (current) / 2;

    while (current > 1 && heap[parent] < heap[current]) {
        swap(parent, current);
        current = parent;
        parent = (current) / 2;
    }
}

int flushQ::deque() {
    if (!isEmpty()) {
        int val = heap[1];
        unsigned int first = 1;
        unsigned int last = size;
        swap(last, first);
        size--;
        bool done = false;
        unsigned int current = 1;
        while (!done && (2 * current) <= size) {
            unsigned int left = 2 * current;
            unsigned int right = 2 * current + 1;
            unsigned int largest = current;
            if (heap[left] > heap[current]) {
                largest = left;
            }
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest != current) {
                swap(largest, current);
                current = largest;
            } else {
                done = true;
            }
        }
        return val;
    }
    return -1;
}

void flushQ::flush(int x, bool odd_State) {
    if (isEmpty()) {
        return;
    }
    x = (odd_State)?2:x;
    unsigned int count = 0;
    for (unsigned int i = 1; i <= size; i++) {
        if (odd_State){
            if (heap[i] % x == 0){
                count++;
            }
        } else if (heap[i] % x != 0) {
            count++;
        }
    }
    int *leftOver = new int[count];
    unsigned int index = 0;
    for (unsigned int i = 1; i <= size && index < count; i++) {
        if (odd_State){
            if (heap[i] % 2 == 0){
                leftOver[index] = heap[i];
                index++;
            }
        }else if (heap[i] % x != 0) {
            leftOver[index] = heap[i];
            index++;
        }
    }
    clear();
    for (unsigned int j = 0; j < count; j++) {
        enqueue(leftOver[j]);
    }
    delete[] leftOver;
}


void flushQ::swap(unsigned int &from, unsigned int &to) {
    if (size == 0) {
        return;
    }
    int temp = heap[from];
    heap[from] = heap[to];
    heap[to] = temp;
}

void flushQ::resize() {
    MAX_CAP *= 2;
    int *temp = new int[MAX_CAP + 1];
    for (unsigned int i = 1; i < size + 1; i++) {
        temp[i] = heap[i];
    }
    delete[] heap;
    heap = temp;
}

bool flushQ::isPrime(int num) {
    if (abs(num) < 2){
        return false;
    }
    for (int i = 2; i < sqrt(abs(num)); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void flushQ::clear() {
    size = 0;
}

bool flushQ::isEmpty() {
    return size == 0;
}

int flushQ::getSize() {
    return size;
}

flushQ::~flushQ() {
    delete[] heap;
}
