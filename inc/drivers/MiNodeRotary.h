#ifndef MINODE_VRES_H
#define MINODE_VRES_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

#define MINODE_ROTARY_EVT_CHANGE                  1

class MiNodeRotary : public MicroBitComponent
{
public:

  MiNodeRotary(int id, ConnName connName);
  MiNodeRotary(int id, PinName pinName);

  float getVolt();
  int getADValue();

  virtual void systemTick();
  ~MiNodeRotary();

private:
  AnalogIn pin;
  int currentAD;
  int count;
  
};

#endif