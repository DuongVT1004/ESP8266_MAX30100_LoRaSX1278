//#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define REPORTING_PERIOD_MS 1000
#define ss 15
#define rst 16
#define dio0 2

//LiquidCrystal_I2C lcd(0x3F, 16, 2);

PulseOximeter pox;
uint32_t tsLastReport = 0;
float BPM, SpO2;
int counter = 0;

void onBeatDetected(){
  ;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if(!pox.begin()){
    Serial.println("FAILED");
    for(;;);
  }else{
    Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
  while(!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if(!LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed!");
    delay(100);
    while(1);
  }else{
    Serial.println("LoRa ready");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  pox.update();
  if(millis() - tsLastReport > REPORTING_PERIOD_MS){
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    Serial.print("BPM: ");
    Serial.print(BPM);
    Serial.print("\tSpO2: ");
    Serial.print(SpO2);
    Serial.print("%");
    Serial.println("\n");  
    tsLastReport = millis();
  }
  LoRa.beginPacket();
  LoRa.print("Pkt No:");
  LoRa.println(counter);
  LoRa.print("Heart Rate: ");
  LoRa.print(BPM);
  LoRa.print("\tSpO2: ");
  LoRa.print(SpO2);
  LoRa.print("%");
  LoRa.print("\n");
  LoRa.endPacket();
  counter++;
  //delay(1000);
}
