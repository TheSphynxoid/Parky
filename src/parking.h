#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

#include <stdio.h>


/*typedef struct
{
    int id_parking;
    int capacite;
    int type;
    int nb_place;
    int horaire;
    float tarif;
    char nom_parking[20];
    char adresse[30];
    char cin_agent[9];
    int service_off;
    float moyenne;

} PARKING;*/
typedef struct {
    int id_parking;
    char nom_parking[50];
    char adresse[100];
    int capacite;
    int type;  // 0: Type A, 1: Type B, etc.
    float tarif;
    int nb_place;
    int horaire;
    char cin_agent[9]; // CIN de l'agent affecté
    int service_off; // Codé en bits pour les services
    float moyenne;
    int statut;

} PARKING;


int ajouter(char *, PARKING); 
int modifier(char *, int, PARKING); 
int supprimer(char *, int);
void afficher(char *);
PARKING chercher(char *, int);
void affecter(char*, int id_parking ,char* cin_agent);

#endif 

