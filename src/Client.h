#ifdef RB_Client
#else
#define RB_Client
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char nom[30];
    char prenom[30];
    int cin;
    int sexe;
    int tel;
    char email[50];
    int notif;
    char mdp[50];
    char ville[30];
}Compte;

int AjouterCompte(char* ficher, Compte c);
int ModiferCompte(char* ficher, Compte c);
int SupprimerCompte(char* ficher, int id);
Compte ChercherCompte(char* ficher, int id);
float FactureMensuelle(char* fichier, int mois, int annee,int cin);

#endif
