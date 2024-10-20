#pragma once
#include "en_commun.h"

typedef struct
{
    GtkWidget* textview;
    commune position;
    int height; //Longueur
    int width; //Largeur
    gboolean edit;
    gboolean cursor;
    int lmargin;
} TextView_object;


TextView_object* init_text_view()
{
    TextView_object* text_view = NULL;
    //Allocation memoire
    text_view = (TextView_object*)malloc(sizeof(TextView_object));
    if (!text_view)
    {
        g_print("Echec d'allocation memoire"); //Message d'erreur
        exit(-1);
    }
    text_view->height = 10;
    text_view->width = 20;
    text_view->position.posx = 0;
    text_view->position.posy = 0;
    text_view->edit = TRUE;
    text_view->cursor = TRUE;
    text_view->lmargin = 0;

    return ((TextView_object*)text_view); //retourner l'objet
}



TextView_object* create_text_view(TextView_object* text_view)
{
    // Création du conteneur ScrolledWindow
    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, text_view->width, text_view->height);

    // Création du TextView
    text_view->textview = gtk_text_view_new();

    //Assurer le retour charriot
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view->textview), GTK_WRAP_WORD_CHAR);

    // Récupération du GtkTextBuffer
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view->textview));

    // Ajout du texte
    gtk_text_buffer_set_text(buffer, "Bonjour, ceci est un exemple de texte dans un TextView", -1);

    // Ajout du TextView au ScrolledWindow
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view->textview);

    // Ajout du ScrolledWindow au conteneur parent
    gtk_fixed_put(GTK_FIXED(text_view->position.container), scrolled_window, text_view->position.posx, text_view->position.posy);

    //GtkTextIter iter;
    //gtk_text_buffer_get_start_iter(buffer, &iter);

    //Texte est modifiable ou non
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view->textview), text_view->edit);
    //Voir ou non le curseur
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view->textview), text_view->cursor);
    //Une indentation a gauche
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view->textview), text_view->lmargin);

    return ((TextView_object*)text_view); //Retourner l'objet cree

}

TextView_object* set_proprietyview(TextView_object* cb, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
        {
            cb->position.posx = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "y") == 0)
        {
            cb->position.posy = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "width") == 0)
        {
            cb->width = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "height") == 0)
        {
            cb->height = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "editable") == 0)
        {
            //cb->edit = atoi(liste->valeur);
            if (strcmp(liste->valeur, "true") == 0) cb->edit = TRUE;
            else if (strcmp(liste->valeur, "false") == 0) cb->edit = FALSE;
        }
        if (strcmp(liste->attribut, "lmargin") == 0)
        {
            cb->lmargin = atoi(liste->valeur);
        }
        liste = liste->suivant;
    }
    return cb;
}


void onbuttontxtview(GtkButton* button, gpointer data)
{
    GtkTextBuffer* buffer;
    GtkTextIter start, end;
    gchar* text;
    GtkWidget* dialog;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(data));
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(data))), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Vous avez entre : %s", text);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    g_free(text);
}


//g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked_textview), text_view->textview);