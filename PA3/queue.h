#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

const int MaxQSize=50;
class Queue
{
private:
    // queue array and its parameters
    int qfront, qrear, qcount;
    int qlist[MaxQSize];

public:
    //constructor
    Queue(void); // initialize data members

    //queue modification operations
    void QInsert(const int& item);
    int QDelete(void);
    void ClearQueue(void);

    // queue access
    int QFront(void) const;

    // queue test methods
    int QLength(void) const;
    int QEmpty(void) const;
    int QFull(void) const;
};

#endif // QUEUE_H_INCLUDED
