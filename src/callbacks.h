#include <gtk/gtk.h>


void
on_HS_rb_femme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_HS_supprimer_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_HS_bt_status_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_HS_Filtre_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_HS_Sexe_toggled                     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_HS_confirmer_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_notif_sms_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RB_notif_email_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RB_confirmer_bouton_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_sexe_h_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RB_sexe_f_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RB_modifier_bouton_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_supprimer_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_chercher_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_totalizer_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RB_afficher_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_buttonCO_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_BCom_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_buttonR_clicked                  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_BR___clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_Affecter_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_Annuler_clicked                  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Rl_buttonSupp_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_buttonMod_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_buttonAdd_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_HS_bt_modifier_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview1_map                       (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_treeview2_map                       (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_RB_tr_map                           (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_RB_ville_map                        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_Auth_conn_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_Auth_cree_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button70_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RL_BCom_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radiobutton_RL_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Inactif_RL_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_RL_buttonR_clicked                  (GtkWidget        *button,
                                        gpointer         user_data);

void
on_RL_Annuler_clicked                  (GtkWidget        *button,
                                        gpointer         user_data);

void
on_RL_Affecter_clicked                 (GtkWidget        *button,
                                        gpointer         user_data);

void
on_actualiserAffec_RL_clicked          (GtkWidget        *button,
                                        gpointer         user_data);

void
on_treeviewParking_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_chercher_RL_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_RL_buttonMod_clicked                (GtkWidget        *button,
                                        gpointer         user_data);

void
on_Rl_buttonSupp_clicked               (GtkWidget        *button,
                                        gpointer         user_data);

void
on_actualiser1_RL_clicked              (GtkWidget        *button,
                                        gpointer         user_data);

void
on_treeviewParking_RL_realize          (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_treeviewAgent_RL_realize            (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_treeviewParking_RL_map              (GtkTreeView* treeview);

void
on_treeviewAgent_RL_map                (GtkTreeView* treeview);

void
on_comboboxParky_RL_map                (GtkComboBox *combobox);

void
on_button2_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button5_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void on_button6_clicked(GtkWidget *widget, gpointer user_data);
void on_butt_OK_clicked(GtkWidget *widget, gpointer user_data);
void on_radio_accept_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radio_bad_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radio_very_good_toggled(GtkToggleButton *togglebutton, gpointer user_data);



void on_valider_cin_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_mal_gar___toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_probleme_paiement_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_place_non_dispo_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_securite_toggled                    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_autre_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void on_butt_reset_formul_clicked(GtkWidget *button, gpointer user_data);

void on_butt_modifier_clicked(GtkWidget *button, gpointer user_data);
void on_butt_trier_clicked(GtkWidget *button, gpointer user_data);
void on_butt_supprimer_clicked(GtkWidget *button, gpointer user_data);



void
on_butt_valider_formu_clicked          (GtkWidget       *button,
                                        gpointer         user_data);


void
on_radio_reclamation_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_avis_toggled                  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_treeviewMF_map(GtkTreeView *treeview);

