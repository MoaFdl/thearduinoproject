//sketch testato su Arduino Uno R3
//IDE usato: Arduino IDE 2.3.4

//main class project

//librerie
#include <stdint.h>
//#include <MemoryFree.h>  //per capire ram disponibile su arduino

//implementazione classi
#include "cAnalogInput.h"      //classe Input Analogico
#include "cAnalogOutput.h"     //classe Output Analogico
#include "cDigitalInput.h"     //classe per input digitale(in questo caso il sensore di contatto magnetico)
#include "cDigitalOutput.h"    //classe Output Digitale(in questo caso l'Allarme_CM)
#include "cTimer.h"            //classe timer
#include "cSV_Vento.h"         //classe per sensore velocità vento
#include "cSU_Distanza.h"      //classe per sensore distanza
#include "enum_PinStates.h"    //enum per gestione stati classe input digitale
#include "cRTC_timestamp.h"    //classe  modulo rtc
#include "cSD.h"               //classe modulo sd
#include "cModbusRegisters.h"  //classe gestione modbus

//definizione costanti

//indici array
#define N_CelleModBusRW 10  //indice per l'array di registri modbus di  lettura e scrittura
#define N_CelleModBusR 20   //indice per l'array di registri modbus di sola lettura

//contatto magnetico
#define DigitalOutput_PIN A1  //pin uscita Output(Allarme_CM)
#define DigitalInput_PIN 9    //pin interruttore input(contatto magnetico)

/*
#define Pin_AnalogOutput 9 //pin led Output
#define Pin_AnalogInput A0
*/

//anemometro velocità vento
#define ANEMOMETRO_PIN A0  //pin sensore velocità vento

//sensore di distanza
#define SDU_ECHO_TRIGGER_PIN 4        // Pin Echo del sensore
#define SDU_MAX_DISTANCE 150  // Distanza massima da misurare (in cm)


//modulo Real Time Clock
#define RTC_RST_PIN 7  // Chip Enable
#define RTC_DAT_PIN 6  // Input/Output
#define RTC_CLK_PIN 5  // Serial Clock

//modulo SD
#define SD_PIN 10                          //pin CS SD
#define SD_FILE_NAME "Config.csv"  //nome file configurazione

//modulo RS485
#define SLAVE_ID 1   //id dello slave
#define DE_RE_PIN 8  //pin di transceiver


// Creazione degli oggetti

cModbusRegisters modbus(SLAVE_ID, DE_RE_PIN);                            //oggetto classe cModbusRegisters(NB:comunicazione seriale e comunicazione modbus non possono essere simultanee)
cDigitalInput ContattoMagnetico(DigitalInput_PIN);                       //oggetto classe cDigitalInput
cDigitalOutput Allarme_CM(DigitalOutput_PIN);                            //oggetto classe cDigitalOutput
cTimer timerSensore[N_CelleModBusRW];                                    //array oggetti classe cTimer
cSU_Distanza Distanza(SDU_ECHO_TRIGGER_PIN, SDU_MAX_DISTANCE);           //oggetto classe cSU_Distanza
cSV_Vento vento(ANEMOMETRO_PIN);                                         //oggetto classe cSV_Vento
cRTC_timestamp rtc(RTC_RST_PIN, RTC_DAT_PIN, RTC_CLK_PIN);               //oggetto classe cRTC_timestamp
cSD sd(SD_PIN, SD_FILE_NAME);                                            //oggetto classe cSD
/*
cAnalogInput testInputAnalog(Pin_AnalogInput);  // Input analogico sul pin A0
cAnalogOutput testOutputAnalog(Pin_AnalogOutput);     // Output PWM sul pin 9
*/


//dichiarazione variabili globali
//array per la gestione dei registri modbus
uint16_t iRegisterRW[N_CelleModBusRW] = { 0 };
uint16_t iCoilRW[N_CelleModBusRW] = { 0 };
uint16_t iRegisterR[N_CelleModBusR] = { 0 };
uint16_t iCoilR[N_CelleModBusR] = { 0 };

int tempo = 0;


void setup() {
  // Setup dei componenti
  Serial.begin(9600);         //setup seriale
  sd.setup();                 // Inizializza il modulo SD
  ContattoMagnetico.setup();  // Inizializza l'input(in questo caso il sensore di contatto magnetico)
  Allarme_CM.setup();         //inizializzazione Output(in questo caso l'Allarme_CM)
  vento.setup();              //inizializzazione sensore velocità del vento
  rtc.setup();                //inizializzazione modulo RTC

  // Buffer per leggere dati dal file
  char buffer[20];

  // Leggi dati dal file CSV
  for (uint16_t i = 0; i < N_CelleModBusRW; i++) {
    sd.read_dato(i+1, 0, buffer, sizeof(buffer));
    iRegisterRW[i] = atoi(buffer);  // Converte la stringa in intero

    sd.read_dato(i+1, 1, buffer, sizeof(buffer));
    iCoilRW[i] = atoi(buffer);
  }

  //inizializzazione modbus
  modbus.setupCoilR(N_CelleModBusR);        // inizializzazione Discrete Inputs
  modbus.setupCoilRW(N_CelleModBusRW);      // inizializzazione Coils
  modbus.setupRegistroR(N_CelleModBusR);    // inizializzazione Input Registers
  modbus.setupRegistroRW(N_CelleModBusRW);  // inizializzazione Holding Registers

  // assegnazione valore ai registri
  for (uint16_t i = 0; i < N_CelleModBusRW; i++) {
    modbus.letRegistroRW(i, iRegisterRW[i]);
    modbus.letCoilRW(i, iCoilRW[i]);                // tutti i pin sono abilitati di default
  }

  /*
 testInputAnalog.setup();
  testOutputAnalog.setup();
  */

  /*
  //debug per vedere se i dati inseritio sono giusti
  for (uint16_t i = 0; i < N_CelleModBusRW; i++) {
      Serial.print(iRegisterRW[i]);
      Serial.print("\t");
      Serial.println(iCoilRW[i]);
    
  } 
 */
  //settaggio timer
  for (uint16_t i = 0; i < N_CelleModBusRW; i++) {  // imposto il tempo del timer e poi lo avvio
    tempo = iRegisterRW[i] * 100;                   //unità di misura: decimi di secondo
    timerSensore[i].setDuration(tempo);
    if (i != 3) {                                  //escludiamo questo dall'essere avviato perchè è il timer dell'Allarme_CM
      timerSensore[i].start();
    }
  }

  ContattoMagnetico.set_pinNormalState(iCoilRW[0]);  //imposta lo stato normale come NC

  //callback timers
  timerSensore[0].setCallback(wrap_ContattoMagnetico);  //gestisce il contatto magnetico
  timerSensore[1].setCallback(wrap_VVento);             //gestisce l'anemometro
  timerSensore[2].setCallback(wrap_SU_Distanza);        //gestisce il sensore di distanza
  timerSensore[3].setCallback(wrap_Allarme_CM);         //gestisce l'output dell'Allarme_CM
  timerSensore[4].setCallback(wrap_modificaFile);
  //timerSensore[5].setCallback(wrap_stampaTutto);    //debug per vedere se i dati vengono inseriti correttamente
}

void loop() {

  //aggiorno il valore degli array quando è diverso rispetto al valore dei registri modbus
  for (uint16_t i = 0; i < N_CelleModBusRW; i++) {
    if (iRegisterRW[i] != modbus.getRegistroRW(i)) {
      iRegisterRW[i] = modbus.getRegistroRW(i);
      tempo = iRegisterRW[i] * 100;
      timerSensore[i].setDuration(tempo);  //aggiornamento durata timers
    }
    if (iCoilRW[i] != modbus.getCoilRW(i)) {
      iCoilRW[i] = modbus.getCoilRW(i);
    }
  }

  //aggiorno lo stato abilitato/disabilitato nei sensori
  ContattoMagnetico.set_IsEnabled(iCoilRW[1]);
  Allarme_CM.set_IsEnabled(iCoilRW[2]);
  vento.set_IsEnabled(iCoilRW[3]);
  Distanza.set_IsEnabled(iCoilRW[4]);

  //aggiorno lo stato normale
  ContattoMagnetico.set_pinNormalState(iCoilRW[0]);

  //imposto il valore dei registri sola lettura modbus
  for (uint16_t i = 0; i < N_CelleModBusR; i++) {
    modbus.letRegistroR(i, iRegisterR[i]);
    modbus.letCoilR(i, iCoilR[i]);
  }

  modbus.task();  //aggiorna modbus

  //timers al loro scadere viene effettuata una callback
  if (timerSensore[0].isExpired()) {  //timer per il ContattoMagnetico
    timerSensore[0].start();
  }

  if (timerSensore[1].isExpired()) {  //timer per anemometro velocità vento
    timerSensore[1].start();
  }

  if (timerSensore[2].isExpired()) {  //timer per sensore ultrasuoni distanza
    timerSensore[2].start();
  }

  if (timerSensore[3].running()) {  //timer disattivazione allarme
    if (timerSensore[3].isExpired()) {
    }
  }

  if (timerSensore[4].isExpired()) {  //timer aggiornamento file configurazione
    timerSensore[4].start();
  }

  /* 
     testInputAnalog.read_pin();  // Aggiorna lo stato del testInputAnalog
    testOutputAnalog.set_Output((testInputAnalog.get_PinValue())/4);// Scala il valore da 0-1023 a 0-255  (stato dell'output PWM)
  */

  // iRegisterR[19] =freeMemory(); //per capire ram disponibile su arduino
}

//metodi per la gestione delle azioni da compiere allo scadere del timer

//timer 0
void wrap_ContattoMagnetico() {  //controlla lo stato del sensore di contatto magnetico
  ContattoMagnetico.read_pin();  //controlliamo il valore del sensore
  iCoilR[0] = ContattoMagnetico.get_PinState();
  iCoilR[1] = Allarme_CM.get_OutputState();
  if (iCoilR[0] == static_cast<uint8_t>(PinState::ALARM)) {  //se il sensore è in stato di Allarme
    if (ContattoMagnetico.PinHasChanged()) {                 //se il sensore ha cambiato stato
      Allarme_CM.attiva_Output();                            //attiviamo l'Allarme_CM,il suo timer e creiamo un timestamp dell'evento
      iRegisterR[2] = rtc.TimestampData();                   //mettiamo i timestamp
      iRegisterR[3] = rtc.TimestampTempo();
      timerSensore[3].start();                               //avviamo il timer per lo spegnimento dell'allarme
    }
  }
}
//timer 1
void wrap_VVento() {                        //misura la velocità del vento
  vento.read_pin();                         //legge il valore del pin
  iRegisterR[0] = vento.calcolaVelocita();  //restituisce la velocità del vento
}
//timer 2
void wrap_SU_Distanza() {                     //misura la distanza
  Distanza.read_pin();                        //legge il valore del pin
  iRegisterR[1] = Distanza.misuraDistanza();  //restituisce la distanza dall'acqua
}
//timer 3
void wrap_Allarme_CM() {  //disattiva l'Allarme e crea un timestamp dell'evento
  Allarme_CM.disattiva_Output();
  iRegisterR[4] = rtc.TimestampData();
  iRegisterR[5] = rtc.TimestampTempo();
}
//timer 4
void wrap_modificaFile() {  //periodicamente aggiorna i parametri all'interno del file di nome FILE_NAME
  sd.write_dati(iRegisterRW, iCoilRW, N_CelleModBusRW);
}

/*

//timer 5
void wrap_stampaTutto() {
  Serial.println("contenuto array: ");
  for (int i = 0; i < 10; i++) {
    Serial.print(iRegisterR[i]);
    Serial.print("\t");
    Serial.println(iCoilR[i]);
  }
}

*/
