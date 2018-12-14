#include <iostream>
#include "../include/iotHumiditySensor.h"

using namespace std;

HumiditySensor::HumiditySensor()
{
    //ctor
    status = SENSOR_ENABLE;
    responsetime = 1;
    rhmin = -20;
    rhmax=120;
    accuracy=5;
}

HumiditySensor::~HumiditySensor()
{
    //dtor

}

int HumiditySensor::read()
{
    //Return garbage value since this application doesn't
    //involve actual sensor at this moment.
    return data%120;
}

void HumiditySensor::enabledisable(int argid, int enadis)
{
   if(argid == id && (enadis == SENSOR_ENABLE ||  enadis == SENSOR_DISABLE )) {
       status = enadis;
   }
}

void HumiditySensor::printproperties()
{
        cout<<"\nRelative Humidity Minimum:"<<rhmin<<"\n";
        cout<<"Relative Humidity Maximum:"<<rhmax<<"\n";
        cout<<"Humidity sensor accuracy:"<<accuracy<<"\n";
        cout<<"Humidity Response Time:"<<responsetime<<"\n";
}
