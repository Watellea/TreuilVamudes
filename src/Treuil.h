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
        byte phase;

        unsigned long startTime = 0;
        int startDegree = 0;

        float getVitesseTheorique();

    public:
        /**
         * @brief Constructeur par defaut, prend les pines utilisés par le treuil et les inities.
        */
        Treuil(byte pinLoad, byte pinHotWire, byte pinBrake);

        /**
         * @brief Ordonne le début de la descente de la payload
         * @param hauteurDrone La hauteur actuelle du drone par-rapport au sol en cm
        */
        void descend(short hauteurDrone);

        /**
         * @brief update la position de la payload et sa vitesse lors de la descente. Cette fonction doit être appelé régulièrement
        */
        void update();

        /**
         * @return La hauteur de la payload par rapport au sol
        */
        short getPayloadHeight();

        /**
         * @brief Coupe le fil de la payload avec le Hotwire. Fait un nombre d'essai fixée par MAX_ESSAI_CUT et active le hot wire pendant MAX_CUT_TIME ms
         * @return true si la charge à bien été largué, false si on detecte encore la charge
        */
        bool cutWire();

        /**
         * @return Le status du treuil : 0 si il n'est pas enclanché , 1 si il est en train de descendre et 2 si la payload est lachée
        */
        byte getStatus();

        /**
         * @return Si le fil à été coupé
        */
        bool isCut();

        /**
         * @return Si le payload est encore présent dans le treuil
        */
        bool isPayload();
};

#endif