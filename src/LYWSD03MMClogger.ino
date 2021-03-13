// Board settings
// Board: "ESP32 Dev Module"
// Upload Speed: "921600"
// CPU Frequency: "240MHz (WiFi/BT)"
// Flash Frequency: "80MHz"
// Flash Mode: "QIO"
// Flash Size: "4MB (32Mb)"
// Partition Scheme: "Huge APP (3MB No OTA/1MB SPIFFS)"
// Core Debug Level: "Keine"
// PSRAM: "Disabled"

/*
   Goal:
     ** scan for multiple LYWSD03MMCs
     ** log their data
     ** post it as mqtt into home network

   2021-03-11
     -- beginn


   Currently, the mix of std::string and String() makes it a total mess.  


    BLEAddress
    https://github.com/espressif/arduino-esp32/blob/master/libraries/BLE/src/BLEAddress.h

    BLEDevice
    https://github.com/espressif/arduino-esp32/blob/master/libraries/BLE/src/BLEDevice.h

    BLEClient
    https://github.com/espressif/arduino-esp32/blob/master/libraries/BLE/src/BLEClient.h

    BLERemoteCharacteristic
    https://github.com/espressif/arduino-esp32/blob/master/libraries/BLE/src/BLERemoteCharacteristic.h


    anderer ansatz:
      https://github.com/tobozo/ESP32-BLECollector/blob/master/BLE.h

*/

// Wifi-Login, mqtt ips etc
// https://github.com/holgerlembke/privatedata
#include <privatedata.h>

// ESP32
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>


const String banner = F("LYWSD03MMC Scanner and Monitor ");
const String prgversion = F("0.2");

// Suchdauer nach LYWSD03MMCs
const int scan4LYWSD03MMCtime = 45;


//Jepp.
void setup(void) {
  setupAll();
}

void loop(void) {
  loopAll();
}
