#include <iostream>
#include "../include/iotDataQueue.h"

using namespace std;

DataQueue::DataQueue()
{
    //ctor
}

DataQueue::~DataQueue()
{
    //dtor
}

void DataQueue::init()
{
    rloc = 0;
    sloc = 0;
}

//initialise the queue
void DataQueue::qput(int i)
{
    if(sloc==IOT_DATAQUEUE_SIZE){
        cout << "\nqueue is full. \n";
        return;
    }
    sloc++;
    cout <<"\n sloc "<<sloc<<"\t"<<i;
    q[sloc] = i;
    cout << "\nWrite is success \n";
}

//get an integer from the queue
int DataQueue::qget()
{
    if(rloc == sloc){
        cout << "\nqueue underflow. \n";
        return 0;
    }
    rloc++;
    return q[rloc];
}

