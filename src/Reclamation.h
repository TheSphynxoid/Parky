#ifndef RECLAMATION_H_INCLUDED
#define RECLAMATION_H_INCLUDED

typedef struct {
    char cin[100]; char autre[100];
    char typeReclamation[500];
    char numeroPlace[10];
    char date_incident[20];
    char service[50];
    int note;
    int avis_ou_reclamation;
} Reclamation;

int ajouterReclamation(char *filename, Reclamation r);
int modifierReclamation(char *filename, char *cin, Reclamation nouv);  
int supprimerReclamation(char *filename, char *cin);  
Reclamation chercherReclamation(char *filename, char *cin);  
void trier_par_note(Reclamation reclamations[], int count);
void afficher_MF(char *filename, int type);

#endif

