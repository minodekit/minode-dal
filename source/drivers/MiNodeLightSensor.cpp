#include "MiNodeLightSensor.h"

MiNodeLight::MiNodeLight(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  sigma = 0;
  system_timer_add_component(this);
}

MiNodeLight::MiNodeLight(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  sigma = 0;
  system_timer_add_component(this);
}

void MiNodeLight::onOpen()
{
}

void MiNodeLight::onClose()
{
}

unsigned short MiNodeLight::getLight()
{
  return pin.read_u16();
}

unsigned short MiNodeLight::getLightLevel(void)
{
  unsigned short currnt_light = 0;
  for (int i = 0; i < MINODE_LIGHT_SAMPLE_NUM; ++i)
  {
    currnt_light += getLight();
  }
  
  currnt_light /= MINODE_LIGHT_SAMPLE_NUM;

  if ((currnt_light > MICROBIT_LIGHT_MIN) && (currnt_light < MICROBIT_LIGHT_LEVEL_A+1))
  {
    return MICROBIT_LIGHT_LEVEL_1;
  }
  else if ((currnt_light > MICROBIT_LIGHT_LEVEL_A) && (currnt_light < MICROBIT_LIGHT_LEVEL_B+1))
  {
    return MICROBIT_LIGHT_LEVEL_2;
  }
  else if ((currnt_light > MICROBIT_LIGHT_LEVEL_B) && (currnt_light < MICROBIT_LIGHT_LEVEL_C+1))
  {
    return MICROBIT_LIGHT_LEVEL_3;
  }
  else if ((currnt_light > MICROBIT_LIGHT_LEVEL_C) && (currnt_light < MICROBIT_LIGHT_LEVEL_D+1))
  {
    return MICROBIT_LIGHT_LEVEL_4;
  }
  else if ((currnt_light > MICROBIT_LIGHT_LEVEL_D) && (currnt_light < MICROBIT_LIGHT_MAX+1))
  {
    return MICROBIT_LIGHT_LEVEL_5;
  }
  else
  {
    return MICROBIT_LIGHT_LEVEL_ERROR;
  }
}

void MiNodeLight::systemTick()
{
  sigma++;

  if(sigma == 100)
  {
    sigma = 0;

    status = getLightLevel();
    if(pre_status == MICROBIT_LIGHT_LEVEL_NULL)
    {
      pre_status = status;
    }

    if (status != pre_status)
    {
      pre_status = status;
      MicroBitEvent(id, MINODE_LIGHT_EVT_LEVEL_CHANGE);
    }
  }
}

MiNodeLight::~MiNodeLight()
{
    system_timer_remove_component(this);
}
