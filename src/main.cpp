#include <Arduino.h>
#include <Treuil.h>

#define PINLOAD1 0 //TODO mettre les bonnes pines pour les treuils
#define PINHW1 0
#define IDBRAKE1 0

#define PINLOAD2 0
#define PINHW2 0
#define IDBRAKE2 0

#define PINLOAD3 0
#define PINHW3 0
#define IDBRAKE3 0

Treuil t1(PINLOAD1,PINHW1,IDBRAKE1);
Treuil t2(PINLOAD2,PINHW2,IDBRAKE2);
Treuil t3(PINLOAD3,PINHW3,IDBRAKE3);

#define LSS_BAUD	(LSS_DefaultBaud)
#define LSS_SERIAL	(Serial)	// ex: Many Arduino boards

void setup() {
    Serial.begin(115200);
    LSS::initBus(LSS_SERIAL,LSS_BAUD);
}

void loop() {
    //TODO attendre un message du controleur principal et drop quand c'est demand
    //TODO interpréter le message du controleur


}

