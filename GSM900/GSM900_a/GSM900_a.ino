#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,12);

void GprsInit(void)
{
  unsigned char temp = 0;
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
}

void GprsTest(void)
{
  while(1)
  {
     if(Serial.available())
     {
        unsigned char input = Serial.read();
        mySerial.write(input); 
     }
     if( mySerial.available())
    { 
        unsigned char input2 = mySerial.read();
        Serial.write(input2);
    }
  }
}

void setup()
{
   GprsInit();
   SubmitHttpRequest();
   Serial.println("END------------------------");
}
void loop()
{
    // if(Serial.available())
    // {
    //    unsigned char input = Serial.read();
    //    mySerial.write(input); 
    // }
    // if( mySerial.available())
    //{ 
    //    unsigned char input2 = mySerial.read();
    //    Serial.write(input2);
    //}
}

String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//String myurl ="www.google.com.hk";

String CSQ = "AT+CSQ";
String CGA = "AT+CGATT?";
String SAP = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";//setting the SAPBR, the connection type is using gprs
String APN = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";//setting the APN, the second need you fill in your local apn server
String PBR = "AT+SAPBR=1,1";//setting the SAPBR, for detail you can refer to the AT command mamual
String HTP = "AT+HTTPINIT"; //init the HTTP request
String URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
String ACT = "AT+HTTPACTION=0";//submit the request 
String REA = "AT+HTTPREAD"; //read the data from the website you access
String REAT = "AT+HTTPREAD=0,1000";


void SubmitHttpRequest()
{
  mySerial.println(CSQ);  delay(100);   ShowSerialData();  
  mySerial.println(CGA);  delay(100);   ShowSerialData(); 
  mySerial.println(SAP);  delay(1000);  ShowSerialData(); 
  mySerial.println(APN);  delay(4000);  ShowSerialData();
  //mySerial.println(PBR);  delay(2000);  ShowSerialData();
  //mySerial.println(HTP);  delay(2000);  ShowSerialData();
  mySerial.println(URL);  delay(1000);  ShowSerialData();
  mySerial.println(ACT);  delay(10000);  ShowSerialData();
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available()); 
  ShowSerialData();
  mySerial.println(REA);  delay(2000);   ShowSerialData(); 
  mySerial.println("");   delay(1000);
}

void SubmitHttpRequest2()
{
  mySerial.println("AT+CSQ");
  delay(100);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 
  mySerial.println("AT+CGATT?");
  delay(100);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, the second need you fill in your local apn server
  delay(4000);
 
  ShowSerialData();
 
  mySerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();
 
  mySerial.println("AT+HTTPPARA=\"URL\",\"www.google.com.hk\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available());
 
  ShowSerialData();
 
  mySerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
 
  ShowSerialData();
 
  mySerial.println("");
  delay(100);
}

void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

