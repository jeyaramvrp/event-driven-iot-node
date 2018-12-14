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


