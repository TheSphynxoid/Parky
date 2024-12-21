#include "Reclamation.h"
#include <string.h>
#include <stdio.h>

#define MAX_RECLAMATIONS 100

int ajouterReclamation(char *filename, Reclamation r) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s  %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident,  r.note, r.avis_ou_reclamation); 
        fclose(f);
        return 1;
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier en mode ajout.\n");
        return 0;
    }
}

void trier_par_note(Reclamation reclamations[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (reclamations[i].note < reclamations[j].note) {
                Reclamation temp = reclamations[i];
                reclamations[i] = reclamations[j];
                reclamations[j] = temp;
            }
        }
    }
}

void afficher_MF(char *filename, int type) {
    Reclamation reclamations[MAX_RECLAMATIONS];
    int count = 0;
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (count < MAX_RECLAMATIONS &&
               fscanf(f, "%s %s %s; %s %d %d\n", reclamations[count].cin, reclamations[count].typeReclamation, 
                      reclamations[count].numeroPlace, reclamations[count].date_incident, 
                       &reclamations[count].note, 
                      &reclamations[count].avis_ou_reclamation) == 7) {
            if (reclamations[count].avis_ou_reclamation == type) {
                count++;
            }
        }
        
        fclose(f);

        if (count == 0) {
            printf("Aucune %s trouvée.\n", type == 0 ? "réclamation" : "avis");
            return;
        }

        trier_par_note(reclamations, count);

        printf("Liste des %s triée par note (décroissant):\n", type == 0 ? "Réclamations" : "Avis");
        for (int i = 0; i < count; i++) {
            printf("CIN: %s\n", reclamations[i].cin);
            printf("Type Réclamation: %s\n", reclamations[i].typeReclamation);
            printf("Numéro Place: %s\n", reclamations[i].numeroPlace);
            printf("Date Incident: %s\n", reclamations[i].date_incident);
          
            printf("Note: %d\n", reclamations[i].note);
            printf("Avis ou Réclamation: %d\n", reclamations[i].avis_ou_reclamation);
            printf("---------------\n");
        }
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier pour l'affichage.\n");
    }
}

int modifierReclamation(char *filename, char *cin, Reclamation nouv) {
    int tr = 0;
    Reclamation r;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f == NULL || f2 == NULL) {
        printf("Erreur : Impossible d'ouvrir les fichiers pour la modification.\n");
        if (f) fclose(f);
        if (f2) fclose(f2);
        return 0;
    }

    while (fscanf(f, "%s %s; %s %s  %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident, &r.note, &r.avis_ou_reclamation) != EOF) {
        if (strcmp(r.cin, cin) == 0) {  // Comparer les chaînes de caractères
            fprintf(f2, "%s %s; %s %s  %d %d\n", nouv.cin, nouv.typeReclamation, nouv.numeroPlace, nouv.date_incident, nouv.note, nouv.avis_ou_reclamation);
            tr = 1;
        } else {
            fprintf(f2, "%s %s; %s %s  %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident,  r.note, r.avis_ou_reclamation);
        }
    }

    if (tr == 0) {
        printf("Réclamation avec CIN %s non trouvée.\n", cin);
    }

    fclose(f);
    fclose(f2);

    if (tr == 1) {
        remove(filename);
        rename("temp.txt", filename);
    } else {
        remove("temp.txt");
    }

    return tr;
}

int supprimerReclamation(char *filename, char *cin) {
    int tr = 0;
    Reclamation r;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s; %s %s  %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident,  &r.note, &r.avis_ou_reclamation) != EOF) {
            if (strcmp(r.cin, cin) != 0) {
                fprintf(f2, "%s %s; %s %s  %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident, r.note, r.avis_ou_reclamation);
            } else {
                tr = 1;
            }
        }
        fclose(f);
        fclose(f2);
        if (remove(filename) != 0) {
            perror("Error deleting the original file");
        } else if (rename("temp.txt", filename) != 0) {
            perror("Error renaming the temporary file");
        } else {
            printf("Fichier mis à jour avec succès.\n");
        }
    } else {
        printf("Erreur : Impossible d'ouvrir les fichiers pour la suppression.\n");
        if (f) fclose(f);
        if (f2) fclose(f2);
    }
    return tr;
}

Reclamation chercherReclamation(char *filename, char *cin) {
    Reclamation r;
    int found = 0;
    FILE *f = fopen(filename, "r");

    if (f != NULL) {
        while (found == 0 && fscanf(f, "%s %s; %s %s %d %d\n", r.cin, r.typeReclamation, r.numeroPlace, r.date_incident,  &r.note, &r.avis_ou_reclamation) != EOF) {
            if (strcmp(r.cin, cin) == 0) {  // Comparer les chaînes
                found = 1;
            }
        }
        fclose(f);
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier pour la recherche.\n");
    }

    if (!found) {
        r.cin[0] = '\0';  // Indiquer qu'aucune réclamation n'a été trouvée
    }
    return r;
}


