#include "MicroBit.h"
#include "../inc/drivers/MiNodeSwitch.h"
#include "../inc/drivers/MiNodeLightSensor.h"
#include "../inc/drivers/MiNodeDHT11.h"
#include "../inc/drivers/MiNodeRGB.h"
#include "../inc/drivers/MiNodePIR.h"
#include "../inc/drivers/MiNodeMIC.h"
#include "../inc/drivers/MiNodeRotary.h"
#include "../inc/drivers/MiNodeFan.h"
#include "mbed.h"
#include "MiNodeModules.h"

#define DEMO_STATUS_ROBOT           1
#define DEMO_STATUS_GUARD           2
#define MINODE_FAN_EVT_OPEN         3

MicroBitImage smiley("0,0,0,0,0\n0,255,0,255,0\n0,0,0,0,0\n255,0,0,0,255\n0,255,255,255,0\n");
MicroBitImage alarm("255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n");

MicroBitImage sad("0,0,0,0,0\n0,255,255,255,0\n0,255,255,255,0\n0,255,255,255,0\n0,0,0,0,0\n");
MicroBitImage sad1("0,0,0,0,0\n0,180,180,180,0\n0,180,180,180,0\n0,180,180,180,0\n0,0,0,0,0\n");
MicroBitImage sad2("0,0,0,0,0\n0,100,100,100,0\n0,100,100,100,0\n0,100,100,100,0\n0,0,0,0,0\n");

int demo_status=0;
int trig_flag=0;
int guard_flag=0;
int Human_flag=0;
MiNodeModules minode;

MicroBit uBit;
MicroBitDisplay display1;
ManagedString s();

ConnName Speaker_Conn = A0;
ConnName Light_Conn = A1;
ConnName MIC_Conn = A2;

ConnName FAN_Conn = D13;
ConnName DHT11_Conn = D12;
ConnName PIR_Conn = D15;
unsigned short temp;

MiNodeDHT dhtModule(MINODE_ID_MODULE_DHT11, DHT11_Conn);
MiNodePIR PIRModule(MINODE_ID_MODULE_PIR, PIR_Conn);
MiNodeMIC MICModule(MINODE_ID_MODULE_MIC, MIC_Conn);

void  speakerAlarm()
{
  uBit.io.P0.setServoPulseUs(10000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(15000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(10000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(15000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(10000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(15000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(10000);
  uBit.sleep(300);
  uBit.io.P0.setServoPulseUs(15000);
  uBit.sleep(300);
}

void fanOpen()
{
  uBit.io.P1.setServoPulseUs(5000);
}

void fanClose()
{
  uBit.io.P1.setServoPulseUs(0);
}

void onPIRTRIG(MicroBitEvent)
{
  if (demo_status == DEMO_STATUS_ROBOT)
  {
    Human_flag = 1;
    uBit.io.P0.setServoPulseUs(0);
  }

  if (demo_status == DEMO_STATUS_GUARD)
  {
    guard_flag = 0;
    trig_flag = 1;
  }
}

void onMICTRIG(MicroBitEvent)
{
  if (demo_status == DEMO_STATUS_ROBOT)
  {
    Human_flag = 1;
    uBit.io.P0.setServoPulseUs(0);
  }

  if (demo_status == DEMO_STATUS_GUARD)
  {
    guard_flag = 0;
    trig_flag = 1;
  }
}

void onButtonAClick(MicroBitEvent)
{
  if (demo_status == DEMO_STATUS_GUARD)
  {
    trig_flag = 0;
    guard_flag = 0;
    demo_status = DEMO_STATUS_ROBOT;
  }
  else
  {
    demo_status = DEMO_STATUS_ROBOT;
    uBit.io.P0.setAnalogValue(0);
    uBit.io.P1.setServoPulseUs(0);  
    temp = dhtModule.getTemperature();
    ManagedString s(temp);
    display1.scroll(s);
  }
}

void onButtonBClick(MicroBitEvent)
{
  demo_status = DEMO_STATUS_GUARD;
  guard_flag = 1;
  Human_flag = 0;
  trig_flag = 0;

  uBit.io.P1.setServoPulseUs(0);
}

void onSwitch0Change(MicroBitEvent e)
{
  switch(e.value) {
    case MINODE_SWITCH_EVT_OPEN:
      display1.scroll("0");
      break;
    case MINODE_SWITCH_EVT_CLOSE:
      display1.scroll("x");
      break;
  }
}

void onSwitch1Change(MicroBitEvent e)
{
  switch(e.value) {
    case MINODE_SWITCH_EVT_OPEN:
      display1.scroll("y");
      break;
    case MINODE_SWITCH_EVT_CLOSE:
      display1.scroll("n");
      break;
  }
}

int main() {

  int temp;
  MiNodeSwitch* pSwitchA;
  MiNodeSwitch* pSwitchB;
  uBit.init();

  pSwitchA = minode.switchs.attach(A0);
  pSwitchB = minode.switchs.attach(A1);
  uBit.messageBus.listen(pSwitchA->getId(), MINODE_SWITCH_EVT_OPEN, onSwitch0Change);
  uBit.messageBus.listen(pSwitchA->getId(), MINODE_SWITCH_EVT_CLOSE, onSwitch0Change);
  uBit.messageBus.listen(pSwitchB->getId(), MINODE_SWITCH_EVT_OPEN, onSwitch1Change);
  uBit.messageBus.listen(pSwitchB->getId(), MINODE_SWITCH_EVT_CLOSE, onSwitch1Change);
  while(1) {
    uBit.sleep(100);
  }

  uBit.messageBus.listen(MINODE_ID_MODULE_PIR, MINODE_PIR_EVT_TRIG, onPIRTRIG);
  uBit.messageBus.listen(MINODE_ID_MODULE_MIC, MINODE_MIC_EVT_NOISE, onMICTRIG);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonAClick);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonBClick);

  demo_status = DEMO_STATUS_ROBOT;


  while(1) {
    uBit.sleep(100);
    //uBit.io.P0.setAnalogValue(0);

    if (Human_flag == 1)
    {
      display1.print(smiley);
      //uBit.io.P1.setServoPulseUs(4000);

      if(PIRModule.readPir() == 0)
      {
        Human_flag = 0;
      }
    }
    else
    {
      uBit.io.P1.setServoPulseUs(0);
      display1.clear();
    }

    if (guard_flag == 1 && demo_status == DEMO_STATUS_GUARD)
    {
      while(1)
      {
        display1.print(sad);
        uBit.sleep(800);
        display1.clear();
        uBit.sleep(800);
        if (guard_flag == 0)
        {
          break;
        }
      }
    }

    if (trig_flag == 1 && demo_status == DEMO_STATUS_GUARD)
    {
      while(1)
      {
        display1.print(alarm);
        uBit.sleep(200);
        display1.clear();
        uBit.sleep(200);
        display1.print(alarm);
        uBit.sleep(200);
        display1.clear();
        uBit.sleep(200);
        if (trig_flag == 0)
        {
          break;
        }
      }
    }

/*    temp = dhtModule.getTemperature();
    if (temp > 19 && demo_status != DEMO_STATUS_GUARD)
    {
      uBit.io.P1.setServoPulseUs(5000);
    }
    ManagedString s(temp);
    uBit.serial.send(s);
    uBit.serial.send("\n");
*/
  }
}

