#include <gtk/gtk.h>
#include <stdio.h>
//structure de box
#include "en_commun.h"
typedef struct box
{
    GtkOrientation style;//0 vert 1 horiz
    float space;
    short pack; //0 -> 1 <- 
    gboolean same_size; //child widgets should have the same size 
    gboolean expand; //the child widget should expand to fill the available space 
    gboolean fill;// in the direction perpendicular
    guint padding; // between the child widget and its neighbors
    taille taille;
    gboolean fixed;
    GtkWidget* box;
    GtkPolicyType hs;   //scroll bar horizontal
    GtkPolicyType vs;   //scroll bar vertical
}box;







box* initialiser_valeurs_box()
{
    box* bx = (box*)malloc(sizeof(box));

    bx->style = 1;
    bx->space = 0;
    bx->pack = 0;
    bx->same_size = FALSE;
    bx->expand = FALSE;
    bx->fill = FALSE;
    bx->padding = 20;
    return (box*)bx;
}

//
//box* set_propriety_box(box* var, cellule_propriete* liste)
//{
//    while (liste != NULL)
//    {
//        if (strcmp(liste->attribut, "style") == 0)
//        {
//            var->style = atoi(liste->valeur);
//        }
//        else if (strcmp(liste->attribut, "space") == 0)
//        {
//            var->space = atoi(liste->valeur);
//        }
//        else if (strcmp(liste->attribut, "pack") == 0)
//        {
//            var->pack = atoi(liste->valeur);
//        }
//        else if (strcmp(liste->attribut, "same_size"))
//        {
//            if (g_strcmp0(liste->valeur, "true") == 0)
//                var->same_size = TRUE;
//            else var->same_size = FALSE;
//        }
//        else if (strcmp(liste->attribut, "present"))
//        {
//            if (g_strcmp0(liste->valeur, "true") == 0)
//                var->expand = TRUE;
//            else var->expand = FALSE;
//        }
//        else if (strcmp(liste->attribut, "present"))
//        {
//            if (g_strcmp0(liste->valeur, "true") == 0)
//                var->fill = TRUE;
//            else var->fill = FALSE;
//        }
//        else if (strcmp(liste->attribut, "padding") == 0)
//        {
//            var->padding = atoi(liste->valeur);
//        }
//
//        liste = liste->suivant;
//    }
//    return var;
//}





box* add_box(box* bx, fenetre* var)
{
    // Create the vertical box and set its properties
    bx->box = gtk_box_new(bx->style, bx->space);
    gtk_container_add(GTK_CONTAINER(var->window), bx->box);

    //change spacing after creating the box
    gtk_box_set_spacing(bx->box, bx->space);
    //the same size or not
    gtk_box_set_homogeneous(bx->box, bx->same_size);
    return (box*)bx;
}


//void add_widgwt_to_box(box* bx, GtkWidget** button1)
//{
//
//
//    //gtk_box_pack_start(GTK_BOX(bx->box), *button1, TRUE, TRUE, 5);
//
//    if (bx->pack == 0)
//        //gche -> dte
//        gtk_box_pack_start(GTK_BOX(bx->box), *button1, TRUE, TRUE, 0);
//    else
//        //dte -> gche
//        gtk_box_pack_end(GTK_BOX(bx->box), *button1, TRUE, TRUE, 0);
//
//
//    //padding and expand and fil
//    if (bx->pack == 0)
//        gtk_box_set_child_packing(GTK_BOX(bx->box), *button1, bx->expand, bx->fill, bx->padding, GTK_PACK_START);
//
//    else gtk_box_set_child_packing(GTK_BOX(bx->box), *button1, bx->expand, bx->fill, bx->padding, GTK_PACK_END);
//    //move object to a position;
//    gtk_box_reorder_child(GTK_BOX(bx->box), *button1, 0);  //au debut
//}



GtkWidget* creer_scroll_bar(fenetre* var)
{
    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(var->window), scrolled_window);

    return  (GtkWidget*)scrolled_window;
}

void add_scroll_bar(GtkWidget** scrolled_window, int x)
{
    // set the scrollbar policy to always show
    if (x == 0)
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scrolled_window),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    else if (x == 1)
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scrolled_window),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    else if (x == 2)
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scrolled_window),
            GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC);
    else
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(*scrolled_window),
            GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);


}