#ifndef cDigitalInput_H
#define cDigitalInput_H

#include <stdint.h>          //libreria
#include "enum_PinStates.h"  //enum utilizzati
#include "caInput.h"         //classe astratta ereditata

class cDigitalInput : public caInput {
private:
  uint8_t mPinNormalState;  // Stato normale del pin (STATE_NA/STATE_NC)
  uint8_t mPinState;        // Stato del digital input (STATE_NORMAL/STATE_ALARM)
  uint8_t mPinPrevState;    // Stato precedente di mPinState

public:

  cDigitalInput(uint8_t pin);  // Costruttore

  // Metodi ereditati
  void setup() override;                     // inizializzar il sensore
  void read_pin() override;                  // Aggiorna lo stato corrente di mPinValue
  bool PinHasChanged() override;             //stato del pin è cambiato
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  uint16_t get_PinValue() override;          //ritorna valore del pin

  // Metodi aggiuntivi specifici
  uint8_t get_pinNormalState();            //stato normale del sensore
  void set_pinNormalState(uint8_t state);  //impostalo stato normale del sensore
  uint8_t get_PinState();                  // Stato del pin in funzione di mPinValue e mPinNormalState (ritorna STATE_NORMAL/STATE_ALARM)
  uint8_t get_PinPrevState();              // Stato precedente del pin
};

#endif