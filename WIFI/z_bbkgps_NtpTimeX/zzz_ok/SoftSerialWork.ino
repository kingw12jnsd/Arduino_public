//=========================================
void SerialPrintln(String cmd) {
  Serial.print(cmd);
  Serial.println("");
}
void SerialPrint(char c) {
  Serial.print(c);
}
//=========================================
void SoftSerialPrintln(String cmd) {
  Serial1.println(cmd);
  //Serial.println(cmd);
}
boolean SoftSerialAvailable() {
  return Serial1.available() > 0;
}
char SoftSerialRead() {
  return Serial1.read();
}
//=========================================
