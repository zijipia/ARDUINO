#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

byte mac[] = {0x00, 0xBA, 0xDA, 0xDF, 0xAC, 0x02};
IPAddress ip(192, 168, 1, 55);
IPAddress serverIp(192, 168, 1, 177); 
unsigned int serverPort = 8888;

EthernetUDP Udp;

void setup() {
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  Udp.begin(serverPort);  
  Serial.begin(115200);
  Serial.println("UDP Client started");
  sendPacket("Hello from COM8");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char replyBuffer[255];
    Udp.read(replyBuffer, 255);
    Serial.print("Reply from");
    Serial.println(Udp.remoteIP());

    Serial.println(replyBuffer);

  }

  // Kiểm tra nếu có dữ liệu từ Serial
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n'); // Đọc toàn bộ dòng từ Serial
    sendPacket(message.c_str()); // Gửi dữ liệu đến server
  }
}

void sendPacket(const char *message) {
    Udp.beginPacket(serverIp, serverPort);
    Udp.write(message);
    Udp.endPacket();
    Serial.print(".");
}
