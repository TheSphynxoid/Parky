#include "Client.h"
#include <string.h>

int AjouterCompte(char* ficher, Compte c){
    FILE* f = fopen(ficher, "w");
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return 0;
    }
    fprintf(f, "%d %s %s %d %d %s %d %s %d", c.id, c.nom, c.prenom, c.sexe, c.email, c.notif, c.mdp);
    fclose(f);
    return 1;
}
int ModiferCompte(char* ficher, Compte nouv){
    FILE* f = fopen(ficher, "r");
    FILE* temp = fopen(".temp.txt", "w");
    Compte c;
    int modif = 0;
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return -1;
    }
    while(fscanf(f, "%d %s %s %d %d %s %d %s %d", &c.id, c.nom, c.prenom, &c.sexe, c.email, &c.notif, c.mdp) != EOF){
        if(c.id == nouv.id){
            fprintf(f, "%d %s %s %d %d %s %d %s %d", nouv.id, nouv.nom, nouv.prenom, nouv.sexe, nouv.email, nouv.notif, nouv.mdp);
            modif = 1;
        }
        else{
            fprintf(f, "%d %s %s %d %d %s %d %s %d", c.id, c.nom, c.prenom, c.sexe, c.email, c.notif, c.mdp);
        }
    }
    fclose(f);
    fclose(temp);
    remove(ficher);
    rename(".temp.txt", ficher);
    return modif;
}
int SupprimerCompte(char *ficher, int id)
{
        FILE* f = fopen(ficher, "r");
    FILE* temp = fopen(".temp.txt", "w");
    Compte c;
    int supprimer = 0;
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return -1;
    }
    while(fscanf(f, "%d %s %s %d %d %s %d %s %d", &c.id, c.nom, c.prenom, &c.sexe, c.email, &c.notif, c.mdp) != EOF){
        if(c.id != id){
            fprintf(f, "%d %s %s %d %d %s %d %s %d", c.id, c.nom, c.prenom, c.sexe, c.email, c.notif, c.mdp);
            supprimer = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove(ficher);
    rename(".temp.txt", ficher);
    return supprimer;
}
Compte ChercherCompte(char *ficher, int id)
{
    FILE* f = fopen(ficher, "r");
    Compte c;
    while(fscanf(f, "%d %s %s %d %d %s %d %s %d", &c.id, c.nom, c.prenom, &c.sexe, c.email, &c.notif, c.mdp) != EOF){
        if(c.id == id){
            return c;
        }
    }
    c.id = -1;
    return c;
}
float FactureMensuelle(char* fichier, int mois, int annee){
    
}
