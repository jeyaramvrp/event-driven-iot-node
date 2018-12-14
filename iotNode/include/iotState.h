#ifndef IOTSTATE_H
#define IOTSTATE_H

#include "iotDataQueue.h"
#include "iotHumiditySensor.h"
#include "iotTempSensor.h"

class NodeManager
{
  class State *current;
  public:
    NodeManager();
    void setCurrent(State *s)
    {
        current = s;
    }

    void idle();
    void sense();
    void command();

    DataQueue temperature, humidity; //create two queue objects
    TempSensor t;
    HumiditySensor h;
};

#endif
