
#ifndef CMODBUSREGISTERS_H
#define CMODBUSREGISTERS_H

//librerie
#include <stdint.h>
#include <ModbusRTU.h> //testato su versione 4.1.0

class cModbusRegisters {
private:
  ModbusRTU mModB;  //oggetto libreria modbusRTU

public:
  //costruttore
  cModbusRegisters(uint8_t slaveID, uint8_t deRePin);

  void setupCoilR(uint16_t size);                       //inizializzazione Discrete Inputs solo lettura
  void setupCoilRW(uint16_t size);                      //inizializzazione coil lettura e scrittura
  void setupRegistroR(uint16_t size);                   //inizializzazione input registers solo lettura
  void setupRegistroRW(uint16_t size);                  //inizializzazione holding registers lettura e scrittura
  uint16_t getRegistroR(uint16_t index);                //ritorna contenuto input registers solo lettura dato indice
  void letRegistroR(uint16_t index, uint16_t valore);   //modifica contenuto input registers solo lettura
  uint16_t getRegistroRW(uint16_t index);               //ritorna contenuto holding registers lettura e scrittura dato indice
  void letRegistroRW(uint16_t index, uint16_t valore);  //modifica contenuto holding registers lettura e scrittura
  uint16_t getCoilR(uint16_t index);                    //ritorna contenuto Discrete Inputs solo lettura
  void letCoilR(uint16_t index, uint16_t valore);       //modifica contenuto Discrete Inputs solo lettura
  uint16_t getCoilRW(uint16_t index);                   //ritorna contenuto coil lettura e scrittura
  void letCoilRW(uint16_t index, uint16_t valore);      //modifica contenuto coil lettura e scrittura
  void task();                                          //gestisce ciclo di comunicazione Modbus RTU
};

#endif