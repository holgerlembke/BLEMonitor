//***************************************************************************************************
void setupAll(void) {
  Serial.begin(115200);
  delay(1000);

  bootinfo();
  ramDisplayDings();

  BLEDevice::init(devName().c_str());
}

//***************************************************************************************************
void loopAll(void) {
  static unsigned long ticker = 0;

  static int sekunden = 0;
  static byte state = 0;
  static byte oldstate = 255;
  const int bledelay = 15;
  const int bledatawait = 60;
  const int blerescanwait = 5 * 60;

  if (oldstate != state) {
    Serial.print(F("State: "));
    Serial.print(state);
    Serial.println();
    oldstate = state;
  }

  if (millis() - ticker >= 1000) {
    sekunden += (millis() - ticker) / 1000;
    ticker = millis();

    switch (state) {
      case 0: {
          if (sekunden > bledelay) {
            scan4LYWSD03MMCAdresses();
            ramDisplayDings();
            sekunden = 0;
            state = 1;
          }
          break;
        }
      case 1: {
          if (sekunden > bledelay) {
            CreateBLEClients();
            ramDisplayDings();
            sekunden = 0;
            state = 2;
          }
          break;
        }
      case 2: {
          if (sekunden > bledelay) {
            ConnectBLEClients();
            ramDisplayDings();
            sekunden = 0;
            state = 3;
          }
          break;
        }
      case 3: {
          if (sekunden > bledelay) {
            CreateBLEServices();
            ramDisplayDings();
            sekunden = 0;
            state = 4;
          }
          break;
        }
      case 4: {
          // haben alle Daten erhalten?
          if (DisconnectAllBLEClients()) {
            ramDisplayDings();
            sekunden = 0;
            state = 12;
          }
          if (sekunden > bledatawait) {
            ramDisplayDings();
            sekunden = 0;
            state = 5;
          }
          break;
        }
      case 5: {
          // wenn nicht, alle beenden
          DisconnectAllBLEClients(true);
          ramDisplayDings();
          sekunden = 0;
          state = 12;
          break;
        }

      // Warten auf den nächsten Scan
      case 12: {
          Serial.println(F("Wait"));
          state = 13;
          break;
        }
      case 13: {
          if (sekunden > blerescanwait) {
            ramDisplayDings();
            sekunden = 0;
            state = 0;
          }
        }
    }
  }
}
