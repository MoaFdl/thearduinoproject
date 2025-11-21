#include "cDigitalOutput.h"

// Costruttore
cDigitalOutput::cDigitalOutput(uint8_t pin) 
  : caOutput(pin) // Inizializza i membri della classe base (mPinOut(pin), mIsEnabled(false), mOutputState(false))
     {}  

// metodo per inizializzare il pin del sensore
void cDigitalOutput::setup() {
    pinMode(mPinOut, OUTPUT);
    digitalWrite(mPinOut, LOW);  
}

// metodo per attivare l'Output con una durata specifica
void cDigitalOutput::attiva_Output() {
  if(mIsEnabled){
    digitalWrite(mPinOut, HIGH);
    mOutputState = 1;
    }
}

// metodo per attivare l'Output con una durata specifica
void cDigitalOutput::disattiva_Output() {
    digitalWrite(mPinOut, LOW);
        mOutputState = 0;
}

//metodo per sapere lo stato dell'Output
uint16_t cDigitalOutput::get_OutputState(){
  return mOutputState;
}
//metodo per sapere lo stato del sensore
bool cDigitalOutput::IsEnabled()
{
    return mIsEnabled;
}
//metodo per impostare lo stato del sensore
void cDigitalOutput::set_IsEnabled(bool enable)
{
  mIsEnabled=enable;
}
//metodo per impostare lo stato dell'output         
void cDigitalOutput::set_Output(uint16_t value) 
{
  digitalWrite(mPinOut, value);
}

