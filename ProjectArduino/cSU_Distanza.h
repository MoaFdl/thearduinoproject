#ifndef cSU_DISTANZA_H
#define cSU_DISTANZA_H

//librerie
#include <stdint.h>
#include <NewPing.h> //testato su versione 1.9.7

#include "caInput.h"        //classe astratta ereditata


class cSU_Distanza : public caInput{
private:
  NewPing mSonar;        //oggetto della libreria newping
  uint16_t mDistanza;    //distanza misurata
  uint16_t mTrigger;      //trigger per indicare una soglia

public:
  // Costruttore
  cSU_Distanza(uint8_t pin, uint16_t maxDistance);

// Metodi ereditati
  void setup() override;                     // inizializza il sensore
  void read_pin() override;                  //aggiorna distanza
  bool PinHasChanged() override;             
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  uint16_t get_PinValue() override;          
                  
// Metodi aggiuntivi specifici
  uint16_t misuraDistanza();           // Metodo per misurare la distanza
  void set_Trigger(uint16_t trigger);  //imposta un valore di Trigger
  uint16_t get_Trigger();              //ritorna mTrigger
};

#endif