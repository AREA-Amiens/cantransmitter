#include <FlexCAN.h>
#include <kinetis_flexcan.h>
/*
Base pour la transmission de trame sur le bus CAN, code fonctionnel pour Teensy 3.2
Pas besoin d'installer de librairie la librairie FlexCAN.h (collin80 fork sur GHUb) est dans Teensyduino.
Si questions, voir P.A (kingovchouffe sur github) ou mail au pierre.anthony.legeay@gmail.com
*/
int led = 13;
// Déclaration du message à envoyé (ESSENTIEL)
static CAN_message_t msg;

void setup() {
  // initialisation du bus CAN, le baudrate est en paramètre, pas besoin de mettre de filtre ici.
  // 500kbps ok suffisant pour les tests à voir en conditions réelles.(ESSENTIEL)
  Can0.begin(500000);
  pinMode(led, OUTPUT);
  // attente pour le paramètrage du bus peut etre un peu long et overkill
  delay(1000);
  Serial.println("CAN Transmitter Initialized");
}

void loop() {
  Serial.print("Sending: ");
  // id du message plus l'id est bas plus le message est prioritaire(ESSENTIEL)
  msg.id = 0x422;
  //taille du message en octet
  msg.len = 4;
  // le message est découpé en buffer de taille d'un octet, on ecrit le message dedans (8 buffer max car trame CAN 8 octets max)
  msg.buf[0] = 'c' ;
  msg.buf[1] = 'i' ;
  msg.buf[2] = 't' ;
  msg.buf[3] = 'e' ;
  // affichage des messages envoyés
  for(int i=0; i<msg.len; i++) {

    Serial.print(msg.buf[i]); Serial.print(" ");
  }
  Serial.println("");

// envoie des messages sur le bus A NE PAS OUBLIER!!
  Can0.write(msg);
  digitalWrite(led, !digitalRead(led));
  delay(500);
}
