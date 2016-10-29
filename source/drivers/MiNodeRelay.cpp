#include "MiNodeRelay.h"

MiNodeRELAY::MiNodeRELAY(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  system_timer_add_component(this);
}

MiNodeRELAY::MiNodeRELAY(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  system_timer_add_component(this);
}

void MiNodeRELAY::systemTick()
{
}

void MiNodeRELAY::relayOpen()
{
	pin.write(1);
}

void MiNodeRELAY::relayClose()
{
	pin.write(0);
}

MiNodeRELAY::~MiNodeRELAY()
{
    system_timer_remove_component(this);
}

