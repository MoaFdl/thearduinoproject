#include "cRTC_timestamp.h"
// Costruttore: inizializza l'oggetto DS1302 con i pin forniti
cRTC_timestamp::cRTC_timestamp(uint8_t rst_pin, uint8_t dat_pin, uint8_t clk_pin)
  : mRTC(rst_pin, dat_pin, clk_pin)//inizializzazione oggetto classe  DS1302
 {}

// Metodo di inizializzazione
void cRTC_timestamp::setup() {
  // Disattiva la protezione in scrittura e arresta il clock halt
  mRTC.writeProtect(false);
  mRTC.halt(false);
  Time t = mRTC.time();
  mLastDay = t.date;  // Imposta il giorno corrente come riferimento iniziale
}


// Metodo per ottenere il giorno corrente
uint16_t cRTC_timestamp::getDay() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.date;
}

// Metodo per ottenere il mese corrente
uint16_t cRTC_timestamp::getMonth() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.mon;
}

// Metodo per ottenere l'anno corrente
uint16_t cRTC_timestamp::getYear() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.yr;
}

// Metodo per ottenere l'ora corrente
uint16_t cRTC_timestamp::getHour() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.hr;
}

// Metodo per ottenere i minuti correnti
uint16_t cRTC_timestamp::getMinutes() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.min;
}

// Metodo per ottenere i secondi correnti
uint16_t cRTC_timestamp::getSeconds() {
  Time t = mRTC.time();  // Aggiorna l'orario corrente
  return t.sec;
}


// metodo timestamp orario: 4 bit ore/6 bit minuti/6 bit secondi  formato: HHMMSS
uint16_t cRTC_timestamp::TimestampTempo() {
  Time t = mRTC.time();
  uint16_t results = 0;
  results = (uint16_t)(t.sec / 2);  //sono i primi 5 bit
  results += t.min << 5;            //facciamo uno shift di 5 posizioni e mettiamo i successivi 6 bit
  results += t.hr << 11;            //sono i successivi 11

  return results;
}
// metodo timestamp data: 7 bit anno/4 bit mese/5 bit giorno  formato: YYMMDD
uint16_t cRTC_timestamp::TimestampData() {
  Time t = mRTC.time();
  uint16_t results = 0;
  uint16_t anno = t.yr - 2000;
  results = t.date;
  results += t.mon << 5;
  results += anno << 9;

  return results;
}