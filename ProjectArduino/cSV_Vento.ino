//classe gestore sensore di vento
#include "cSV_Vento.h"

// Costruttore
cSV_Vento::cSV_Vento(uint8_t pin)
  : caInput(pin),   // Inizializza i membri della classe base (mPinIn, mPinValue, mIsEnabled, mPinHasChanged)
    mVoltage(0) {}  //inizializza il voltaggio a 0

// Metodo per inizializzare il sensore
void cSV_Vento::setup() {
  pinMode(mPinIn, INPUT);
}
// Metodo per leggere il valore del pin
void cSV_Vento::read_pin() {
  if (mIsEnabled) {
    mPinValue = analogRead(mPinIn);
    mVoltage = mPinValue * (5.0 / 1023.0);  // Converte il valore analogico in tensione (0-5V)
  }
}
//metodo per vedere se il sensore è abilitato
bool cSV_Vento::IsEnabled() {
  return mIsEnabled;
}
//metodo per impostare l'abilitazione del sensore
void cSV_Vento::set_IsEnabled(bool enable) {
  mIsEnabled = enable;
}
//metodo per vedere se lo stato del sensore è cambiato
bool cSV_Vento::PinHasChanged() {
  mPinHasChanged = mPinValue != get_PinValue();
  return mPinHasChanged;
}
//metodo per ottenere il valore del pin
uint16_t cSV_Vento::get_PinValue() {
  return mPinValue;
}

//metodo per calcolare la velocità del vento
uint16_t cSV_Vento::calcolaVelocita() {
  float windSpeed = 0;
  if (mIsEnabled) {
    //calcoli fatti per ricevere dati più attendibili dal sensore
    if (mVoltage >= 0 && mVoltage <= 0.3) {
      windSpeed = 106.67 * mVoltage;
    } else if (mVoltage > 0.3 && mVoltage <= 0.6) {
      windSpeed = (93.33 * mVoltage) + 4;
    } else if (mVoltage > 0.6 && mVoltage <= 0.9) {
      windSpeed = (73.33 * mVoltage) + 16;
    } else if (mVoltage > 0.9) {
      windSpeed = (85.71 * mVoltage) + 5;
    }
    windSpeed = windSpeed * 100;  // rende più facile la consultazione attraverso modbus
  }

  return (uint16_t)windSpeed;
}
