#ifndef caInput_H
#define caInput_H

#include <stdint.h> //libreria 

class caInput {
protected:
  uint8_t mPinIn;       // Pin in cui colleghiamo con Arduino
  bool mIsEnabled;      // Classe abilitata o meno
  bool mPinHasChanged;  // Lo stato del pin è cambiato dall'ultima chiamata di read_pin()
  uint16_t mPinValue;   // Variabile per memorizzare il valore del pin

public:
  // Costruttore
  caInput(uint8_t pin)  //pin sensore
    : mPinIn(pin), mIsEnabled(true), mPinHasChanged(false), mPinValue(0) {}

  virtual ~caInput() =default; // Distruttore virtuale 

  // Metodi virtuali puri (senza implementazione)
  virtual void setup() = 0;                     // Metodo per inizializzare il sensore
  virtual void read_pin() = 0;                  //aggiorna lo stato corrente di mPinValue
  virtual bool PinHasChanged() = 0;             //stato del pin è cambiato
  virtual bool IsEnabled() = 0;                 //ritorna oggetto abilitato o meno
  virtual void set_IsEnabled(bool enable) = 0;  //set stato abilitazione oggetto
  virtual uint16_t get_PinValue() = 0;          //ritorna valore del pin
};

#endif  