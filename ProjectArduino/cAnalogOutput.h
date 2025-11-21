#ifndef CANALOGOUTPUT_H
#define CANALOGOUTPUT_H

#include <stdint.h> //libreria 
#include "caOutput.h"  //ereditiamo classe astratta

class cAnalogOutput : public caOutput {
private:
  uint16_t mOutputValue;  // Valore corrente dell'output PWM

public:
  // Costruttore
  cAnalogOutput(uint8_t pin);

  //metodi ereditati
  void setup() override;                     // Metodo per inizializzare il sensore
  bool IsEnabled() override;                 //ritorna oggetto abilitato o meno
  void set_IsEnabled(bool enable) override;  //set stato abilitazione oggetto
  void set_Output(uint16_t value) override;  //imposta un valore di output
  
  // Metodi aggiuntivi specifici
  void disattiva_Output();  //disattiva l'output
};

#endif