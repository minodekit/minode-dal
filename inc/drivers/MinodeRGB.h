#ifndef MINODE_RGB_H
#define MINODE_RGB_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

typedef enum MinodeColor {
    MiNode_RGB_COLOR_RED=0,
    MiNode_RGB_COLOR_GREEN,
    MiNode_RGB_COLOR_BLUE,
    MiNode_RGB_COLOR_YELLOW,
    MiNode_RGB_COLOR_PINK,
    MiNode_RGB_COLOR_CYAN,
    MiNode_RGB_COLOR_WHITE
}MiNodeColor;

class MiNodeRGB : public MicroBitComponent
{
public:

  MiNodeRGB(int id, ConnName connName);
  MiNodeRGB(int id, PinName pinName1, PinName pinName2);

  void setRGB(uint8_t r,uint8_t g,uint8_t b);
  void setRGBInHex(unsigned int);
  void chooseColor(MiNodeColor c);

private:
  DigitalOut CLOCK;
  DigitalOut DATA;
  unsigned int rgbHEX;

  void rgbDelay();
  void rgbWrite(uint8_t r,uint8_t g,uint8_t b);
  void rgbClockWrite(int value);
  void rgbDataWrite(int value);

};

#endif