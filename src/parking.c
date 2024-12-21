#include "parking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "Agent.h"



int id_existe(char *filename, int id) {
    PARKING p;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %d %d %d %d %f %s %d %f %d\n",
                      &p.id_parking, p.nom_parking, p.adresse, &p.capacite,
                      &p.type, &p.nb_place, &p.horaire, &p.tarif, p.cin_agent, &p.service_off, &p.moyenne , &p.statut) != EOF) {
            if (p.id_parking == id) {
                fclose(f);
                return 1;
            }
        }
        fclose(f);
    }
    return 0;
}

int ajouter(char *filename, PARKING p) {
    p.moyenne = 0;
    if (id_existe(filename, p.id_parking)) {
        printf("Erreur : L'ID de parking %d existe d�j�.\n", p.id_parking);
        return 0;
    }

    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                p.id_parking, p.nom_parking, p.adresse, p.capacite,
                p.type, p.nb_place, p.horaire, p.tarif, p.cin_agent, p.service_off, p.moyenne , p.statut);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier(char *filename, int id, PARKING p) {
    FILE *file = fopen(filename, "r+");
    PARKING temp;
    int trouve = 0;

    if (file == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return 0;
    }

    FILE *tempfile = fopen("temp.txt", "w");
    if (tempfile == NULL) {
        fclose(file);
        printf("Erreur : impossible de créer un fichier temporaire.\n");
        return 0;
    }

    while (fscanf(file, "%d %s %s %d %d %d %d %f %s %d %f %d\n",
                  &temp.id_parking, temp.nom_parking, temp.adresse, &temp.capacite,
                  &temp.type, &temp.nb_place, &temp.horaire, &temp.tarif,
                  temp.cin_agent, &temp.service_off, &temp.moyenne, &temp.statut) != EOF) {
        if (temp.id_parking == id) {
            fprintf(tempfile, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                    p.id_parking, p.nom_parking, p.adresse, p.capacite,
                    p.type, p.nb_place, p.horaire, p.tarif,
                    p.cin_agent, p.service_off, p.moyenne, p.statut);
            trouve = 1;
        } else {
            fprintf(tempfile, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                    temp.id_parking, temp.nom_parking, temp.adresse, temp.capacite,
                    temp.type, temp.nb_place, temp.horaire, temp.tarif,
                    temp.cin_agent, temp.service_off, temp.moyenne, temp.statut);
        }
    }

    fclose(file);
    fclose(tempfile);

    if (trouve) {
        remove(filename);
        rename("temp.txt", filename);
    } else {
        remove("temp.txt");
    }

    return trouve;
}


int supprimer(char *filename, int id) {
    int tr = 0;
    PARKING p;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %s %s %d %d %d %d %f %s %d %f %d\n",
                      &p.id_parking, p.nom_parking, p.adresse, &p.capacite,
                      &p.type, &p.nb_place, &p.horaire, &p.tarif, p.cin_agent, &p.service_off, &p.moyenne , &p.statut) != EOF) {
            if (p.id_parking == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                        p.id_parking, p.nom_parking, p.adresse, p.capacite,
                        p.type, p.nb_place, p.horaire, p.tarif, p.cin_agent, p.service_off, p.moyenne , p.statut);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

PARKING chercher(char *filename, int id) {
    PARKING p;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (tr == 0 && fscanf(f, "%d %s %s %d %d %d %d %f %s %d %f %d\n",
                                 &p.id_parking, p.nom_parking, p.adresse, &p.capacite,
                                 &p.type, &p.nb_place, &p.horaire, &p.tarif, p.cin_agent, &p.service_off, &p.moyenne , &p.statut) != EOF) {
            if (p.id_parking == id)
                tr = 1;
        }
        fclose(f);
    }
    if (tr == 0)
        p.id_parking = -1;
    return p;
}

void afficher(char *filename) {
    PARKING p;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        printf("ID | Nom          | Adresse             | Capacit� | Type | Places | Horaire | Tarif  | CIN Agent | Services | Moyenne | statut\n");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        while (fscanf(f, "%d %s %s %d %d %d %d %f %s %d %f %d\n",
                      &p.id_parking, p.nom_parking, p.adresse, &p.capacite,
                      &p.type, &p.nb_place, &p.horaire, &p.tarif, p.cin_agent, &p.service_off, &p.moyenne , &p.statut) != EOF) {
            printf("%2d | %-12s | %-20s | %8d | %4d | %6d | %7d | %.2f | %-8s | %d | %.2f | %d\n",
                   p.id_parking, p.nom_parking, p.adresse, p.capacite,
                   p.type, p.nb_place, p.horaire, p.tarif, p.cin_agent, p.service_off, p.moyenne , p.statut);
        }
        fclose(f);
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
    }
}


void affecter(char *filename, int id_parking, char *cin_agent) {
    PARKING p = chercher(filename, id_parking);
    FILE *fagent = fopen("agents.txt", "r");
    Agent agent;
    int agent_tr = 0;  

    if (fagent == NULL) {
        printf("Erreur d'ouverture du fichier agents.txt\n");
        return;
    }

    if (p.id_parking != -1) {
        while (fscanf(fagent, "%s %s %s %s %u %s %s %d %u %i\n",
                      agent.CIN, agent.nom, agent.prenom, agent.email, &agent.sexe, agent.date_naissance, 
                      agent.lieu_naissance, &agent.num_banque, &agent.etat_civil, &agent.nombre_enfant) != EOF) {
            if (!strcmp(cin_agent, agent.CIN)) {
                strncpy(p.cin_agent, cin_agent, sizeof(p.cin_agent) - 1);
                p.cin_agent[sizeof(p.cin_agent) - 1] = '\0';
                modifier(filename, id_parking, p);
                printf("Agent affect� avec succ�s\n");
                agent_tr = 1;
                break;  
            }
        }
        
        if (!agent_tr) {
            printf("Agent n'existe pas\n");
        }
    } else {
        printf("Parking non trouv�\n");
    }

    fclose(fagent);  
}



