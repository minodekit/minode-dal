#include "MiNodePIR.h"

MiNodePIR::MiNodePIR(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  pin.mode(PullNone);
  pin.rise(this, &MiNodePIR::onTrigger);
  system_timer_add_component(this);
}

MiNodePIR::MiNodePIR(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  pin.mode(PullNone);
  pin.rise(this, &MiNodePIR::onTrigger);
  system_timer_add_component(this);
}

void MiNodePIR::eventOn()
{
  pin.rise(this, &MiNodePIR::onTrigger);
}

void MiNodePIR::onTrigger()
{
  MicroBitEvent evt(MINODE_ID_MODULE_PIR,MINODE_PIR_EVT_TRIG);
}

int MiNodePIR::readPir()
{
	return pin.read();
}

void MiNodePIR::systemTick()
{
}

MiNodePIR::~MiNodePIR()
{
    system_timer_remove_component(this);
}

