//classe gestione sensore di distanza
#include "cSU_Distanza.h"


//costruttore
cSU_Distanza::cSU_Distanza(uint8_t pin, uint16_t maxDistance)
  :caInput(pin),                              // Inizializza i membri della classe base (mPinIn, mPinValue, mIsEnabled, mPinHasChanged)
    mSonar(pin, pin, maxDistance), //inizializzazione oggetto mSonar
    mDistanza(0),
    mTrigger(0) {}  //inizializza mTrigger a 0

// Metodo per inizializzare il sensore
void cSU_Distanza::setup() {
}

//metodo per vedere se lo stato del sensore è cambiato
bool cSU_Distanza::PinHasChanged() {
  if (mIsEnabled) {
    return mPinHasChanged;
  }
  return false;
}

//metodo per ottenere il valore del pin
uint16_t cSU_Distanza::get_PinValue() {
  return mPinValue;
}

// Metodo effettuare la misurazione
void cSU_Distanza::read_pin() 
{
  if (mIsEnabled) 
  {
    mDistanza=mSonar.ping_cm();
  }
  
}   
//metodo per vedere se il sensore è abilitato 
bool cSU_Distanza::IsEnabled() 
{
    return mIsEnabled;
}
//metodo per impostare l'abilitazione del sensore
void cSU_Distanza::set_IsEnabled(bool enable) 
{
  mIsEnabled=enable;
}
//metodo per ottenere la distanza
uint16_t cSU_Distanza::misuraDistanza() 
{
    return mDistanza; // Restituisce la distanza in centimetri
}

//metodo per impostare un trigger
void cSU_Distanza::set_Trigger(uint16_t trigger) {
  mTrigger = trigger;
}
//metodo per ottenere il valore del trigger
uint16_t cSU_Distanza::get_Trigger() {
  return mTrigger;
}
