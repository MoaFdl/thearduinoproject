#include "cAnalogOutput.h"

// Costruttore
cAnalogOutput::cAnalogOutput(uint8_t pin)
  : caOutput(pin),      // Inizializza i membri della classe base (mPinOut(pin), mIsEnabled(false), mOutputState(false))
    mOutputValue(0) {}  //inizializza l'output a 0

// Metodo per configurare il pin come output PWM
void cAnalogOutput::setup() {
  pinMode(mPinOut, OUTPUT);
  analogWrite(mPinOut, 0);  // Imposta il valore iniziale a 0
}

// Metodo per disattivare l'output
void cAnalogOutput::disattiva_Output() {
  analogWrite(mPinOut, 0);
  mOutputState = false;
}
//metodo per sapere lo stato del sensore
bool cAnalogOutput::IsEnabled() {
  return mIsEnabled;
}
//metodo per impostare lo stato del sensore
void cAnalogOutput::set_IsEnabled(bool enable) {
  mIsEnabled = enable;
}
//metodo per impostare lo stato dell'output
void cAnalogOutput::set_Output(uint16_t value) {
  analogWrite(mPinOut, value);
}