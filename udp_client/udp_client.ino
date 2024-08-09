#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
// IPAddress myDns(192, 168, 1, 1);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 0, 0);
IPAddress serverIp(192, 168, 1, 55); 
unsigned int serverPort = 8888;

EthernetUDP Udp;

unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  // Ethernet.begin(mac, ip, myDns, gateway, subnet);
  Udp.begin(serverPort);
  Serial.begin(115200);
  Serial.println("UDP Client started");
  sendPacket("Hello from client");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char replyBuffer[255];
    Udp.read(replyBuffer, 255);
    Serial.println("Reply from server: ");
    Serial.println(replyBuffer);

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("ReplyBuffer");
    Udp.endPacket();
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sendPacket("Another message from client");
  }
}

void sendPacket(const char *message) {
    Udp.beginPacket(serverIp, serverPort);
    Udp.write(message);
    Udp.endPacket();
    Serial.print(".");
}