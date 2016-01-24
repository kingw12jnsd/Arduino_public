//===================================================================
#define  rc  Serial1
static const long RcBaud = 9600;
//===================================================================
void rc_setup() {
  rc.begin(LGSBaud);
  lgln(F("RC.Serial1.start!"));
}
//===================================================================
void rcFeed() {
  //----------------------------------------------------------
  while (rc.available()) {
    char c = rc.read();
    rc_cmd_loop(c);
  }
  //----------------------------------------------------------
}
void rcSend(String str) {
  rc.print(str);
}

