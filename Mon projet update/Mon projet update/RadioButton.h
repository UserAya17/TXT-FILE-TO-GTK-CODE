#pragma once
#include<stdio.h>
#include <gtk/gtk.h>
#include "en_commun.h"


#pragma once
typedef struct {
    GtkWidget* widget;
    GtkWidget* ButtonPere;
    char* label;
    gboolean active;
    gboolean sensitive;
    commune positionnement;
} ToogleButton;

ToogleButton* init_radio_button()
{
    ToogleButton* radio_button = g_new(ToogleButton, 1);
    radio_button->widget = NULL;
    radio_button->ButtonPere = NULL;
    radio_button->label = "Button Radio";
    radio_button->positionnement.container = NULL;
    radio_button->active = FALSE;
    radio_button->sensitive = TRUE;
    radio_button->positionnement.posx = 0;
    radio_button->positionnement.posy = 0;

    return radio_button;
}

ToogleButton* cree_radio_button(ToogleButton* radio_button)
{

    if (radio_button->ButtonPere)
    {

        //GtkWidget* label_1 = gtk_label_new_with_mnemonic(radio_button->label);
        radio_button->widget = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radio_button->ButtonPere));
        //radio_button->widget = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button->ButtonPere), label_1);
    }
    else
    {
        //GtkWidget* label_1 = gtk_label_new_with_mnemonic(radio_button->label);
        radio_button->widget = gtk_radio_button_new(NULL);
        //radio_button->widget =  gtk_radio_button_new_with_label(NULL,label_1);
    }
    //char* label_widget = gtk_button_get_label(GTK_RADIO_BUTTON(radio_button->widget));


    //GtkWidget* label_1 = gtk_label_new_with_mnemonic(radio_button->label);
    gtk_button_set_label(GTK_BUTTON(radio_button->widget), radio_button->label);
    /*gtk_label_set_mnemonic_widget(GTK_LABEL(label_1), radio_button->widget);
    gtk_label_set_use_underline(GTK_LABEL(label_1), TRUE);*/

    /*GtkWidget* label_widget = gtk_label_new_with_mnemonic(radio_button->label);
    gtk_button_set_label(GTK_BUTTON(radio_button->widget), label_widget);*/
    /*gtk_button_set_label(GTK_BUTTON(radio_button->widget), radio_button->label);
    gtk_label_set_mnemonic_widget(gtk_button_get_label(GTK_RADIO_BUTTON(radio_button->widget)), radio_button->widget);
    gtk_label_set_use_underline(gtk_button_get_label(GTK_RADIO_BUTTON(radio_button->widget)), TRUE);*/
    //gtk_container_add(GTK_CONTAINER(radio_button->widget), label_widget);



    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button->widget), radio_button->active);
    gtk_widget_set_sensitive(GTK_TOGGLE_BUTTON(radio_button->widget), radio_button->sensitive);

    return radio_button;
}

ToogleButton* set_propriety_RadioButtonItem(ToogleButton* buttonRadio, cellule_propriete* liste, int* type)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
        {
            buttonRadio->positionnement.posx = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "y") == 0)
        {
            buttonRadio->positionnement.posy = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "label") == 0)
        {
            buttonRadio->label = liste->valeur;
        }
        if (strcmp(liste->attribut, "active") == 0)
        {
            if (strcmp(liste->valeur, "TRUE") == 0)
            {
                buttonRadio->active = TRUE;
            }
            if (strcmp(liste->valeur, "FALSE") == 0)
            {
                buttonRadio->active = FALSE;
            }
        }
        if (strcmp(liste->attribut, "sensitive") == 0)
        {
            if (strcmp(liste->valeur, "TRUE") == 0)
            {
                buttonRadio->sensitive = TRUE;
            }
            if (strcmp(liste->valeur, "FALSE") == 0)
            {
                buttonRadio->sensitive = FALSE;
            }
        }

        if (strcmp(liste->attribut, "group") == 0)
        {
            if (strcmp(liste->valeur, "Pere") == 0)
            {
                printf("\n un button pere \n ");
                *type = 1;
            }
            if (strcmp(liste->valeur, "item") == 0)
            {
                printf("\n un button item \n ");
                *type = 0;
            }
        }
        liste = liste->suivant;
    }
    return buttonRadio;
}


void show_checked_buttons2(GList* group)
{
    for (GSList* button = group; button != NULL; button = g_slist_next(button))
    {
        ToogleButton* button_R = (ToogleButton*)button->data;
        // Vérifier si le bouton est sélectionné
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button_R->widget))) {

            printf("%s\n", button_R->label);
            break;
        }
    }
}


//void on_button_clicked2(GSList* button_groups) {
//    GSList* group;
//    for (group = button_groups; group != NULL; group = group->next) {
//
//        GtkWidget* button = gtk_radio_button_get_group(group->data);
//        while (button != NULL) {
//           /* if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {
//                printf("Button with label '%s' selected in group '%p'\n", gtk_button_get_label(GTK_BUTTON(button)), group->data);
//            }*/
//            printf("Button with label '%s' selected in group '%p'\n", gtk_button_get_label(GTK_BUTTON(button)), group->data);
//            button = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
//
//        }
//
//       // printf("Button with label '%s' \n", gtk_button_get_label(GTK_BUTTON(button)));
//    }
//}

int show(GList* MaListe)
{
    GtkWidget* bouton_radio;
    GtkWidget* bouton_radio2;
    while (MaListe != NULL)
    {
        bouton_radio = GTK_RADIO_BUTTON(MaListe->data);
        GList* group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(bouton_radio));
        //printf("Le bouton radio '%s' est sélectionné\n", gtk_button_get_label(GTK_RADIO_BUTTON(bouton_radio)));

        //printf("Le bouton radio Group '%s' est sélectionné\n", gtk_button_get_label(GTK_RADIO_BUTTON(bouton_radio)));

        while (group != NULL) {
            bouton_radio2 = GTK_RADIO_BUTTON(group->data);
            //printf("Le bouton radio '%s' est sélectionné\n", gtk_button_get_label(GTK_BUTTON(bouton_radio2)));
            if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(bouton_radio2))) {
                printf("Le bouton radio '%s' est sélectionné\n", gtk_button_get_label(GTK_TOGGLE_BUTTON(bouton_radio2)));
            }
            group = group->next;
        }

        /*if (g_list_length(group) == 0) {
            printf("La liste est vide\n");

        }
        else {
            printf("La liste n'est pas vide\n");
            printf(" taille : %d \n ", g_list_length(group));
        }*/

        MaListe = MaListe->next;
    }


}

void on_button_clicked2(GtkButton* button, gpointer user_data)
{
    // Appeler la fonction show_checked_buttons()
    GList* button_list = (GList*)user_data;
    int valeur = show(button_list);
}