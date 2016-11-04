#ifndef _MINODE_H
#define _MINODE_H

#include "MiNodeModulePool.h"
#include "MiNodeSwitch.h"

class MiNode
{

public:
  MiNode() {

  }

  ~MiNode() {

  }

  MiNodeModulePool<MiNodeSwitch> switchs;
};

#endif