#include <SPI.h>
#include <Ethernet.h>

// Địa chỉ MAC và IP của Client
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 178);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
// Địa chỉ IP của Server
IPAddress server(192, 168, 1, 177);

EthernetClient client;

void setup() {
  Serial.begin(115200);
  Ethernet.init(5);   // MKR ETH Shield

  // Khởi động Ethernet với địa chỉ MAC và IP đã chỉ định
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  delay(1000);
  Serial.println("Connecting...");

  // Kết nối tới server
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    client.println("GET / HTTP/1.1");
    client.println("Host: 192.168.1.177");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting.");
    client.stop();
    while (true);
  }
}
