#ifndef MINODE_FAN_H
#define MINODE_FAN_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

class MiNodeFAN : public MicroBitComponent
{
public:

  MiNodeFAN(int id, ConnName connName);
  MiNodeFAN(int id, PinName pinName);

  virtual void systemTick();
  ~MiNodeFAN();

private:
  InterruptIn pin;
  
};

#endif