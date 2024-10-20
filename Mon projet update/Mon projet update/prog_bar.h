#pragma once
#ifndef NEW_PROG_BAR_H
#define NEW_PROG_BAR_H
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "en_commun.h"

typedef struct {
    commune commune;
    GtkProgressBar* progressbar;
    int temps_entre_trans; //temps entre les transitions
    char label[20]; //label de la barre
    int vitesse; // la vitesse de basculement dans le va et vient
    int progress; //le nombre de fois que la barre va bouger pour atteindre sa fin (un seul parcours)
    float fraction;
    float step;
    int etat; //transition ou deplacement ou un seul parcours
}ProgressBar_object;


ProgressBar_object* init_prog_bar_default()
{
    ProgressBar_object* p_bar = g_new(ProgressBar_object, 1);
    p_bar->commune.posx = 0;
    p_bar->commune.posy = 0;
    p_bar->vitesse = 50;
    strcpy(p_bar->label, "chargement...");
    p_bar->fraction = 0.5;
    p_bar->temps_entre_trans = 100;
    p_bar->step = 0.01;
    p_bar->etat = 1;
    if (!p_bar)
    {
        g_print("\nErreur d'allocation memoire");
        exit(1);
    }
    return(ProgressBar_object*)p_bar;
}
ProgressBar_object* create_progress_bar(ProgressBar_object* p_bar)
{
    p_bar->progressbar = gtk_progress_bar_new();
    if (p_bar->etat == 3)
    {
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p_bar->progressbar), p_bar->label);
    }
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(p_bar->progressbar), TRUE);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p_bar->progressbar), p_bar->fraction);
    return p_bar;
}
ProgressBar_object* set_propriety_prog(ProgressBar_object* p_bar, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
            p_bar->commune.posx = atoi(liste->valeur);
        if (strcmp(liste->attribut, "y") == 0)
            p_bar->commune.posy = atoi(liste->valeur);
        if (strcmp(liste->attribut, "label") == 0)
            strcpy(p_bar->label, liste->valeur);
        if (strcmp(liste->attribut, "vitesse") == 0)
            p_bar->vitesse = atoi(liste->valeur);
        if (strcmp(liste->attribut, "progress") == 0)
            p_bar->progress = atoi(liste->valeur);
        if (strcmp(liste->attribut, "fraction") == 0)
            p_bar->fraction = atof(liste->valeur);
        if (strcmp(liste->attribut, "step") == 0)
            p_bar->step = atof(liste->valeur);
        if (strcmp(liste->attribut, "etat") == 0)
        {
            if (strcmp(liste->valeur, "parcours") == 0)  p_bar->etat = 1;
            else if (strcmp(liste->valeur, "transaction") == 0)  p_bar->etat = 2;
            else if (strcmp(liste->valeur, "deplacement") == 0)  p_bar->etat = 3;
            else  p_bar->etat = 0;
        }
        liste = liste->suivant;
    }
    return p_bar;
}

gboolean update_progressbar(GtkProgressBar* progressbar)
{
    // Incrémenter la barre de progression de 0.01
    gdouble fraction = gtk_progress_bar_get_fraction(progressbar) + 0.02;
    if (fraction > 0.8) fraction = 0.0;
    gtk_progress_bar_set_fraction(progressbar, fraction);
    return TRUE;
}
/*description : cette fonction permet de parcourir la barre une seul fois
 entree : l'objet barre et une variable qui presente
            combien de fois la barre va faire un saut
 sortie : void (le mouvement de la barre)
 */
void un_seul_parcours(ProgressBar_object* progressbar, gint progress)
{
    int i;
    for (i = 0; i <= progress; i++)
    {
        //à chaque fois la valeur de la fraction va changer dans un bout de temps
        gdouble fraction = (gdouble)i / 10.0;
        gchar* text = g_strdup_printf("%.0f %%", fraction * 100);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar->progressbar), fraction);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar->progressbar), text);
        g_free(text);
        while (gtk_events_pending())
        {
            gtk_main_iteration();
        }
        g_usleep(500000);
    }
}
/*description : cette fonction permet à la barre va se rafraichir
            dans un bout de temps (temps_entre_trans déjà définit dans la structure)
 entree : l'objet barre
 sortie : void (la transaction de la barre de la barre)
 */
void transaction(ProgressBar_object* progressbar)
{
    gdouble fraction = 0.0;
    g_timeout_add(progressbar->temps_entre_trans, (GSourceFunc)update_progressbar, progressbar->progressbar);
}
/*description : cette fonction permet à la barre va se deplacer ( va et vient)
                (Cas de chargement) avec une vitesse (vitesse déjà définit dans la structure)
 entree : l'objet barre
 sortie : void (le deplacement de la barre de la barre)
 */
void deplacement(ProgressBar_object* progressbar)
{
    g_timeout_add(progressbar->vitesse, (GSourceFunc)gtk_progress_bar_pulse, progressbar->progressbar);
}

//transaction(progressbar->progressbar , 50);
//un_seul_parcours(progressbar,5);
//deplacement(progressbar);

#endif //NEW_PROG_BAR_H
