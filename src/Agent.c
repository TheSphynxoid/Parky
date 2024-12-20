#include "Agent.h"


int AjouterAgent(char* filename, Agent agent){
    FILE* f = fopen(filename, "a");
    if(f == NULL)return 1;
    if(ChercherAgent(filename, agent.CIN, NULL)){
        fprintf(f,"%s %s %s %s %u %s %s %d %u %i \n",
            agent.CIN, agent.nom, agent.prenom, agent.email, agent.sexe, agent.date_naissance, agent.lieu_naissance, agent.num_banque,
            agent.etat_civil, agent.nombre_enfant);
    }
    else{
        printf("L'agent existe deja dans la base de donne�s\n");
    }
    fclose(f);
    return 0;
}
int ModifierAgent(char* filename, char* id, Agent nouv){
    int tr=0;
    Agent agent;
    FILE* f =fopen(filename, "r");
    FILE* f2 =fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, &agent.sexe, agent.date_naissance, agent.lieu_naissance, &agent.num_banque,
                &agent.etat_civil, &agent.nombre_enfant)!=EOF)
        {
            if(!strcmp(agent.CIN, id))
            {
                fprintf(f2,"%s %s %s %s %u %s %s %d %u %i \n",
                    nouv.CIN, nouv.nom, nouv.prenom, nouv.email, nouv.sexe, nouv.date_naissance, nouv.lieu_naissance, nouv.num_banque,
                    nouv.etat_civil, nouv.nombre_enfant);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, agent.sexe, agent.date_naissance, agent.lieu_naissance, agent.num_banque,
                agent.etat_civil, agent.nombre_enfant);

        }
    }
    fclose(f);
    fclose(f2);
    if (remove(filename) != 0) {
        printf("Erreur lors de la suppression du fichier");
    }
    if (rename("nouv.txt", filename) != 0) {
        printf("Erreur lors du renommage du fichier");
    }
    return tr;
}

int SupprimerAgent(char* filename, char* id){
    int tr=0;
    Agent agent;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, &agent.sexe, agent.date_naissance, agent.lieu_naissance, &agent.num_banque,
                &agent.etat_civil, &agent.nombre_enfant)!= EOF)
        {
            if(!strcmp(agent.CIN, id))
                tr=1;
            else
                fprintf(f2,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, agent.sexe, agent.date_naissance, agent.lieu_naissance, agent.num_banque,
                agent.etat_civil, agent.nombre_enfant);
        }
    }
    fclose(f);
    fclose(f2);
    if (remove(filename) != 0) {
        printf("Erreur lors de la suppression du fichier");
    }
    if (rename("nouv.txt", filename) != 0) {
        printf("Erreur lors du renommage du fichier");
    }
    return tr;
}

void AfficherAgents(char* filename){
    FILE* f = fopen(filename, "r");
    Agent rAgent;
    while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
            rAgent.CIN, rAgent.nom, rAgent.prenom, rAgent.email, &rAgent.sexe, rAgent.date_naissance, rAgent.lieu_naissance, &rAgent.num_banque,
            &rAgent.etat_civil, &rAgent.nombre_enfant) != EOF){
        printf("%s %s %s %s %u %s %s %d %u %i \n",
                rAgent.CIN, rAgent.nom, rAgent.prenom, rAgent.email, rAgent.sexe, rAgent.date_naissance, rAgent.lieu_naissance, rAgent.num_banque,
                rAgent.etat_civil, rAgent.nombre_enfant);
    }
}

//Retourne 1 Si agent n'est pas trouv�.
int ChercherAgent(char* filename, char* id, Agent* agent){
    //si rAgent == NULL, on simplement fait un recherche sans retourner une valeur.
    Agent back;
    Agent* rAgent = (agent != NULL ? agent : &back);
    FILE* f = fopen(filename, "r");
    if(f == NULL){
        printf("Erreur overture du fichier");
        return -1;
    }

    while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
            rAgent->CIN, rAgent->nom, rAgent->prenom, rAgent->email, &rAgent->sexe, rAgent->date_naissance, rAgent->lieu_naissance, &rAgent->num_banque,
            &rAgent->etat_civil, &rAgent->nombre_enfant) != EOF){
        if(!strcmp(rAgent->CIN, id)){
            return 0;
        }
    }
    return 1;
}

void ListeReservation(char* filename,int id_parking, Date date){
    FILE* file = fopen(filename, "r");
    FILE* temp = fopen("temp.txt","w");
    Reservation reservation;
    while(fscanf(file, "%d %s %s %s %d %d %d %d/%d/%d/%d %d/%d/%d/%d %f\n",
            &reservation.ID_Parking, reservation.nom_parking, reservation.nom, reservation.prenom, &reservation.numero,
            &reservation.CIN, &reservation.immatricule, &reservation.arr_jour, &reservation.arr_mois, &reservation.arr_annee,  &reservation.arr_heure,
            &reservation.dep_jour, &reservation.dep_mois, &reservation.dep_annee,  &reservation.dep_heure, &reservation.prix) != EOF){

        if(reservation.ID_Parking == id_parking && date.jour == reservation.arr_jour && date.mois == reservation.arr_mois && date.annee == reservation.arr_annee){
            printf("Une reservation pour %s %s\n", reservation.nom, reservation.prenom);
			fprintf(temp, "%d %s %s %s %d %d %d %d/%d/%d/%d %d/%d/%d/%d %f\n",
            	reservation.ID_Parking, reservation.nom_parking, reservation.nom, reservation.prenom, reservation.numero,
            	reservation.CIN, reservation.immatricule, reservation.arr_jour, reservation.arr_mois, reservation.arr_annee, reservation.arr_heure,
            	reservation.dep_jour, reservation.dep_mois, reservation.dep_annee,  reservation.dep_heure, reservation.prix);
        }
    }
    fclose(file);
}
