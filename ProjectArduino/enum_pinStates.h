#ifndef ENUM_PIN_STATES_H
#define ENUM_PIN_STATES_H

#include <stdint.h> //libreria 

// Enum class per rappresentare lo stato del pin
enum class PinState : uint8_t {
  NORMAL = 0,  // Stato normale
  ALARM = 1    // Stato di allarme
};

// Enum class per rappresentare lo stato normale del pin (NA o NC)
enum class PinNormalState : uint8_t {
  NA = 0,  // Normalmente Aperto (Normally Open)
  NC = 1   // Normalmente Chiuso (Normally Closed)
};

#endif 