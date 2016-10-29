#ifndef MINODE_SWITCH_H
#define MINODE_SWITCH_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"


#define MINODE_SWITCH_EVT_OPEN                  1
#define MINODE_SWITCH_EVT_CLOSE                 2

class MiNodeSwitch : public MicroBitComponent
{
public:

  MiNodeSwitch(int id, ConnName connName);
  MiNodeSwitch(int id, PinName pinName);

  void eventOn();
  int isOpened();

  virtual void systemTick();
  ~MiNodeSwitch();

private:
  InterruptIn pin;
  
  void onOpen();
  void onClose();
};

#endif