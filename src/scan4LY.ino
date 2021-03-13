//***************************************************************************************************
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      if ( (advertisedDevice.haveName()) &&
           (String(advertisedDevice.getName().c_str()) == "LYWSD03MMC") ) {
        if (addDevice(advertisedDevice.getAddress().toString().c_str())) {
          Serial.print(F("Found device: "));
          Serial.print(advertisedDevice.getAddress().toString().c_str());
          Serial.println();
        }
      }
    }
};

BLEScan * pBLEScan = NULL;

//***************************************************************************************************
void scan4LYWSD03MMCAdresses()
{
  Serial.println(F("Scan for LYWSD03MMCs"));

  if (!pBLEScan) {
    // put your main code here, to run repeatedly:
    pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(0x50);
    pBLEScan->setWindow(0x30);
  }

  BLEScanResults foundDevices = pBLEScan->start(scan4LYWSD03MMCtime);
}
