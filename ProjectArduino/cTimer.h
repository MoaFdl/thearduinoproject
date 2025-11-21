#ifndef cTIMER_H
#define cTIMER_H


class cTimer {
private:
  unsigned long startTime;     // Tempo di inizio del timer
  unsigned long duration;      // Durata del timer
  bool isRunning;              // Stato del timer
  void (*callbackFunction)();  // Puntatore alla funzione di callback

public:
  // Costruttore di default
  cTimer();

  // Costruttore con durata specificata
  cTimer(unsigned long milliseconds);
  void start();                                  // Avvia il timer
  void stop();                                   // Ferma il timer
  void setDuration(unsigned long milliseconds);  // Imposta la durata del timer
  void setCallback(void (*callback)());          // Metodo per impostare la funzione di callback
  bool isExpired();                              // Verifica se il timer è scaduto
  unsigned long getRemainingTime();              // Restituisce il tempo rimanente
  bool running();                                // Verifica se il timer è in esecuzione

  //  void setAutoReset(bool autoResetFlag);  // Abilita/disabilita il riavvio automatico
};

#endif