#ifndef MINODE_SWITCH_H
#define MINODE_SWITCH_H

#include "mbed.h"
#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"


#define MINODE_SWITCH_EVT_OPEN                  1
#define MINODE_SWITCH_EVT_CLOSE                 2

class MiNodeSwitch : public MicroBitComponent
{
public:
  MiNodeSwitch();
  MiNodeSwitch(ConnName connName);
  ~MiNodeSwitch();

  void initConnector(ConnName connName);
  ConnName getConnector();
  int getId();
  int isOpened();

protected:

  void onOpen();
  void onClose();
  void eventOn();

private:
  ConnName _connName;
  InterruptIn* pin;
};

#endif