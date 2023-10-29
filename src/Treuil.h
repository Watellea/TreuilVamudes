#ifndef TREUIL_H
#define TREUIL_H
#include <Arduino.h>
#include <AS5600.h>
#include <LSS.h>



class Treuil{
    private:
        AS5600 encodeur;
        LSS servo;

        const float diametreBobine = 2;

        byte pinLoad;
        byte pinHotWire;
        byte idBrake;

        short hauteurDrone; // Hauteur du drone en m
        short hauteurPayload; // Hauteur actuelle de la payload (s'actualise) en m
        short speedPayload; // Vitesse payload en m/s

        byte status;
        byte phase;

        unsigned long startTime = 0;
        int startDegree = 0;

        /**
         * @brief Retourne la fonction de la vitesse du payload en fonction de son altitude 
         * @return La vitesse theorique en m/s
        */
        float getVitesseTheorique();

        /**
         * @brief Gere tout le PID des freins (servo) afin de match la vitesse theorique donnée
        */
        void ajustBrakes(float vitesseActuelle);

        /**
         * @brief calcule l'angle parcourue par la bobine (l'encodeur) depuis le dernier appel
         * @return L'angle total parcourue en valeur absolue en degrés
        */
        long getDeltaAngle();

    public:
        /**
         * @brief Constructeur par defaut, prend les pines utilisés par le treuil et les inities.
        */
        Treuil(byte pinLoad, byte pinHotWire, byte idBrake);

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
         * @return Le status du treuil : 0 si il n'est pas enclanché ,1 si il descend  et 2 si le payload a été lâché
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