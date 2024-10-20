//#ifndef NEW_FRAME_H
//#define NEW_FRAME_H
//#include <stdio.h>
//#include <gtk/gtk.h>
//#include <string.h>
//#include "en_commun.h"
//
//typedef struct
//{
//    commune commune;
//    GtkWidget* frame;
//    char label[20];//nom de la frame
//    taille taille;
//    GtkShadowType type; //type style du cadre
//}Frame_object;
//
//GtkWidget* create_frame(Frame_object* frame)
//{
//    frame->frame = gtk_frame_new(frame->label);
//    gtk_widget_set_size_request(frame->frame, frame->taille.width, frame->taille.height);
//    gtk_frame_set_shadow_type(GTK_FRAME(frame->frame), frame->type);
//    //gtk_frame_set_shadow_visible(GTK_FRAME(frame->frame), TRUE);
//    return frame;
//}
//Frame_object* init_frame_default()
//{
//    Frame_object* frame = g_new(Frame_object, 1);
//    strcpy(frame->label, "label par defaut");
//    frame->commune.posx = 0;
//    frame->commune.posy = 0;
//    frame->taille.width = 50;
//    frame->taille.height = 50;
//    frame->type = GTK_SHADOW_NONE;
//    if (!frame)
//    {
//        printf("\nErreur d'allocation memoire");
//        exit(1);
//    }
//    return frame;
//}
//Frame_object* set_propriety_frame(Frame_object* frame, cellule_propriete* liste)
//{
//    while (liste != NULL)
//    {
//        if (strcmp(liste->attribut, "x") == 0)
//            frame->commune.posx = atoi(liste->valeur);
//        if (strcmp(liste->attribut, "y") == 0)
//            frame->commune.posy = atoi(liste->valeur);
//        if (strcmp(liste->attribut, "label") == 0)
//            strcpy(frame->label, liste->valeur);
//        if (strcmp(liste->attribut, "width") == 0)
//            frame->taille.width = atoi(liste->valeur);
//        if (strcmp(liste->attribut, "height") == 0)
//            frame->taille.height = atoi(liste->valeur);
//        if (strcmp(liste->attribut, "type") == 0)
//        {
//            if (strcmp(liste->valeur, "GTK_SHADOW_NONE") == 0)
//                frame->type = GTK_SHADOW_NONE;
//            if (strcmp(liste->valeur, "GTK_SHADOW_IN") == 0)
//                frame->type = GTK_SHADOW_IN;
//            if (strcmp(liste->valeur, "GTK_SHADOW_OUT") == 0)
//                frame->type = GTK_SHADOW_OUT;
//            if (strcmp(liste->valeur, "GTK_SHADOW_ETCHED_IN") == 0)
//                frame->type = GTK_SHADOW_ETCHED_IN;
//            if (strcmp(liste->valeur, "GTK_SHADOW_ETCHED_OUT") == 0)
//                frame->type = GTK_SHADOW_ETCHED_OUT;
//        }
//        liste = liste->suivant;
//    }
//    return frame;
//}
//
//#endif //NEW_FRAME_H




#ifndef NEW_FRAME_H
#define NEW_FRAME_H
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "en_commun.h"

typedef struct
{
    // GtkWidget* container;//L'objet p�re
    GtkWidget* frame;
    char label[20];//nom de la frame
    taille taille;
    //int x; // la position horizontale
    //int y; // la position verticale
    commune commune;
    GtkShadowType type; //type style du cadre
}Frame_object;

GtkWidget* create_frame(Frame_object* frame)
{
    frame->frame = gtk_frame_new(frame->label);
    gtk_widget_set_size_request(frame->frame, frame->taille.width, frame->taille.height);
    //gtk_frame_set_shadow_type(GTK_FRAME(frame->frame), type);
    //gtk_frame_set_shadow_visible(GTK_FRAME(frame->frame), TRUE);
    return frame;
}
Frame_object* init_frame_default()
{
    Frame_object* frame = g_new(Frame_object, 1);
    strcpy(frame->label, "");
    frame->commune.posx = 0;
    frame->commune.posy = 0;
    frame->taille.width = 50;
    frame->taille.height = 50;
    frame->type = GTK_SHADOW_NONE;
    if (!frame)
    {
        printf("\nErreur d'allocation memoire");
        exit(1);
    }
    return frame;
}
Frame_object* set_propriety_frame(Frame_object* frame, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
            frame->commune.posx = atoi(liste->valeur);
        if (strcmp(liste->attribut, "y") == 0)
            frame->commune.posy = atoi(liste->valeur);
        if (strcmp(liste->attribut, "label") == 0)
            strcpy(frame->label, liste->valeur);
        if (strcmp(liste->attribut, "width") == 0)
            frame->taille.width = atoi(liste->valeur);
        if (strcmp(liste->attribut, "height") == 0)
            frame->taille.height = atoi(liste->valeur);
        liste = liste->suivant;
    }
    return frame;
}

#endif //NEW_FRAME_H