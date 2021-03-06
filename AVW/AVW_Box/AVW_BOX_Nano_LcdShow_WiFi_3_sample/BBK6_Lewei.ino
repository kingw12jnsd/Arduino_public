//-------------------------------------------------------------------------
static String Lewei_Link = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
static String Lewei_Keys = "4a7c908d0de946de96e041dd84834154";
//-------------------------------------------------------------------------
String Lewei_Post = "";
//-------------------------------------------------------------------------
void GetLeweiPostString(String Key, String Gate, String ValJson) {
  Lewei_Post = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/" + String(Gate) + " HTTP/1.1\r\n";
  Lewei_Post += "userkey: " + Key + "\r\n";
  Lewei_Post += "Host: www.lewei50.com\r\n";
  Lewei_Post += "Content-Length: " + String(ValJson.length()) + "\r\n";
  Lewei_Post += "\r\n";
  Lewei_Post += ValJson;
  Lewei_Post += "\r\n";
}
String Lewei_ValueJson() {
  float tx = 9.0;
  //return "[{\"Name\":\"WD\",\"Value\":\"" + String(tx) + "\"}]";
  return "[{\"Name\":\"WD\",\"Value\":\"" + String(tx) + "\"}]";
}
//-------------------------------------------------------------------------
void Lewei_Report() {
  GetLeweiPostString(Lewei_Keys, "01", Lewei_ValueJson());
  HttpGetPost(Lewei_Link, Lewei_Post, 5);
}
//-------------------------------------------------------------------------
