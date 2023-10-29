#include "Treuil.h"

#define MAX_CUT_TIME 100
#define MAX_ESSAI_CUT 3

#define MAX_SPEED 10

#define DIAMETER 10

#define KD 0.2



Treuil::Treuil(byte pinLoad, byte pinHotWire, byte idBrake)
{
    this->pinLoad = pinLoad;
    this->pinHotWire = pinHotWire;
    this->idBrake = idBrake;
    this->status = 0; // Le status 0 indique que le treuil n'a pas commencé à descendre
    this->speedPayload = 0;
    this->phase = 0;

    pinMode(pinLoad, INPUT);
    pinMode(pinHotWire, OUTPUT);

    encodeur.begin();   //!! Savoir quel encodeur est utilisé et l'adapter
    encodeur.resetPosition();

    servo = LSS(idBrake);

    servo.move(0);
}

void Treuil::ajustBrakes(float vitesseActuelle){
    float vitesseTheo = getVitesseTheorique();
    float erreur = vitesseTheo - vitesseActuelle;

    servo.move(servo.getPosition() + erreur * KD); //!! Ajuster le KD en fonction du frein
}

long Treuil::getDeltaAngle(){
    if(startDegree >= encodeur.readAngle()){ // Si l'angle a relooper à 0 degrés, calculer l'angle
        return ( startDegree - encodeur.readAngle()); //!! Adapter en fonction de l'encodeur
    }else{
       return ( (startDegree + encodeur.getMaxAngle()) - encodeur.readAngle());
    }
}

void Treuil::descend(short hauteurDrone)
{
    this->hauteurDrone = hauteurDrone;
    this->hauteurPayload = hauteurDrone;

    status = 1;
    startTime = millis();

}

float Treuil::getVitesseTheorique(){
    //TODO actualiser la phase en fonction hauteur de payload / hauteur drone
    switch (phase)  //TODO Faire une fonction par partie en fonction de la phase de la charge
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
    int deltaDegree = getDeltaAngle();

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