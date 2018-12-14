#include <iostream>
#include "../include/iotState.h"

using namespace std;

class State
{
  public:
    virtual void idle(NodeManager *m)
    {
        cout << "   already idle\n";
    }
    virtual void sense(NodeManager *m)
    {
        cout << "   already sense\n";
    }
    virtual void command(NodeManager *m)
    {
        cout << "   already command\n";
    }
};

void NodeManager::idle()
{
  current->idle(this);
}

void NodeManager::sense()
{
  current->sense(this);
}

void NodeManager::command()
{
  current->command(this);
}

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE-ctor ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sense(NodeManager *m);
};

class COMMAND: public State
{
  public:
    COMMAND()
    {
        cout << "   COMMAND-ctor ";
    };
    ~COMMAND()
    {
        cout << "   dtor-COMMAND\n";
    };
    void idle(NodeManager *m)
    {
        cout << "   going from COMMAND to IDLE";
        m->t.status = SENSOR_DISABLE;
        m->h.status = SENSOR_DISABLE;
        cout << "\n Disabling Sensors... \n";
        m->setCurrent(new IDLE());
        delete this;
    }
};

class SENSE: public State
{
  public:
    SENSE()
    {
        cout << "   SENSE-ctor ";
    };
    ~SENSE()
    {
        cout << "   dtor-SENSE\n";
    };
    void command(NodeManager *m)
    {
        cout << "\n   going from SENSE to COMMAND";
        #if 0
        if(m->t.status == SENSOR_ENABLE && m->h.status == SENSOR_ENABLE)
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
                    m->t.printproperties();
                    m->h.printproperties();
                    break;
                case 2:
                    readdata = m->t.read();
                    cout << "\n Temp Value:"<<readdata;
                    m->temperature.qput(readdata);
                    break;
                case 3:
                    readdata = m->h.read();
                    cout << "\n Humidity Value:"<<readdata;
                    m->humidity.qput(readdata);
                    break;
                case 4:
                    cout << "\n Humidity Queue:";
                    while((readdata=m->humidity.qget()) != 0)
                          cout <<readdata<<"\t";

                    cout << "\n Temp Queue:";
                    while((readdata=m->temperature.qget()) != 0)
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
        #endif
        m->setCurrent(new COMMAND());
        delete this;
    }
};

void IDLE::sense(NodeManager *m)
{
  cout << "\n   going from IDLE to SENSE";
  m->setCurrent(new SENSE());
  delete this;
}

NodeManager::NodeManager()
{
  //Sensor id and serial numbers
  t.id = 100;
  h.id = 101;
  t.serialnum=4321;
  h.serialnum=1234;

  temperature.init();
  humidity.init();

  //Default state is Idle
  current = new IDLE();
  cout << '\n';
}


