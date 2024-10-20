#pragma once
#include "en_commun.h"

typedef struct Combo_box_item
{
    char* value; //le label de l element
    struct Combo_box_item* next; //pointeur sur suivant
} Combo_box_item;

typedef struct
{
    GtkWidget* combo;
    commune position;
    int width;
    int height;
    Combo_box_item* items;
    int direction;
    int entry;
} Combo_box_object;

typedef gboolean(*GtkComboBoxRowSeparatorFunc) (GtkTreeModel* model, GtkTreeIter* iter, gpointer data);


// Fonction de rappel pour la gestion de l'événement clavier
gboolean on_key_pressed(GtkWidget* widget, GdkEventKey* event, gpointer data)
{
    GtkComboBox* combo_box = GTK_COMBO_BOX(data);
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_m))
    {
        gtk_combo_box_popup(combo_box); // Affiche la liste déroulante
        return TRUE; // Empêche le widget de traiter cet événement
    }
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_Y))
    {
        gint active = gtk_combo_box_get_active(combo_box);
        if (active >= 0)
            gtk_combo_box_set_active(combo_box, active); // Sélectionne l'élément actif
        return TRUE; // Empêche le widget de traiter cet événement
    }
    return FALSE;
}


void on_popup_shown(GtkWidget* widget, gpointer data)
{
    GtkAllocation alloc;
    gint x, y, width, height;
    gtk_widget_get_allocation(widget, &alloc);
    x = alloc.x;
    y = alloc.y;
    width = alloc.width;
    height = alloc.height;
    // Récupération des coordonnées de la fenêtre parente
    GtkWidget* toplevel = gtk_widget_get_toplevel(GTK_WIDGET(widget));
    gint toplevel_x, toplevel_y, toplevel_width, toplevel_height;
    gtk_window_get_position(GTK_WINDOW(toplevel), &toplevel_x, &toplevel_y);
    gtk_window_get_size(GTK_WINDOW(toplevel), &toplevel_width, &toplevel_height);
    // Calcul de la hauteur disponible en dessous de la combobox
    gint space_below = toplevel_height - (y + height + toplevel_y);
    // Si l'espace disponible en dessous est insuffisant, on affiche le menu vers le haut
    if (space_below < 0)
    {
        //dessiner une ligne de séparation entre les éléments de la liste
        gtk_combo_box_set_row_separator_func(GTK_COMBO_BOX(widget), (GtkComboBoxRowSeparatorFunc)gtk_false, NULL, NULL);
        gtk_combo_box_set_popup_fixed_width(GTK_COMBO_BOX(widget), width);
    }
}
Combo_box_object* init_combo_box()
{
    //Allocation memoire
    Combo_box_object* cb = g_new(Combo_box_object, 1);

    if (!cb)
    {
        g_print("l'allocation a echouée\n");//Message d'erreur
        exit(-1);
    }
    cb->position.posx = 0;
    cb->position.posy = 0;
    cb->width = 50;
    cb->height = 10;
    cb->direction = 1;
    cb->entry = 0;
    cb->items = NULL;

    return ((Combo_box_object*)cb); //retourner l'objet
}




Combo_box_object* create_combo_box(Combo_box_object* cb)
{
    //Créer la liste déroulante
    if (cb->entry == 0) cb->combo = gtk_combo_box_text_new();
    else cb->combo = gtk_combo_box_text_new_with_entry();
    //gtk_widget_set_name(cb->combo, "combo");
    gtk_widget_set_sensitive(cb->combo, TRUE);
    gtk_widget_set_size_request(cb->combo, cb->width, cb->height);
    gtk_fixed_put(GTK_FIXED(cb->position.container), cb->combo, cb->position.posx, cb->position.posy);


    Combo_box_item* item = cb->items;
    while (item != NULL)
    {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cb->combo), item->value);
        item = item->next;
    }

    //pour afficher les elements horizontalement
    if (cb->direction == 0) gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(cb->combo), 200);

    // Ajout des événements clavier au widget
    gtk_widget_add_events(cb->combo, GDK_KEY_PRESS_MASK);

    if (cb->entry == 0) gtk_combo_box_set_active(GTK_COMBO_BOX(cb->combo), 0);

    // Connexion de la gestion des événements clavier
    g_signal_connect(cb->combo, "key-press-event", G_CALLBACK(on_key_pressed), cb->combo);

    // Connexion du signal "popup-menu" pour afficher le menu vers le haut si nécessaire
    g_signal_connect(cb->combo, "popup-menu", G_CALLBACK(on_popup_shown), NULL);

    return cb; //Retourner l'objet
}



Combo_box_object* set_proprietycombo(Combo_box_object* cb, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)  cb->position.posx = atoi(liste->valeur);
        if (strcmp(liste->attribut, "y") == 0)	cb->position.posy = atoi(liste->valeur);
        if (strcmp(liste->attribut, "width") == 0)	cb->width = atoi(liste->valeur);
        if (strcmp(liste->attribut, "height") == 0)	 cb->height = atoi(liste->valeur);
        if (strcmp(liste->attribut, "item") == 0)
        {
            Combo_box_item* item = g_new(Combo_box_item, 1);
            item->value = (char*)malloc((strlen(liste->valeur) + 1) * sizeof(char));
            strcpy(item->value, liste->valeur);
            item->next = NULL;
            if (cb->items == NULL)	cb->items = item;
            else
            {
                Combo_box_item* current_item = cb->items;
                while (current_item->next != NULL)   current_item = current_item->next;
                current_item->next = item;
            }
        }
        if (strcmp(liste->attribut, "direction") == 0) cb->direction = atoi(liste->valeur);
        if (strcmp(liste->attribut, "entry") == 0) cb->entry = atoi(liste->valeur);
        liste = liste->suivant;
    }
    return cb;
}





static void add_element(GtkButton* button, gpointer data)
{
    Combo_box_object* combo_box_obj = (Combo_box_object*)data;
    // Récupération du GtkEntry intégré dans le GtkComboBoxText
    GtkEntry* entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_box_obj->combo)));
    // Récupération du texte entré dans l'entrée GtkEntry
    const gchar* text = gtk_entry_get_text(entry);
    // Ajout du texte au GtkComboBoxText
    if (text != NULL && text[0] != '\0')
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo_box_obj->combo), NULL, text);
    // Mise à jour du texte de l'entrée GtkEntry
    gtk_entry_set_text(entry, "");
}




static void remove_element(GtkWidget* widget, gpointer data)
{
    Combo_box_object* combo_box = (Combo_box_object*)data;
    gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box->combo));
    printf("test :  %d\n", active);
    // Récupération du GtkEntry intégré dans le GtkComboBoxText
    GtkEntry* entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_box->combo)));
    if (active != -1)
    {
        printf("khraa\n");
        gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box->combo));
        gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(combo_box->combo), active);
        if (text != NULL) gtk_entry_set_text(entry, "");
    }
}







//static void combo_box_changed(GtkWidget* widget, gpointer data)
//{
//    Combo_box_object* combo_box = (Combo_box_object*)data;
//    gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box->combo));
//    if (active != -1)
//    {
//        gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box->combo));
//
//        // Créer une boîte de dialogue personnalisée avec le texte sélectionné
//        GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(data))),
//            GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
//            "Vous avez sélectionné : %s", text);
//
//        // Afficher la boîte de dialogue et attendre que l'utilisateur la ferme
//        gtk_dialog_run(GTK_DIALOG(dialog));
//
//        // Détruire la boîte de dialogue
//        gtk_widget_destroy(dialog);
//
//        g_free(text);
//    }
//}


void show_combochanged(GList* group)
{
    for (GSList* comb = group; comb != NULL; comb = g_slist_next(comb))
    {
        Combo_box_object* combo_box = (Combo_box_object*)comb->data;
        // Vérifier si le bouton est sélectionné
        gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box->combo));
        if (active != -1)
        {
            gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box->combo));

            // Créer une boîte de dialogue personnalisée avec le texte sélectionné
            GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(comb->data))),
                GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                "Vous avez sélectionné : %s", text);

            // Afficher la boîte de dialogue et attendre que l'utilisateur la ferme
            gtk_dialog_run(GTK_DIALOG(dialog));

            // Détruire la boîte de dialogue
            gtk_widget_destroy(dialog);

            g_free(text);
        }
    }
}
void on_button_combo(GtkButton* button, gpointer user_data)
{
    // Appeler la fonction show_checked_buttons()
    GList* button_list = (GList*)user_data;
    show_combochanged(button_list);
}



void show_combochanged1(GList* group)
{
    for (GSList* comb = group; comb != NULL; comb = g_slist_next(comb))
    {
        Combo_box_object* combo_box = (Combo_box_object*)comb->data;
        // Vérifier si le bouton est sélectionné
        gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box->combo));
        if (active != -1)
        {
            gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box->combo));

            // Créer une boîte de dialogue personnalisée avec le texte sélectionné
            GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(comb->data))),
                GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                "Vous avez sélectionné : %s", text);

            // Afficher la boîte de dialogue et attendre que l'utilisateur la ferme
            gtk_dialog_run(GTK_DIALOG(dialog));

            // Détruire la boîte de dialogue
            gtk_widget_destroy(dialog);

            g_free(text);
        }
    }
}
void on_button_add(GtkButton* button, gpointer user_data)
{
    // Appeler la fonction show_checked_buttons()
    GList* button_list = (GList*)user_data;
    show_combochanged1(button_list);
}



void show_combochanged2(GList* group)
{
    for (GSList* comb = group; comb != NULL; comb = g_slist_next(comb))
    {
        Combo_box_object* combo_box = (Combo_box_object*)comb->data;
        // Vérifier si le bouton est sélectionné
        gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box->combo));
        if (active != -1)
        {
            gchar* text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box->combo));

            // Créer une boîte de dialogue personnalisée avec le texte sélectionné
            GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(comb->data))),
                GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                "Vous avez sélectionné : %s", text);

            // Afficher la boîte de dialogue et attendre que l'utilisateur la ferme
            gtk_dialog_run(GTK_DIALOG(dialog));

            // Détruire la boîte de dialogue
            gtk_widget_destroy(dialog);

            g_free(text);
        }
    }
}
void on_button_remove(GtkButton* button, gpointer user_data)
{
    // Appeler la fonction show_checked_buttons()
    GList* button_list = (GList*)user_data;
    show_combochanged2(button_list);
}