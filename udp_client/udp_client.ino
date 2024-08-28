#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress serverIp(192, 168, 1, 55); 
unsigned int serverPort = 8888;

EthernetUDP Udp;

void setup() {
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  Udp.begin(serverPort);  
  Serial.begin(115200);
  Serial.println("UDP Client started");
  sendPacket("Hello from COM5");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char replyBuffer[255];
    Udp.read(replyBuffer, 255);
    Serial.print("Reply from ");
    Serial.println(Udp.remoteIP());

    Serial.println(replyBuffer);

  }


  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    sendPacket(message.c_str());
  }
}

void sendPacket(const char *message) {
    Udp.beginPacket(serverIp, serverPort);
    Udp.write(message);
    Udp.endPacket();
    Serial.print(".");
}
