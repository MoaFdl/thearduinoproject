#include "cSD.h"

// Costruttore
cSD::cSD(uint8_t pin, const char* filename)
  : mPinIn(pin),
    mFileName(filename) {}  //nome del file CSV da utilizzare sul modulo SD

// Inizializza il modulo SD
void cSD::setup() {
  pinMode(mPinIn, OUTPUT);
  if (!mSD.begin(mPinIn)) {  // Inizializza il modulo SD con il pin specificato,se ha successo restituisce true
    // Serial.println("Inizializzazione SD fallita!");
    return;
  }
  // Serial.println("SD inizializzata con successo.");
}

// Legge una cella specifica da un file CSV
void cSD::read_dato(uint8_t riga, uint8_t colonna, char* buffer, size_t dimensioneBuffer) {
  File file = mSD.open(mFileName, O_READ);  // Apre il file in lettura
  if (!file) {
    buffer[0] = '\0';  // Buffer vuoto in caso di errore
    return;
  }

  char linea[128];  // Buffer per leggere una riga
  uint8_t rigaCorrente = 0;

  while (file.fgets(linea, sizeof(linea))) {  // Legge il file riga per riga
    if (rigaCorrente == riga) {               // Controlla se è la riga giusta
      char* token;
      char* context;
      char* ptr = linea;
      uint8_t colonnaCorrente = 0;

      while ((token = strtok_r(ptr, ";", &context))) {  // Divide la riga in colonne usando il punto e virgola come separatore
        if (colonnaCorrente == colonna) {               //Se trova la colonna richiesta, copia il dato nel buffer
          strncpy(buffer, token, dimensioneBuffer - 1);
          buffer[dimensioneBuffer - 1] = '\0';  // Terminatore stringa
          file.close();
          return;
        }
        colonnaCorrente++;
        ptr = NULL;
      }
      break;
    }
    rigaCorrente++;
  }

  buffer[0] = '\0';  // Valore predefinito se non trovato
  file.close();
}

// Scrive due array nel file CSV
void cSD::write_dati(uint16_t array1[], uint16_t array2[], uint8_t dimensioneArray) {
  if (mSD.exists(mFileName)) {  // Elimina il file esistente se esiste già
    mSD.remove(mFileName);
  }

  File file = mSD.open(mFileName, O_WRITE | O_CREAT);  // Crea un nuovo file in modalità scrittura
  if (!file) return;
  char riga[30];                                              // Buffer per formattare la riga
  snprintf(riga, sizeof(riga), "%d;%d", 10, 0);  //mantiene il numero di righe nel file
  file.println(riga);
  for (uint8_t i = 0; i < dimensioneArray; i++) {  // Scrive ogni coppia di valori nel file come riga CSV

    snprintf(riga, sizeof(riga), "%d;%d", array1[i], array2[i]);  // Formatta i dati come "valore1;valore2"
    file.println(riga);
  }

  file.close();
}