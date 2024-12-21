#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "Agent.h"
#include "Client.h"
#include "parking.h"
#include "Reclamation.h"

typedef GtkWidget* pGtkWidget;

//0 pour homme, 1 pour femme.
unsigned int AgentSexe = 0;
unsigned int ClientSexe = 0;
int ClientNotif = 0;

char probleme[500] = "";
int oui = 0;
int service = 0;
int choix[5] = {0, 0, 0, 0, 0};

//int T[4];
int ServiceSelect = 0;
int statut = 0;

typedef struct{
	char cin[9];
}Cin;

Cin* AgentsAffecte = NULL;
unsigned int nAffecte = 0;
unsigned int TailleAgents = 20;

Reservation* reservation; 

void Refresh_tr(GtkWidget* treeview){
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (!store) {
        // Create the list store if it doesn't exist
        store = gtk_list_store_new(10, G_TYPE_INT, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING );
    }else{
        //clear_list_store(store);
        gtk_list_store_clear(store);
    }
	FILE* f = fopen("Compte.txt","r");
	Compte c;

	while(fscanf(f, "%d %s %s %d %d %s %d %d %s %s\n", &c.id, c.nom, c.prenom, &c.cin, &c.sexe, c.email, &c.tel, &c.notif, c.mdp, c.ville) != EOF){
		gtk_list_store_append(store, &iter);
    	gtk_list_store_set(store, &iter,0, c.id, 1, c.nom,2,c.prenom,3,c.cin,4,c.sexe,5,c.email,6,c.tel,7,c.notif,8,c.mdp,9,c.ville,-1);
	   
	}
	 gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

	fclose(f);
}

void RB_affichage(GtkTreeView* treeview){
	GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        // Create the list store if it doesn't exist
        store = gtk_list_store_new(10, G_TYPE_INT, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING );
    }else{
        //clear_list_store(store);
        gtk_list_store_clear(store);
    }
	FILE* f = fopen("Compte.txt","r");
	Compte c;

	while(fscanf(f, "%d %s %s %d %d %s %d %d %s %s\n", &c.id, c.nom, c.prenom, &c.cin, &c.sexe, c.email, &c.tel, &c.notif, c.mdp, c.ville) != EOF){
		gtk_list_store_append(store, &iter);
    	gtk_list_store_set(store, &iter,0, c.id, 1, c.nom,2,c.prenom,3,c.cin,4,c.sexe,5,c.email,6,c.tel,7,c.notif,8,c.mdp,9,c.ville,-1);
	   
	}
	 gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("ID_citoyen", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
   
    //
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Num_tel", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Notificationl", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

	renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    fclose(f);

}


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
    if(!ChercherAgent("Agent.txt", agent.CIN, NULL)){
                GtkWidget *dialog;
        gint response;

        // Create the message dialog with Yes and No buttons
        dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    "Voulez-vous vraiment modifier ?");

        // Run the dialog and get the response
        response = gtk_dialog_run(GTK_DIALOG(dialog));

        // Handle the response
        if (response == GTK_RESPONSE_YES) {
            if(ModifierAgent("Agent.txt", agent.CIN, agent)){
                GtkWidget *success_dialog;
	            success_dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Agent Modifie avec succès !");
	            gtk_dialog_run(GTK_DIALOG(success_dialog));
	            gtk_widget_destroy(success_dialog);
            }
        }
   
        // Destroy the dialog after it's closed
        gtk_widget_destroy(dialog);
    }else{
        AjouterAgent("Agent.txt", agent);
        GtkWidget *success_dialog;
	    success_dialog = gtk_message_dialog_new(NULL,
                            GTK_DIALOG_MODAL,
                            GTK_MESSAGE_INFO,
                            GTK_BUTTONS_OK,
                            "Agent ajouté avec succès !");
	    gtk_dialog_run(GTK_DIALOG(success_dialog));
	    gtk_widget_destroy(success_dialog);
    }

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
    pGtkWidget id, nom, prenom, email, tel, cin, mdp, ville, treeview;

    Compte compte;

    id = lookup_widget(button, "RB_id");
    nom = lookup_widget(button, "RB_nom");
    prenom = lookup_widget(button, "RB_prenom");
    cin = lookup_widget(button, "RB_CIN");
    email = lookup_widget(button, "RB_mail");
    tel = lookup_widget(button, "RB_tel");
    mdp = lookup_widget(button, "RB_mdp");
	ville=lookup_widget(button, "RB_ville");
	treeview = lookup_widget(button,"RB_tr");

    compte.id = atoi(gtk_entry_get_text(GTK_ENTRY(id)));
    compte.cin = atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
    strcpy(compte.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(compte.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
    strcpy(compte.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(compte.mdp, gtk_entry_get_text(GTK_ENTRY(mdp)));
    compte.tel = atoi(gtk_entry_get_text(GTK_ENTRY(tel)));
	strcpy(compte.ville, gtk_combo_box_get_active_text(GTK_COMBO_BOX(ville)));
    compte.sexe = ClientSexe;
    compte.notif = ClientNotif;
    if (ChercherCompte("Compte.txt",compte.id).id!=-1){
        GtkWidget *dialog;
        gint response;

        // Create the message dialog with Yes and No buttons
        dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    "Voulez-vous vraiment modifier ?");

        // Run the dialog and get the response
        response = gtk_dialog_run(GTK_DIALOG(dialog));

        // Handle the response
        if (response == GTK_RESPONSE_YES) {
            if(ModiferCompte("Compte.txt", compte)){
                GtkWidget *success_dialog;
	            success_dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Compte modifie avec succès !");
	            gtk_dialog_run(GTK_DIALOG(success_dialog));
	            gtk_widget_destroy(success_dialog);
            }
        }
   
        // Destroy the dialog after it's closed
        gtk_widget_destroy(dialog);

    }else{
        AjouterCompte("Compte.txt", compte);
	GtkWidget *success_dialog;
	success_dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Compte ajouté avec succès !");
	gtk_dialog_run(GTK_DIALOG(success_dialog));
	gtk_widget_destroy(success_dialog);
    }

	Refresh_tr(treeview);		
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
	GtkWidget* tr = lookup_widget(button, "RB_tr");
	
	GtkTreeModel* model;
    GtkTreeIter iter;
   
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tr));
    if(!gtk_tree_selection_get_selected(selection, &model, &iter)){
    	g_print("Aucun Compte Selection");
    	return;
    }


    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);

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

		char id_str[20];
		sprintf(id_str, "%d", id);
		
        gtk_entry_set_text(GTK_ENTRY(id_2), id_str);
        
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
    GtkWidget* treeview = lookup_widget(button, "RB_tr");
	
	GtkTreeModel* model;
    GtkTreeIter iter;
   
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if(!gtk_tree_selection_get_selected(selection, &model, &iter)){
    	g_print("Aucun Compte Selection");
    	return;
    }


    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);

    Compte c = ChercherCompte("Compte.txt", id);

    if(c.id != -1){
        SupprimerCompte("Compte.txt", id);
	GtkWidget *success_dialog;
        success_dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "Compte supprimé avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
	
	Refresh_tr(treeview);
    }
	else {
        // Afficher un message d'erreur si le compte n'existe pas
        GtkWidget *error_dialog;
        error_dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_ERROR,
                                              GTK_BUTTONS_OK,
                                              "Erreur : Compte introuvable !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
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
        pGtkWidget id_2, nom, prenom, email, tel, cin, mdp, ville;

        id_2 = lookup_widget(button, "RB_id");
        nom = lookup_widget(button, "RB_nom");
        prenom = lookup_widget(button, "RB_prenom");
        email = lookup_widget(button, "RB_mail");
        tel = lookup_widget(button, "RB_tel");
        mdp = lookup_widget(button, "RB_mdp");
        cin = lookup_widget(button, "RB_CIN");
		ville = lookup_widget(button, "RB_ville");


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
{ GtkWidget* id_cit;

    id_cit = lookup_widget(button, "RB_id_cit");
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(id_cit)));

    Compte c = ChercherCompte("Compte.txt", id);
    if (c.id!=-1){
        GtkWidget* mois = lookup_widget(button, "RB_mois");
        int m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
        GtkWidget* annee = lookup_widget(button, "RB_annee");
        int a = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
        float resultat = FactureMensuelle("reservations.txt",m,a, c.cin);
        GtkWidget* label;
        label = lookup_widget(button, "RB_label_total");
        char chaine[20];
        sprintf(chaine, "%f", resultat);
        gtk_label_set_text(GTK_LABEL(label), chaine);

    }else{
        GtkWidget* label;
		label = lookup_widget(button, "RB_label_total");
        gtk_label_set_text(GTK_LABEL(label), "0");
	}
}

void on_RB_afficher_clicked(GtkWidget *button, gpointer user_data)
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

void
on_RB_ville_map                        (GtkWidget       *widget,
                                        gpointer         user_data)
{
	FILE* f = fopen("ville.txt", "r");
	char ville[50];
	while(fscanf(f, "%s", ville) != EOF){
		gtk_combo_box_append_text(GTK_COMBO_BOX(widget), ville);
        g_print("%s \n", ville);
	}
    fclose(f);
}
void
on_RB_tr_map                           (GtkWidget       *widget,
                                        gpointer         user_data)
{
	RB_affichage(GTK_TREE_VIEW(widget));
}

void
on_Auth_conn_clicked                   (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget* id = lookup_widget(button, "Auth_User");
    GtkWidget* pass = lookup_widget(button, "Auth_pass");
    const char* user = gtk_entry_get_text(GTK_ENTRY(id));
    const char* mdp = gtk_entry_get_text(GTK_ENTRY(pass));
    g_print("%s\n", user);
    if(!strcmp(user, "admin") && !strcmp(mdp, "admin")){
        gtk_widget_show(create_G4_PARKY());
        return;
    }
    Compte c = ChercherCompte("Compte.txt", atoi(user));
    if(c.cin == -1){
        GtkWidget *error_dialog;
        error_dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_ERROR,
                                              GTK_BUTTONS_OK,
                                              "Erreur : Compte introuvable !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }else{
        if(strcmp(mdp, c.mdp) == 0){
            gtk_widget_show(create_G4_PARKY_client());
        }else{
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL,
                                GTK_MESSAGE_ERROR,
                                GTK_BUTTONS_OK,
                                "Erreur : Mot de passe erroné !");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
    }
}


void
on_Auth_cree_clicked                   (GtkWidget       *button,
                                        gpointer         user_data)
{

}


void
on_button70_clicked                    (GtkWidget       *button,
                                        gpointer         user_data)
{

}

void
on_Rl_buttonSupp_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{
	GtkWidget* parkingtree = lookup_widget(button, "treeviewParking_RL");

    GtkTreeModel* model;
    GtkTreeIter iter;
   
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(parkingtree));
    if(gtk_tree_selection_get_selected(selection, &model, &iter)){
		g_print("Aucune Selection\n");
	}


    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);

 int resultat = supprimer("parking.txt", id);
 if(resultat ==1){
 printf("parking supp avec succée");
}else{ printf("erreur");}
on_actualiser1_RL_clicked(button, user_data);
}


void
on_RL_buttonMod_clicked(GtkWidget *button, gpointer user_data) {
    PARKING p;
	GtkWidget* parkingtree = lookup_widget(button, "treeviewParking_RL");

    GtkTreeModel* model;
    GtkTreeIter iter;
   
    GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(parkingtree));
    if(gtk_tree_selection_get_selected(selection, &model, &iter)){
		g_print("Aucune Selection\n");
	}


    int id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);

    // Chercher le parking correspondant
    p = chercher("parking.txt", id);

    if (p.id_parking != -1) {
        GtkWidget *input1, *input2, *input3, *input4, *input5, *input6, *input7, *input8;

        // Récupérer les champs du formulaire
        input1 = lookup_widget(button, "id_Rl");
        input2 = lookup_widget(button, "nom_RL");
        input3 = lookup_widget(button, "add_RL");
        input4 = lookup_widget(button, "cap_RL");
        input5 = lookup_widget(button, "type_RL");
        input6 = lookup_widget(button, "tarif_RL");
        input7 = lookup_widget(button, "nb_RL");
        input8 = lookup_widget(button, "horaire_RL");

        // Charger les données dans le formulaire
        gtk_entry_set_text(GTK_ENTRY(input1), g_strdup_printf("%d", p.id_parking));
        gtk_entry_set_text(GTK_ENTRY(input2), p.nom_parking);
        gtk_entry_set_text(GTK_ENTRY(input3), p.adresse);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input4), p.capacite);
        gtk_combo_box_set_active(GTK_COMBO_BOX(input5), p.type);
        gtk_entry_set_text(GTK_ENTRY(input6), g_strdup_printf("%.2f", p.tarif));
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input7), p.nb_place);
        gtk_entry_set_text(GTK_ENTRY(input8), g_strdup_printf("%d", p.horaire));

        // Préparer le parking modifié
        PARKING p_mod;
        p_mod.id_parking = atoi(gtk_entry_get_text(GTK_ENTRY(input1)));
        strcpy(p_mod.nom_parking, gtk_entry_get_text(GTK_ENTRY(input2)));
        strcpy(p_mod.adresse, gtk_entry_get_text(GTK_ENTRY(input3)));
        p_mod.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
        p_mod.type = gtk_combo_box_get_active(GTK_COMBO_BOX(input5));
        p_mod.tarif = atof(gtk_entry_get_text(GTK_ENTRY(input6)));
        p_mod.nb_place = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input7));
        p_mod.horaire = atoi(gtk_entry_get_text(GTK_ENTRY(input8)));
        p_mod.service_off = ServiceSelect;
        p_mod.statut = statut;
        snprintf(p_mod.cin_agent, sizeof(p_mod.cin_agent), "%s", p.cin_agent);
        p_mod.moyenne = p.moyenne;

        // Lire le fichier et modifier l'entrée
        FILE *file = fopen("parking.txt", "r");
        FILE *temp = fopen("temp_parking.txt", "w");
        if (file == NULL || temp == NULL) {
            printf("Erreur lors de l'ouverture des fichiers.\n");
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            PARKING current;
            sscanf(line, "%d %s %s %d %d %d %d %f %s %d %f %d",
                   &current.id_parking, current.nom_parking, current.adresse,
                   &current.capacite, &current.type, &current.nb_place, &current.horaire,
                   &current.tarif, current.cin_agent, &current.service_off,
                   &current.moyenne, &current.statut);

            if (current.id_parking == id) {
                // Écrire le parking modifié
                fprintf(temp, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                        p_mod.id_parking, p_mod.nom_parking, p_mod.adresse,
                        p_mod.capacite, p_mod.type, p_mod.nb_place, p_mod.horaire,
                        p_mod.tarif, p_mod.cin_agent, p_mod.service_off,
                        p_mod.moyenne, p_mod.statut);
            } else {
                // Garder les autres lignes
                fprintf(temp, "%s", line);
            }
        }

        fclose(file);
        fclose(temp);

        // Remplacer le fichier original par le fichier temporaire
        remove("parking.txt");
        rename("temp_parking.txt", "parking.txt");

        printf("Parking modifié avec succès !\n");
    } else {
        printf("Parking introuvable.\n");
    }
}





void
on_RL_buttonAdd_clicked                (GtkWidget        *button,
                                        gpointer         user_data)
{

}




void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    int value = gtk_toggle_button_get_active(togglebutton);
	ServiceSelect = (value == 1) ? (ServiceSelect | (1)) : (ServiceSelect & ~(1));
}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	int value = gtk_toggle_button_get_active(togglebutton);
	ServiceSelect = (value == 1) ? (ServiceSelect | (1 << 3)) : (ServiceSelect & ~(1 << 3));
}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	int value = gtk_toggle_button_get_active(togglebutton);
	ServiceSelect = (value == 1) ? (ServiceSelect | (1 << 1)) : (ServiceSelect & ~(1 << 1));
}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	int value = gtk_toggle_button_get_active(togglebutton);
	ServiceSelect = (value == 1) ? (ServiceSelect | (1 << 2)) : (ServiceSelect & ~(1 << 2));
}


void on_RL_buttonR_clicked(GtkWidget *button, gpointer user_data) {
    
    GtkWidget *input1, *input2, *input3, *input4, *input5, *input6, *input7, *input8;
    GtkWidget *input9, *input10, *input11, *input12;

    
    input1 = lookup_widget(button, "id_Rl");          
    input2 = lookup_widget(button, "nom_RL");          
    input3 = lookup_widget(button, "add_RL");          
    input4 = lookup_widget(button, "cap_RL");          
    input5 = lookup_widget(button, "type_RL");         
    input6 = lookup_widget(button, "tarif_RL");       
    input7 = lookup_widget(button, "nb_RL");           
    input8 = lookup_widget(button, "horaire_RL");      
    input9 = lookup_widget(button, "checkbutton1");    
    input10 = lookup_widget(button, "checkbutton4");   
    input11 = lookup_widget(button, "checkbutton2");   
    input12 = lookup_widget(button, "checkbutton3");   

    gtk_entry_set_text(GTK_ENTRY(input1), "");         
    gtk_entry_set_text(GTK_ENTRY(input2), "");         
    gtk_entry_set_text(GTK_ENTRY(input3), "");         
    gtk_entry_set_text(GTK_ENTRY(input6), "");        
    gtk_entry_set_text(GTK_ENTRY(input8), "");         
    gtk_combo_box_set_active(GTK_COMBO_BOX(input5), 0); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(input4), 1); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(input7), 1); 
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input9), FALSE); 
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input10), FALSE); 
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input11), FALSE); 
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input12), FALSE); 
    printf("Réinitialisation complète des champs et widgets effectuée.\n");
}



 void on_RL_BCom_clicked(GtkWidget *button, gpointer user_data)
{
    PARKING p;
    GtkWidget *input1, *input2, *input3, *input4, *input5, *input6, *input7, *input8;
    GtkWidget *message_dialog;

    // Récupérer les valeurs des entrées
    input1 = lookup_widget(button, "id_Rl");
    input2 = lookup_widget(button, "nom_RL");
    input3 = lookup_widget(button, "add_RL");
    input4 = lookup_widget(button, "cap_RL");
    input5 = lookup_widget(button, "type_RL");
    input6 = lookup_widget(button, "tarif_RL");
    input7 = lookup_widget(button, "nb_RL");
    input8 = lookup_widget(button, "horaire_RL");

    // Validation des champs obligatoires
    const gchar *id_text = gtk_entry_get_text(GTK_ENTRY(input1));
    if (strlen(id_text) == 0) {
        message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                                "L'identifiant ne peut pas être vide.");
        gtk_dialog_run(GTK_DIALOG(message_dialog));
        gtk_widget_destroy(message_dialog);
        return;
    }

    p.id_parking = atoi(id_text);
    strcpy(p.nom_parking, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(p.adresse, gtk_entry_get_text(GTK_ENTRY(input3)));
    p.capacite = gtk_spin_button_get_value_as_int((GtkSpinButton *)input4);
    p.service_off = ServiceSelect;
    p.type = gtk_combo_box_get_active((GtkComboBox *)input5);
    p.tarif = atof(gtk_entry_get_text(GTK_ENTRY(input6)));
    p.nb_place = gtk_spin_button_get_value_as_int((GtkSpinButton *)input7);
    p.horaire = atoi(gtk_entry_get_text(GTK_ENTRY(input8)));
    p.moyenne = 0;
    snprintf(p.cin_agent, sizeof(p.cin_agent), "00000000");
    p.statut = statut;
	PARKING cherche = chercher("parking.txt", p.id_parking);
    if (cherche.id_parking != -1) {
        // Parking déjà existant, demande de confirmation de modification
        GtkWidget *dialog;
        gint response;

        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
                                        "Voulez-vous vraiment modifier ?");
        response = gtk_dialog_run(GTK_DIALOG(dialog));


        if (response == GTK_RESPONSE_YES) {
			strcpy(p.cin_agent, cherche.cin_agent);
            modifier("parking.txt", p.id_parking, p);
            message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "Modification réussie.");
            gtk_dialog_run(GTK_DIALOG(message_dialog));
            gtk_widget_destroy(message_dialog);
        }
        gtk_widget_destroy(dialog);
    } else {
        // Nouveau parking, tentative d'ajout
        if (ajouter("parking.txt", p)) {
            message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "Ajout réussi.");
			on_comboboxParky_RL_map(GTK_COMBO_BOX(lookup_widget(button, "comboboxParky_RL")));
			on_actualiser1_RL_clicked(button, user_data);
			
        } else {
            message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                                    "Erreur lors de l'ajout du parking.");
        }
        gtk_dialog_run(GTK_DIALOG(message_dialog));
        gtk_widget_destroy(message_dialog);
    }
}



//statut actif
void
on_radiobutton_RL_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    statut = 0;
}


void
on_Inactif_RL_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    statut = 1;
}


void on_RL_Affecter_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *treeview_agents, *combobox_parking, *treeview_parkings;
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *selected_cin_agent;
    gchar *selected_id_parking;

    // Récupérer les widgets
    treeview_agents = lookup_widget(button, "treeviewAgent_RL");
    combobox_parking = lookup_widget(button, "comboboxParky_RL");
    treeview_parkings = lookup_widget(button, "treeviewParking_RL");

    if (!treeview_agents || !combobox_parking || !treeview_parkings) {
        g_warning("Erreur : Impossible de récupérer les widgets.\n");
        return;
    }

    // Obtenir le CIN de l'agent sélectionné dans le TreeView
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_agents));
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        g_warning("Erreur : Aucun agent sélectionné.\n");
        return;
    }
    gtk_tree_model_get(model, &iter, 0, &selected_cin_agent, -1); // Colonne 0 = CIN

    // Obtenir l'ID du parking sélectionné dans le ComboBox
    selected_id_parking = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox_parking));
    if (!selected_id_parking) {
        g_warning("Erreur : Aucun parking sélectionné.\n");
        g_free(selected_cin_agent);
        return;
    }
   
    
    // Mettre à jour le fichier parking.txt
    FILE *file = fopen("parking.txt", "r");
    FILE *temp = fopen("temp_parking.txt", "w");
    if (!file || !temp) {
        g_warning("Erreur lors de l'ouverture des fichiers.\n");
        g_free(selected_cin_agent);
        g_free(selected_id_parking);
        return;
    }

    PARKING parking;
    while (fscanf(file, "%d %s %s %d %d %d %d %f %s %d %f %d",
                  &parking.id_parking, parking.nom_parking, parking.adresse,
                  &parking.capacite, &parking.type, &parking.nb_place,
                  &parking.horaire, &parking.tarif, parking.cin_agent,
                  &parking.service_off, &parking.moyenne, &parking.statut) != EOF) {
        if (parking.id_parking == atoi(selected_id_parking)) {
            snprintf(parking.cin_agent, sizeof(parking.cin_agent), "%s", selected_cin_agent);
        }
        fprintf(temp, "%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
                parking.id_parking, parking.nom_parking, parking.adresse,
                parking.capacite, parking.type, parking.nb_place, parking.horaire,
                parking.tarif, parking.cin_agent, parking.service_off,
                parking.moyenne, parking.statut);
    }

    fclose(file);
    fclose(temp);
    remove("parking.txt");
    rename("temp_parking.txt", "parking.txt");

    // Actualiser les widgets
    on_actualiser1_RL_clicked(button, user_data); // TreeView parkings
    on_comboboxParky_RL_map(GTK_COMBO_BOX(combobox_parking)); // ComboBox des parkings
    on_treeviewAgent_RL_map(GTK_TREE_VIEW(treeview_agents)); // TreeView des agents

    g_free(selected_cin_agent);
    g_free(selected_id_parking);

    printf("Affectation réussie.\n");
}

void
on_RL_Annuler_clicked                  (GtkWidget        *button,
                                        gpointer         user_data)
{

}
void on_actualiser1_RL_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *treeview;

    // Locate the treeview widget by its name
    treeview = lookup_widget(button, "treeviewParking_RL");

    if (treeview) {
        // Clear and repopulate the treeview with the updated data
        on_treeviewParking_RL_map(GTK_TREE_VIEW(treeview));
        gtk_widget_show_all(treeview); // Forcer l'affichage de la TreeView actualisée
        printf("TreeView updated successfully.\n");
    } else {
        printf("Error: Could not find treeviewParking_RL.\n");
    }
}




void
on_actualiserAffec_RL_clicked         (GtkWidget *button, gpointer user_data) {
    GtkWidget *combobox = lookup_widget(button, "comboboxParkingSansAgent");

    if (combobox) {
        on_comboboxParky_RL_map(GTK_COMBO_BOX(combobox));
        printf("ComboBox mis à jour avec les ID des parkings sans agent.\n");
    } else {
        printf("Erreur : Impossible de trouver le ComboBox.\n");
    }



}
void on_chercher_RL_clicked(GtkWidget *button, gpointer user_data) {
    PARKING p;
    GtkWidget *idEntry;
    GtkWidget *treeview;
    GtkTreeModel *model;
    GtkTreeIter iter;
    int r;
    gboolean valid;

    // Get the ID entered by the user
    idEntry = lookup_widget(button, "idRecherche_RL");
    r = atoi(gtk_entry_get_text(GTK_ENTRY(idEntry)));

    // Search for the parking entry with the given ID
    p = chercher("parking.txt", r);
    printf("%d %s %s %d %d %d %d %.2f %s %d %.2f %d\n",
           p.id_parking, p.nom_parking, p.adresse, p.capacite,
           p.type, p.nb_place, p.horaire, p.tarif, p.cin_agent, p.service_off, p.moyenne, p.statut);

    // Get the TreeView widget
    treeview = lookup_widget(button, "treeviewParking_RL");
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    // Iterate through the TreeView model to find the matching ID
    valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        int id_parking;

        // Get the ID from the current row
        gtk_tree_model_get(model, &iter, 0, &id_parking, -1);

        // Check if the ID matches
        if (id_parking == r) {
            // Select the matching row
            GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
            gtk_tree_selection_select_iter(selection, &iter);
            break;
        }

        // Move to the next row
        valid = gtk_tree_model_iter_next(model, &iter);
    }
}






void
on_treeviewAgent_RL_realize            (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void on_treeviewParking_RL_map(GtkTreeView *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;

	if(AgentsAffecte == NULL){
		AgentsAffecte = (Cin*)malloc(sizeof(Cin) * 20);
		memset(AgentsAffecte, '0', TailleAgents * sizeof(Cin));
	}

    // Clear all existing columns before adding new ones
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *iter = columns; iter != NULL; iter = iter->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(iter->data));
    }
    g_list_free(columns);

    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        // Create the list store if it doesn't exist
        store = gtk_list_store_new(11, 
            G_TYPE_INT,    // ID Parking
            G_TYPE_STRING, // Nom Parking
            G_TYPE_STRING, // Adresse
            G_TYPE_INT,    // Capacité
            G_TYPE_STRING,    // Type
            G_TYPE_INT,    // Places
            G_TYPE_INT,    // Horaire
            G_TYPE_FLOAT,  // Tarif
            G_TYPE_STRING, // CIN Agent
            G_TYPE_FLOAT,  // Moyenne
            G_TYPE_STRING     // Statut
        );
    } else {
        gtk_list_store_clear(store);
    }

    FILE *f = fopen("parking.txt", "r");
    if (!f) {
        printf("Erreur : Impossible d'ouvrir le fichier parking.txt\n");
        return;
    }

    PARKING parking;

    while (fscanf(f, "%d %s %s %d %d %d %d %f %s %d %f %d",
                  &parking.id_parking, parking.nom_parking, parking.adresse,
                  &parking.capacite, &parking.type, &parking.nb_place,
                  &parking.horaire, &parking.tarif, parking.cin_agent,
                  &parking.service_off, &parking.moyenne, &parking.statut) != EOF) {

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 
            0, parking.id_parking,
            1, parking.nom_parking,
            2, parking.adresse,
            3, parking.capacite,
            4, parking.type ? "Prive" : "Public",
            5, parking.nb_place,
            6, parking.horaire,
            7, parking.tarif,
            8, parking.cin_agent,
            9, parking.moyenne,
            10, parking.statut ? "Inactif" : "Actif",
            -1);

		if(strcmp(parking.cin_agent, "00000000")){
			int tr = 0;
			for(unsigned int i = 0; i < nAffecte; i++){
				if(!strcmp(parking.cin_agent, AgentsAffecte[i].cin)){
					tr = 1;
					break;
				}
			}
			if(tr == 1){
				continue;
			}
			strcpy(AgentsAffecte[nAffecte].cin, parking.cin_agent);
			nAffecte++;
			if(nAffecte == TailleAgents){
				Cin* nv = realloc(AgentsAffecte, TailleAgents * 2);
				if(nv == NULL){
					g_print("Memoire indisponible\n");
					return;
				}
				AgentsAffecte = nv;
				TailleAgents *= 2;
			}
		}
    }

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Add columns to the tree view
    GtkCellRenderer *renderer;

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 0, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Nom Parking", renderer, "text", 1, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 2, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 3, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 4, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Places", renderer, "text", 5, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Horaire", renderer, "text", 6, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", 7, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("CIN Agent", renderer, "text", 8, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Moyenne", renderer, "text", 9, NULL));

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), 
        gtk_tree_view_column_new_with_attributes("Statut", renderer, "text", 10, NULL));
}

void on_treeviewAgent_RL_map(GtkTreeView *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;

	    // Clear all existing columns before adding new ones
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *iter = columns; iter != NULL; iter = iter->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(iter->data));
    }
    g_list_free(columns);
		
    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        // Create the list store if it doesn't exist
        store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    }else{
        //clear_list_store(store);
        gtk_list_store_clear(store);
    }


   
    FILE* f = fopen("Agent.txt", "r");

    Agent agent;

    while(fscanf(f,"%s %s %s %s %u %s %s %d %u %i \n",
                agent.CIN, agent.nom, agent.prenom, agent.email, &agent.sexe, agent.date_naissance, agent.lieu_naissance, &agent.num_banque,
                &agent.etat_civil, &agent.nombre_enfant) != EOF){
		int tr = 0;
		for(unsigned int i = 0; i < nAffecte; i++){
			if(!strcmp(agent.CIN, AgentsAffecte[i].cin)){
				tr = 1;
				break;
			}
		}
		if(tr == 1){
			continue;
		}
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, agent.CIN, 1, agent.nom, 2, agent.prenom, -1);
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
    




    fclose(f);

}




void on_comboboxParky_RL_map(GtkComboBox *combobox) {
    GtkListStore *store;
    GtkTreeIter iter;

    // Récupérer le modèle existant
    store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox)));

    if (!store) {
        // Créer le modèle s'il n'existe pas
        store = gtk_list_store_new(1, G_TYPE_STRING); // Une seule colonne pour les ID
        gtk_combo_box_set_model(GTK_COMBO_BOX(combobox), GTK_TREE_MODEL(store));
    } else {
        // Nettoyer le modèle existant
        gtk_list_store_clear(store);
    }

    // Ouvrir le fichier parking.txt
    FILE *f = fopen("parking.txt", "r");
    if (!f) {
        g_warning("Erreur : Impossible d'ouvrir parking.txt\n");
        return;
    }

    PARKING parking;
    while (fscanf(f, "%d %*s %*s %*d %*d %*d %*d %*f %s %*d %*f %*d", 
                  &parking.id_parking, parking.cin_agent) != EOF) {
        // Vérifier si le parking n'a pas d'agent affecté
        if (strcmp(parking.cin_agent, "00000000") == 0) {
            gchar id_str[10];
            sprintf(id_str, "%d", parking.id_parking);
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, id_str, -1);
        }
    }
    fclose(f);

    // Configurer le rendu du ComboBox
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_clear(GTK_CELL_LAYOUT(combobox)); // Supprimer les colonnes existantes
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combobox), renderer, TRUE);
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(combobox), renderer, "text", 0);
}

void on_butt_OK_clicked(GtkWidget *widget, gpointer user_data) {
    const char *service_text = ""; 
    const char *type_text = ""; 

    if (service == 1) {
        service_text = "acceptable";
    } else if (service == 2) {
        service_text = "mauvais";
    } else if (service == 3) {
        service_text = "très bien";
    } else {
        service_text = "Aucun service sélectionné";
    }

    if (oui == 1) {
        type_text = "avis";
    } else {
        type_text = "réclamation";
    }

    GtkWidget *spin_note = lookup_widget(widget, "spin_note");
    int note = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_note));

    FILE *file = fopen("reclamation.txt", "a"); 
    
    if (file != NULL) {
        fprintf(file, "%s, %s,  %d\n", 
                type_text, service_text, note);
        fclose(file); 
        g_print(" %s, %s, %d", 
                type_text, service_text, note);
GtkWidget *success_dialog;
        success_dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "Avis ajoutée avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } 
}
   


void on_radio_accept_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    service = 1;
}

void on_radio_bad_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    service = 2;
}

void on_radio_very_good_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    service = 3;
}

void on_mal_gar___toggled(GtkToggleButton *togglebutton, gpointer user_data) {
if (gtk_toggle_button_get_active(togglebutton)){
    choix[0] = 1;}
else { choix[0] = 0;
}
}
void on_probleme_paiement_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
if (gtk_toggle_button_get_active(togglebutton)){
    choix[1] = 1;}
else{ choix[1] = 0;}
}

void on_place_non_dispo_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
if (gtk_toggle_button_get_active(togglebutton)){
    choix[2] = 1;}
else{choix[2] = 0;}
}

void on_securite_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
if (gtk_toggle_button_get_active(togglebutton)){
    choix[3] = 1;}
else {choix[3] = 0;}
}

void on_autre_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    // Récupérer le widget d'entrée (entry2)
GtkWidget *entry2 = lookup_widget(GTK_WIDGET(togglebutton), "entry2");

    const gchar *texte = gtk_entry_get_text(GTK_ENTRY(entry2));

    if (gtk_toggle_button_get_active(togglebutton)) {
        choix[4] = 1;

        g_print("Problème sélectionné : %s\n", texte);
    } else {
        strcpy(probleme, "");
    }

    g_print("Problème sélectionné : %s\n", probleme);
}

void on_butt_valider_formu_clicked(GtkWidget *button, gpointer user_data) {

    GtkWidget *input1 = lookup_widget(button, "entry1");
    GtkWidget *input2 = lookup_widget(button, "numeroPlace");
    GtkWidget *calendar = lookup_widget(button, "calendar1");
    GtkWidget *entry_autre = lookup_widget(button, "entry2");

    Reclamation reclamation;

    // Initialisation explicite de tous les champs de la structure
    memset(&reclamation, 0, sizeof(Reclamation));
    strcpy(reclamation.cin, "");
    strcpy(reclamation.numeroPlace, "");
    strcpy(reclamation.date_incident, "");
    strcpy(reclamation.typeReclamation, "");

    char probleme[100] = "";

    // Récupération des entrées utilisateur
    strcpy(reclamation.cin, gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(reclamation.numeroPlace, gtk_entry_get_text(GTK_ENTRY(input2)));

    // Ajout des types de réclamations selon les choix
    if (choix[0] == 1) {
        strcat(reclamation.typeReclamation, "Véhicule mal garé; ");
    }
    if (choix[1] == 1) {
        strcat(reclamation.typeReclamation, "Problème de paiement; ");
    }
    if (choix[2] == 1) {
        strcat(reclamation.typeReclamation, "Place non disponible; ");
    }
    if (choix[3] == 1) {
        strcat(reclamation.typeReclamation, "Sécurité de véhicule; ");
    }
    if (choix[4] == 1) {
        const gchar *texte = gtk_entry_get_text(GTK_ENTRY(entry_autre));
        if (strlen(texte) > 0) {
            strcpy(probleme, texte);
            strcat(reclamation.typeReclamation, "Autre : ");
            strcat(reclamation.typeReclamation, probleme);
        } else {
            strcat(reclamation.typeReclamation, "Autre");
        }
    }

    // Récupération de la date du calendrier
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    sprintf(reclamation.date_incident, "%02d/%02d/%d", day, month + 1, year);

    // Vérification des données avant écriture
    g_print("CIN: %s\n", reclamation.cin);
    g_print("Numéro de Place: %s\n", reclamation.numeroPlace);
    g_print("Date: %s\n", reclamation.date_incident);
    g_print("Type de Réclamation: %s\n", reclamation.typeReclamation);

    // Appel de la fonction pour ajouter la réclamation
    ajouterReclamation("reclamation.txt", reclamation);

    g_print("Réclamation enregistrée\n");
GtkWidget *success_dialog;
        success_dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "Réclamation ajoutée avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } 



void on_butt_reset_formul_clicked(GtkWidget *button, gpointer user_data) {
GtkWidget *entry_cin = lookup_widget(button, "entry_cin");
    gtk_entry_set_text(GTK_ENTRY(entry_cin), "");

    // Réinitialiser le champ numéro de parking (entry)
    GtkWidget *entry_parking = lookup_widget(button, "numeroPlace");
    gtk_entry_set_text(GTK_ENTRY(entry_parking), "");

    // Réinitialiser les cases à cocher (Type de réclamation)
    GtkWidget *check_mal_gare = lookup_widget(button, "mal_gar__");
    GtkWidget *check_paiement = lookup_widget(button, "probleme_paiement");
    GtkWidget *check_place_non_dispo = lookup_widget(button, "place_non_dispo");
    GtkWidget *check_securite = lookup_widget(button, "securite");
    GtkWidget *check_autre = lookup_widget(button, "autre");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_mal_gare), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_paiement), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_place_non_dispo), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_securite), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_autre), FALSE);

    // Réinitialiser la zone de texte "Autre"
    GtkWidget *entry_autre = lookup_widget(button, "entry_autre");
    gtk_entry_set_text(GTK_ENTRY(entry_autre), "");
 FILE *file = fopen("reclamation.txt", "w");
    if (file != NULL) {
        fclose(file);
    }

    g_print("Formulaire réinitialisé et fichier de réclamations vidé\n");
GtkWidget *success_dialog;
        success_dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "Suppression avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } 



void on_radio_reclamation_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        oui = 0;
    }
}

void on_radio_avis_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        oui = 1;
    }
}

void on_butt_modifier_clicked(GtkWidget *button, gpointer user_data) {

    // Récupérer les widgets avec vérification
    GtkWidget *entry_cin = lookup_widget(GTK_WIDGET(button), "entry_cin");
    if (!entry_cin) {
        g_print("Erreur : Widget entry_cin introuvable\n");
        return;
    }

    GtkWidget *entry_parking = lookup_widget(GTK_WIDGET(button), "numeroPlace");
    if (!entry_parking) {
        g_print("Erreur : Widget numeroPlace introuvable\n");
        return;
    }

    GtkWidget *calendar = lookup_widget(GTK_WIDGET(button), "calendar1");
    if (!calendar) {
        g_print("Erreur : Widget calendar1 introuvable\n");
        return;
    }

    // Récupérer les valeurs des widgets
    const char *cin = gtk_entry_get_text(GTK_ENTRY(entry_cin));
    const char *numero_parking = gtk_entry_get_text(GTK_ENTRY(entry_parking));

    guint day, month, year;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    char date_incident[20];
    sprintf(date_incident, "%02d/%02d/%d", day, month + 1, year);

    // Ouvrir le fichier d'origine et un fichier temporaire
    FILE *file = fopen("reclamation.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    if (file == NULL || temp_file == NULL) {
        g_print("Erreur : Impossible d'ouvrir les fichiers\n");
        return;
    }

    Reclamation reclamation;
    int found = 0;

    // Parcourir les réclamations pour chercher celle à modifier
    while (fscanf(file, "%s %s %s", reclamation.cin, reclamation.numeroPlace, reclamation.date_incident) != EOF) {
        if (strcmp(reclamation.cin, cin) == 0) {
            // Mettre à jour les données
            strcpy(reclamation.numeroPlace, numero_parking);
            strcpy(reclamation.date_incident, date_incident);
            found = 1;
        }
        // Écrire dans le fichier temporaire
        fprintf(temp_file, "%s %s %s\n %s %s %d %d", reclamation.cin, reclamation.numeroPlace,reclamation.typeReclamation, reclamation.date_incident,reclamation.service,reclamation.note,reclamation.avis_ou_reclamation);
    }

    fclose(file);
    fclose(temp_file);

    // Remplacer le fichier original par le fichier temporaire
    remove("reclamation.txt");
    rename("temp.txt", "reclamation.txt");

    if (found) {
        g_print("Réclamation modifiée avec succès\n");
    } else {
        g_print("Réclamation non trouvée\n");
    }
}

void on_butt_trier_clicked(GtkWidget *button, gpointer user_data) {
    // Code pour trier
    Reclamation liste[100]; // Tableau pour stocker les réclamations (jusqu'à 100)
    int n = 0; // Nombre de réclamations
    FILE *file;

    // Ouvrir le fichier pour lire les réclamations
    file = fopen("reclamation.txt", "r");
    if (file == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier reclamation.txt\n");
        return;
    }

    // Lire les réclamations dans le tableau
while (fscanf(file, "%s %s %s %s %d %d",
              liste[n].cin,               // %s pour une chaîne
              liste[n].typeReclamation,   // %s
              liste[n].numeroPlace,       // %s
              liste[n].date_incident,     // %s
              &liste[n].note,             // %d pour un entier
              &liste[n].avis_ou_reclamation) != EOF) { // %d
    n++;
}
    fclose(file);

    // Trier les réclamations par note (tri à bulles)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (liste[j].note < liste[j + 1].note) { // Tri par ordre décroissant
                Reclamation temp = liste[j];
                liste[j] = liste[j + 1];
                liste[j + 1] = temp;
            }
        }
    }

    // Réécrire les réclamations triées dans le fichier
    file = fopen("reclamation.txt", "w");
    if (file == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier pour écriture\n");
        return;
    }

    for (int i = 0; i < n; i++) {
fprintf(file, "%s %s %s %s %d %d\n",
        liste[i].cin,               // %s pour une chaîne
        liste[i].typeReclamation,   // %s
        liste[i].numeroPlace,       // %s
        liste[i].date_incident,     // %s
        liste[i].note,              // %d pour un entier
        liste[i].avis_ou_reclamation);
    }
    fclose(file);

    g_print("Les réclamations/avis ont été triés par note avec succès\n");
}

int compare_reclamations(const void *a, const void *b) {
    Reclamation *rec_a = (Reclamation *)a;
    Reclamation *rec_b = (Reclamation *)b;
    return (rec_a->note - rec_b->note); // Tri par note croissante
}

void on_treeviewMF_map(GtkTreeView *treeview) 
{
   
    GtkListStore *store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(6,
            G_TYPE_STRING, // CIN
            G_TYPE_STRING, // Type de Réclamation
            G_TYPE_STRING, // Numéro de Place
            G_TYPE_STRING, // Date
            G_TYPE_STRING, // Service
            G_TYPE_INT     // Note
        );
    } else {
        gtk_list_store_clear(store);
    }

    // Open the file where the reclamations are stored
    FILE *f = fopen("reclamation.txt", "r");
    if (!f) {
        printf("Erreur : Impossible d'ouvrir le fichier reclamation.txt\n");
        return;
    }

    Reclamation reclamations[100]; // Tableau pour stocker les réclamations
    int count = 0;

    // Lire les réclamations dans le fichier et les stocker dans le tableau
    while (fscanf(f, "%s %s %s %s %s %d", 
            reclamations[count].cin, 
            reclamations[count].typeReclamation, 
            reclamations[count].numeroPlace, 
            reclamations[count].date_incident, 
            reclamations[count].service, 
            &reclamations[count].note) == 6) {
        count++;
    }

    fclose(f);

    // Trier les réclamations (ici par note, tu peux ajuster selon ce que tu veux trier)
    qsort(reclamations, count, sizeof(Reclamation), compare_reclamations);

    // Ajouter les réclamations triées dans le store
    for (int i = 0; i < count; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, reclamations[i].cin,
            1, reclamations[i].typeReclamation,
            2, reclamations[i].numeroPlace,
            3, reclamations[i].date_incident,
            4, reclamations[i].service,
            5, reclamations[i].note,
            -1);
    }

    // Appliquer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);

    // Ajouter les colonnes (si elles ne sont pas déjà présentes)
    if (g_list_length(gtk_tree_view_get_columns(treeview)) == 0) {
        GtkCellRenderer *renderer;

        // Ajout des colonnes comme précédemment...
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 0, NULL));
 // Column Type de Réclamation
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("Type de Réclamation", renderer, "text", 1, NULL));

        // Column Numéro de Place
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("Numéro de Place", renderer, "text", 2, NULL));

        // Column Date
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 3, NULL));

        // Column Service
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("Service", renderer, "text", 4, NULL));

        // Column Note
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),
            gtk_tree_view_column_new_with_attributes("Note", renderer, "text", 5, NULL));
  


        // Répéter pour les autres colonnes
    }
}

