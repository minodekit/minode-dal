#include "MiNodeSwitch.h"

MiNodeSwitch::MiNodeSwitch(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  pin.mode(PullNone);
  system_timer_add_component(this);
}

MiNodeSwitch::MiNodeSwitch(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  pin.mode(PullNone);
  system_timer_add_component(this);
}

void MiNodeSwitch::eventOn()
{
  pin.rise(this, &MiNodeSwitch::onOpen);
  pin.fall(this, &MiNodeSwitch::onClose);
}

void MiNodeSwitch::onOpen()
{
  MicroBitEvent evt(MINODE_ID_MODULE_SWITCH,MINODE_SWITCH_EVT_OPEN);
}

void MiNodeSwitch::onClose()
{
  MicroBitEvent evt(MINODE_ID_MODULE_SWITCH,MINODE_SWITCH_EVT_CLOSE);
}

int MiNodeSwitch::isOpened()
{
  return pin.read();
}

void MiNodeSwitch::systemTick()
{
}

MiNodeSwitch::~MiNodeSwitch()
{
    system_timer_remove_component(this);
}

