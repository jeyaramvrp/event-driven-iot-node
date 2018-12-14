#include <iostream>
#include "include/iotDataQueue.h"
#include "include/iotHumiditySensor.h"
#include "include/iotTempSensor.h"
#include "include/iotState.h"
//this is an example
using namespace std;

int main()
{
  void(NodeManager:: *ptrs[])() =
  {
    NodeManager::idle, NodeManager::sense, NodeManager::command
  };
  NodeManager nodemgr;
  int num;
  while (1)
  {
    cout << "Enter 0/1/2: ";
    cin >> num;
    if(num >= 0 && num <= 2) {
        (nodemgr.*ptrs[num])();

        if(num == 1) {
            cout << "   Enabling Sensors... \n";
            nodemgr.h.enabledisable(nodemgr.h.id, SENSOR_ENABLE);
            nodemgr.t.enabledisable(nodemgr.t.id, SENSOR_ENABLE);
        }
        else if(num == 2){
                if(nodemgr.t.status == SENSOR_ENABLE && nodemgr.h.status == SENSOR_ENABLE)
        {
          int cmd;
          int readdata = 0;

          while (1)
          {
              cout << "\nSensors status: Enabled \n";
              cout << "1.Print Sensor Properties \n";
              cout << "2.Read Temperature \n";
              cout << "3.Read Humidity \n";
              cout << "4.Print Data Queue(s) \n";
              cout << "99.Exit \n";
              cout << "Command[1-4]: ";
              cin >> cmd;

              if(cmd == 99)
                break;
            if(cmd >= 1 && cmd <= 4) {
                switch(cmd)
                {
                case 1:
                    nodemgr.t.printproperties();
                    nodemgr.h.printproperties();
                    break;
                case 2:
                    readdata = nodemgr.t.read();
                    cout << "\n Temp Value:"<<readdata;
                    nodemgr.temperature.qput(readdata);
                    break;
                case 3:
                    readdata = nodemgr.h.read();
                    cout << "\n Humidity Value:"<<readdata;
                    nodemgr.humidity.qput(readdata);
                    break;
                case 4:
                    cout << "\n Humidity Queue:";
                    while((readdata=nodemgr.humidity.qget()) != 0)
                          cout <<readdata<<"\t";

                    cout << "\n Temp Queue:";
                    while((readdata=nodemgr.temperature.qget()) != 0)
                          cout <<readdata<<"\t";
                    break;
                }
            }
          }
        }
        else
        {
            cout << "\nSensors status: Disabled \n";
        }
        }
    }
  }

  return 0;
}
