#include "cAnalogInput.h"

// Costruttore
cAnalogInput::cAnalogInput(uint8_t pin)
  : caInput(pin),   // Inizializza i membri della classe base (mPinIn, mPinValue, mIsEnabled, mPinHasChanged)
    mTrigger(0) {}  //inizializza mTrigger a 0

// Metodo per inizializzare il sensore
void cAnalogInput::setup() {
  pinMode(mPinIn, INPUT);
}
// Metodo per leggere il valore del pin
void cAnalogInput::read_pin() {
  if (mIsEnabled) {
    mPinValue = analogRead(mPinIn);  // Legge il valore analogico
  }
}
//metodo per vedere se lo stato del sensore è cambiato
bool cAnalogInput::PinHasChanged() {
  if (mIsEnabled) {
    return mPinHasChanged;
  }
  return false;
}
//metodo per vedere se il sensore è abilitato
bool cAnalogInput::IsEnabled() {
  return mIsEnabled;
}
//metodo per impostare l'abilitazione del sensore
void cAnalogInput::set_IsEnabled(bool enable) {
  mIsEnabled = enable;
}
//metodo per ottenere il valore del pin
uint16_t cAnalogInput::get_PinValue() {
  if (mIsEnabled) {
    return mPinValue;
  }
  return 0;
}
//metodo per impostare un trigger
void cAnalogInput::set_Trigger(uint16_t trigger) {
  mTrigger = trigger;
}
//metodo per ottenere il valore del trigger
uint16_t cAnalogInput::get_Trigger() {
  return mTrigger;
}
