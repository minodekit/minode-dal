#ifndef _MINODE_MODULES_H
#define _MINODE_MODULES_H

#include "MiNodeModulePool.h"
#include "MiNodeSwitch.h"

class MiNodeModules
{

public:
  MiNodeModules() {

  }

  ~MiNodeModules() {

  }

  MiNodeModulePool<MiNodeSwitch> switchs;
};

#endif