#include <Arduino.h>
#include <Treuil.h>

#define PINLOAD1 0 //TODO mettre les bonnes pines
#define PINHW1 0
#define PINBRAKE1 0

#define PINLOAD2 0
#define PINHW2 0
#define PINBRAKE2 0

#define PINLOAD3 0
#define PINHW3 0
#define PINBRAKE3 0

Treuil t1(PINLOAD1,PINHW1,PINBRAKE1);
Treuil t2(PINLOAD2,PINHW2,PINBRAKE2);
Treuil t3(PINLOAD3,PINHW3,PINBRAKE3);

void setup() {
    Serial.begin(115200);
}

void loop() {
    //TODO attendre un message du controleur principal


}

