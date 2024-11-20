void setup() {
  // Khởi tạo Serial
  Serial.begin(9600);
  // Khởi tạo bộ sinh số ngẫu nhiên với seed từ giá trị ngẫu nhiên của analog (nếu cần)
  randomSeed(analogRead(0));
}

void loop() {
  // Sinh số ngẫu nhiên từ 0 đến 100
  int randomNumber = random(0, 101);
  // Xuất số ngẫu nhiên ra Serial
  Serial.println(randomNumber);
  // Chờ 5 giây
  delay(5000);
}
