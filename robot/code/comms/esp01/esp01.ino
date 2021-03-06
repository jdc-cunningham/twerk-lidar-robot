// using library https://github.com/gilmaimon/ArduinoWebsockets
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

using namespace websockets;
WebsocketsServer socketServer;

bool clientActive = false;

void connectToWiFi()
{
  WiFi.begin("SSID", "PASS");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }

  Serial.println("Connected!");
  Serial.println("Starting socket server...");
  socketServer.listen(80);
}

void clearSerial()
{
  while (Serial.available())
  {
    Serial.read();
  }
}

void setup()
{
  Serial.begin(115200);
  connectToWiFi();
} 

void loop()
{
  if (!clientActive)
  {
    auto client = socketServer.accept();
    clientActive = true;

    for (int i = 0; i < 5000; i++)
    {
      if (client.available())
      {
        auto msg = client.readBlocking();

        if (msg.data().length() > 0)
        {
          Serial.print(msg.data());
        }

        if (Serial.available())
        {
          client.send(Serial.readString());
        }
      }
      delay(1);
    }

    client.close();
    clientActive = false;
  }

  delay(50);
}