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
    cout << "Enter 0/1/2/99: ";
    cin >> num;
    if(num >= 0 && num <= 2) {
        (nodemgr.*ptrs[num])();
    }
    else
        break;
  }
  return 0;
}
