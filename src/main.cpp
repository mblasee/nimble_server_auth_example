#include <Arduino.h>
#include "NimBLEDevice.h"

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Starting NimBLE Server");
    NimBLEDevice::init("NimBLE");
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    NimBLEDevice::setSecurityAuth(true, true, true);
    NimBLEDevice::setSecurityPasskey(123356);
    NimBLEDevice::setSecurityIOCap(BLE_HS_IO_KEYBOARD_ONLY);
    NimBLEServer *pServer = NimBLEDevice::createServer();
    NimBLEService *pService = pServer->createService("ABCD");
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic("1234", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::READ_ENC);

    pService->start();
    pCharacteristic->setValue("Hello BLE");

    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID("ABCD");
    pAdvertising->start();
}

void loop()
{
}