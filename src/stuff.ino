//***************************************************************************************************
void bootinfo(void) {
  Serial.print(F("\n"));
  Serial.print(banner);
  Serial.print(prgversion);
  Serial.print(": ");
  Serial.print(__DATE__);
  Serial.print("/");
  Serial.print(__TIME__);
  Serial.println();

  // Magic stuff...
  esp_chip_info_t out_info;
  esp_chip_info(&out_info);

  Serial.println("ESP: " + String(ESP.getSdkVersion()));
  Serial.println("Chip: Revision 0x" + String(out_info.revision, HEX) +
                 " Cores 0x" + String(out_info.cores, HEX));
  // Serial.println("Boot-Version " + String(ESP.getBootVersion()) + " -Mode: " + String(ESP.getBootMode()));
  Serial.println("CPU-Freq: " + String(ESP.getCpuFreqMHz()) + " MHz");
  //Serial.println("FlashChipID: 0x" + String(ESP.getFlashChipId(), HEX) + "/0x" + String(ESP.getFlashChipVendorId(), HEX));
  Serial.println("Flash: Size " + String(ESP.getFlashChipSize()) +
                 " B Speed: " + String(ESP.getFlashChipSpeed()) + " Hz"); // Hz. Because it makes so much sense....
  Serial.println("Sketch Size: " + String(ESP.getSketchSize()) + " B");
  //Serial.println("Reset Reason: " + String(ESP.getResetReason()));
  //Serial.println("Reset Info: " + String(ESP.getResetInfo()));
  // Serial.println("Heap Size: " + String(ESP.getHeapSize()) + " B, free: " + String(ESP.getFreeHeap()) + " B");
  Serial.println("Psram Size: " + String(ESP.getPsramSize()) + " B, free: " + String(ESP.getFreePsram()) + " B");
}

//***************************************************************************************************
void ramDisplayDings(void) {
  Serial.print(F("Heap Size: "));
  Serial.print(ESP.getHeapSize());
  Serial.print(F(" B, free: "));
  Serial.print(ESP.getFreeHeap());
  Serial.print(F(" B, largest: "));
  Serial.print(ESP.getMaxAllocHeap());
  Serial.print(F(" B"));
  Serial.println();
}

//***************************************************************************************************
String devName(void) {
  char ssid[23];
  uint64_t chipid = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
  uint16_t chip = (uint16_t)(chipid >> 32);
  snprintf(ssid, 23, "esp32BleHub_%04X%08X", chip, (uint32_t)chipid);
  return String(ssid);
}
