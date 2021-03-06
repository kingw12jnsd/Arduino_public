#include <SPI.h>
#include <Ethernet.h>
#include <LeweiClient.h>
#include <EEPROM.h>
//----------------------------------------------------
#define USERKEY          "4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
#define LW_GATEWAY       "01" // BOBOKing_Lewei_GAT
//----------------------------------------------------  
LeWeiClient *lwc;
//----------------------------------------------------
byte my_mac[] = {
  0x74,0x69,0x69,0x2D,0x30,0x31};
//----------------------------------------------------
IPAddress mylwip(192,168,1,18);
IPAddress mylwgw(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress my_dns(202,106,196,115); 
//----------------------------------------------------
//boolean lastConnected = false;
//unsigned long lastConnectionTime = 0;
//const unsigned long postingInterval = 30*1000;
//----------------------------------------------------
//unsigned long duration;
//unsigned long starttime;
//unsigned long sampletime_ms = 30000;
//unsigned long lowpulseoccupancy = 0;
//float ratio = 0;
//double concentration = 0;
//----------------------------------------------------
void LEWEI_Setup() {
  //----------------------------------------------------
  lwc = new LeWeiClient(USERKEY, LW_GATEWAY);
  //lwc = new LeWeiClient(USERKEY, LW_GATEWAY,my_mac,mylwip,my_dns,mylwgw,subnet);
  //----------------------------------------------------
  //starttime = millis();
  //----------------------------------------------------
}
//----------------------------------------------------
void LeweiLoop() {
  //---------------------------------------
  //  lwc->append("YDL", Kwh);
  //  lwc->append("GL", Watt);
  //  lwc->append("DL", Amp); 
  //  lwc->append("DY", Voltage); 
  //  lwc->append("GLYS", Pf);
  //---------------------------------------
  lwc->append("WD", DHT_WD); 
  lwc->append("SD", DHT_SD); 
  //---------------------------------------     
  lwc->send();
  //---------------------------------------
}

