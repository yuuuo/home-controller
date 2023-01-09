
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SparkFunBME280.h>
#include <ArduinoOTA.h>
#include "arduino_secret.h"

uint16_t LightOff[83] = {3554, 1614, 536, 320, 532, 320, 532, 1186, 536, 1186, 536, 320, 532, 1186, 512, 340, 538, 320, 532, 320, 532, 1186, 536, 320, 532, 320, 532, 1186, 536, 320, 532, 1186, 536, 320, 532, 1186, 536, 320, 532, 320, 532, 1190, 532, 320, 534, 318, 506, 346, 510, 342, 510, 1212, 506, 1218, 532, 1190, 532, 320, 532, 1192, 532, 1190, 532, 320, 532, 320, 534, 318, 590, 1134, 532, 1190, 532, 1190, 532, 1190, 532, 1186, 536, 320, 532, 320, 506};
uint16_t LightOn[85] = {2206, 808,  5640, 902,  1608, 412,  1604, 412,  608, 420,  602, 420,  520, 508,  588, 434,  594, 430,  594, 434,  1604, 412,  604, 426,  602, 420,  602, 420,  520, 508,  590, 434,  594, 434,  1604, 412,  606, 420,  1604, 416,  604, 420,  602, 420,  520, 508,  590, 434,  594, 430,  594, 434,  602, 420,  602, 422,  606, 420,  602, 420,  520, 502,  594, 434,  594, 430,  590, 434,  608, 420,  1604, 412,  602, 424,  1604, 416,  1606, 412,  594, 434,  1604, 412,  1610, 412,  492};

uint16_t AC20[375] = {3430, 1604,  494, 1188,  488, 1188,  520, 320,  492, 346,  490, 346,  492, 1188,  490, 350,  488, 346,  494, 1188,  488, 1186,  494, 346,  494, 1184,  492, 346,  492, 346,  490, 1186,  494, 1186,  488, 346,  494, 1188,  492, 1182,  494, 346,  494, 346,  488, 1188,  492, 346,  494, 348,  488, 1186,  494, 346,  492, 346,  488, 346,  494, 346,  494, 346,  490, 346,  520, 320,  494, 346,  494, 346,  488, 346,  494, 346,  494, 346,  490, 350,  488, 346,  494, 346,  494, 9002,  3428, 1606,  492, 1188,  494, 1182,  494, 346,  494, 348,  488, 346,  494, 1186,  492, 346,  490, 346,  520, 1162,  492, 1182,  494, 346,  494, 1186,  490, 346,  494, 348,  492, 1182,  492, 1188,  492, 346,  488, 1188,  492, 1188,  488, 346,  520, 320,  494, 1182,  492, 346,  494, 346,  488, 1188,  494, 346,  494, 346,  490, 350,  488, 346,  494, 346,  488, 350,  490, 346,  494, 346,  494, 346,  490, 350,  488, 346,  494, 346,  494, 346,  490, 346,  494, 346,  494, 346,  488, 346,  494, 346,  492, 348,  494, 346,  490, 1186,  494, 346,  488, 346,  494, 346,  494, 346,  494, 346,  490, 1186,  494, 346,  488, 346,  494, 346,  492, 346,  490, 350,  488, 346,  494, 1186,  490, 350,  488, 346,  494, 346,  494, 346,  490, 346,  492, 346,  492, 346,  488, 352,  514, 320,  494, 1186,  490, 346,  494, 346,  494, 346,  488, 352,  488, 346,  520, 320,  494, 346,  490, 346,  494, 346,  494, 1186,  488, 1188,  492, 1186,  490, 346,  492, 1188,  488, 350,  490, 346,  494, 346,  494, 346,  490, 1186,  494, 346,  490, 350,  490, 346,  494, 346,  494, 346,  488, 346,  494, 346,  494, 346,  490, 350,  490, 346,  494, 346,  494, 346,  488, 346,  494, 346,  494, 346,  490, 350,  490, 346,  494, 346,  494, 346,  490, 346,  494, 346,  492, 346,  494, 346,  488, 346,  494, 346,  492, 346,  490, 1186,  494, 1186,  490, 346,  492, 346,  494, 346,  494, 346,  490, 346,  518, 320,  494, 346,  488, 352,  488, 346,  494, 346,  492, 346,  490, 350,  490, 346,  492, 346,  494, 1186,  490, 346,  492, 348,  492, 346,  488, 346,  494, 346,  494, 346,  494, 1182,  494, 1186,  488, 350,  490, 346,  492, 1188,  488, 352,  488, 1186,  494};
uint16_t AC26[375] = {3432, 1608, 462, 1212, 466, 1212, 492, 346, 494, 346, 492, 346, 492, 1186, 466, 374, 462, 376, 462, 1212, 494, 1186, 468, 372, 466, 1212, 466, 372, 468, 372, 466, 1212, 462, 1212, 494, 346, 492, 1186, 466, 1214, 492, 346, 492, 346, 466, 1212, 462, 372, 494, 346, 492, 1186, 492, 346, 466, 372, 468, 372, 494, 346, 492, 346, 468, 372, 462, 376, 462, 372, 466, 372, 466, 372, 466, 372, 466, 372, 466, 372, 466, 372, 466, 372, 462, 9032, 3430, 1604, 492, 1186, 492, 1186, 468, 372, 466, 372, 494, 346, 468, 1212, 462, 372, 466, 372, 466, 1212, 468, 1212, 468, 372, 494, 1186, 466, 372, 466, 372, 462, 1212, 468, 1212, 494, 346, 492, 1186, 494, 1186, 494, 346, 494, 346, 492, 1186, 462, 372, 468, 372, 494, 1186, 468, 372, 494, 346, 494, 346, 494, 346, 466, 372, 462, 376, 462, 372, 466, 372, 492, 346, 494, 346, 468, 372, 468, 372, 468, 372, 494, 344, 468, 372, 462, 376, 488, 346, 492, 346, 492, 346, 492, 346, 492, 1186, 492, 346, 494, 346, 494, 346, 462, 376, 462, 372, 468, 1212, 466, 1212, 466, 372, 492, 346, 492, 346, 492, 346, 468, 1208, 468, 372, 468, 1212, 494, 346, 468, 372, 466, 372, 466, 372, 494, 346, 468, 1212, 462, 1212, 492, 346, 494, 1184, 494, 1186, 492, 346, 494, 346, 462, 376, 462, 372, 468, 372, 468, 372, 494, 346, 468, 372, 494, 1186, 494, 1186, 462, 1212, 494, 346, 492, 346, 492, 1186, 494, 1186, 466, 372, 468, 1212, 462, 376, 488, 346, 468, 372, 494, 346, 494, 346, 494, 346, 492, 346, 492, 346, 492, 346, 466, 372, 462, 372, 466, 372, 492, 346, 492, 346, 466, 372, 468, 372, 468, 372, 466, 374, 466, 376, 464, 372, 462, 376, 462, 372, 466, 372, 492, 346, 492, 346, 492, 346, 492, 346, 492, 1186, 492, 1186, 462, 376, 490, 346, 492, 346, 492, 346, 492, 346, 492, 346, 492, 346, 494, 346, 494, 346, 494, 346, 494, 346, 468, 372, 462, 372, 468, 372, 468, 1212, 466, 372, 492, 346, 466, 372, 466, 372, 492, 346, 466, 372, 466, 1212, 462, 1212, 494, 346, 494, 1186, 492, 1186, 466, 372, 494, 1186, 492};   // UNKNOWN 80D3CBE8
uint16_t AC27[375] = {3406, 1634, 466, 1212, 462, 1212, 466, 372, 466, 372, 466, 372, 468, 1212, 466, 372, 466, 372, 466, 1212, 436, 1238, 468, 372, 468, 1212, 468, 372, 442, 398, 466, 1212, 462, 1216, 462, 372, 466, 1212, 468, 1212, 466, 372, 440, 398, 462, 1216, 462, 372, 466, 372, 468, 1212, 468, 372, 468, 372, 466, 372, 436, 404, 462, 376, 462, 372, 466, 372, 468, 372, 468, 372, 440, 398, 440, 398, 442, 398, 462, 376, 462, 376, 462, 372, 466, 9030, 3404, 1634, 436, 1238, 466, 1212, 440, 398, 442, 398, 440, 400, 440, 1238, 436, 402, 436, 398, 466, 1212, 440, 1238, 440, 398, 440, 1238, 436, 404, 436, 404, 436, 1238, 442, 1238, 436, 404, 440, 1238, 436, 1238, 440, 398, 440, 398, 410, 1268, 440, 398, 436, 404, 436, 1238, 442, 398, 442, 398, 440, 398, 410, 428, 410, 428, 436, 402, 440, 398, 436, 404, 436, 402, 436, 398, 442, 398, 440, 398, 440, 398, 410, 430, 436, 404, 436, 402, 436, 402, 436, 402, 436, 398, 440, 398, 440, 1238, 436, 404, 436, 402, 436, 402, 436, 402, 436, 398, 442, 1238, 410, 1270, 436, 402, 436, 402, 436, 402, 436, 1238, 442, 1238, 410, 428, 410, 1270, 436, 404, 436, 404, 436, 398, 442, 398, 442, 398, 410, 1270, 436, 1244, 436, 402, 436, 1238, 442, 1238, 410, 430, 410, 430, 436, 402, 436, 402, 410, 428, 436, 398, 442, 398, 440, 400, 410, 1268, 410, 1270, 410, 1268, 436, 398, 440, 398, 410, 1268, 410, 1268, 410, 428, 410, 1266, 440, 398, 410, 428, 412, 428, 410, 430, 410, 428, 436, 402, 410, 428, 410, 424, 442, 398, 440, 398, 410, 428, 410, 428, 410, 428, 410, 428, 410, 428, 410, 430, 410, 424, 440, 398, 440, 398, 410, 430, 410, 430, 410, 430, 410, 428, 410, 430, 410, 430, 410, 430, 436, 398, 442, 1238, 410, 1268, 438, 402, 412, 428, 410, 428, 410, 428, 410, 424, 440, 398, 410, 428, 410, 428, 410, 428, 410, 428, 410, 428, 410, 428, 410, 424, 440, 398, 410, 1268, 410, 428, 410, 430, 410, 428, 410, 428, 410, 424, 440, 1238, 410, 1268, 410, 1268, 410, 428, 410, 1264, 414, 1264, 410, 428, 410, 1268, 410}; // UNKNOWN 38342480
uint16_t AC28[375] = {3430, 1608, 492, 1186, 468, 1208, 492, 346, 492, 346, 492, 346, 494, 1186, 492, 346, 494, 346, 492, 1186, 490, 1186, 492, 346, 492, 1186, 492, 346, 492, 346, 492, 1186, 494, 1180, 494, 346, 494, 1186, 494, 1186, 492, 346, 494, 346, 492, 1186, 466, 372, 462, 372, 494, 1186, 494, 346, 494, 346, 494, 346, 494, 346, 492, 346, 492, 346, 488, 346, 492, 346, 494, 346, 494, 346, 494, 346, 494, 346, 494, 346, 492, 346, 494, 346, 494, 9002, 3430, 1608, 488, 1186, 492, 1186, 492, 346, 494, 346, 494, 346, 494, 1186, 492, 346, 490, 346, 492, 1186, 492, 1186, 492, 346, 492, 1186, 492, 346, 488, 350, 462, 1212, 492, 1186, 492, 346, 494, 1186, 492, 1186, 492, 346, 492, 346, 462, 1212, 494, 346, 494, 346, 494, 1186, 494, 346, 494, 346, 494, 346, 492, 346, 466, 372, 488, 350, 488, 346, 492, 346, 494, 346, 494, 346, 494, 346, 492, 346, 492, 346, 492, 346, 492, 346, 494, 346, 492, 346, 490, 350, 462, 372, 494, 346, 494, 1186, 494, 346, 492, 346, 494, 346, 492, 346, 492, 346, 494, 1186, 466, 1208, 492, 346, 494, 346, 494, 346, 492, 346, 494, 346, 494, 1186, 494, 1186, 488, 346, 494, 346, 492, 346, 492, 346, 494, 346, 494, 1186, 492, 1186, 492, 346, 494, 1186, 488, 1186, 492, 346, 492, 346, 492, 346, 492, 346, 492, 346, 494, 344, 494, 346, 494, 346, 492, 1186, 492, 1186, 488, 1190, 488, 346, 492, 346, 494, 1186, 492, 1186, 494, 346, 494, 1186, 492, 348, 492, 346, 494, 346, 488, 346, 492, 346, 492, 346, 494, 346, 494, 346, 494, 346, 492, 346, 494, 346, 494, 346, 488, 350, 490, 344, 494, 346, 494, 346, 494, 346, 492, 346, 492, 346, 494, 346, 492, 346, 492, 346, 494, 346, 492, 346, 468, 372, 466, 368, 492, 346, 492, 1186, 494, 1186, 494, 346, 492, 346, 492, 348, 466, 372, 488, 350, 488, 346, 492, 346, 492, 346, 494, 346, 492, 346, 492, 346, 494, 346, 492, 346, 492, 346, 492, 1186, 488, 346, 494, 346, 492, 346, 492, 346, 492, 346, 492, 346, 492, 346, 494, 346, 494, 1186, 488, 1186, 492, 1186, 492, 346, 492, 1186, 494};    // UNKNOWN 3277D7A4
uint16_t ACOff[375] = {3432, 1604, 492, 1186, 492, 1186, 488, 350, 490, 346, 492, 346, 494, 1186, 494, 346, 492, 346, 488, 1190, 488, 1186, 492, 346, 520, 1160, 494, 346, 492, 346, 488, 1190, 488, 1186, 492, 346, 492, 1186, 494, 1186, 490, 346, 520, 320, 494, 1186, 488, 350, 488, 350, 488, 1190, 488, 346, 492, 346, 518, 320, 492, 346, 488, 350, 488, 350, 488, 350, 488, 346, 494, 346, 494, 346, 518, 320, 494, 346, 494, 346, 488, 350, 488, 350, 488, 9004, 3432, 1608, 490, 1186, 492, 1186, 494, 346, 488, 350, 490, 350, 488, 1186, 494, 346, 492, 346, 492, 1186, 488, 1190, 488, 350, 490, 1186, 494, 346, 494, 346, 494, 1186, 488, 1190, 488, 346, 492, 1186, 492, 1186, 488, 350, 488, 350, 490, 1186, 520, 320, 494, 346, 488, 1192, 488, 350, 488, 350, 488, 346, 494, 346, 518, 320, 492, 346, 488, 350, 488, 350, 488, 352, 488, 350, 488, 346, 492, 346, 520, 320, 494, 346, 488, 350, 490, 350, 488, 350, 488, 350, 490, 346, 494, 346, 494, 346, 494, 346, 488, 350, 494, 346, 488, 350, 488, 346, 492, 1186, 520, 1160, 488, 352, 488, 350, 514, 324, 516, 320, 492, 346, 494, 1186, 494, 1186, 488, 350, 490, 350, 488, 346, 494, 346, 494, 346, 494, 1186, 494, 1186, 488, 350, 490, 1186, 494, 1186, 494, 346, 494, 346, 492, 346, 488, 350, 488, 350, 488, 346, 520, 320, 492, 346, 492, 1186, 488, 1192, 488, 1190, 488, 346, 494, 346, 492, 1186, 492, 1186, 488, 350, 488, 1190, 488, 346, 494, 346, 494, 346, 494, 346, 494, 346, 488, 350, 494, 346, 488, 350, 488, 352, 488, 346, 492, 346, 494, 346, 492, 346, 494, 346, 490, 350, 488, 350, 488, 346, 494, 346, 492, 346, 518, 322, 492, 346, 488, 350, 488, 350, 488, 346, 494, 346, 494, 346, 494, 346, 488, 1190, 490, 1190, 490, 350, 488, 346, 492, 346, 494, 346, 494, 346, 492, 346, 488, 350, 488, 350, 488, 350, 488, 346, 494, 346, 492, 346, 492, 346, 488, 350, 490, 1190, 488, 350, 488, 346, 494, 346, 494, 346, 494, 346, 488, 352, 488, 350, 488, 350, 516, 1160, 494, 1186, 494, 346, 494, 346, 488, 1190, 490};     // UNKNOWN 7F6DD306

const char *ssid = STASSID;
const char *password = STAPSK;

const uint16_t kIrLed = 16;

ESP8266WebServer server(80);
IRsend irsend(kIrLed);
BME280 bme280;

void handleLight()
{
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  if (server.method() != HTTP_POST)
  {
    server.send(204);
  }
  else
  {

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));
    if (error)
    {
      server.send(400, "application/json", String("{result: \"error\", message: \"") + String(error.c_str()) + String("\"}"));
      return;
    }
    if (doc["status"])
    {
      irsend.sendRaw(LightOn, 83, 38);
    }
    else
    {
      irsend.sendRaw(LightOff, 83, 38);
    }

    server.send(200, "text/plane", "{result: \"success\", message: \"success\"}");
  }
}

void handleAC()
{
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  if (server.method() != HTTP_POST)
  {
    server.send(204);
  }
  else
  {

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));
    if (error)
    {
      server.send(400, "application/json", String("{result: \"error\", message: \"") + String(error.c_str()) + String("\"}"));
      return;
    }
    if (doc["status"])
    {
      float temperature = doc["temperature"];
      if (temperature == 28.0)
      {
        irsend.sendRaw(AC28, 375, 38);
      }
      else if (temperature == 27.0)
      {
        irsend.sendRaw(AC27, 375, 38);
      }
      else if (temperature == 26.0)
      {
        irsend.sendRaw(AC26, 375, 38);
      }
      else if (temperature == 20.0)
      {
        irsend.sendRaw(AC20, 375, 38);
      }
      else
      {
        server.send(400, "application/json", "{result: \"error\", message: \"incompatible temperature\"}");
        return;
      }
    }
    else
    {
      irsend.sendRaw(ACOff, 375, 38);
    }

    server.send(200, "application/json", "{result: \"success\", message: \"success\"}");
  }
}

void handleEnvironment()
{
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  if (server.method() != HTTP_GET)
  {
    server.send(204);
  }
  else
  {
    float humidity = bme280.readFloatHumidity();
    float pressure = bme280.readFloatPressure();
    float temperature = bme280.readTempC();
    server.send(200, "application/json", String("{\"humidity\": ") + String(humidity) + String(", \"pressure\": ") + String(pressure) + String(", \"temperature\": ") + String(temperature) + String("}"));
  }
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "application/json", message);
}

void setup()
{
  irsend.begin();
  Serial.begin(115200);
  WiFi.config(IPAddress(192, 168, 11, 52), IPAddress(192, 168, 11, 1), IPAddress(255, 255, 255, 0));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.onStart([]()
  {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]()
  {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
  {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error)
  {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  if (!MDNS.begin("irsender") || bme280.beginSPI(4) == false)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("MDNS responder started");
  MDNS.addService("http", "tcp", 80);

  server.enableCORS(true);
  server.on("/light/", handleLight);
  server.on("/air-conditioner/", handleAC);
  server.on("/environment/", handleEnvironment);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  MDNS.update();
  server.handleClient();
  ArduinoOTA.handle();
}
