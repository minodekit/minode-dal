#include "MiNodeMIC.h"

MiNodeMIC::MiNodeMIC(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName)),currentAD(-1)
{
  this->id = id;
  count = 0;
  system_timer_add_component(this);
}

MiNodeMIC::MiNodeMIC(int id, PinName pinName) :
pin(pinName),currentAD(-1)
{
  this->id = id;
  count = 0;
  system_timer_add_component(this);
}

void MiNodeMIC::systemTick()
{
  count++;
  int temp_ad=0;

  if (count == 20)
  {
    if (currentAD == -1)
    {
      currentAD = getADvalue();
    }
    else
    {
      temp_ad = getADvalue();
      if ((temp_ad - currentAD > MINODE_MIC_NOISE_THRESHOLD) || (temp_ad - currentAD < (0-MINODE_MIC_NOISE_THRESHOLD)))
      {
        MicroBitEvent evt(MINODE_ID_MODULE_MIC,MINODE_MIC_EVT_NOISE);
        currentAD = temp_ad;
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

