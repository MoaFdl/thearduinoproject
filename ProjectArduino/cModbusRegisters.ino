#include "cModbusRegisters.h"

//costruttore
//Configura il pin DE/RE per comunicazione RS485 e inizializza il Modbus Slave
cModbusRegisters::cModbusRegisters(uint8_t slaveID, uint8_t deRePin) {
  pinMode(deRePin, OUTPUT);       //configura il pin DE/RE come uscita
  digitalWrite(deRePin, LOW);     //imposta in modalità ricezione
  mModB.begin(&Serial, deRePin);  //inizializza la comunicazione seriale Modbus
  mModB.slave(slaveID);           //imposta l'indirizzo Modbus del dispositivo(1-247)
}

//Inizializza una serie di registri di tipo Discrete Inputs (solo lettura)
void cModbusRegisters::setupCoilR(uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    mModB.addIsts(i);  //aggiunge registro Input Status (coils di sola lettura)
  }
}

//Inizializza una serie di registri di tipo Coil (lettura/scrittura)
void cModbusRegisters::setupCoilRW(uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    mModB.addCoil(i);  //aggiunge registro Coil (disponibile per R/W)
  }
}

//Inizializza una serie di registri di tipo Input Register (solo lettura)
void cModbusRegisters::setupRegistroR(uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    mModB.addIreg(i);  //aggiunge registro Input Register (solo lettura)
  }
}

//Inizializza una serie di registri di tipo Holding Register (lettura/scrittura)
void cModbusRegisters::setupRegistroRW(uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    mModB.addHreg(i);  //aggiunge registro Holding Register (disponibile per R/W)
  }
}

//Legge il valore di un Input Register
uint16_t cModbusRegisters::getRegistroR(uint16_t index) {
  return mModB.Ireg(index);
}

//Modifica il valore di un Input Register
void cModbusRegisters::letRegistroR(uint16_t index, uint16_t valore) {
  mModB.Ireg(index, valore);
}

//Legge il valore di un Holding Register
uint16_t cModbusRegisters::getRegistroRW(uint16_t index) {
  return mModB.Hreg(index);
}

//Modifica il valore di un Holding Register
void cModbusRegisters::letRegistroRW(uint16_t index, uint16_t valore) {
  mModB.Hreg(index, valore);
}

//Legge lo stato di un Discrete Inputs
uint16_t cModbusRegisters::getCoilR(uint16_t index) {
  return mModB.Ists(index);
}

//Modifica lo stato di un Discrete Inputs
void cModbusRegisters::letCoilR(uint16_t index, uint16_t valore) {
  mModB.Ists(index, valore);
}

//Legge lo stato di un Coil (lettura/scrittura)
uint16_t cModbusRegisters::getCoilRW(uint16_t index) {
  return mModB.Coil(index);
}

//Modifica lo stato di un Coil (lettura/scrittura)
void cModbusRegisters::letCoilRW(uint16_t index, uint16_t valore) {
  mModB.Coil(index, valore);
}

//Gestisce il ciclo di comunicazione Modbus RTU
//Deve essere chiamata periodicamente nel loop principale
void cModbusRegisters::task() {
  mModB.task();  //elabora le richieste Modbus ricevute
}