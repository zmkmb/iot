#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
static WiFiClient espClient;
#include <ArduinoJson.h>

#include <AliyunIoTSDK.h>
AliyunIoTSDK iot;

#define PRODUCT_KEY "xxx"
#define DEVICE_NAME "xxx"
#define DEVICE_SECRET "xxxx"
#define REGION_ID "cn-shanghai"

#define WIFI_SSID "wifi"//网络名
#define WIFI_PASSWD "123456"//wifi密码

unsigned int localPort = 8888;
WiFiUDP Udp;

void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    WiFi.setAutoConnect (true);
    WiFi.setAutoReconnect (true);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}

void setup()
{
    Serial.begin(115200);

    wifiInit(WIFI_SSID, WIFI_PASSWD);

    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);

    // 绑定属性回调
    AliyunIoTSDK::bindData("MACAddress", wolCallback);
    Udp.begin(localPort);
}

void loop()
{
    AliyunIoTSDK::loop();
}

//网络唤醒
void wolCallback(JsonVariant p)
{
    String MACAddress = p["MACAddress"];
    if (MACAddress)
    { 
      byte mac[6];
      parseBytes(&MACAddress[0], ':', mac, 6, 16);
      byte ReplyBuffer[102];
      for(int i=0;i<102;i++){
        if(i<6){
          ReplyBuffer[i] = 0xFF;  
        }else{
          ReplyBuffer[i] = mac[i%6];  
        }
      }
      IPAddress ip(255,255,255,255);
      Udp.beginPacket(ip, 9);
      Udp.write(ReplyBuffer,102);
      Udp.endPacket();
      Serial.println("wol");
    }
    else
    {
       Serial.println("parameter error");
    }
}

//mac字符串转换为byte数组
void parseBytes(const char* str, char sep, byte* bytes, int maxBytes, int base) { 
    for (int i = 0; i < maxBytes; i++) { 
     bytes[i] = strtoul(str, NULL, base); // Convert byte 
     str = strchr(str, sep);    // Find next separator 
     if (str == NULL || *str == '\0') { 
      break;       // No more separators, exit 
     } 
     str++;        // Point to next character after separator 
    } 
} 
