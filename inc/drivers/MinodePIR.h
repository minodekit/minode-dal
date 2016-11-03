#ifndef MINODE_PIR_H
#define MINODE_PIR_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

#define MINODE_PIR_EVT_TRIG                  1
#define MINODE_PIR_EVT_CLOSE                 2

class MiNodePIR : public MicroBitComponent
{
public:

  MiNodePIR(int id, ConnName connName);
  MiNodePIR(int id, PinName pinName);

  void eventOn();
  void onTrigger();
  int readPir();

  virtual void systemTick();
  ~MiNodePIR();

private:
  InterruptIn pin;
  
};

#endif
