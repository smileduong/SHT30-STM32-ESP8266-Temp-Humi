#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
#include "webpage.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>


const byte RX = D7;
const byte TX = D8;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

void Read_UART_STM(void);
void Received(void);
void clearbufferEnd(void);
void XuLyJson(String DataJson);
void ConnectWiFi(void);
void SendWebpage(void);
void SendData(void);


String Data = "";
long last = 0;
String DataWeb = "";
float ND = 28.36;
float DA = 65.74;
float a = 0.33;
float b = 1.35;
const char* ssid = "T2";
const char* pass = "38683518";


void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  // connect to WIFI
  ConnectWiFi();
  server.on("/", [] {
    SendWebpage();
  });

  server.on("/LoadData", [] {
    SendData();
  });

  //tao webserver
  server.begin();
  Serial.println("Server Start!!!");



  Serial.println("Start ESP!!!");
  last = millis();
}

void loop()
{
  server.handleClient();
  Read_UART_STM();
  //SendLenh();
//Serial.println(Data);

  delay(3000); // Chờ 20s trước khi gửi dữ liệu mới
}


void Read_UART_STM(void)
{
  // duy tri server
  server.handleClient();
  while (mySerial.available())
  {
    Received();
    //chuongtrinhcambien();

  }
}
void Received(void)
{
  char inChar = (char)mySerial.read();
  if (inChar != '\n')
  {
    Data += inChar;
  }
  else
  {
    Serial.print("Data nhan duoc: ");
    Serial.println(Data);

    DataWeb = Data;

    XuLyJson(Data);
    clearbufferEnd();
  }
}
void SendWebpage(void)
{
  server.send(200, "text/html", webpage);
}
void SendData(void)
{
  server.send(200, "text/html", String(DataWeb));
 
}
void ConnectWiFi(void)
{
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.printf(".");
  }
  Serial.println();
  Serial.println("Connecting to WiFi");
  Serial.print("Address IP esp: ");
  Serial.println(WiFi.localIP());
}
void clearbufferEnd(void)
{
  Data = "";
}
void XuLyJson(String DataJson)
{
  StaticJsonDocument<200> JSON;
  DeserializationError error = deserializeJson(JSON, DataJson);

  if (error)
  {
    Serial.print(F("deserializeJson() failed "));
    //Serial.println(error.c_str());
    return;
  }
  else
  {
    Serial.print("JSON OK!!!\n");
    if (JSON.containsKey("ND"))
    {
      String DataND = JSON["ND"];
      Serial.print("Nhiet do: ");
      Serial.println(DataND);
    }
    if (JSON.containsKey("DA"))
    {
      String DataDA = JSON["DA"];
      Serial.print("Do am: ");
      Serial.println(DataDA);
    }
    JSON.clear();
  }
}
