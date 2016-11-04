#ifndef MINODE_MIC_H
#define MINODE_MIC_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

#define MINODE_MIC_EVT_NOISE                  1

#define MINODE_MIC_NOISE_THRESHOLD            50

class MiNodeMIC : public MicroBitComponent
{
public:

  MiNodeMIC(int id, ConnName connName);
  MiNodeMIC(int id, PinName pinName);

  void eventOn();
  int isOpened();
  int getADvalue();

  virtual void systemTick();
  ~MiNodeMIC();

private:
  AnalogIn  pin;
  int count;
  int currentAD;
  
  void onOpen();
  void onClose();
};

#endif