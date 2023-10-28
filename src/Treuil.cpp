#include "Treuil.h"

#define MAX_CUT_TIME 100
#define MAX_ESSAI_CUT 3
#define MAX_SPEED 10
#define DIAMETER 10
#define KD 0.5

Treuil::Treuil(byte pinLoad, byte pinHotWire, byte pinBrake)
{
    this->pinLoad = pinLoad;
    this->pinHotWire = pinHotWire;
    this->pinBrake = pinBrake;
    this->status = 0; // Le status 0 indique que le treuil n'a pas commencé à descendre
    this->speedPayload = 0;
    this->phase = 0;

    pinMode(pinLoad, INPUT);
    pinMode(pinHotWire, OUTPUT);

    encodeur.begin();   //!! Savoir quel encodeur est utilisé et l'adapter
    encodeur.resetPosition();

    servo.attach(pinBrake); //!! Savoir quel servo est utilisé et adapter
}

void Treuil::ajustBrakes(float vitesseActuelle){
    float vitesseTheo = getVitesseTheorique();
    // TODO PID pour ajuster les freins en fonction vitesseThéorique
}

void Treuil::descend(short hauteurDrone)
{
    this->hauteurDrone = hauteurDrone;
    this->hauteurPayload = hauteurDrone;

    status = 1;
    startTime = millis();
}

float Treuil::getVitesseTheorique(){
    switch (status)  //TODO Faire une fonction par partie en fonction de la phase de la charge
    {
    case 0:
        return 0;
    break;

    case 1:
        return 1;
    break;

    case 2:
        return -1;
    break;

    case 3:
        return MAX_SPEED;
    break;

    case 4:
        return ((-3 * (MAX_SPEED / hauteurDrone) * hauteurPayload) + (3 * MAX_SPEED));
    break;

    case 5:
        return 0;
    break;
    
    default:
        break;
    }
}

void Treuil::update()
{
    unsigned int deltaTime = millis() - startTime;
    int deltaDegree = 0;

    if(startDegree >= encodeur.readAngle()){ // Si l'angle a relooper à 0 degrés, calculer l'angle
        deltaDegree = startDegree - encodeur.readAngle();
    }else{
        deltaDegree = (startDegree + encodeur.getMaxAngle()) - encodeur.readAngle();
    }

    short distanceParcourue = (deltaDegree * DIAMETER) / 360; // Calcule une distance approximative parcourue par le payload en cm
    hauteurPayload -= distanceParcourue; // Soustrait cette distance à la hauteur

    speedPayload = (distanceParcourue / deltaDegree) * 10; // Calcul de la vitesse de la payload en m/s

    ajustBrakes(speedPayload);
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
        digitalWrite(pinHotWire, HIGH); // Active le Hotwire
        delay(MAX_CUT_TIME);
        digitalWrite(pinHotWire, LOW);  // Désactive le HotWire
        delay(MAX_CUT_TIME * 3); // Attend de voir si la charge tombe
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