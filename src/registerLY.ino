
//***************************************************************************************************
static BLEUUID serviceUUID("ebe0ccb0-7a0a-4b0c-8a1a-6ff2997da3a6");
static BLEUUID    charUUID("ebe0ccc1-7a0a-4b0c-8a1a-6ff2997da3a6");

static void notifyCallback( BLERemoteCharacteristic * bleRemoteCharacteristic,
                            uint8_t* pData,
                            size_t length,
                            bool isNotify) {
  if (length == 5) {
    bledevices_t * r = findDeviceByRemoteCharacteristic(bleRemoteCharacteristic);

    if (r) {
      r->temperature = (pData[0] | (pData[1] << 8)) / 100.0; //little endian
      r->humidity = pData[2];
      r->battery = (pData[3] | (pData[4] << 8)) / 1000.0;
      r->habedaten = true;
    } else {
      Serial.println(F("Panic: no r"));
    }

    // wenn wir diconnecten, sind die beiden ungültig
    // device->bleRemoteCharacteristic = NULL;
    // das kann man an dieser stelle nicht machen, crasht....
    // device->bleclient->disconnect();
  }
}

//***************************************************************************************************
class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient * pclient) {
      bledevices_t * r = findDeviceByClientPTR(pclient);
      if (r) {
        r->disconnected = false;
        r->disconnectc = 0;
      }
      /*
        Serial.print(F("Connected: "));
        Serial.print(pclient->getPeerAddress().toString().c_str());
        delay(500);
        BLERemoteService * pRemoteService = pclient->getService(serviceUUID);
        if (!pRemoteService) {
        Serial.print(F(", no service found"));
        pclient->disconnect();
        } else {
        Serial.println(F(", service found"));

        BLERemoteCharacteristic * pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
        if (! pRemoteCharacteristic) {
          Serial.print(F(", no characteristic found."));
          pclient->disconnect();
        } else {
          Serial.print(F(", characteristic found."));
          pRemoteCharacteristic->registerForNotify(notifyCallback);
        }
        }
        Serial.println();
      */
    }

    void onDisconnect(BLEClient * pclient) {
      Serial.print("Disconnected: ");
      Serial.print(pclient->getPeerAddress().toString().c_str());
      Serial.println();
    }
};

//***************************************************************************************************
void CreateBLEClients(void) {
  bledevices_t * r = devicelist;
  while (r) {
    if (!r->bleclient) {
      Serial.print(F("Create: "));
      Serial.print(r->bleaddress->toString().c_str());
      Serial.println();

      r->bleclient = BLEDevice::createClient();
      r->bleclient->setClientCallbacks(new MyClientCallback());
      // r->bleclient->connect(*(r->bleaddress));
    }
    r = r->next;
  }
}

//***************************************************************************************************
void ConnectBLEClients(void) {
  bledevices_t * r = devicelist;
  while (r) {
    if (r->bleclient) {
      if (r->bleclient->isConnected()) {
        Serial.println(F("Panic: Still connected."));
      }
      Serial.print(F("Connecting "));
      Serial.print(r->bleaddress->toString().c_str());
      Serial.println();
      r->habedaten = false;
      r->bleclient->connect(*(r->bleaddress));
    }
    r = r->next;
  }
}

//***************************************************************************************************
bool DisconnectAllBLEClients(const bool auchohnedaten = false) {
  byte bles = 0, blesshut = 0;

  bledevices_t * r = devicelist;
  while (r != NULL) {
    bles++;
    if ( (r->bleclient) && ( (r->habedaten) || (auchohnedaten) ) && (r->bleclient->isConnected()) ) {
      blesshut++;
      Serial.print(F("Data for "));
      Serial.print(r->bleaddress->toString().c_str());
      Serial.print(F(": Temperatur: "));
      Serial.print(r->temperature, 1);
      Serial.print(F("° C, Humidity: "));
      Serial.print(r->humidity);
      Serial.print(F(" %, Battery: "));
      Serial.print(r->battery, 1);
      Serial.print(F(" V"));
      Serial.println();

      Serial.print(F("Disconnecting "));
      Serial.print(r->bleaddress->toString().c_str());
      Serial.println();
      r->bleRemoteCharacteristic = NULL;
      if (r->bleclient->isConnected()) {
        r->disconnectc++;
        if (r->disconnectc > 1) {
          Serial.println(F("Panic: Undisconnect 1?"));
        }
        r->bleclient->disconnect();
      } else {
        Serial.println(F("Panic: Undisconnect 2?"));
      }
    }
    r = r->next;
  }

  return bles==blesshut;
}

//***************************************************************************************************
void CreateBLEServices(void) {
  bledevices_t * r = devicelist;
  while (r) {
    if ( (r->bleclient) && (r->bleclient->isConnected()) ) {
      Serial.print(F("Connected: "));
      Serial.print(r->bleclient->getPeerAddress().toString().c_str());

      BLERemoteService * pRemoteService = r->bleclient->getService(serviceUUID);
      if (!pRemoteService) {
        Serial.print(F(", no service found"));
        r->bleclient->disconnect();
      } else {
        Serial.print(F(", service found"));

        r->bleRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
        if (! r->bleRemoteCharacteristic) {
          Serial.print(F(", no characteristic found."));
          r->bleclient->disconnect();
        } else {
          Serial.print(F(", characteristic found."));
          r->bleRemoteCharacteristic->registerForNotify(notifyCallback);
        }
      }
      Serial.println();
    }
    r = r->next;
  }
}
