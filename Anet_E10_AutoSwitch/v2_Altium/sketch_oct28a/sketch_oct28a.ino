#include <ESP8266WiFi.h>
//#include <ESP32WiFi.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "Red"
#define WIFI_PASSWORD "1234567890"
WiFiClientSecure secured_client;

#define BOT_TOKEN "2091648393:AAERBh_aC9RfqJ1NY2-h7CLZHK4Bvff0Smc"
#define CHAT_ID "747024286" // https://api.telegram.org/bot2091648393:AAERBh_aC9RfqJ1NY2-h7CLZHK4Bvff0Smc/getUpdates
const unsigned long BOT_MRBS = 3000;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;


void setup() {
  Serial.begin(9600);
  configTime(0,0,"pool.ntp.org");
  secured_client.setTrustAnchors(&cert);
  Serial.print("Connecting to WiFi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);    
  }

  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Hi! ANET E10 START!", "");

}

void loop() {
  // put your main code here, to run repeatedly:

}
