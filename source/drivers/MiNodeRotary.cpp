#include "MiNodeRotary.h"

MiNodeRotary::MiNodeRotary(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  currentAD = -1;
  count = 0;
  system_timer_add_component(this);
}

MiNodeRotary::MiNodeRotary(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  currentAD = -1;
  count = 0;
  system_timer_add_component(this);
}

void MiNodeRotary::systemTick()
{
  count++;

  if (count == 40)
  {
    if (currentAD == -1)
    {
      currentAD = getADValue();
    }
    else
    {
      if ((getADValue() - currentAD > 31) || (getADValue() - currentAD < -31))
      {
        MicroBitEvent evt(MINODE_ID_MODULE_ROTARY,MINODE_ROTARY_EVT_CHANGE);
        currentAD = getADValue();
      }
    }
    count = 0;
  }
}

float MiNodeRotary::getVolt()
{
  float result;
  result = 3.3*(getADValue()/1023.0);

  return result;
}

int MiNodeRotary::getADValue()
{
  int temp=0;
  for (int i = 0; i < 3; ++i)
  {
    temp += pin.read_u16();
  }
  temp /= 3;
  return temp;
}

MiNodeRotary::~MiNodeRotary()
{
    system_timer_remove_component(this);
}

