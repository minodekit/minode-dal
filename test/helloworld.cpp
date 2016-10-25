#include "MicroBit.h"
#include "../inc/drivers/MiNodeSwitch.h"


MicroBit uBit;
MiNodeSwitch switch1(MINODE_ID_MODULE_SWITCH, A0);

void onSwitchOnOff(MicroBitEvent e)
{
  if(e.source == MINODE_ID_MODULE_SWITCH) {
    switch(e.value) {
      case MINODE_SWITCH_EVT_OPEN:
        uBit.display.print("ON");
        break;
      case MINODE_SWITCH_EVT_CLOSE:
        uBit.display.print("OFF");
        break;
    }
  }
}


int main() {

  uBit.init();
  uBit.display.print(":)");

  uBit.messageBus.listen(MINODE_ID_MODULE_SWITCH, MINODE_SWITCH_EVT_OPEN, onSwitchOnOff);
  uBit.messageBus.listen(MINODE_ID_MODULE_SWITCH, MINODE_SWITCH_EVT_CLOSE, onSwitchOnOff);


  while(1) {
    uBit.sleep(100);
  }


	return 0;
}