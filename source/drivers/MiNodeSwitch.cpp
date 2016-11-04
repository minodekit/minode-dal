#include "MiNodeSwitch.h"


MiNodeSwitch::MiNodeSwitch() :
_connName(MN_NC),
pin(NULL)
{
  this->id = MINODE_ID_NC;
}

MiNodeSwitch::MiNodeSwitch(ConnName connName) :
_connName(connName),
pin(NULL)
{
  this->id = MiNodeConn::calcId(connName);
}

MiNodeSwitch::~MiNodeSwitch()
{
  if(pin) {
    delete pin;
  }
}

void MiNodeSwitch::initConnector(ConnName connName)
{
  if(_connName != MN_NC) {
    return;
  }

  _connName = connName;
  this->id = MiNodeConn::calcId(connName);
  eventOn();
}

ConnName MiNodeSwitch::getConnector()
{
  return _connName;
}

int MiNodeSwitch::getId()
{
  return MINODE_ID_MODULE_SWITCH + this->id;
}

void MiNodeSwitch::eventOn()
{
  PinName pinName = MiNodeConn::calcP0Name(_connName);
  if(pin) {
    delete pin;
  }
  pin = new InterruptIn(pinName);

  pin->mode(PullNone);
  pin->rise(this, &MiNodeSwitch::onOpen);
  pin->fall(this, &MiNodeSwitch::onClose);
}

void MiNodeSwitch::onOpen()
{
  MicroBitEvent(MINODE_ID_MODULE_SWITCH + id, MINODE_SWITCH_EVT_OPEN);
}

void MiNodeSwitch::onClose()
{
  MicroBitEvent(MINODE_ID_MODULE_SWITCH + id, MINODE_SWITCH_EVT_CLOSE);
}

int MiNodeSwitch::isOpened()
{
  int status = 0;
  if(pin) {
    status = pin->read();
  }
  return status;
}