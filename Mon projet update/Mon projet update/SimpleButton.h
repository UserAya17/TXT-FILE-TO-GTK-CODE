#pragma once
#include<stdio.h>
#include <gtk/gtk.h>

typedef struct
{
    GtkWidget* widget;
    char* label;
    char* image;
    int reliefMode;
    gboolean sensitive;
    int alignementHorizental;
    int alignementVertical;
    GtkPositionType position;
    char* couleur;
    char* name;
    char* image_background;
    taille dimension;
    char signal[60];
    int position_image;
    commune positionnement ;
}ButtonItem;


void on_button_clicked1(GtkButton* button, gpointer user_data)
{
    g_print("Button clicked\n");
}



ButtonItem* init_button()
{
    ButtonItem* Button = g_new(ButtonItem, 1);
    Button->widget = NULL;
    Button->positionnement.container = NULL;
    Button->label = "Button";
    Button->image = NULL;
    Button->reliefMode = 1;

    Button->sensitive = TRUE;
    Button->alignementHorizental = 1;
    Button->alignementVertical = 1;
    GtkPositionType position = GTK_POS_BOTTOM;
    Button->position = position;
    Button->couleur = "white";
    Button->name = "Mon_Button";
    Button->image_background = NULL;
    Button->dimension.width = 20;
    Button->dimension.height = 20;
    Button->positionnement.posx = 0;
    Button->positionnement.posy = 0;
    Button->position_image = 4;
    return Button;
}


ButtonItem* cree_Button(ButtonItem* Data)
{
    Data->widget = gtk_button_new();
    //ajouter label
    //gtk_button_set_label(GTK_BUTTON(Data->widget), Data->label);
    GtkWidget* label_widget = gtk_label_new(Data->label);
    gtk_label_set_mnemonic_widget(GTK_LABEL(label_widget), Data->widget);
    gtk_label_set_use_underline(GTK_LABEL(label_widget), TRUE);
    gtk_container_add(GTK_CONTAINER(Data->widget), label_widget);
    GtkPositionType tab[4] = { GTK_POS_LEFT,GTK_POS_RIGHT,GTK_POS_TOP,GTK_POS_BOTTOM };
    //ajouter image
    if (Data->image)
    {
        GtkWidget* picture;
        GtkIconSize size = GTK_ICON_SIZE_BUTTON;
        picture = gtk_image_new_from_file(Data->image);
        gtk_button_set_image(Data->widget, picture);
        gtk_button_set_always_show_image(GTK_BUTTON(Data->widget), TRUE);
        Data->position = tab[Data->position_image-1];
        gtk_button_set_image_position(GTK_BUTTON(Data->widget), Data->position);
    }

    //relief
    switch (Data->reliefMode)
    {
    case 1: gtk_button_set_relief(GTK_BUTTON(Data->widget), GTK_RELIEF_NORMAL); break;
    case 2: gtk_button_set_relief(GTK_BUTTON(Data->widget), GTK_RELIEF_HALF); break;
    case 3: gtk_button_set_relief(GTK_BUTTON(Data->widget), GTK_RELIEF_NONE); break;
    }

    //sensitive
    gtk_widget_set_sensitive(GTK_TOGGLE_BUTTON(Data->widget), Data->sensitive);

    //printf(" \n alignement vertical %d et  alignement horizontale: %d \n", Data->alignementVertical, Data->alignementHorizental);
    switch (Data->alignementHorizental)
    {
    case 1: gtk_widget_set_halign(Data->widget, GTK_ALIGN_CENTER); break;
    case 2: gtk_widget_set_halign(Data->widget, GTK_ALIGN_START); break;
    case 3: gtk_widget_set_halign(Data->widget, GTK_ALIGN_END); break;
    }
    switch (Data->alignementVertical)
    {
    case 1: gtk_widget_set_valign(Data->widget, GTK_ALIGN_CENTER); break;
    case 2: gtk_widget_set_valign(Data->widget, GTK_ALIGN_START); break;
    case 3: gtk_widget_set_valign(Data->widget, GTK_ALIGN_END); break;
    case 4: gtk_widget_set_valign(Data->widget, GTK_ALIGN_FILL); break;
    }

    //couleur 

    GtkStyleContext* context = gtk_widget_get_style_context(Data->widget);
    gtk_style_context_add_class(context, Data->name);

    GtkCssProvider* provider = gtk_css_provider_new();
    char* css_data = g_strdup_printf(" .%s { background: %s; }", Data->name, Data->couleur);
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);



    if (Data->image_background)
    {
        //image background
        GtkCssProvider* provider2 = gtk_css_provider_new();
        char* css_data2 = g_strdup_printf(".%s { background-image: url('%s'); }", Data->name, Data->image_background);
        gtk_css_provider_load_from_data(provider2, css_data2, -1, NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    //size   on_button_clicked
    gtk_widget_set_size_request(Data->widget, Data->dimension.width, Data->dimension.height);

    if (strcmp(Data->signal, "on_button_clicked") == 0)
    {
        g_signal_connect(Data->widget, "clicked", G_CALLBACK(on_button_clicked1), NULL);
    }
    
    //printf("\nsignale : %s\n", Data->signal); 
    return Data;
}



ButtonItem* set_propriety_ButtonItem(ButtonItem* button, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)
        {
            button->positionnement.posx = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "y") == 0)
        {
            button->positionnement.posy = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "width") == 0)
        {
            button->dimension.width = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "height") == 0)
        {
            button->dimension.height = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "label") == 0)
        {
            button->label = liste->valeur;
        }
        if (strcmp(liste->attribut, "image_background") == 0)
        {
            button->image_background = liste->valeur;
        }
        if (strcmp(liste->attribut, "name") == 0)
        {
            button->name = liste->valeur;
        }
        if (strcmp(liste->attribut, "couleur") == 0)
        {
            button->couleur = liste->valeur;
        }
        if (strcmp(liste->attribut, "alignementHorizental") == 0)
        {
            button->alignementHorizental = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "alignementVertical") == 0)
        {
            button->alignementVertical = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "reliefMode") == 0)
        {
            button->reliefMode = atoi(liste->valeur);
        }
        if (strcmp(liste->attribut, "sensitive") == 0)
        {
            if (strcmp(liste->valeur, "TRUE") == 0)
            {
                button->sensitive = TRUE;
            }
            if (strcmp(liste->valeur, "FALSE") == 0)
            {
                button->sensitive = FALSE;
            }
        }
        if (strcmp(liste->attribut, "image") == 0)
        {
            button->image = liste->valeur;
        }
        if (strcmp(liste->attribut, "signal") == 0)
        {
            strcpy(button->signal, liste->valeur);
        }
        if (strcmp(liste->attribut, "position_image") == 0)
        {
            button->position_image = atoi(liste->valeur);
        }
        liste = liste->suivant;
    }
    return button;
}