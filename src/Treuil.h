#ifndef TREUIL_H
#define TREUIL_H
#include <Arduino.h>
#include <AS5600.h>
#include <Servo.h>

class Treuil{
    private:
        AS5600 encodeur;
        Servo servo;

        const float diametreBobine = 2;

        byte pinLoad;
        byte pinHotWire;
        byte pinBrake;

        short hauteurDrone;
        short hauteurPayload;
        short speedPayload;

        byte status;

        unsigned long startTime = 0;
        int startDegree = 0;

    public:
        Treuil(byte pinLoad, byte pinHotWire, byte pinBrake);
        void descend(short hauteurDrone);
        void update();
        short getPayloadHeight();
        bool cutWire();
        byte getStatus();
        bool isCut();
        bool isPayload();
};

#endif