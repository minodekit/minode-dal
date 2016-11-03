#include "MiNodeFan.h"

MiNodeFAN::MiNodeFAN(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  system_timer_add_component(this);
}

MiNodeFAN::MiNodeFAN(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  system_timer_add_component(this);
}

void MiNodeFAN::systemTick()
{

}

void MiNodeFAN::fanOpen()
{
	pin.write(1);
}

void MiNodeFAN::fanClose()
{
	pin.write(0);
}

MiNodeFAN::~MiNodeFAN()
{
    system_timer_remove_component(this);
}

