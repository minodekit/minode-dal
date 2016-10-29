#ifndef MINODE_SPEAKER_H
#define MINODE_SPEAKER_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"


class MiNodeSPEAKER : public MicroBitComponent
{
public:

  MiNodeSPEAKER(int id, ConnName connName);
  MiNodeSPEAKER(int id, PinName pinName);

private:
  InterruptIn pin;
  
};

#endif