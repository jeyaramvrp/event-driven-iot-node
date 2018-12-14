#include <iostream>
#include "../include/iotTempSensor.h"

using namespace std;


TempSensor::TempSensor()
{
    //ctor
    status = SENSOR_ENABLE;
    min = -45;
    max = 145;
    accuracy=2;
}

TempSensor::~TempSensor()
{
    //dtor
}

int TempSensor::read()
{

    //Return garbage value since this application doesn't
    //involve actual sensor at this moment.
    return data%145;
}

void TempSensor::enabledisable(int argid, int enadis)
{
   if(argid == id && (enadis == SENSOR_ENABLE ||  enadis == SENSOR_DISABLE )) {
       status = enadis;
   }
}

void TempSensor::printproperties()
{
        cout<<"\nMinimum Temp:"<<min<<"\n";
        cout<<"Maximum Temp:"<<max<<"\n";
        cout<<"Temp sensor accuracy:"<<accuracy<<"\n";
}
