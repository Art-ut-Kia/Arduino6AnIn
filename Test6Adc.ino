/******************************************************************************
 * Test6Adc.ino : acquière cycliquement (1kHz) les 6 entrées analogiques et   *
 *                transmet une trame de 14 octets (12 octets transcodés COBS) *
 * - temps d'acuisition : 100µs/channel, 6 voies mesurées à 0.672ms           *
 * - temps de transmission : 140 bits à 230400 bps = 0.61 ms                  *
 * - période de trame : 1ms (la transmission de la trame précédente se        *
 *   termine pendant l'acquisition suivante).                                 *
 ******************************************************************************/

extern "C" {
# include "cobs.h"
}

unsigned long prvtime;

void setup() {
   Serial.begin(230400);
   prvtime = micros();
}

void loop() {
   int ain[7];
   for (int i = 0; i<6; i++) ain[i] = analogRead(i);
   ain[6] = 0;
   char txbf[14];
   cobs_cod((char*)(&ain), 12, txbf);
   Serial.write(txbf, 14);
   unsigned long nt = prvtime + 1000;
   while (micros() < nt); 
   prvtime = nt;
}
