#include "cDigitalInput.h"


// Costruttore
cDigitalInput::cDigitalInput(uint8_t pin)
  : caInput(pin),                                            // Inizializza i membri della classe base (mPinIn, mPinValue, mIsEnabled, mPinHasChanged)
    mPinNormalState(static_cast<uint8_t>(PinState::NORMAL)),  // Stato normale del pin
    mPinState(static_cast<uint8_t>(PinNormalState::NA)),      // Stato iniziale del pin
    mPinPrevState(static_cast<uint8_t>(PinState::NORMAL))     // Stato precedente del pin
{}

// Metodo per inizializzare il sensore
void cDigitalInput::setup() {
  pinMode(mPinIn, INPUT_PULLUP);  // Configura il pin come input con resistenza pull-up interna
}

// Metodo per leggere il valore del pin
void cDigitalInput::read_pin() {
  if (mIsEnabled) {
    mPinPrevState = get_PinState();
    mPinValue = digitalRead(mPinIn);  // Legge lo stato del pin (PIN_STATE_NORMAL/PIN_STATE_ALLARM)
    uint8_t currentState = get_PinState();

    if (currentState != mPinPrevState) {  
      mPinHasChanged = true;
    } else {
      mPinHasChanged = false;
    }
  }
}
//metodo per vedere lo stato normale del sensore
uint8_t cDigitalInput::get_pinNormalState() {
  return mPinNormalState;
}
//metodo per impostare lo stato normale del sensore
void cDigitalInput::set_pinNormalState(uint8_t state) {
  mPinNormalState = state;
}
//metodo per vedere lo stato del sensore
uint8_t cDigitalInput::get_PinState() {
  if (mIsEnabled) {
    if (mPinValue == 0 && mPinNormalState == static_cast<uint8_t>(PinNormalState::NA)) {
      return static_cast<uint8_t>(PinState::ALARM);
    }
    if (mPinValue == 1 && mPinNormalState == static_cast<uint8_t>(PinNormalState::NA)) {
      return static_cast<uint8_t>(PinState::NORMAL);
    }
    if (mPinValue == 0 && mPinNormalState == static_cast<uint8_t>(PinNormalState::NC)) {
      return static_cast<uint8_t>(PinState::NORMAL);
    }
    if (mPinValue == 1 && mPinNormalState == static_cast<uint8_t>(PinNormalState::NC)) {
      return static_cast<uint8_t>(PinState::ALARM);
    }
  }
  return static_cast<uint8_t>(PinState::NORMAL);
}
//metodo per vedere lo stato precedente del sensore
uint8_t cDigitalInput::get_PinPrevState() {
  return mPinPrevState;
}
//metodo per vedere se lo stato del sensore è cambiato
bool cDigitalInput::PinHasChanged() {
  if (mIsEnabled) {
    return mPinHasChanged;
  }
  return false;
}
//metodo per vedere se il sensore è abilitato
bool cDigitalInput::IsEnabled() {
  return mIsEnabled;
}
//metodo per impostare l'abilitazione del sensore
void cDigitalInput::set_IsEnabled(bool enable) {
  mIsEnabled = enable;
}
//metodo per ottenere il valore del pin
uint16_t cDigitalInput::get_PinValue() {
  return mPinValue;
}
