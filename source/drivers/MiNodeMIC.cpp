#include "MiNodeMIC.h"

MiNodeMIC::MiNodeMIC(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  count = 0;
  currentAD = -1;
  system_timer_add_component(this);
}

MiNodeMIC::MiNodeMIC(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  count = 0;
  currentAD = -1;
  system_timer_add_component(this);
}

void MiNodeMIC::systemTick()
{
  count++;

  if (count == 20)
  {
    if (currentAD == -1)
    {
      currentAD = getADvalue();
    }
    else
    {
      if ((getADvalue() - currentAD > MINODE_MIC_NOISE_THRESHOLD) || (getADvalue() - currentAD < (0-MINODE_MIC_NOISE_THRESHOLD)))
      {
        MicroBitEvent evt(MINODE_ID_MODULE_MIC,MINODE_MIC_EVT_NOISE);
        currentAD = getADvalue();
      }
    }
    count = 0;
  }
}

int MiNodeMIC::getADvalue()
{
  int temp=0;

  for (int i = 0; i < 3; ++i)
  {
    temp+=pin.read_u16();
  }
  temp /= 3;

  return temp;
}

MiNodeMIC::~MiNodeMIC()
{
    system_timer_remove_component(this);
}

