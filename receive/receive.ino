//#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>
//#include <Wire.h>

//LiquidCrystal_I2C lcd(0x27, 16, 2);
#define ss 15
#define rst 16
#define dio0 4

//void onReceive(int packetSize){
//  delay(1000);
//  Serial.println("Received packet: ");
//  for (int i = 0; i < packetSize; i++){
//    Serial.print((char)LoRa.read());
//    //if (i == 0 && (char)LoRa.read() == 'a'){
//    //  lcd.setCursor(6,0);
//    //}
//    //if ((char)LoRa.read() != 'b'){
//    //  lcd.print((char)LoRa.read());
//    //}else{
//    //  lcd.setCursor(6,1);
//    //}
//  }
//  Serial.print("\n");
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Wire.begin(2,0);
  //lcd.clear();
  //lcd.init();
  //lcd.backlight();
  //lcd.home();
  //lcd.print("BPM: ");
  //lcd.setCursor(0,1);
  //lcd.print("SpO2: ");
  while(!Serial);
  Serial.println("LoRa receiver:");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed!");
    while(1);
  }
  else{
    Serial.println("LoRa Ready");
  }
  //LoRa.onReceive(onReceive);
  //LoRa.receive();
}

void loop() {
  // put your main code here, to run repeatedly:
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());
  }
  delay(500);

}
