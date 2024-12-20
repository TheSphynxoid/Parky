#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "Agent.h"
#include "Client.h"

typedef GtkWidget* pGtkWidget;

//0 pour homme, 1 pour femme.
unsigned int AgentSexe = 0;
unsigned int ClientSexe = 0;
int ClientNotif = 0;

Reservation* reservation; 

void HS_AffichageListeAgent(GtkTreeView* treeview){
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        // Create the list store if it doesn't exist
        store = gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INT);
    }else{
        //clear_list_store(store);
        gtk_list_store_clear(store);
    }


    
    FILE* f = fopen("Agent.txt", "r");

    Agent agent;

    while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, &agent.sexe, agent.date_naissance, agent.lieu_naissance, &agent.num_banque,
                &agent.etat_civil, &agent.nombre_enfant) != EOF){
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, agent.CIN, 1, agent.nom, 2, agent.prenom, 3, agent.email, 4, agent.sexe ? "M" : "F", 5, agent.date_naissance, 6, agent.lieu_naissance, 7
            , agent.etat_civil, 8, agent.nombre_enfant, -1);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    //
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date Naissance", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Lieu naissance", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Etat Civil", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nb. Enfant", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    fclose(f);

}

void
on_HS_rb_femme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    AgentSexe = 1;
}


void
on_HS_supprimer_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{
    pGtkWidget AgentTV;
    AgentTV = lookup_widget(button, "treeview1");

    GtkTreeModel* model;
    GtkTreeIter iter;
    
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(AgentTV));
    if(!gtk_tree_selection_get_selected(selection, &model, &iter)){
        return;
    }


    char* cin;
    gtk_tree_model_get(model, &iter, 0, &cin, -1);

    g_print("Selected CIN: %s\n", cin);

    
}


void
on_HS_bt_status_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_HS_Filtre_clicked                   (GtkWidget       *button,
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
on_HS_confirmer_clicked                (GtkWidget       *widget,
                                        gpointer         user_data)
{
    pGtkWidget wCIN, wNom, wPrenom, wLieuNaissance, wJour, wMois, wAnnee, wNbEnfant, wEtatCivil, wNumBanque, wEmail;
    
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
    wEtatCivil = lookup_widget(widget, "HS_etat_civil");
    
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
             
    agent.nombre_enfant = atoi(gtk_entry_get_text(GTK_ENTRY(wNbEnfant)));
    
    int selected = gtk_combo_box_get_active(GTK_COMBO_BOX(wEtatCivil));
    
    if(selected == -1){
        g_print("Erreur, aucun etat civil a ete selectionner.");
        return;
    }
    
    agent.etat_civil = ((unsigned int)1) << selected;
    agent.sexe = AgentSexe;
    
    AjouterAgent("Agent.txt", agent);

    HS_AffichageListeAgent(GTK_TREE_VIEW(lookup_widget(widget, "treeview1")));
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
on_RB_confirmer_bouton_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
    pGtkWidget id, nom, prenom, email, tel, cin, mdp;

    Compte compte;

    id = lookup_widget(button, "RB_id");
    nom = lookup_widget(button, "RB_nom");
    prenom = lookup_widget(button, "RB_prenom");
    cin = lookup_widget(button, "RB_CIN");
    email = lookup_widget(button, "RB_mail");
    tel = lookup_widget(button, "RB_tel");
    mdp = lookup_widget(button, "RB_mdp");

    compte.id = atoi(gtk_entry_get_text(GTK_ENTRY(id)));
    compte.cin = atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
    strcpy(compte.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(compte.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(compte.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(compte.mdp, gtk_entry_get_text(GTK_ENTRY(mdp)));
    compte.tel = atoi(gtk_entry_get_text(GTK_ENTRY(tel)));
    compte.sexe = ClientSexe;
    compte.notif = ClientNotif;

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
on_RB_modifier_bouton_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget* id_cit;

    id_cit = lookup_widget(button, "RB_id_cit");

    int id = atoi(gtk_entry_get_text(GTK_ENTRY(id_cit)));

    Compte c = ChercherCompte("Compte.txt", id);

    if(c.id != -1){
        pGtkWidget id_2, nom, prenom, email, tel, cin, mdp;

        id_2 = lookup_widget(button, "RB_id");
        nom = lookup_widget(button, "RB_nom");
        prenom = lookup_widget(button, "RB_prenom");
        email = lookup_widget(button, "RB_mail");
        tel = lookup_widget(button, "RB_tel");
        mdp = lookup_widget(button, "RB_mdp");
        cin = lookup_widget(button, "RB_CIN");


        gtk_entry_set_text(GTK_ENTRY(id_2), gtk_entry_get_text(GTK_ENTRY(id_cit)));
        
        gtk_entry_set_text(GTK_ENTRY(nom), c.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom), c.prenom);
        gtk_entry_set_text(GTK_ENTRY(email), c.email);
        gtk_entry_set_text(GTK_ENTRY(mdp), c.mdp);

        char tel_str[10];
        sprintf(tel_str, "%d", c.tel);

        gtk_entry_set_text(GTK_ENTRY(tel), tel_str);

        char cin_str[10];
        sprintf(cin_str, "%d", c.cin);

        gtk_entry_set_text(GTK_ENTRY(cin), cin_str);
    }
}


void
on_RB_supprimer_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{
    // GtkWidget* id_cit;

    // id_cit = lookup_widget(button, "RB_id_cit");

    // int id = atoi(gtk_entry_get_text(GTK_ENTRY(id_cit)));

    // if(c.id != -1){
    //     SupprimerCompte("Compte.txt", id);
    // }
}


void
on_RB_chercher_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget* id_cit;

    id_cit = lookup_widget(button, "RB_id_cit");

    int id = atoi(gtk_entry_get_text(GTK_ENTRY(id_cit)));

    Compte c = ChercherCompte("Compte.txt", id);

    if(c.id != -1){
        pGtkWidget id_2, nom, prenom, email, tel, cin, mdp;

        id_2 = lookup_widget(button, "RB_id");
        nom = lookup_widget(button, "RB_nom");
        prenom = lookup_widget(button, "RB_prenom");
        email = lookup_widget(button, "RB_mail");
        tel = lookup_widget(button, "RB_tel");
        mdp = lookup_widget(button, "RB_mdp");
        cin = lookup_widget(button, "RB_CIN");


        gtk_entry_set_text(GTK_ENTRY(id_2), gtk_entry_get_text(GTK_ENTRY(id_cit)));
        
        gtk_entry_set_text(GTK_ENTRY(nom), c.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom), c.prenom);
        gtk_entry_set_text(GTK_ENTRY(email), c.email);
        gtk_entry_set_text(GTK_ENTRY(mdp), c.mdp);

        char tel_str[10];
        sprintf(tel_str, "%d", c.tel);

        gtk_entry_set_text(GTK_ENTRY(tel), tel_str);

        char cin_str[10];
        sprintf(cin_str, "%d", c.cin);

        gtk_entry_set_text(GTK_ENTRY(cin), cin_str);
    }
}


void
on_RB_totalizer_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RB_afficher_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonCO_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_BCom_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonR_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_BR___clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_Affecter_clicked                 (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_Annuler_clicked                  (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_Rl_buttonSupp_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonMod_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_RL_buttonAdd_clicked                (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button2_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button3_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button5_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button6_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{

}

void
on_HS_bt_modifier_clicked              (GtkWidget       *button,
                                        gpointer         user_data)
{
    pGtkWidget AgentTV;
    AgentTV = lookup_widget(button, "treeview1");

    GtkTreeModel* model;
    GtkTreeIter iter;
    
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(AgentTV));
    gtk_tree_selection_get_selected(selection, &model, &iter);


    char* cin;
    gtk_tree_model_get(model, &iter, 0, &cin, -1);

    g_print("Selected CIN: %s\n", cin);

    Agent agent;
    if(!ChercherAgent("Agent.txt", cin, &agent)){
        pGtkWidget wCIN, wNom, wPrenom, wLieuNaissance, wJour, wMois, wAnnee, wNbEnfant, wEtatCivil, wNumBanque, wEmail;
    
        wCIN = lookup_widget(button, "HS_CIN");
        wNom = lookup_widget(button, "HS_nom");
        wPrenom = lookup_widget(button, "HS_prenom");
        wJour = lookup_widget(button, "HS_jour");
        wMois = lookup_widget(button, "HS_mois");
        wAnnee = lookup_widget(button, "HS_annee");
        wNbEnfant = lookup_widget(button, "HS_nb_enfant");
        wLieuNaissance = lookup_widget(button, "HS_lieu_naissance");
        wNumBanque = lookup_widget(button, "HS_num_banque");
        wEmail = lookup_widget(button, "HS_email");
        wEtatCivil = lookup_widget(button, "HS_etat_civil");

        gtk_entry_set_text(GTK_ENTRY(wCIN), agent.CIN);
        gtk_entry_set_text(GTK_ENTRY(wNom), agent.nom);
        gtk_entry_set_text(GTK_ENTRY(wPrenom), agent.prenom);
        gtk_entry_set_text(GTK_ENTRY(wEmail), agent.email);
        gtk_entry_set_text(GTK_ENTRY(wLieuNaissance), agent.lieu_naissance);

        char buffer[50];
        sprintf(buffer, "%d", agent.nombre_enfant);
        gtk_entry_set_text(GTK_ENTRY(wNbEnfant), buffer);
        sprintf(buffer, "%d", agent.num_banque);
        gtk_entry_set_text(GTK_ENTRY(wNumBanque), buffer);

        if(agent.sexe){
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "HS_sexe")), 1);
        }else{
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "HS_rb_femme")), 1);
        }

        int j,m,a;

        if (sscanf(agent.date_naissance, "%d-%d-%d", &j, &m, &a) == 3) {
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(wJour), j);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(wMois), m);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(wAnnee), a);
        } else {
            // Error in parsing
            printf("Error parsing date.\n");
        }
    }
}


void
on_treeview1_map                       (GtkWidget       *widget,
                                        gpointer         user_data)
{
    HS_AffichageListeAgent(GTK_TREE_VIEW(widget));  
}


void
on_treeview2_map                       (GtkWidget       *widget,
                                        gpointer         user_data)
{

}

