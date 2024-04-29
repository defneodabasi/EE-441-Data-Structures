#include "queue.h"
#include <iostream>


using namespace std;

/* Class implementation */
// Queue constructor

//initialize queue front, rear, count

Queue::Queue(void): qfront(0), qrear (0), qcount(0)
{}

//Queue Modification Operations

// QInsert: insert item into the queue
void Queue::QInsert(const int& item)
{
    // terminate if queue is full
    if (qcount==MaxQSize)
    {
        cerr<<"Queue overflow!" <<endl;
        exit(1);
    }
    //increment count, assign item to qlist and update rear
    qcount++;
    qlist[qrear] =item;
    qrear=(qrear+1)%MaxQSize;
}

//QDelete : delete element from the front of the queue and return its value
int Queue::QDelete(void)
{
    int temp;
    // if qlist is empty, terminate the program
    if (qcount==0)
    {
        cerr<<"Deleting from an empty queue!"<<endl;
    }
    //record value at the front of the queue
    temp=qlist[qfront];
    //decrement count, advance front and return former front
    qcount--;
    qfront=(qfront+1) % MaxQSize;
    return temp;
}

//clear queue
void Queue::ClearQueue(void)
{
    qfront=0;
    qrear=0;
    qcount=0;
}

//Queue Access
int Queue::QFront(void) const
{
    int temp;
    // if qlist is empty, terminate the program
    if (qcount==0)
    {
        cerr<<"Accessing to an empty queue!"<<endl;
    }
    //record value at the front of the queue
    temp=qlist[qfront];
    return temp;
}

//Queue Test Methods
int Queue::QLength(void) const
{
    return qcount;
}

int Queue::QEmpty(void) const
{
    return qcount==0;
}

int Queue::QFull(void) const
{
    return qcount==MaxQSize;
}

