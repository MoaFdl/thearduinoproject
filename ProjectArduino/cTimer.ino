#include "cTimer.h"

// Costruttore di default
cTimer::cTimer() 
: startTime(0),
  duration(0), 
  isRunning(false), 
  callbackFunction(nullptr) {}

// Costruttore con durata specificata
cTimer::cTimer(unsigned long milliseconds)
    : startTime(0), duration(milliseconds), isRunning(false), callbackFunction(nullptr) {}

// Avvia il cTimer
void cTimer::start() {
    startTime = millis();
    isRunning = true;
}

// Ferma il cTimer
void cTimer::stop() {
    isRunning = false;
}

// Imposta la durata del cTimer
void cTimer::setDuration(unsigned long milliseconds) {
    duration = milliseconds;
}

// Metodo per impostare la funzione di callback
void cTimer::setCallback(void (*callback)()) {
    callbackFunction = callback; // Salva il puntatore alla funzione di callback
}

/*// Abilita/disabilita il riavvio automatico
void cTimer::setAutoReset(bool autoResetFlag) {
    autoReset = autoResetFlag;
}*/

// Verifica se il cTimer è scaduto
bool cTimer::isExpired() {
    if (!isRunning) return false;

    unsigned long currentTime = millis();

    // Gestisce l'overflow di millis()
    if (currentTime < startTime) {
        startTime = currentTime;
        return false;
    }

    // Controlla se il tempo è scaduto
    if (currentTime - startTime >= duration) {
        
            if (callbackFunction) {
            callbackFunction(); // Esegui immediatamente la callback 
            // Ferma il cTimer se non è in auto-reset
            isRunning = false;
        }
        return true;
    }

    return false;
}

// Restituisce il tempo rimanente
unsigned long cTimer::getRemainingTime() {
    if (!isRunning) return 0;

    unsigned long currentTime = millis();

    // Gestisce l'overflow di millis()
    if (currentTime < startTime) {
        startTime = currentTime;
        return duration;
    }

    unsigned long elapsedTime = currentTime - startTime;

    // Se il tempo è scaduto, restituisce 0
    return (elapsedTime >= duration) ? 0 : (duration - elapsedTime);
}

// Verifica se il cTimer è in esecuzione
bool cTimer::running() {
    return isRunning;
}