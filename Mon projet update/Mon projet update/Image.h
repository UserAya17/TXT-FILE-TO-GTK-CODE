#pragma once
#include <gtk/gtk.h>
#include <stdio.h>
#include "en_commun.h"


typedef struct image
{
    float width;
    float height;
    char url[20];
    GtkWidget* image;
    GtkWidget* container; //conteneur d'une entrée.
    float x;
    float y;
}image;



image* initialiser_valeurs_image()
{
    image* im = (image*)malloc(sizeof(image));
    if (!im) g_print("erreur");
    im->container = NULL;
    im->image = NULL;
    im->width = 100;
    im->height = 100;
    strcpy(im->url, "im.jpg");
    im->x = 20;
    im->y = 100;
    return (image*)im;
}





void add_image(image* im, GtkWidget* conteneur)
{
    GdkPixbuf* pixbuf;
    pixbuf = gdk_pixbuf_new_from_file(im->url, NULL);
    pixbuf = gdk_pixbuf_scale_simple(pixbuf, im->width, im->height, GDK_INTERP_BILINEAR);
    im->image = gtk_image_new_from_pixbuf(pixbuf);

    GtkWidget* fix = fix = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(conteneur), fix);
    gtk_fixed_put(GTK_FIXED(fix), im->image, im->x, im->y);
}









image* set_propriety_image(image* var, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
        {
            var->x = atoi(liste->valeur);
        }
        else if (strcmp(liste->attribut, "y") == 0)
        {
            var->y = atoi(liste->valeur);
        }
        else if (strcmp(liste->attribut, "width") == 0)
        {
            var->width = atoi(liste->valeur);
        }
        else if (strcmp(liste->attribut, "height") == 0)
        {
            var->height = atoi(liste->valeur);
        }
        else if (strcmp(liste->attribut, "url") == 0)
        {
            strcpy(var->url, liste->valeur);
        }
        liste = liste->suivant;
    }
    return var;
}