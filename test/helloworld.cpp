#include "MicroBit.h"
#include "../inc/drivers/MiNodeSwitch.h"


MicroBit uBit;

void onSwitchOn(MicroBitEvent evt)
{
  uBit.display.print("ON");
}

int main() {

  uBit.init();

  MiNodeSwitch switchModule(MINODE_ID_MODULE_SWITCH, A0);
  switchModule.eventOn(MINODE_SWITCH_EVT_OPEN);

  uBit.messageBus.listen(MINODE_ID_MODULE_SWITCH, MINODE_SWITCH_EVT_OPEN, onSwitchOn);


  while(1) {
    uBit.sleep(100);
  }

	return 0;
}