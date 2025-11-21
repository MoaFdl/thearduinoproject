#ifndef caOutput_H
#define caOutput_H

#include <stdint.h> //libreria 

class caOutput {
protected:
  uint8_t mPinOut;    // Pin in cui colleghiamo con Arduino
  bool mIsEnabled;    // Classe abilitata o meno
  bool mOutputState;  // Stato dell'output

public:
  // Costruttore
  caOutput(uint16_t pin)  //pin sensore
    : mPinOut(pin), mIsEnabled(false), mOutputState(false) {}

  virtual ~caOutput() =default;  // Distruttore virtuale 

  virtual void setup() = 0;                     // Metodo per inizializzare il sensore
  virtual bool IsEnabled() = 0;                 //ritorna oggetto abilitato o meno
  virtual void set_IsEnabled(bool enable) = 0;  //set stato abilitazione oggetto
  virtual void set_Output(uint16_t value) = 0;  //imposta valore output
};
#endif  
