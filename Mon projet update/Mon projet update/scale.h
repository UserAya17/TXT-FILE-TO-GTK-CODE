#pragma once
#include <gtk/gtk.h>
#include "en_commun.h"


typedef struct
{
    commune commune;
    GtkAdjustment* adjustment;///un objet
    GtkWidget* scale;///Scale
    double valeur_init;///la valeur pour initialiser scale
    double min;///la valeur la plus basse que l’ajustement peut contenir
    double max;///la valeur la plus haute que l’ajustement peut contenir
    double pagesize;
    double page_inc;
    int digits;///le nombre de décimales affichées dans la valeur
    gboolean draw;///pour chiffrer la valeur
    int orientation;///horiz 0 ou vert 1
    int step;///Le pas
    int position; // 1 - 2 - 3 - 4
    taille taille;
}Scale_object;

Scale_object* init_default_scale()
{
    Scale_object* scale = (Scale_object*)malloc(sizeof(Scale_object));
    scale->adjustment == (GtkAdjustment*)malloc(sizeof(GtkAdjustment));
    if (!scale)
    {
        printf("\nErreur d'allocation memoire du scale");
        exit(1);
    }
    if (!scale->adjustment)
        printf("\nErreur d'allocation memoire du adjustment du scale");
    scale->commune.posx = 10;
    scale->commune.posy = 10;
    scale->valeur_init = 50.0;
    scale->min = 0.0;
    scale->max = 100.0;
    scale->step = 1.0;
    scale->page_inc = 1.0;
    scale->pagesize = 0.0;
    scale->orientation = 1;
    scale->draw = TRUE;
    scale->digits = 0;
    scale->taille.width = 200;
    scale->taille.height = 50;
    return (Scale_object*)scale;
}

Scale_object* create_scale(Scale_object* scale)
{
    scale->adjustment = gtk_adjustment_new(scale->valeur_init, scale->min, scale->max, scale->step, scale->page_inc, scale->pagesize);

    if (scale->orientation == 1) scale->scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, scale->adjustment);
    else scale->scale = gtk_scale_new(GTK_ORIENTATION_VERTICAL, scale->adjustment);
    gtk_scale_set_digits(GTK_SCALE(scale->scale), scale->digits);
    gtk_scale_set_draw_value(GTK_SCALE(scale->scale), scale->draw);
    if (scale->position == 1)
        gtk_scale_set_value_pos(GTK_SCALE(scale->scale), GTK_POS_TOP);
    else if (scale->position == 2)
        gtk_scale_set_value_pos(GTK_SCALE(scale->scale), GTK_POS_LEFT);
    else if (scale->position == 3)
        gtk_scale_set_value_pos(GTK_SCALE(scale->scale), GTK_POS_RIGHT);
    else
        gtk_scale_set_value_pos(GTK_SCALE(scale->scale), GTK_POS_BOTTOM);
    gtk_widget_set_size_request(scale->scale, scale->taille.width, scale->taille.height);
    return (Scale_object*)scale;
}

// Fonction de rappel pour la modification de la valeur du scale
void on_scale_value_changed(GtkRange* range, gpointer user_data) {
    // Obtenir la valeur actuelle sélectionnée
    gdouble value = gtk_range_get_value(range);
    g_print("Nouvelle valeur du scale : %.2f\n", value);
}

Scale_object* set_propriety_scale(Scale_object* scale, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
            scale->commune.posx = atoi(liste->valeur);
        if (strcmp(liste->attribut, "y") == 0)
            scale->commune.posy = atoi(liste->valeur);
        if (strcmp(liste->attribut, "valeur_init") == 0)
            scale->valeur_init = atof(liste->valeur);
        if (strcmp(liste->attribut, "min") == 0)
            scale->min = atof(liste->valeur);
        if (strcmp(liste->attribut, "max") == 0)
            scale->max = atof(liste->valeur);
        if (strcmp(liste->attribut, "step") == 0)
            scale->step = atof(liste->valeur);
        if (strcmp(liste->attribut, "orientation") == 0)
            scale->orientation = atoi(liste->valeur);
        if (strcmp(liste->attribut, "draw") == 0)
        {
            if (strcmp(liste->valeur, "true") == 0)
                scale->draw = TRUE;
            else scale->draw = FALSE;
        }
        if (strcmp(liste->attribut, "digits") == 0)
            scale->digits = atoi(liste->valeur);
        if (strcmp(liste->attribut, "width") == 0)
            scale->taille.width = atoi(liste->valeur);
        if (strcmp(liste->attribut, "height") == 0)
            scale->taille.height = atoi(liste->valeur);
        liste = liste->suivant;
    }
    return (Scale_object*)scale;
}



void on_button_scale(GtkButton* button, gpointer user_data) {
    GtkRange* scale = GTK_RANGE(user_data);
    gdouble value = gtk_range_get_value(scale);
    g_print("La valeur de la scale est : %f\n", value);
}

