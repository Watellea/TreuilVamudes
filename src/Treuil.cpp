#include "Treuil.h"
#define MAX_CUT_TIME 100
#define MAX_ESSAI_CUT 3

Treuil::Treuil(byte pinLoad, byte pinHotWire, byte pinBrake)
{
    this->pinLoad = pinLoad;
    this->pinHotWire = pinHotWire;
    this->pinBrake = pinBrake;
    this->status = 0;
    this->speedPayload = 0;

    pinMode(pinLoad, INPUT);
    pinMode(pinHotWire, OUTPUT);

    encodeur.begin();
    encodeur.resetPosition();
    encodeur.

    servo.attach(pinBrake);
}

void Treuil::descend(short hauteurDrone)
{
    this->hauteurDrone = hauteurDrone;
    this->hauteurPayload = hauteurDrone;

    status = 1;
    startTime = millis();
}

void Treuil::update()
{
    unsigned int deltaTime = millis() - startTime;
    int deltaDegree = encodeur.readAngle() - startDegree;



}

short Treuil::getPayloadHeight()
{
    return hauteurPayload;
}

bool Treuil::cutWire()
{
    byte i = 0;
    do
    {
        digitalWrite(pinHotWire, HIGH);
        delay(MAX_CUT_TIME);
        digitalWrite(pinHotWire, LOW);
        delay(MAX_CUT_TIME * 3);
        i++;
    } while (digitalRead(pinLoad) && i < MAX_ESSAI_CUT);
    return digitalRead(pinLoad);
}

bool Treuil::isPayload()
{
    return digitalRead(pinLoad);
}

byte Treuil::getStatus()
{
    return this->status;
}

bool Treuil::isCut()
{
    return (status == 2);
}