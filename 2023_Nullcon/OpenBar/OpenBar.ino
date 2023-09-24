#include <BLEDevice.h>
#include <BLEUtils.h>
#include "BLEUUID.h"
#include <BLEServer.h>
#include <BLE2902.h>

uint8_t  BLE_ADDRESS[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0x13, 0x37};

#define SERVICE_UUID            "0000ffe0-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID_1   "0000ffe1-0000-1000-8000-00805f9b34fb"
#define CHARACTERISTIC_UUID_2   "00001143-0000-1000-8000-00805f9b34fb"

bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println(F("BLEServerCallbacks.onConnect()"));
  }
  
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println(F("BLEServerCallbacks.onDisconnect()"));
    ESP.restart(); // easier than restarting advertising
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic) {
    std::string uuid = pCharacteristic->getUUID().toString();
    
    uint8_t data[1] = {0x00};
    pCharacteristic->setValue(data, 1);

    std::string value = pCharacteristic->getValue();

    Serial.println(F("BLECharacteristic.onRead()"));
    Serial.print(F("> UUID:  "));
    Serial.println(uuid.c_str());
    Serial.print(F("> Value: "));
    for (uint8_t i = 0; i < value.length(); i++)
      Serial.printf("%02X ", value[i]);
    Serial.println();
	}
 
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string uuid = pCharacteristic->getUUID().toString();
    std::string value = pCharacteristic->getValue();

    Serial.println(F("BLECharacteristic.onWrite()"));
    Serial.print(F("> UUID:  "));
    Serial.println(uuid.c_str());
    Serial.print(F("> Value: "));
    for (uint8_t i = 0; i < value.length(); i++)
      Serial.printf("%02X ", value[i]);
    Serial.println();
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting the fake box!");

  BLEDevice::init("Arduino");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic_1 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_1,
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_WRITE_NR
  );
  pCharacteristic_1->setCallbacks(new MyCallbacks());
  
  BLECharacteristic *pCharacteristic_2 = pService->createCharacteristic(
    CHARACTERISTIC_UUID_2,
    BLECharacteristic::PROPERTY_BROADCAST |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_READ
  );
  pCharacteristic_2->setCallbacks(new MyCallbacks());
  pCharacteristic_2->addDescriptor(new BLE2902());

  pService->start();
  
  // Data Types
  // 0x01: Flags
  // 0x06: Incomplete List of 128-bit Service Class UUIDs
  // 0x09: Local Name
  BLEAdvertisementData advData = BLEAdvertisementData();
  advData.setFlags(0x06);         // 0x01
  advData.setPartialServices(BLEUUID::fromString(SERVICE_UUID));

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setAdvertisementData(advData);
  
  BLEAdvertisementData scanData =  BLEAdvertisementData();
  scanData.setName("OpenBar");    // 0x09

  pAdvertising->setScanResponseData(scanData);
  pAdvertising->setDeviceAddress(BLE_ADDRESS);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  
  BLEDevice::startAdvertising();
}

void loop() {
  delay(2000);
}
