#include "MicroBit.h"
#include "../inc/drivers/MiNodeSwitch.h"


MicroBit uBit;
MiNodeSwitch switchModule(MINODE_ID_MODULE_SWITCH, A0);

void onSwitchOn(MicroBitEvent evt)
{
  uBit.display.print("ON");
}

void onSwitchOff(MicroBitEvent evt)
{
  uBit.display.print("OFF");
}


int main() {

  uBit.init();
  uBit.display.print(":)");

  switchModule.eventOn(MINODE_SWITCH_EVT_OPEN);
  switchModule.eventOn(MINODE_SWITCH_EVT_CLOSE);

  uBit.messageBus.listen(MINODE_ID_MODULE_SWITCH, MINODE_SWITCH_EVT_OPEN, onSwitchOn);
  uBit.messageBus.listen(MINODE_ID_MODULE_SWITCH, MINODE_SWITCH_EVT_CLOSE, onSwitchOff);


  while(1) {
    uBit.sleep(100);
  }

	return 0;
}