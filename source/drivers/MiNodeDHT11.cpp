#include "MiNodeDHT11.h"


MiNodeDHT::MiNodeDHT(int id, ConnName connName) :
pin(MiNodeConn::calcP0Name(connName)),currentTem(-99)
{
  this->id = id;
  pin.mode(PullNone);
  system_timer_add_component(this);
}

MiNodeDHT::MiNodeDHT(int id, PinName pinName) :
pin(pinName),currentTem(-99)
{
  this->id = id;
  pin.mode(PullNone);
  system_timer_add_component(this);
}

void MiNodeDHT::dhtSet(int level)
{
  pin.output();
  pin.write(level);
}

int MiNodeDHT::dhtGet()
{
  pin.input();
  return pin.read();
}

int MiNodeDHT::whileGet(int v)
{
  time_out = 0;
  while(v==dhtGet() && (time_out < TIME_TH))
  {
    time_out ++;
  }
  if(time_out == TIME_TH)
    return 1;
}

void MiNodeDHT::dhtStart()
{
    dhtSet(1);
    delay60US();
    dhtSet(0);
    wait_ms(25);
    dhtSet(1);
}

void MiNodeDHT::dhtReadAck()
{
    whileGet(1);
    whileGet(0);
    whileGet(1);
}

void MiNodeDHT::dhtReadOneBit()
{
  whileGet(0);
  delay60US();
  bt <<= 1;
  if(1==dhtGet())
  {
    bt |= 1;
    whileGet(1);
  }
  else
    bt |= 0;
}

void MiNodeDHT::dhtReadOneByte()
{
  bt=0;
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
  dhtReadOneBit();
}

void MiNodeDHT::systemTick()
{
  int temp=0;
  count++;

 if (count == 100)
  {
    /* if (currentTem == -99)
    {
      currentTem = getTemperature();
    }
    */
    //temp = getTemperature();
  /*  if ((temp - currentTem == 1) || (currentTem - temp == 1))
    {
      currentTem = temp;
      MicroBitEvent(id, MINODE_DHT_EVT_CHANGE);
    }
   */
    count = 0;
  }

}

int MiNodeDHT::dhtGetHt()
{
    int CHECKSUM=0;
    int R_H=0;
    int R_L=0;
    int T_H=0;
    int T_L=0;

    dhtStart();
    dhtReadAck();

    dhtReadOneByte();
    R_H = bt;
    dhtReadOneByte();
    R_L = bt;
    dhtReadOneByte();
    T_H = bt;
    dhtReadOneByte();
    T_L = bt;
    dhtReadOneByte();
    CHECKSUM = bt;

    if(CHECKSUM == R_H+R_L+T_H+T_L)
    {                
        Humidity = R_H;
        Temperature = T_H;
        return 0;
    }
    else
        return 1;
}

int MiNodeDHT::getTemperature()
{
  dhtGetHt();
  return Temperature;
}

int MiNodeDHT::getFahrenheitTemperature()
{
  int temp = getTemperature();
  return temp*9/5+32;
}

int MiNodeDHT::getHumidity()
{
  dhtGetHt();
  return Humidity;
}

MiNodeDHT::~MiNodeDHT()
{
    system_timer_remove_component(this);
}

