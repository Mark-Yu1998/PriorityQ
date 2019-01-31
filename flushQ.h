/*
 * G. Yu(Mark)
 * Nov 14, 2018
 */

/*
 *  Priority: The greater the number is, the more prioritized it is.
 *  supports the standard Q operations but stores only non-prime numbers, orders items by their value (priority),uses an internal heap data structure.
 *  The priority queue would be constructed using a integer array.
 *  The flushQ allows deep copying.
 *  provides basic queue operation and filtering. Enqueuing, filter and store only non-prime numbers. Deque will remove and return the first element in the queue.
 *  Copy constructor and overloaded assignment operator allow user to pass in another flushQ object and setting it equal to another flushQ object.
 *  It also support flushing all the multiple of a number in the queue. Duplication is allowed in the queue
 *  Other utilities functions include clear - clear the queue, isEmpty- return the current state of the queue - empty or not. getSize- return the size of the queue
 *
 *  Private members include: size of the queue, the maximum capacity, and the array pointer(the heap), filter function isPrime, and swap function. internal resizing is supported if the size is greater
 *  then the capacity. Double the capacity of the heap.
 *
 */
#ifndef P4_FLUSHQ_H
#define P4_FLUSHQ_H


class flushQ {
public:
    flushQ();

    flushQ(const unsigned int CAP);

    flushQ(const flushQ &ref);

    ~flushQ();

    flushQ operator=(const flushQ &rhs);

    void enqueue(int num);

    int deque();

    void flush(int x, bool odd_state);

    void clear();

    bool isEmpty();

    int getSize();

    void print();

private:
    unsigned int size;
    unsigned int MAX_CAP;
    int *heap;
    bool isPrime(int num);
    void resize();
    void swap(unsigned int &from, unsigned int &to);
};

#endif //P4_FLUSHQ_H
