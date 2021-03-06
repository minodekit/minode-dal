#ifndef MINODE_DHT11_H
#define MINODE_DHT11_H

#include "mbed.h"

#include "MicroBitConfig.h"
#include "MicroBitComponent.h"
#include "MicroBitEvent.h"
#include "MiNodeComponent.h"
#include "MiNodeConn.h"
#include "MicroBitDisplay.h"
#include "MicroBitSystemTimer.h"

#define MINODE_DHT_EVT_CHANGE                  1
#define TIME_TH 		                       10000


#define delay60US()\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\
t++;t++;t++;t++;t++;t++;t++;t++;t++;t++;\

class MiNodeDHT : public MicroBitComponent
{
    
  public:
    MiNodeDHT(int id, ConnName connName);
    MiNodeDHT(int id, PinName pinName);

    int getTemperature();
    int getHumidity();
    int getFahrenheitTemperature();

    virtual void systemTick();
    ~MiNodeDHT();

  private:
    DigitalInOut  pin;

    int Humidity;
    int Temperature;
    int currentTem;
    int count;
    int bt;

    volatile int t;
    volatile int time_out;

    void dhtSet(int  level);
    int dhtGet();
    int whileGet(int v);
    void dhtStart();
    void dhtReadAck();
    void dhtReadOneBit();
    void dhtReadOneByte();
    int dhtGetHt();
};

#endif

