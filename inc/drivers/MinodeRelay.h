#ifndef MINODE_RELAY_H
#define MINODE_RELAY_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

#define MINODE_RELAY_EVT_OPEN                  1

class MiNodeRELAY : public MicroBitComponent
{
public:

  MiNodeRELAY(int id, ConnName connName);
  MiNodeRELAY(int id, PinName pinName);

  void relayOpen();
  void relayClose();

  virtual void systemTick();
  ~MiNodeRELAY();

private:
  DigitalOut pin;
  
};

#endif