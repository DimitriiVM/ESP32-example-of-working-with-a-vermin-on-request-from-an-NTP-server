#include <WiFi.h>

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0

struct tm timeinfo;

void setup() {
  Serial.begin(115200);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {

  if (!getLocalTime(&timeinfo)) {
    Serial.println("ERROR");
    return;
  }

char timeSec[3];
char timeMin[3];
char timeHour[3];
char timeDay[3];
char timeMon[3];
char timeYear[5];
char q[2] =";";
strftime(timeSec, 3, "%S", &timeinfo);
strftime(timeMin, 3, "%M", &timeinfo);
strftime(timeHour, 3, "%H", &timeinfo);
strftime(timeDay, 3, "%d", &timeinfo);
strftime(timeMon, 3, "%m", &timeinfo);
strftime(timeYear, 5, "%Y", &timeinfo);
char pack[256];

Serial.println(&timeinfo);
strcat(pack, timeDay);
strcat(pack, timeMon);
strcat(pack, timeYear);
strcat(pack, q);
strcat(pack, timeHour);
strcat(pack, timeMin);
strcat(pack, timeSec);
strcat(pack, q);
Serial.println(pack);
for(byte i = 0; i < sizeof(pack); i++)
{
  if(pack[i] == 0x00) break;
  pack[i] = 0x00;
  
}
/*
Serial.println(timeSec);
Serial.println(timeMin);
Serial.println(timeHour);
Serial.println(timeDay);
Serial.println(timeMon);
Serial.println(timeYear);
*/

delay(5000);
}
