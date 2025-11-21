#ifndef C_SD_H
#define C_SD_H

//librerie
#include <stdint.h>
#include <SdFat.h> //testato su versione 2.3.0

class cSD {
private:
  uint8_t mPinIn;         //pin di collegamento
  const char* mFileName;  //nome del file(Utilizzare nomi di file brevi e senza caratteri speciali per garantire compatibilità)
  SdFat mSD;              //oggetto libreria SdFat

public:
  // Costruttore
  cSD(uint8_t pin, const char* filename);

  void setup();                                                                          // Inizializza il modulo SD
  void read_dato(uint8_t riga, uint8_t colonna, char* buffer, size_t dimensioneBuffer);  // Legge una cella specifica da un file CSV
  void write_dati(uint16_t array1[], uint16_t array2[], uint8_t dimensioneArray);        // Scrive array di dati nel file CSV
};

#endif