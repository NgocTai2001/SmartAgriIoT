#pragma once
#include "Type.h"

//store data suport to MQTT sver 
class DataStore {
public:
  DataStore() = default;

  void set(const EnvReading& r);   
  const EnvReading& latest() const; 

  String toJsonString() const; 

private:
  EnvReading _latest;
};