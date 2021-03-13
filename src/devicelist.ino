//***************************************************************************************************
struct bledevices_t {
  String adress;
  BLEAddress * bleaddress;
  BLEClient * bleclient;
  BLERemoteCharacteristic * bleRemoteCharacteristic;

  bool habedaten;
  bool disconnected;
  int disconnectc;
  float temperature;
  float battery;
  byte humidity;

  bledevices_t * next;
};

bledevices_t * devicelist = NULL;

//***************************************************************************************************
bledevices_t * findDeviceByDeviceAdress(const String deviceAddr /**/) { // no forward, please
  bledevices_t * r = devicelist;
  while (r) {
    if (String(r->bleaddress->toString().c_str()) == deviceAddr) {
      return r;
    } else {
      r = r->next;
    }
  }

  return NULL;
}

//***************************************************************************************************
bledevices_t * findDeviceByRemoteCharacteristic(BLERemoteCharacteristic * bleRemoteCharacteristic /**/) { // no forward, please
  bledevices_t * r = devicelist;
  while (r) {
    if (r->bleRemoteCharacteristic == bleRemoteCharacteristic) {
      return r;
    } else {
      r = r->next;
    }
  }

  return NULL;
}

//***************************************************************************************************
bledevices_t * findDeviceByClientPTR(BLEClient * pclient /**/) { // no forward, please
  bledevices_t * r = devicelist;
  while (r) {
    if (r->bleclient == pclient) {
      return r;
    } else {
      r = r->next;
    }
  }

  return NULL;
}

//***************************************************************************************************
bledevices_t * addDevice(const String deviceAddr /**/) { // no forward, please
  if (findDeviceByDeviceAdress(deviceAddr) == NULL) {
    bledevices_t * d = new bledevices_t();

    // vorne einhängen
    d->next = devicelist;
    devicelist = d;

    d->bleaddress = new BLEAddress(deviceAddr.c_str());
    d->adress = deviceAddr;
    d->bleclient = NULL;
    d->bleRemoteCharacteristic = NULL;

    return d;
  } else {
    return NULL;
  }
}
