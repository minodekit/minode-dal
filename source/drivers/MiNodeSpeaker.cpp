#include "MiNodeSpeaker.h"

MiNodeSPEAKER::MiNodeSPEAKER(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName))
{
  this->id = id;
  pin.mode(PullNone);
}

MiNodeSPEAKER::MiNodeSPEAKER(int id, PinName pinName) :
pin(pinName)
{
  this->id = id;
  pin.mode(PullNone);
}
