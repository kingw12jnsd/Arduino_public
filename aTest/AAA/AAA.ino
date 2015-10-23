// LeWei AC Power Meter trail success2013.06.25
// LeWei AC Power Meter (ZongBiao60A)trail syccess 2013.06.30 18:50pm
// 4 Parameter: watt / kwh / Amp / Voltage / Pf


int preset_multiple_registers(int slave, int start_addr, int reg_count, int *data);
int read_holding_registers(int slave, int start_addr, int count, int *dest, int dest_size);


int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
double concentration = 0;

void setup() {
  Serial.begin(4800);
  pinMode(8,INPUT);
  delay(10000);
  starttime = millis();
}

#define FILTERLEN 10 

unsigned long Array_Average( unsigned long* Array,int length)
{
  int x;
  unsigned long returnVal;
  unsigned long result=0;
  for(x=0;x<length;x++)
  {
    result+=Array[x];
    Serial.print("result=");
    Serial.println(result);
  }
  returnVal=result/length;
  return returnVal;
}

unsigned long Filter1(unsigned long lowpulse)
{
  static unsigned long sfiterArray[FILTERLEN];
  static int sindex=0;
  int x;
  Serial.println("filter1 begin:");
  if(FILTERLEN>sindex)
  {
    sindex++;
    Serial.println(sindex);
    sfiterArray[sindex]=lowpulse;
    Serial.println("filter1 END");
    return lowpulse;
  }
  else
  {
    for(x=0;x<FILTERLEN-1;x++)
    {
      sfiterArray[x]=sfiterArray[x+1];
    }
    sfiterArray[FILTERLEN-1]=lowpulse;
    for(x=0;x<FILTERLEN;x++)
    {
      Serial.println(sfiterArray[x]);
    }
    Serial.println("Aver:");
    Serial.println(Array_Average(sfiterArray,FILTERLEN));
    Serial.println("filter1 END");
    return(Array_Average(sfiterArray,FILTERLEN));

  }


}
/*END: filter program : 20130521 */

int x=0; //simulated sensor output
int sampling=1;
int transfering=0;

/* Modbus para */
int retval;
int tt[30];  //int changed to unsigned int
int data[10];

void loop() { 
  //---------------------------------------  
  retval = read_holding_registers(1, 0x49, 6, tt, 1); // 1:5,2:7,3:9
  //---------------------------------------  
  int     Voltage  = tt[0]; Voltage  = Voltage / 100;
  float   Amp      = tt[1]; Amp      = Amp     / 1000;
  int     Watt     = tt[2];
  unsigned   int Kwhh = (unsigned int)tt[3];
  unsigned   int Kwhl = (unsigned int)tt[4];
  unsigned  long kwhA = (unsigned long) Kwhh *65536 + Kwhl;
  //    unsigned  long kwhA = Kwhh <<16 + Kwhl;
  float Kwh = kwhA;           Kwh = Kwh / 3200;
  float Pf = tt[5];             Pf = Pf / 1000;
  float Cabon  = tt[5];  Cabon  = Cabon / 1000;
  //---------------------------------------  
  Serial.print("Voltage");  Serial.println(Voltage,DEC);
  Serial.print("Amp");  Serial.println(Amp,DEC);
  Serial.print("Watt");  Serial.println(Watt,DEC);
  Serial.print("Kwh");  Serial.println(Kwh,DEC);
  Serial.print("Pf");  Serial.println(Pf,DEC);
  Serial.print("Cabon");  Serial.println(Cabon,DEC);
  //---------------------------------------
  delay(sampletime_ms);
  //---------------------------------------
}

/****************************************************************************
 * BEGIN MODBUS RTU MASTER FUNCTIONS
 ****************************************************************************/

//#define TIMEOUT 1000          /* 1 second */
#define TIMEOUT 10000          /* 10 second */
#define MAX_READ_REGS 125
#define MAX_WRITE_REGS 125
#define MAX_RESPONSE_LENGTH 256
#define PRESET_QUERY_SIZE 256
/* errors */
#define PORT_ERROR -5

/*
CRC
 
 INPUTS:
 buf   ->  Array containing message to be sent to controller.           
 start ->  Start of loop in crc counter, usually 0.
 cnt   ->  Amount of bytes in message being sent to controller/OUTPUTS:
 temp  ->  Returns crc byte for message.
 COMMENTS:
 This routine calculates the crc high and low byte of a message.
 Note that this crc is only used for Modbus, not Modbus+ etc.
 ****************************************************************************/

unsigned int crc(unsigned char *buf, int start, int cnt)
{
  int i, j;
  unsigned temp, temp2, flag;

  temp = 0xFFFF;

  for (i = start; i < cnt; i++) {
    temp = temp ^ buf[i];

    for (j = 1; j <= 8; j++) {
      flag = temp & 0x0001;
      temp = temp >> 1;
      if (flag)
        temp = temp ^ 0xA001;
    }
  }

  /* Reverse byte order. */

  temp2 = temp >> 8;
  temp = (temp << 8) | temp2;
  temp &= 0xFFFF;

  return (temp);
}


/***********************************************************************
 *
 *      The following functions construct the required query into a modbus query packet.
 *
 ***********************************************************************/

#define REQUEST_QUERY_SIZE 6     /* the following packets require          */
#define CHECKSUM_SIZE 2          /* 6 unsigned chars for the packet plus   */
/* 2 for the checksum.                    */

void build_request_packet(int slave, int function, int start_addr, int count, unsigned char *packet)
{
  start_addr -= 1;
  packet[0] = slave;
  packet[1] = function;
  packet[2] = start_addr >> 8;
  packet[3] = start_addr & 0x00ff;
  packet[4] = count >> 8;
  packet[5] = count & 0x00ff;

  //below test only
  //        packet[0] = 0x01;
  //        packet[1] = 0x03;
  //        packet[2] = 0;
  //        packet[3] = 0x48;
  //        packet[4] = 0;
  //        packet[5] = 0x02;
}

/*************************************************************************
 *
 * modbus_query( packet, length)
 *
 * Function to add a checksum to the end of a packet.
 * Please note that the packet array must be at least 2 fields longer than
 * string_length.
 **************************************************************************/

void modbus_query(unsigned char *packet, size_t string_length)
{
  int temp_crc;
  temp_crc = crc(packet, 0, string_length);
  packet[string_length++] = temp_crc >> 8;
  packet[string_length++] = temp_crc & 0x00FF;
  packet[string_length] = 0;
}



/***********************************************************************
 * send_query(query_string, query_length )
 * Function to send a query out to a modbus slave.
 ************************************************************************/
int send_query(unsigned char *query, size_t string_length)
{
  int i;
  modbus_query(query, string_length);
  string_length += 2;
  for (i = 0; i < string_length; i++) {
    //Serial.print(query[i], HEX); //Orginal
    Serial.write(query[i]); //JingLi
  }
  delay(200); 
  return i;
}


/***********************************************************************
 *      receive_response( array_for_data )
 * Function to monitor for the reply from the modbus slave.
 * This function blocks for timeout seconds if there is no reply.
 * Returns:     Total number of characters received.
 ***********************************************************************/
int receive_response(unsigned char *received_string)
{

  int bytes_received = 0;
  int i = 0;
  /* wait for a response; this will block! */
  while(Serial.available() == 0) {
    delay(1);
    if (i++ > TIMEOUT)
      return bytes_received;
  }
  delay(200);
  /* FIXME: does Serial.available wait 1.5T or 3.5T before exiting the loop? */
  while(Serial.available()) {
    received_string[bytes_received] = Serial.read();
    //                Serial.print(bytes_received);                     //only test
    //                Serial.print("-");                                //only test
    //                Serial.println(received_string[bytes_received]);  //only test
    bytes_received++;
    if (bytes_received >= MAX_RESPONSE_LENGTH)
      return PORT_ERROR;
  }   
  //Serial.print("bytes_received=");
  //Serial.println(bytes_received);
  return (bytes_received);
}


/*********************************************************************
 *
 *      modbus_response( response_data_array, query_array )
 * Function to the correct response is returned and that the checksum is correct.
 *
 * Returns:     string_length if OK
 *           0 if failed
 *           Less than 0 for exception errors
 *
 *      Note: All functions used for sending or receiving data via
 *            modbus return these return values.
 *
 **********************************************************************/

int modbus_response(unsigned char *data, unsigned char *query)
{
  int response_length;
  int i;
  unsigned int crc_calc = 0;
  unsigned int crc_received = 0;
  unsigned char recv_crc_hi;
  unsigned char recv_crc_lo;

  do {        // repeat if unexpected slave replied
    response_length = receive_response(data);
  } 
  while ((response_length > 0) && (data[0] != query[0]));
  //  for (i = 0; i <response_length; i++) { Serial.print(data[i]);Serial.print("---"); Serial.println(query[i]);} //only test

  if (response_length) {
  
    crc_calc = crc(data, 0, response_length - 2);

    recv_crc_hi = (unsigned) data[response_length - 2];
    recv_crc_lo = (unsigned) data[response_length - 1];

    crc_received = data[response_length - 2];
    crc_received = (unsigned) crc_received << 8;
    crc_received =
      crc_received | (unsigned) data[response_length - 1];
    /*********** check CRC of response ************/
    if (crc_calc != crc_received) {
      response_length = 0;
      // Serial.println("CRC erro");  //only test
    }
    /********** check for exception response *****/
    if (response_length && data[1] != query[1]) {
      response_length = 0 - data[2];
    }
  }
  return (response_length);
}


/************************************************************************
 *      read_reg_response
 *      reads the response data from a slave and puts the data into an array.
 ************************************************************************/
int read_reg_response(int *dest, int dest_size, unsigned char *query)
{
  unsigned char data[MAX_RESPONSE_LENGTH];
  int raw_response_length;
  int temp, i;
  raw_response_length = modbus_response(data, query);
  if (raw_response_length > 0)
    raw_response_length -= 2;

  if (raw_response_length > 0) {
    /* FIXME: data[2] * 2 ???!!! data[2] isn't already the byte count (number of registers * 2)?! */
    for (i = 0;
         i < (data[2] * 2) && i < (raw_response_length / 2);
         i++) {

      /* shift reg hi_byte to temp */
      temp = data[3 + i * 2] << 8;
      /* OR with lo_byte           */
      temp = temp | data[4 + i * 2];

      dest[i] = temp;
    }
  }
  return (raw_response_length);
}


/***********************************************************************
 *      preset_response
 *      Gets the raw data from the input stream.
 ***********************************************************************/

int preset_response(unsigned char *query)
{
  unsigned char data[MAX_RESPONSE_LENGTH];
  int raw_response_length;
  raw_response_length = modbus_response(data, query);
  return (raw_response_length);
}


/************************************************************************
 *      read_holding_registers
 *      Read the holding registers in a slave and put the data into an array.
 *************************************************************************/
int read_holding_registers(int slave, int start_addr, int count, int *dest, int dest_size)
{
  int function = 0x03;      /* Function: Read Holding Registers */
  int ret;
  unsigned char packet[REQUEST_QUERY_SIZE + CHECKSUM_SIZE];
  if (count > MAX_READ_REGS) {
    count = MAX_READ_REGS;
  }
  build_request_packet(slave, function, start_addr, count, packet);
  if (send_query(packet, REQUEST_QUERY_SIZE) > -1) {
    ret = read_reg_response(dest, dest_size, packet);
  }
  else {
    ret = -1;
  }
  return (ret);
}


/************************************************************************
 *      preset_multiple_registers
 *      Write the data from an array into the holding registers of a slave.
 *************************************************************************/
int preset_multiple_registers(int slave, int start_addr, int reg_count, int *data)
{
  int function = 0x10;      /* Function 16: Write Multiple Registers */
  int byte_count, i, packet_size = 6;
  int ret;
  unsigned char packet[PRESET_QUERY_SIZE];
  if (reg_count > MAX_WRITE_REGS) {
    reg_count = MAX_WRITE_REGS;
  }
  build_request_packet(slave, function, start_addr, reg_count, packet);
  byte_count = reg_count * 2;
  packet[6] = (unsigned char)byte_count;
  for (i = 0; i < reg_count; i++) {
    packet_size++;
    packet[packet_size] = data[i] >> 8;
    packet_size++;
    packet[packet_size] = data[i] & 0x00FF;
  }
  packet_size++;
  if (send_query(packet, packet_size) > -1) {
    ret = preset_response(packet);
  }
  else {
    ret = -1;
  }
  return (ret);
}







