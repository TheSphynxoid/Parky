#include "Client.h"
#include "Agent.h"
#include <string.h>

int AjouterCompte(char* ficher, Compte c){
    FILE* f = fopen(ficher, "a");
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return 0;
    }
    fprintf(f, "%d %s %s %d %d %s %d %d %s %s\n", c.id, c.nom, c.prenom, c.cin, c.sexe, c.email, c.tel, c.notif, c.mdp, c.ville);
    fclose(f);
    return 1;
}
int ModiferCompte(char* ficher, Compte nouv){
    FILE* f = fopen(ficher, "r");
    FILE* temp = fopen("temp.txt", "w");
    Compte c;
    int modif = 0;
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return -1;
    }
    while(fscanf(f, "%d %s %s %d %d %s %d %d %s %s\n", &c.id, c.nom, c.prenom, &c.cin, &c.sexe, c.email, &c.tel, &c.notif, c.mdp, c.ville) != EOF){
        if(c.id == nouv.id){
            fprintf(temp, "%d %s %s %d %d %s %d %d %s %s\n", nouv.id, nouv.nom, nouv.prenom, nouv.cin, nouv.sexe, nouv.email, nouv.tel, nouv.notif, nouv.mdp,nouv.ville);
            modif = 1;
        }
        else{
            fprintf(temp, "%d %s %s %d %d %s %d %d %s %s\n", c.id, c.nom, c.prenom, c.cin, c.sexe, c.email, c.tel, c.notif, c.mdp, c.ville);
        }
    }
    fclose(f);
    fclose(temp);
    remove(ficher);
    rename("temp.txt", ficher);
    return modif;
}
int SupprimerCompte(char *ficher, int id)
{
    FILE* f = fopen(ficher, "r");
    FILE* temp = fopen("temp.txt", "w");
    Compte c;
    int supprimer = 0;
    if(f == NULL){
        printf("Erreur d'overture de fichier");
        return -1;
    }
    while(fscanf(f, "%d %s %s %d %d %s %d %d %s %s\n", &c.id, c.nom, c.prenom, &c.cin, &c.sexe, c.email, &c.tel, &c.notif, c.mdp, c.ville) != EOF){
        if(c.id != id){
            fprintf(temp, "%d %s %s %d %d %s %d %d %s %s\n", c.id, c.nom, c.prenom, c.cin, c.sexe, c.email, c.tel, c.notif, c.mdp, c.ville);
            supprimer = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove(ficher);
    rename("temp.txt", ficher);
    return supprimer;
}
Compte ChercherCompte(char *ficher, int id)
{
    FILE* f = fopen(ficher, "r");
    Compte c;
    while(fscanf(f, "%d %s %s %d %d %s %d %d %s %s\n", &c.id, c.nom, c.prenom, &c.cin, &c.sexe, c.email, &c.tel, &c.notif, c.mdp, c.ville) != EOF){
        if(c.id == id){
            return c;
        }
    }
    c.id = -1;
    return c;
}
float FactureMensuelle(char* fichier, int mois, int annee, int cin){
	float total=0;
	FILE* file = fopen(fichier, "r");
Reservation reservation;
    while(fscanf(file, "%d %s %s %s %d %d %d %d/%d/%d/%d %d/%d/%d/%d %f\n",
            &reservation.ID_Parking, reservation.nom_parking, reservation.nom, reservation.prenom, &reservation.numero,
            &reservation.CIN, &reservation.immatricule, &reservation.arr_jour, &reservation.arr_mois, &reservation.arr_annee,  &reservation.arr_heure,
            &reservation.dep_jour, &reservation.dep_mois, &reservation.dep_annee,  &reservation.dep_heure, &reservation.prix) != EOF){

		if(reservation.CIN == cin){
	    total+=reservation.prix;
		}
	}

   return total; 
}
