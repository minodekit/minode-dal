#include "MiNodeConn.h"

MiNodeConn::MiNodeConn(int id, PinName p0, PinName p1) :
  P0 (id, p0, PIN_CAPABILITY_ALL),
  P1 (id + 1, p1, PIN_CAPABILITY_ALL)
{

}