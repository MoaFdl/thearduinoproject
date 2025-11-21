#ifndef CRTC_TIMESTAMP_H
#define CRTC_TIMESTAMP_H

//librerie
#include <stdint.h> 
#include <DS1302.h> //testato con l'unica versione presente su github

class cRTC_timestamp {

private:
  DS1302 mRTC;                 // Oggetto della classe DS1302
  uint16_t mLastDay;           // Ultimo giorno registrato

public:
  // Costruttore
  cRTC_timestamp(uint8_t rst_pin, uint8_t dat_pin, uint8_t clk_pin);

  void setup();                          //inizializzazione sensore
  uint16_t getDay();                     //ritorna il giorno
  uint16_t getMonth();                   //ritorna il mese
  uint16_t getYear();                    //ritorna l'anno
  uint16_t getHour();                    //ritorna l'ora
  uint16_t getMinutes();                 //ritorna i minuti
  uint16_t getSeconds();                 //ritorna i secondi
  uint16_t TimestampTempo();             // timestamp orario: 4 bit ore/6 bit minuti/6 bit secondi  formato: HHMMSS
  uint16_t TimestampData();              // timestamp data: 7 bit anno/4 bit mese/5 bit giorno  formato: YYMMDD
};

#endif