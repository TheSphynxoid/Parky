#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "Agent.h"
#include "Client.h"

typedef GtkWidget* pGTKWidget;

//0 pour homme, 1 pour femme.
unsigned int AgentSexe = 0;
unsigned int ClientSexe = 0;
int ClientNotif = 0;
void
on_HS_rb_femme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    AgentSexe = 1;
}


void
on_HS_supprimer_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{
}


void
on_HS_bt_status_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_HS_Filtre_clicked                   (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_HS_Sexe_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    AgentSexe = 0;
}


void
on_HS_confirmer_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{
    pGTKWidget wCIN, wNom, wPrenom, wLieuNaissance, wJour, wMois, wAnnee, wNbEnfant, wEtatCivil, wNumBanque, wEmail;
    
    wCIN = lookup_widget(widget, "HS_CIN");
    wNom = lookup_widget(widget, "HS_nom");
    wPrenom = lookup_widget(widget, "HS_prenom");
    wJour = lookup_widget(widget, "HS_jour");
    wMois = lookup_widget(widget, "HS_mois");
    wAnnee = lookup_widget(widget, "HS_annee");
    wNbEnfant = lookup_widget(widget, "HS_nb_enfant");
    wLieuNaissance = lookup_widget(widget, "HS_lieu_naissance");
    wNumBanque = lookup_widget(widget, "HS_num_banque");
    wEmail = lookup_widget(widget, "HS_email");
    
    Agent agent;
    //Le champs a une limite de 8 caractere, on copie 9 pour /n.
    strncpy(agent.CIN, gtk_entry_get_text(GTK_ENTRY(wCIN)), 9);
    //Même ici.
    strncpy(agent.nom, gtk_entry_get_text(GTK_ENTRY(wNom)), 20);
    strncpy(agent.prenom, gtk_entry_get_text(GTK_ENTRY(wPrenom)), 20);
    strncpy(agent.email, gtk_entry_get_text(GTK_ENTRY(wEmail)), 60);
    strncpy(agent.lieu_naissance, gtk_entry_get_text(GTK_ENTRY(wLieuNaissance)), 20);
    agent.num_banque = atoi(gtk_entry_get_text(GTK_ENTRY(wNumBanque)));
    snprintf(agent.date_naissance, sizeof(agent.date_naissance), 
             "%02d-%02d-%04d",
             gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(wJour)),
             gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(wMois)),
             gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(wAnnee)));
             
    agent.nombre_enfant = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(wNbEnfant));
    
    int selected = gtk_combo_box_get_active(GTK_COMBO_BOX(wEtatCivil));
    
    if(selected == -1){
        g_print("Erreur, aucun etat civil a ete selectionner.");
        return;
    }
    
    agent.etat_civil = ((unsigned int)1) << selected;
    agent.sexe = AgentSexe;
    
    AjouterAgent("Agent.txt", agent);
    
}


void
on_RB_notif_sms_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)){
        ClientNotif += 1;
    }else{
        ClientNotif -= 1;
    }
}


void
on_RB_notif_email_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)){
        ClientNotif += 2;
    }else{
        ClientNotif -= 2;
    }
}


void
on_RB_confirmer_bouton_clicked         (GTKWidget       *button,
                                        gpointer         user_data)
{
    pGTKWidget id, nom, prenom, email, tel, cin, mdp;

    Compte compte;

    id = lookup_widget(button, "RB_id");
    nom = lookup_widget(button, "RB_nom");
    prenom = lookup_widget(button, "RB_prenom");
    email = lookup_widget(button, "RB_email");
    tel = lookup_widget(button, "RB_tel");
    mdp = lookup_widget(button, "RB_mdp");

    compte.id = atoi(gtk_entry_get_text(GTK_ENTRY(id)));
    strcpy(compte.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(compte.prenom, gtk_entry_get_text)(GTK_ENTRY(prenom));
    strcpy(compte.email, gtk_entry_get_text)(GTK_ENTRY(email));
    strcpy(compte.mdp, gtk_entry_get_text)(GTK_ENTRY(mdp));
    compte.tel = atoi(gtk_get_entry_get_text(GKT_ENTRY(tel)));

    AjouterCompte("Compte.txt", compte);
}


void
on_RB_sexe_h_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    ClientSexe = 1;
}


void
on_RB_sexe_f_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    ClientSexe = 0;
}


void
on_RB_modifier_bouton_clicked          (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RB_supprimer_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RB_chercher_clicked                 (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RB_totalizer_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RB_afficher_clicked                 (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonCO_clicked                 (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_BCom_clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonR_clicked                  (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_BR___clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_Affecter_clicked                 (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_Annuler_clicked                  (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_Rl_buttonSupp_clicked               (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonMod_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonAdd_clicked                (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button2_clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button3_clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button5_clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button6_clicked                     (GTKWidget       *button,
                                        gpointer         user_data)
{

}

