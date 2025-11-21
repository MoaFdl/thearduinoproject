#ifndef cDigitalOutput_H
#define cDigitalOutput_H

#include <stdint.h>    //libreria
#include "caOutput.h"  //ereditiamo classe astratta

class cDigitalOutput : public caOutput {

public:
  // Costruttore
  cDigitalOutput(uint8_t pin);  
  
  //metodi ereditati
  void setup() override;                     // Metodo per inizializzare il sensore
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  void set_Output(uint16_t value) override;  //imposta un valore di output

  // Metodi aggiuntivi specifici
  void attiva_Output();                      //attiva l'output
  void disattiva_Output();                   //disattiva l'output
  uint16_t get_OutputState();                //ritorna stato output(0 o 1)
};

#endif