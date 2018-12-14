#ifndef IOTTEMPSENSOR_H
#define IOTTEMPSENSOR_H

#include "iotSensor.h"

class TempSensor:public Sensor
{
    public:
        TempSensor();
       ~TempSensor();
        int read();
        void enabledisable(int id, int enadis);
        void printproperties();

    private:
        int min;
        int max;
        int accuracy;
};

#endif // IOTTEMPSENSOR_H
