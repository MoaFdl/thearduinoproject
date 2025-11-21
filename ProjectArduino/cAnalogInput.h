#ifndef CANALOGINPUT_H
#define CANALOGINPUT_H

#include <stdint.h> //libreria 
#include "caInput.h"  //classe astratta ereditata

class cAnalogInput : public caInput {
private:
  uint16_t mTrigger;  //trigger per indicare una soglia

public:
  // Costruttore
  cAnalogInput(uint8_t pin);

  // Metodi ereditati
  void setup() override;                     // inizializzar il sensore
  void read_pin() override;                  // Aggiorna lo stato corrente di mPinValue
  bool PinHasChanged() override;             //stato del pin è cambiato
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  uint16_t get_PinValue() override;          //ritorna valore del pin
   
  // Metodi aggiuntivi specifici
  void set_Trigger(uint16_t trigger);        //imposta un valore di Trigger
  uint16_t get_Trigger();                    //ritorna mTrigger
};
#endif