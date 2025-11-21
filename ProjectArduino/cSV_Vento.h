#ifndef cSV_VENTO_H
#define cSV_VENTO_H

#include <stdint.h> //libreria 
#include "caInput.h"  //classe astratta ereditata

class cSV_Vento : public caInput {

private:
  uint8_t mPinIn;  // Pin analogico a cui è collegato il sensore
  float mVoltage;  //valore voltaggio

public:
  //costruttore
  cSV_Vento(uint8_t pin);
  
  // Metodi ereditati
  void setup() override;                     // inizializzar il sensore
  void read_pin() override;                  // Aggiorna lo stato corrente di mPinValue
  bool PinHasChanged() override;             //stato del pin è cambiato
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  uint16_t get_PinValue() override;          //ritorna valore del pin
  
  // Metodi aggiuntivi specifici
  uint16_t calcolaVelocita();                //calcola velocità del vento
};

#endif