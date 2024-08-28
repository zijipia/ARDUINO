#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

// Địa chỉ MAC và IP tĩnh của Arduino server
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);
unsigned int localPort = 8888; // Port UDP server lắng nghe

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// Tạo đối tượng UDP
EthernetUDP Udp;

void setup() {
  Ethernet.init(5);   // MKR ETH Shield

  // Khởi động Ethernet
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);

  Serial.begin(115200);
  Serial.println("UDP Server started");
}

void loop() {
  // Kích thước của gói tin nhận được
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    Serial.print(remote);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // Đọc dữ liệu gói tin
    char packetBuffer[255];
    Udp.read(packetBuffer, 255);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // Gửi phản hồi lại client
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("Hello from server");
    Udp.endPacket();
  }
}
