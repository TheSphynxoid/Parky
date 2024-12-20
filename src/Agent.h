#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//

typedef struct {
    //8 caracteres + /n
    char CIN[9];
    char nom[20];
    char prenom[20];
    char email[60];
    unsigned int sexe;
    char date_naissance[11];
    char lieu_naissance[20];
    int num_banque;
    unsigned int etat_civil;
    int nombre_enfant;
}Agent;

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;

//A supprimer apres intergration.
typedef struct {
int ID_Parking;
char nom_parking[50];
char nom[50];
char prenom[50];
int numero;
int CIN;
int immatricule;
int arr_jour;
int arr_mois;
int arr_annee;
int arr_heure;
int dep_jour;
int dep_mois;
int dep_annee;
int dep_heure;
float prix;
} Reservation;


int AjouterAgent(char* filename, Agent agent);
int ModifierAgent(char* filename, char* id, Agent agent);
int SupprimerAgent(char* filename, char* id);
void AfficherAgents(char* filename);
int ChercherAgent(char* filename, char* id, Agent* );
void ListeReservation(char * filename, int id_parking, Date date);

// typedef struct AgentReader AgentReader;

// void initReader(AgentReader* r, char* filepath);
// Agent ReadNext(AgentReader* r);
// Agent PeekNext(AgentReader* r);
// int GetCurrentLine(AgentReader r);
// FILE* GetFile(AgentReader r);
// void Foreach(AgentReader* r,void(*Predicate)(Agent));

#endif // AGENT_H_INCLUDED
