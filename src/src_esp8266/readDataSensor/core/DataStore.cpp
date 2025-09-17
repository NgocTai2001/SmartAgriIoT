#include "DataStore.h"
#include <ArduinoJson.h>

void DataStore::set(const EnvReading& r) {
  _latest = r;
}

const EnvReading& DataStore::latest() const {
  return _latest;
}

String DataStore::toJsonString() const {
  return _latest.toJsonString();
}